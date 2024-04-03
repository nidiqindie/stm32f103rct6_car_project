#include "bsp_pwm.h" 

/*****************************PWM1**********************/
static void PWM1_TIM_GPIO_Config(uint16_t CCR1_Val , uint16_t CCR2_Val , uint16_t CCR3_Val , uint16_t CCR4_Val) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

  // ����Ƚ�ͨ��1 GPIO ��ʼ��
  if(CCR1_Val>0)
  {
  RCC_APB2PeriphClockCmd(PWM1_TIM_CH1_GPIO_CLK, ENABLE);	
  GPIO_InitStructure.GPIO_Pin =  PWM1_TIM_CH1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(PWM1_TIM_CH1_PORT, &GPIO_InitStructure);
  }
	
	// ����Ƚ�ͨ��2 GPIO ��ʼ��
  if(CCR2_Val>0)
  {
  RCC_APB2PeriphClockCmd(PWM1_TIM_CH2_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  PWM1_TIM_CH2_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(PWM1_TIM_CH2_PORT, &GPIO_InitStructure);
  }

	// ����Ƚ�ͨ��3 GPIO ��ʼ��
	if(CCR3_Val>0)
	{
  RCC_APB2PeriphClockCmd(PWM1_TIM_CH3_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  PWM1_TIM_CH3_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(PWM1_TIM_CH3_PORT, &GPIO_InitStructure);
	}

	// ����Ƚ�ͨ��4 GPIO ��ʼ��
	if(CCR4_Val>0)
	{
  RCC_APB2PeriphClockCmd(PWM1_TIM_CH4_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  PWM1_TIM_CH4_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(PWM1_TIM_CH4_PORT, &GPIO_InitStructure);
	}
}


///*
// * ע�⣺TIM_TimeBaseInitTypeDef�ṹ��������5����Ա��TIM6��TIM7�ļĴ�������ֻ��
// * TIM_Prescaler��TIM_Period������ʹ��TIM6��TIM7��ʱ��ֻ���ʼ����������Ա���ɣ�
// * ����������Ա��ͨ�ö�ʱ���͸߼���ʱ������.
// *-----------------------------------------------------------------------------
// *typedef struct
// *{ TIM_Prescaler            ����
// *	TIM_CounterMode			     TIMx,x[6,7]û�У���������
// *  TIM_Period               ����
// *  TIM_ClockDivision        TIMx,x[6,7]û�У���������
// *  TIM_RepetitionCounter    TIMx,x[1,8,15,16,17]����
// *}TIM_TimeBaseInitTypeDef; 
// *-----------------------------------------------------------------------------
// */

/* ----------------   PWM�ź� ���ں�ռ�ձȵļ���--------------- */
// ARR ���Զ���װ�ؼĴ�����ֵ
// CLK_cnt����������ʱ�ӣ����� Fck_int / (psc+1) = 72M/(psc+1)
// PWM �źŵ����� T = (ARR+1) * (1/CLK_cnt) = (ARR+1)*(PSC+1) / 72M
// ռ�ձ�P=CCR/(ARR+1)

static void PWM1_TIM_Mode_Config(uint16_t CCR1_Val , uint16_t CCR2_Val , uint16_t CCR3_Val , uint16_t CCR4_Val)
{
  // ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M
	PWM1_TIM_APBxClock_FUN(PWM1_TIM_CLK,ENABLE);

/*--------------------ʱ���ṹ���ʼ��-------------------------*/
	// �������ڣ���������Ϊ50Hz
	
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
	TIM_TimeBaseStructure.TIM_Period=PWM1_TIM_Period-1;	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= PWM1_TIM_Prescaler-1;	
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// ����������ģʽ������Ϊ���ϼ���
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// �ظ���������ֵ��û�õ����ù�
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��
	TIM_TimeBaseInit(PWM1_TIM, &TIM_TimeBaseStructure);

	TIM_OCInitTypeDef  TIM_OCInitStructure;
	// ����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	// ���ʹ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	// ����Ƚ�ͨ�� 1
	if(CCR1_Val>0)
	{
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
	TIM_OC1Init(PWM1_TIM, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(PWM1_TIM, TIM_OCPreload_Enable);
	}

	// ����Ƚ�ͨ�� 2
	if(CCR2_Val>0)
	{
	TIM_OCInitStructure.TIM_Pulse = CCR2_Val;
	TIM_OC2Init(PWM1_TIM, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(PWM1_TIM, TIM_OCPreload_Enable);
	}	

	// ����Ƚ�ͨ�� 3
	if(CCR3_Val>0)
	{
	TIM_OCInitStructure.TIM_Pulse = CCR3_Val;
	TIM_OC3Init(PWM1_TIM, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(PWM1_TIM, TIM_OCPreload_Enable);
	}

	// ����Ƚ�ͨ�� 4
	if(CCR4_Val>0)
	{
	TIM_OCInitStructure.TIM_Pulse = CCR4_Val;
	TIM_OC4Init(PWM1_TIM, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(PWM1_TIM, TIM_OCPreload_Enable);
	}

	// ʹ�ܼ�����
	TIM_Cmd(PWM1_TIM, ENABLE);
}


/**
  * @brief  PWM��ʼ�������4��PWM�����ھ�Ϊ20ms.
  * @param  CCRx_Val: �ڼ���PWM���������ڿ��Ϊ2000�����øò������Ե���ռ�ձ�. 
  *   This parameter can be one of the following values:
  *   0��      ������PWMx��ͬʱ��ռ��IO��
  *   1-2000
  * @retval None
  */
void SERVO_TIM_Init(uint16_t CCR1_Val , uint16_t CCR2_Val , uint16_t CCR3_Val , uint16_t CCR4_Val)
{
	SERVO_TIM_GPIO_Config(CCR1_Val , CCR2_Val , CCR3_Val , CCR4_Val);
	SERVO_TIM_Mode_Config(CCR1_Val , CCR2_Val , CCR3_Val , CCR4_Val);		
}
/*********************************END OF PWM1**********************/

/**
  * @brief  PWM�ı�����.
  * @param  CCRx_Val: �ڼ���PWM���������ڿ��Ϊ2000�����øò������Ե���ռ�ձ�. 
  *   This parameter can be one of the following values:
  *   0��      ������PWMx��ͬʱ��ռ��IO��
  *   1-2000
  * @retval None
  */
void Servo_Angle_Config(uint8_t channel_n , uint16_t CCR_Val)
{
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	// ����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

	TIM_OCInitStructure.TIM_Pulse = CCR_Val;
		
	switch (channel_n)
	{
	case 1:
	TIM_OC1Init(PWM1_TIM, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(PWM1_TIM, TIM_OCPreload_Enable);
	break;
	case 2:
	TIM_OC2Init(PWM1_TIM, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(PWM1_TIM, TIM_OCPreload_Enable);
	break;
	case 3:
	TIM_OC3Init(PWM1_TIM, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(PWM1_TIM, TIM_OCPreload_Enable);
	break;
	case 4:
	TIM_OC4Init(PWM1_TIM, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(PWM1_TIM, TIM_OCPreload_Enable);
	break;
	default:
		break;
	}		
}
/*********************************END OF PWM1**********************/

/*****************************PWM1**********************/
static void PWM2_TIM_GPIO_Config(uint16_t CCR1_Val , uint16_t CCR2_Val , uint16_t CCR3_Val , uint16_t CCR4_Val) 
{
  GPIO_InitTypeDef GPIO_InitStructure;

  // ����Ƚ�ͨ��1 GPIO ��ʼ��
  if(CCR1_Val>0)
  {
  RCC_APB2PeriphClockCmd(PWM2_TIM_CH1_GPIO_CLK, ENABLE);	
  GPIO_InitStructure.GPIO_Pin =  PWM2_TIM_CH1_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(PWM2_TIM_CH1_PORT, &GPIO_InitStructure);
  }
	
	// ����Ƚ�ͨ��2 GPIO ��ʼ��
  if(CCR2_Val>0)
  {
  RCC_APB2PeriphClockCmd(PWM2_TIM_CH2_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  PWM2_TIM_CH2_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(PWM2_TIM_CH2_PORT, &GPIO_InitStructure);
  }

	// ����Ƚ�ͨ��3 GPIO ��ʼ��
	if(CCR3_Val>0)
	{
  RCC_APB2PeriphClockCmd(PWM2_TIM_CH3_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  PWM2_TIM_CH3_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(PWM2_TIM_CH3_PORT, &GPIO_InitStructure);
	}

	// ����Ƚ�ͨ��4 GPIO ��ʼ��
	if(CCR4_Val>0)
	{
  RCC_APB2PeriphClockCmd(PWM2_TIM_CH4_GPIO_CLK, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  PWM2_TIM_CH4_PIN;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(PWM2_TIM_CH4_PORT, &GPIO_InitStructure);
	}
}


///*
// * ע�⣺TIM_TimeBaseInitTypeDef�ṹ��������5����Ա��TIM6��TIM7�ļĴ�������ֻ��
// * TIM_Prescaler��TIM_Period������ʹ��TIM6��TIM7��ʱ��ֻ���ʼ����������Ա���ɣ�
// * ����������Ա��ͨ�ö�ʱ���͸߼���ʱ������.
// *-----------------------------------------------------------------------------
// *typedef struct
// *{ TIM_Prescaler            ����
// *	TIM_CounterMode			     TIMx,x[6,7]û�У���������
// *  TIM_Period               ����
// *  TIM_ClockDivision        TIMx,x[6,7]û�У���������
// *  TIM_RepetitionCounter    TIMx,x[1,8,15,16,17]����
// *}TIM_TimeBaseInitTypeDef; 
// *-----------------------------------------------------------------------------
// */

/* ----------------   PWM�ź� ���ں�ռ�ձȵļ���--------------- */
// ARR ���Զ���װ�ؼĴ�����ֵ
// CLK_cnt����������ʱ�ӣ����� Fck_int / (psc+1) = 72M/(psc+1)
// PWM �źŵ����� T = (ARR+1) * (1/CLK_cnt) = (ARR+1)*(PSC+1) / 72M
// ռ�ձ�P=CCR/(ARR+1)

static void PWM2_TIM_Mode_Config(uint16_t CCR1_Val , uint16_t CCR2_Val , uint16_t CCR3_Val , uint16_t CCR4_Val)
{
  // ������ʱ��ʱ��,���ڲ�ʱ��CK_INT=72M
	PWM2_TIM_APBxClock_FUN(PWM2_TIM_CLK,ENABLE);

/*--------------------ʱ���ṹ���ʼ��-------------------------*/
	// �������ڣ���������Ϊ50Hz
	
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	// �Զ���װ�ؼĴ�����ֵ���ۼ�TIM_Period+1��Ƶ�ʺ����һ�����»����ж�
	TIM_TimeBaseStructure.TIM_Period=PWM2_TIM_Period-1;	
	// ����CNT��������ʱ�� = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= PWM2_TIM_Prescaler-1;	
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// ����������ģʽ������Ϊ���ϼ���
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// �ظ���������ֵ��û�õ����ù�
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// ��ʼ����ʱ��
	TIM_TimeBaseInit(PWM2_TIM, &TIM_TimeBaseStructure);

	TIM_OCInitTypeDef  TIM_OCInitStructure;
	// ����ΪPWMģʽ1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������	
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	// ����Ƚ�ͨ�� 1
	if(CCR1_Val>0)
	{
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
	TIM_OC1Init(PWM2_TIM, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(PWM2_TIM, TIM_OCPreload_Enable);
	}

	// ����Ƚ�ͨ�� 2
	if(CCR2_Val>0)
	{
	TIM_OCInitStructure.TIM_Pulse = CCR2_Val;
	TIM_OC2Init(PWM2_TIM, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(PWM2_TIM, TIM_OCPreload_Enable);
	}	

	// ����Ƚ�ͨ�� 3
	if(CCR3_Val>0)
	{
	TIM_OCInitStructure.TIM_Pulse = CCR3_Val;
	TIM_OC3Init(PWM2_TIM, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(PWM2_TIM, TIM_OCPreload_Enable);
	}

	// ����Ƚ�ͨ�� 4
	if(CCR4_Val>0)
	{
	TIM_OCInitStructure.TIM_Pulse = CCR4_Val;
	TIM_OC4Init(PWM2_TIM, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(PWM2_TIM, TIM_OCPreload_Enable);
	}

	// ʹ�ܼ�����
	TIM_Cmd(PWM2_TIM, ENABLE);
	//�����ʹ�ܣ���ʹ��ͨ�ö�ʱ��ʱ���˾䲻��Ҫ
	TIM_CtrlPWMOutputs(PWM2_TIM,ENABLE);
}


/**
  * @brief  PWM��ʼ�������4��PWM�����ھ�Ϊ20ms.
  * @param  CCRx_Val: �ڼ���PWM���������ڿ��Ϊ2000�����øò������Ե���ռ�ձ�. 
  *   This parameter can be one of the following values:
  *   0��      ������PWMx��ͬʱ��ռ��IO��
  *   1-2000
  * @retval None
  */
void PWM2_TIM_Init(uint16_t CCR1_Val , uint16_t CCR2_Val , uint16_t CCR3_Val , uint16_t CCR4_Val)
{
	PWM2_TIM_GPIO_Config(CCR1_Val , CCR2_Val , CCR3_Val , CCR4_Val);
	PWM2_TIM_Mode_Config(CCR1_Val , CCR2_Val , CCR3_Val , CCR4_Val);		
}
/*********************************END OF PWM2**********************/
/*********************************************END OF FILE**********************/
