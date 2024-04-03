#ifndef __BSP_PWM_H
#define __BSP_PWM_H


#include "stm32f10x.h"


/************ͨ�ö�ʱ��TIM�������壬ֻ��TIM2��3��4��5************/
// ��ʹ�ò�ͬ�Ķ�ʱ����ʱ�򣬶�Ӧ��GPIO�ǲ�һ���ģ����Ҫע��
// ��������ʹ��TIM3������ĸ�ͨ����PWM
//SERVO_1->PA6��SERVO_2->PA7��SERVO_3->PB0��SERVO_4->PB1

/**************************PWM********************************/
#define            SERVO_TIM                   TIM3
#define            SERVO_TIM_APBxClock_FUN     RCC_APB1PeriphClockCmd
#define            SERVO_TIM_CLK               RCC_APB1Periph_TIM3
#define            SERVO_TIM_Period            2000
#define            SERVO_TIM_Prescaler         720
// TIM3 ����Ƚ�ͨ��1
#define            SERVO_TIM_CH1_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            SERVO_TIM_CH1_PORT          GPIOA
#define            SERVO_TIM_CH1_PIN           GPIO_Pin_6

// TIM3 ����Ƚ�ͨ��2
#define            SERVO_TIM_CH2_GPIO_CLK      RCC_APB2Periph_GPIOA
#define            SERVO_TIM_CH2_PORT          GPIOA
#define            SERVO_TIM_CH2_PIN           GPIO_Pin_7

// TIM3 ����Ƚ�ͨ��3
#define            SERVO_TIM_CH3_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            SERVO_TIM_CH3_PORT          GPIOB
#define            SERVO_TIM_CH3_PIN           GPIO_Pin_0

// TIM3 ����Ƚ�ͨ��4
#define            SERVO_TIM_CH4_GPIO_CLK      RCC_APB2Periph_GPIOB
#define            SERVO_TIM_CH4_PORT          GPIOB
#define            SERVO_TIM_CH4_PIN           GPIO_Pin_1

/**************************��������********************************/
void SERVO_TIM_Init(uint16_t CCR1_Val , uint16_t CCR2_Val , uint16_t CCR3_Val , uint16_t CCR4_Val);
void Servo_Angle_Config(uint8_t channel_n , uint16_t CCR_Val);

#endif	/* __SERVO_H */
