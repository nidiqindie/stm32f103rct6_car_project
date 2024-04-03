#include "servo.h" 
#include <math.h>
#include <stdio.h>
#include "bsp_delay.h"
#include "bsp_led.h"
/*****************************SERVO**********************/
static void SERVO_TIM_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

  // 输出比较通道1 GPIO 初始化
  RCC_APB2PeriphClockCmd(SERVO_TIM_CH1_GPIO_CLK, ENABLE);	
  GPIO_InitStructure.GPIO_Pin =  SERVO_TIM_CH1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(SERVO_TIM_CH1_PORT, &GPIO_InitStructure);
	
	// 输出比较通道2 GPIO 初始化
  RCC_APB2PeriphClockCmd(SERVO_TIM_CH2_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  SERVO_TIM_CH2_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(SERVO_TIM_CH2_PORT, &GPIO_InitStructure);

	// 输出比较通道3 GPIO 初始化
  RCC_APB2PeriphClockCmd(SERVO_TIM_CH3_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  SERVO_TIM_CH3_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(SERVO_TIM_CH3_PORT, &GPIO_InitStructure);

	// 输出比较通道4 GPIO 初始化
  RCC_APB2PeriphClockCmd(SERVO_TIM_CH4_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  SERVO_TIM_CH4_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(SERVO_TIM_CH4_PORT, &GPIO_InitStructure);
}

/* ----------------   PWM信号 周期和占空比的计算--------------- */
// ARR ：自动重装载寄存器的值
// CLK_cnt：计数器的时钟，等于 Fck_int / (psc+1) = 72M/(psc+1)
// PWM 信号的周期 T = (ARR+1) * (1/CLK_cnt) = (ARR+1)*(PSC+1) / 72M
// 占空比P=CCR/(ARR+1)

static void SERVO_TIM_Mode_Config(void)
{
  // 开启定时器时钟,即内部时钟CK_INT=72M
	SERVO_TIM_APBxClock_FUN(SERVO_TIM_CLK,ENABLE);

/*--------------------时基结构体初始化-------------------------*/
	// 配置周期，这里配置为50Hz

    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
	TIM_TimeBaseStructure.TIM_Period=SERVO_TIM_Period-1;	
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= SERVO_TIM_Prescaler-1;	
	// 时钟分频因子 ，配置死区时间时需要用到
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// 计数器计数模式，设置为向上计数
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// 重复计数器的值，没用到不用管
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// 初始化定时器
	TIM_TimeBaseInit(SERVO_TIM, &TIM_TimeBaseStructure);

	TIM_OCInitTypeDef  TIM_OCInitStructure;
	// 配置为PWM模式1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	

	TIM_OC1Init(SERVO_TIM, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(SERVO_TIM, TIM_OCPreload_Enable);

	TIM_OC2Init(SERVO_TIM, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(SERVO_TIM, TIM_OCPreload_Enable);

	TIM_OC3Init(SERVO_TIM, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(SERVO_TIM, TIM_OCPreload_Enable);

	TIM_OC4Init(SERVO_TIM, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(SERVO_TIM, TIM_OCPreload_Enable);

	// 使能计数器
	TIM_Cmd(SERVO_TIM, ENABLE);
	//主输出使能，当使用通用定时器时，此句不需要
	TIM_CtrlPWMOutputs(SERVO_TIM,ENABLE);
}


/**
  * @brief  PWM初始化，输出4个PWM，周期均为20ms.
  * @param  CCRx_Val: 第几个PWM的脉宽，周期宽度为2000，配置该参数可以调节占空比. 
  *   This parameter can be one of the following values:
  *   0：      不开启PWMx，同时不占用IO口
  *   1-2000
  * @retval None
  */
void SERVO_TIM_Init(void)
{
	SERVO_TIM_GPIO_Config();
	SERVO_TIM_Mode_Config();		
}
/*********************************END OF SERVO**********************/

/**
  * @brief  角度设置.
  * @param  channel_n: 第几个舵机. 
  * @param  CCR_Val: 要设置的角度值.  
  *   
  *   
  * @retval None
  */
void Servo_Angle_Config(uint8_t channel_n , int16_t angle)
{
	uint16_t compare;
	//角度转换为PWM
	switch (channel_n)
	{
	case 1:
	// compare = 20 + angle;
	compare = angle;
	TIM_SetCompare1(SERVO_TIM, compare);
	break;
	case 2:
	// compare = 155 - angle;
	compare = angle;
	TIM_SetCompare2(SERVO_TIM, compare);
	break;
	case 3:
	// compare = 50 + angle;
	compare = angle;
	TIM_SetCompare3(SERVO_TIM, compare);
	break;
	case 4:
	compare = angle;
	TIM_SetCompare4(SERVO_TIM, compare);
	break;
	default:
	break;
	}		
}

//根据车身直角坐标系X,Y,Z计算三个舵机需要的角度,并使舵机动作,单位cm
void Compute_Angle_and_Response(int8_t CAR_X, int8_t CAR_Y, int8_t CAR_Z)
{
	float H = 5.1; //底座高度
    float A1 = 8;   //大臂长度
    float A2 = 8.3;  //小臂长度
    float delat_L = 7.5;  //爪子中心距小臂末端距离

//机械臂坐标
    float ARM_X = 0;
    float ARM_Y = 0;     
    float ARM_Z = 0; 

    float j1 = 0; //底座旋转角度
    float j2 = 0; //大臂旋转角度
    float j3 = 0; //小臂旋转角度、

//计算过程中，为简化运算定义的中间变量
    float z1 = 0;
    float z2 = 0;
    float z3 = 0;
    float z4 = 0;
    float z5 = 0;

if((CAR_X*CAR_X + CAR_Y*CAR_Y)<400) 
    {
    //车身坐标系转换为机械臂坐标系
        ARM_X = CAR_X;
        ARM_Y = CAR_Y+3;
        ARM_Z = CAR_Z+1.5;

        if(ARM_X == 0){
            j1 = 90;
        }
        else{
            j1 = atan(ARM_Y/ARM_X) * 57.29578;        
        }
        if(j1 < 0) {j1 = j1 + 180;}

        z1 = sqrtf(ARM_X*ARM_X+ARM_Y*ARM_Y) - delat_L; 
        z2 = ARM_Z-H;
        z3 = A1*A1+A2*A2;
        z4 = 2*A1*A2;
        z5 = asin((z1*z1+z2*z2-z3)/(z4));

        j3 = asin((z1*A1*cos(z5) - z2*(A1*sin(z5)+A2))/(z3+z4*sin(z5))) * 57.29578;
        j2 = z5 * 57.29578 + j3;

        if((j1 > 45) && (j1 < 210)){
			Servo_Angle_Config(1 , (int16_t)j1);
			Delay_ms(200);
            }
		else  printf("舵机1角度超出安全限制范围(45°--210°),%f\r\n",j1); 

        if((j2 > -10) && (j2 < 90)){
 			Servo_Angle_Config(2 , (int16_t)j2); 
			Delay_ms(200);        
            }
		else  printf("舵机2角度超出安全限制范围(-10°--90°),%f\r\n",j2); 
		
        if((j3 > 0) && (j3 < 90)){
		 	Servo_Angle_Config(3 , (int16_t)j3); 
			Delay_ms(200);
            }
		else printf("舵机3角度超出安全限制范围(0°--90°),%f\r\n",j3); 
    }    
    else    printf("超出爪子抓取量程\r\n");
}


/*********************************************END OF FILE**********************/
