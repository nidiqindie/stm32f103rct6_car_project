#include "servo.h" 
#include <math.h>
#include <stdio.h>
#include "bsp_delay.h"
#include "bsp_led.h"
/*****************************SERVO**********************/
static void SERVO_TIM_GPIO_Config(void) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

  // ����Ƚ�ͨ��1 GPIO ��ʼ��
  RCC_APB2PeriphClockCmd(SERVO_TIM_CH1_GPIO_CLK, ENABLE);	
  GPIO_InitStructure.GPIO_Pin =  SERVO_TIM_CH1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(SERVO_TIM_CH1_PORT, &GPIO_InitStructure);
	
	// ����Ƚ�ͨ��2 GPIO ��ʼ��
  RCC_APB2PeriphClockCmd(SERVO_TIM_CH2_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  SERVO_TIM_CH2_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(SERVO_TIM_CH2_PORT, &GPIO_InitStructure);

	// ����Ƚ�ͨ��3 GPIO ��ʼ��
  RCC_APB2PeriphClockCmd(SERVO_TIM_CH3_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  SERVO_TIM_CH3_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(SERVO_TIM_CH3_PORT, &GPIO_InitStructure);

	// ����Ƚ�ͨ��4 GPIO ��ʼ��
  RCC_APB2PeriphClockCmd(SERVO_TIM_CH4_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  SERVO_TIM_CH4_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(SERVO_TIM_CH4_PORT, &GPIO_InitStructure);
}

/* ----------------   PWM�ź� ���ں�ռ�ձȵļ���--------------- */
// ARR ���Զ���װ�ؼĴ�����ֵ
// CLK_cnt����������ʱ�ӣ����� Fck_int / (psc+1) = 72M/(psc+1)
// PWM �źŵ����� T = (ARR+1) * (1/CLK_cnt) = (ARR+1)*(PSC+1) / 72M
// ռ�ձ�P=CCR/(ARR+1)

static void SERVO_TIM_Mode_Config(void)
{
  // ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M
	SERVO_TIM_APBxClock_FUN(SERVO_TIM_CLK,ENABLE);

/*--------------------ʱ���ṹ���ʼ��-------------------------*/
	// �������ڣ���������Ϊ50Hz

    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
	TIM_TimeBaseStructure.TIM_Period=SERVO_TIM_Period-1;	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= SERVO_TIM_Prescaler-1;	
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// ����������ģʽ������Ϊ���ϼ���
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// �ظ���������ֵ��û�õ����ù�
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��
	TIM_TimeBaseInit(SERVO_TIM, &TIM_TimeBaseStructure);

	TIM_OCInitTypeDef  TIM_OCInitStructure;
	// ����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	

	TIM_OC1Init(SERVO_TIM, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(SERVO_TIM, TIM_OCPreload_Enable);

	TIM_OC2Init(SERVO_TIM, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(SERVO_TIM, TIM_OCPreload_Enable);

	TIM_OC3Init(SERVO_TIM, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(SERVO_TIM, TIM_OCPreload_Enable);

	TIM_OC4Init(SERVO_TIM, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(SERVO_TIM, TIM_OCPreload_Enable);

	// ʹ�ܼ�����
	TIM_Cmd(SERVO_TIM, ENABLE);
	//�����ʹ�ܣ���ʹ��ͨ�ö�ʱ��ʱ���˾䲻��Ҫ
	TIM_CtrlPWMOutputs(SERVO_TIM,ENABLE);
}


/**
  * @brief  PWM��ʼ�������4��PWM�����ھ�Ϊ20ms.
  * @param  CCRx_Val: �ڼ���PWM���������ڿ��Ϊ2000�����øò������Ե���ռ�ձ�. 
  *   This parameter can be one of the following values:
  *   0��      ������PWMx��ͬʱ��ռ��IO��
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
  * @brief  �Ƕ�����.
  * @param  channel_n: �ڼ������. 
  * @param  CCR_Val: Ҫ���õĽǶ�ֵ.  
  *   
  *   
  * @retval None
  */
void Servo_Angle_Config(uint8_t channel_n , int16_t angle)
{
	uint16_t compare;
	//�Ƕ�ת��ΪPWM
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

//���ݳ���ֱ������ϵX,Y,Z�������������Ҫ�ĽǶ�,��ʹ�������,��λcm
void Compute_Angle_and_Response(int8_t CAR_X, int8_t CAR_Y, int8_t CAR_Z)
{
	float H = 5.1; //�����߶�
    float A1 = 8;   //��۳���
    float A2 = 8.3;  //С�۳���
    float delat_L = 7.5;  //צ�����ľ�С��ĩ�˾���

//��е������
    float ARM_X = 0;
    float ARM_Y = 0;     
    float ARM_Z = 0; 

    float j1 = 0; //������ת�Ƕ�
    float j2 = 0; //�����ת�Ƕ�
    float j3 = 0; //С����ת�Ƕȡ�

//��������У�Ϊ�����㶨����м����
    float z1 = 0;
    float z2 = 0;
    float z3 = 0;
    float z4 = 0;
    float z5 = 0;

if((CAR_X*CAR_X + CAR_Y*CAR_Y)<400) 
    {
    //��������ϵת��Ϊ��е������ϵ
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
		else  printf("���1�Ƕȳ�����ȫ���Ʒ�Χ(45��--210��),%f\r\n",j1); 

        if((j2 > -10) && (j2 < 90)){
 			Servo_Angle_Config(2 , (int16_t)j2); 
			Delay_ms(200);        
            }
		else  printf("���2�Ƕȳ�����ȫ���Ʒ�Χ(-10��--90��),%f\r\n",j2); 
		
        if((j3 > 0) && (j3 < 90)){
		 	Servo_Angle_Config(3 , (int16_t)j3); 
			Delay_ms(200);
            }
		else printf("���3�Ƕȳ�����ȫ���Ʒ�Χ(0��--90��),%f\r\n",j3); 
    }    
    else    printf("����צ��ץȡ����\r\n");
}


/*********************************************END OF FILE**********************/
