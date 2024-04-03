#ifndef __APP_H
#define __APP_H 	


/*************按键检测标志值****************/
//key1_val  key2_val  key3_val key4_val
//按键采用外部中断的方式判断，若有按键按下，对应标志值在中断中被置1
//调用标志值后，要把标志值置0，以便下次判断
/*******************END**********************/

/*************测量PWM脉宽的返回值****************/
//pulse_value1	 pulse_value2	pulse_value3	pulse_value4
//分别对应四个通道的返回值，最大不超过5000，单位是us
/*******************END**********************/
 
/**********************PWM*************************/
//两组PWM，一组有四个通道
//PWM1_TIM_Init(0 , 0 , 0 ,0);
//PWM2_TIM_Init(0 , 0 , 0 ,0);
//4个通道的PWM，周期均为20ms，不使用的通道对应参数置0，这样就不会占用IO口z
/*******************END**********************/

/**********************PPM*************************/
//Channel_x[1]  Channel_x[2] ...... Channel_x[8]
//最多8个通道输出，输出值0-2000，单位us
/*******************END**********************/

/**********************RANGER*************************/
//distance1  distance2  distance3  distance4
//注意初始化RANGER_TRIG_GPIO_Init();之前要先初始化PWMCAPTURE_PULSEWIDTH_TIM_Init(); 单位cm
/*******************END**********************/

/* 嵌套向量中断控制器组选择分组2*/
/* 
	抢占优先级0-3，子优先级0-3
	优先级分配：
			UART1：1-1、UART2: 1-2、UART: 1-3;
			按键中断：3-0,3-1,3-2
			PWMCAPTURE_PULSEWIDTH: 0-0
			PPM : 2-0 
*/
extern int main_target;
extern int flag_weitiao;

void  app_task0(void);
void car_init(void);

#endif

