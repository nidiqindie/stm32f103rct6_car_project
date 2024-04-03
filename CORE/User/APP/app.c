#include "app.h"
#include "stm32f10x.h"
#include "bsp_GpioRemap.h"
#include "bsp_delay.h"
#include "bsp_led.h"
#include "bsp_beep.h" 
#include "bsp_key.h"  
#include "bsp_usart.h"
#include "Motor.h"
#include "servo.h" 
#include "Encoder.h"
#include "PID.h"
//#include "mpu6050.h"
//#include "mpuiic.h"
//#include "exti.h"
#include "OLED.h"
#include "communication_protocol.h"
#define GB 50 
int main_target=0;//while(1)中任务逻辑位初始给1就会进入任务；
extern float curSp_L1;
int flag_weitiao=0;
void gui0(void)
{
	A_j=0;
	B_j=0;
	C_j=0;
	D_j=0;
}


static void System_Init(void)
{
/***********setting_NVIC***********/	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

/***********GpioRemap***********/	
	GpioRemap_init();
/***********Delay_init***********/
	Delay_init();
/***********LED***********/
  	LED_GPIO_Config();
/***********BEEP***********/
   BEEP_GPIO_Config();
///***********KEY***********/
	Key_GPIO_Config();
   Delay_ms(100);   

///***********Motor_init***********/
//	Motor_init();
//	Delay_ms(100);
//    LED_RED;

// /***********USART1***********/
// 	USART1_Config();
//     Delay_ms(100);
// 	ADCx_Init();
//     LED_BLUE;
//////// /***********USART2***********/
//  	USART2_Config();
//     Delay_ms(100);
//     LED_RED;
// /***********USART3***********/
	UART5_Config();
	Delay_ms(100);
    LED_BLUE;
///***********SERVO_init***********/
	SERVO_TIM_Init(); //????��???
	Delay_ms(100);
   LED_RED;
/////***********PWM2_init***********/  
//	PWM2_TIM_Init(1000 , 1000 , 1000 ,1000);
//	Delay_ms(100);
//    LED_BLUE;
}
void car_init(void)
{
//电机驱动初始化
Motor_Init();
Encoder_Init_TIM2();
Encoder_Init_TIM3();
Encoder_Init_TIM4();
Encoder_Init_TIM5();
PID_timebase_init();

//串口初始化
    UART4_Config();
	UART5_Config();
	OLED_Init();
	//mpu6050初始化
	// MPU_Init();
	// mpu_dmp_init();
	// MPU6050_EXTI_Init();
// MPU6050_Init();
}

void app_task0(void)
{
	// u8 f[6];
   
// int16_t a,b,c,d,f,e;
// uint8_t j;
	System_Init();
	Delay_ms(100);
	USART2_Config();
	UART4_Config();
    UART5_Config();
	// LED_WHITE;
	// C_NORMAL;
		// Set_speed(500, 500, 500, 500);
// LED_BLUE;
	USART_ITConfig(DEBUG_USART1, USART_IT_RXNE, ENABLE);
	USART_ITConfig(DEBUG_USART2, USART_IT_RXNE, ENABLE);	
	USART_ITConfig(DEBUG_USART3, USART_IT_RXNE, ENABLE);	
	USART_ITConfig(DEBUG_UART4, USART_IT_RXNE, ENABLE);
	// mpu_dmp_init();
	// MPU6050_EXTI_Init();
	Delay_ms(5000);
	Delay_ms(5000);
	Delay_ms(5000);
	    car_init();

	// target_a();
	// L_Translation(50);

		// A_NORMAL;
		// Set_speed(500,0,0,0);
		// PID_timebase_init();//
	//move_forward(26);//
	LED_WHITE;
	main_target=0;

	// i=MPU6050ReadID();
	// printf("%c",j);
		Stop() ;
		gui0();
						// L_Translation(50);


	while (1)
	{
		runPID();
		OLED_ShowSignedNum(1,1,A_j,7);
		OLED_ShowSignedNum(2,1,B_j,7);
		OLED_ShowSignedNum(3,1,C_j,7);
		OLED_ShowSignedNum(4,1,D_j,7);
		//第一圈第一边
		if(main_target==1)
		{
			flag_weitiao=1;
			L_Translation(GB);
			if(A_j<=-500)
		    {
				Stop();
			gui0();
			main_target=0;

			Delay_ms(1500);

			}
		}

		if(main_target==2)
		{
			Forward(GB);
			if(A_j>=2953||B_j>=2970||C_j>=3018||D_j>=2980)
			{
			Stop();

			gui0();
						main_target=0;

			Delay_ms(1500);
		

			}
		}
		
		if(main_target==3)
		{
			Forward(GB);
			if(A_j>=4239|| B_j>=4231||C_j>=4247||D_j>=4225)
			{
								Stop();

			gui0();
			Delay_ms(1500);
			main_target=0;

			}
		}

		if(main_target==4)
		{
			Forward(GB);
			if (A_j>=2492)
			{
								Stop();

			gui0();
			Delay_ms(1500);
						main_target=0;

			}
		}
//第一圈第二边
		if(main_target==5)
		{
			flag_weitiao=2;
			L_Translation(GB);
			if(A_j<=-3406)
			{
								Stop();

				gui0();
				Delay_ms(1500);
							main_target=0;

			}
		}

		if (main_target==6)
		{
			L_Translation(GB);
			if (A_j<=-871)
			{
								Stop();

				gui0();

				Delay_ms(1500);
							main_target=0;

			}
		}

		if (main_target==7)
		{
			L_Translation(GB);
			if (A_j<=-809)
			{
								Stop();

				gui0();

				Delay_ms(1500);
							main_target=0;

			}
		}
		
		if (main_target==8)
		{
			L_Translation(GB);
			if (A_j<=-2738)
			{
								Stop();

				gui0();

				Delay_ms(1500);
							main_target=0;

			}
		}

		if (main_target==9)
		{
			L_Translation(GB);
			if(A_j<=-350)
			{
				Stop();

				gui0();

				Delay_ms(1500);
							main_target=0;

			}

		}


//第一圈第三边
		if(main_target==10)
		{
			flag_weitiao=3;
			Backward(GB);
			if(A_j<=-3809)
			{
				Stop();


				Delay_ms(1500);
							main_target=0;

			}
		}
		
		
		if (main_target==11)
		{
			Backward(GB);
			if (A_j<=-4464)
			{
								Stop();


				Delay_ms(1500);
							main_target=0;

			}
		}

		if(main_target==12)
		{
			Backward(GB);
			if (A_j<=-5352)
			{
								Stop();


				Delay_ms(1500);
							main_target=0;


			}
		}
		
		if (main_target==13)
		{
			Backward(GB);
			if (A_j<=-9105)
			{
								Stop();

				gui0();

				Delay_ms(1500);
							main_target=0;

			}
		}
//第一圈第四边
		if (main_target==14)
		{
			
			R_Translation(GB);
			if (A_j>=8261)
			{
								Stop();

				gui0();

				Delay_ms(1500);
							main_target=0;

			}
		}

		// if (main_target==15)
		// {
		// 	R_Translation(GB);
		// 	if (A_j>=8574)
		// 	{
		// 						Stop();

		// 		gui0();
		// 		main_target=16;
		// 		Delay_ms(1000);
		// 	}	
		// }
		

	}
		
}

// // 	}	
// // }
// // //????????????
// // // void  app_task0(void)
// // // {
// // // 	System_Init();
// // // 	Delay_ms(100);
// // // 	Servo_Angle_Config(1 , 120);
// // // 	Servo_Angle_Config(2 , 140);
// // // 	Servo_Angle_Config(3 , 160);
// // // 	Servo_Angle_Config(4 , 180);
// // // 	while(1) 
// // // 	{
// // //    LED_RED;
// // // 		Delay_ms(1000);
// // //    LED_RGBOFF;
// // // 		Delay_ms(1000);
// // //		if(key1_val == 1)
// // //		{
// // //		Compute_Angle_and_Response(10, 13, 6);
// // //			key1_val = 0;
// // //		}
// // //		if(key2_val == 1)
// // //		{
// // //		Compute_Angle_and_Response(10, 14, 6);
// // //		 key2_val = 0;
// // //		}		
// // // 	}
// // // }
// }
