#include "bsp_usart.h"
#include "Motor.h"
#include "communication_protocol.h"
#include "bsp_led.h"
#include "PID.h"
#include "app.h"
uint8_t fc_recv_buff[fc_recv_buff_size];
uint8_t nano_recv_buff[nano_recv_buff_size];  
uint8_t yaw_recv_buff[yaw_recv_buff_size]; 

uint8_t flag_seq_fc = 0;
uint8_t flag_seq_nano = 0;
uint8_t flag_seq_yaw = 0;
int q=0;
#define ok  50 
// static void NVIC_USART1_Configuration(void)
// {
//   NVIC_InitTypeDef NVIC_InitStructure;
  
//   /* ����USARTΪ�ж�Դ */
//   NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART1_IRQ;
//   /* �������ȼ�*/
//   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//   /* �����ȼ� */
//   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
//   /* ʹ���ж� */
//   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//   /* ��ʼ������NVIC */
//   NVIC_Init(&NVIC_InitStructure);
// }

static void NVIC_USART2_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* ����USARTΪ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART2_IRQ;
  /* �������ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* �����ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
  /* ʹ���ж� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
  NVIC_Init(&NVIC_InitStructure);
}

static void NVIC_USART3_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* ����USARTΪ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_USART3_IRQ;
  /* �������ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  /* �����ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  /* ʹ���ж� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
  NVIC_Init(&NVIC_InitStructure);
}
static void NVIC_UART5_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* ����USARTΪ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = DEBUG_UART5_IRQ;
  /* �������ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  /* �����ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  /* ʹ���ж� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
  NVIC_Init(&NVIC_InitStructure);
}

static void NVIC_UART4_Configuration()
{
	  NVIC_InitTypeDef NVIC_InitStructure;
 
 /* ����USARTΪ�ж�Դ */
 NVIC_InitStructure.NVIC_IRQChannel = DEBUG_UART4_IRQ;
 /* �������ȼ�*/
 NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
 /* �����ȼ� */
 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
 /* ʹ���ж� */
 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
 /* ��ʼ������NVIC */
 NVIC_Init(&NVIC_InitStructure);

}
 /*
  * @brief  USART GPIO ����,������������
  * @param  ��
  * @retval ��
  */
// void USART1_Config(void)
// {
// 	GPIO_InitTypeDef GPIO_InitStructure;
// 	USART_InitTypeDef USART_InitStructure;

// 	// �򿪴���GPIO��ʱ��
// 	DEBUG_USART1_GPIO_APBxClkCmd(DEBUG_USART1_GPIO_CLK, ENABLE);
	
// 	// �򿪴��������ʱ��
// 	DEBUG_USART1_APBxClkCmd(DEBUG_USART1_CLK, ENABLE);

// 	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
// 	GPIO_InitStructure.GPIO_Pin = DEBUG_USART1_TX_GPIO_PIN;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(DEBUG_USART1_TX_GPIO_PORT, &GPIO_InitStructure);

//   // ��USART Rx��GPIO����Ϊ��������ģʽ
// 	GPIO_InitStructure.GPIO_Pin = DEBUG_USART1_RX_GPIO_PIN;
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
// 	GPIO_Init(DEBUG_USART1_RX_GPIO_PORT, &GPIO_InitStructure);
	
// 	// ���ô��ڵĹ�������
// 	// ���ò�����
// 	USART_InitStructure.USART_BaudRate = DEBUG_USART1_BAUDRATE;
// 	// ���� �������ֳ�
// 	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
// 	// ����ֹͣλ
// 	USART_InitStructure.USART_StopBits = USART_StopBits_1;
// 	// ����У��λ
// 	USART_InitStructure.USART_Parity = USART_Parity_No ;
// 	// ����Ӳ��������
// 	USART_InitStructure.USART_HardwareFlowControl = 
// 	USART_HardwareFlowControl_None;
// 	// ���ù���ģʽ���շ�һ��
// 	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
// 	// ��ɴ��ڵĳ�ʼ������
// 	USART_Init(DEBUG_USART1, &USART_InitStructure);
	
// #ifdef Enable_IRQ_USERT1_RX
// 	{// �����ж����ȼ�����
// 	NVIC_USART1_Configuration();
// 	// ʹ�ܴ��ڽ����ж�
// 	USART_ITConfig(DEBUG_USART1, USART_IT_RXNE, ENABLE);	
// 	}
// 	#endif
// 	// ʹ�ܴ���
// 	USART_Cmd(DEBUG_USART1, ENABLE);	    
// }



void USART2_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// �򿪴���GPIO��ʱ��
	DEBUG_USART2_GPIO_APBxClkCmd(DEBUG_USART2_GPIO_CLK, ENABLE);
	
	// �򿪴��������ʱ��
	DEBUG_USART2_APBxClkCmd(DEBUG_USART2_CLK, ENABLE);

	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART2_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART2_TX_GPIO_PORT, &GPIO_InitStructure);

  // ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART2_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART2_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// ���ô��ڵĹ�������
	// ���ò�����
	USART_InitStructure.USART_BaudRate = DEBUG_USART2_BAUDRATE;
	// ���� �������ֳ�
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// ����ֹͣλ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// ����У��λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// ����Ӳ��������
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	// ���ù���ģʽ���շ�һ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// ��ɴ��ڵĳ�ʼ������
	USART_Init(DEBUG_USART2, &USART_InitStructure);
	
#ifdef Enable_IRQ_USERT2_RX
	{// �����ж����ȼ�����
	NVIC_USART2_Configuration();
	// ʹ�ܴ��ڽ����ж�
	USART_ITConfig(DEBUG_USART2, USART_IT_RXNE, ENABLE);	
	}
	#endif
	// ʹ�ܴ���
	NVIC_USART2_Configuration();
	USART_Cmd(DEBUG_USART2, ENABLE);	    
}

void USART3_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// �򿪴���GPIO��ʱ��
	DEBUG_USART3_GPIO_APBxClkCmd(DEBUG_USART3_GPIO_CLK, ENABLE);
	
	// �򿪴��������ʱ��
	DEBUG_USART3_APBxClkCmd(DEBUG_USART3_CLK, ENABLE);

	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART3_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_USART3_TX_GPIO_PORT, &GPIO_InitStructure);

  // ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_USART3_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_USART3_RX_GPIO_PORT, &GPIO_InitStructure);
	
	
	USART_InitStructure.USART_BaudRate = DEBUG_USART3_BAUDRATE;

	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// ����У��λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// ����Ӳ��������
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	// ���ù���ģʽ���շ�һ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// ��ɴ��ڵĳ�ʼ������
	USART_Init(DEBUG_USART3, &USART_InitStructure);
	
#ifdef Enable_IRQ_USERT1_RX
	{// �����ж����ȼ�����
	NVIC_USART3_Configuration();
	// ʹ�ܴ��ڽ����ж�
	USART_ITConfig(DEBUG_USART3, USART_IT_RXNE, ENABLE);	
	}
	#endif
	// ʹ�ܴ���
	NVIC_USART3_Configuration();
	USART_Cmd(DEBUG_USART3, ENABLE);	    
}
void UART4_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// �򿪴���GPIO��ʱ��
	DEBUG_UART4_GPIO_APBxClkCmd(DEBUG_UART4_GPIO_CLK, ENABLE);
	
	// �򿪴��������ʱ��
	DEBUG_UART4_APBxClkCmd(DEBUG_UART4_CLK, ENABLE);

	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_UART4_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_UART4_TX_GPIO_PORT, &GPIO_InitStructure);

  // ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_UART4_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_UART4_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// ���ô��ڵĹ�������
	// ���ò�����
	USART_InitStructure.USART_BaudRate = DEBUG_UART4_BAUDRATE;
	// ���� �������ֳ�
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// ����ֹͣλ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// ����У��λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// ����Ӳ��������
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	// ���ù���ģʽ���շ�һ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(DEBUG_UART4, &USART_InitStructure);
	
// #ifdef Enable_IRQ_UART4_RX
// 	{
// 	NVIC_UART4_Configuration();
	
// 	USART_ITConfig(DEBUG_UART4, USART_IT_RXNE, ENABLE);	
// 	}
// 	#endif
	// ʹ�ܴ���
	NVIC_UART4_Configuration();
	
	USART_Cmd(DEBUG_UART4, ENABLE);	    
}

void UART5_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// �򿪴���GPIO��ʱ��
	DEBUG_UART5_GPIO_APBxClkCmd(DEBUG_UART5_GPIO_CLK1, ENABLE);
	DEBUG_UART5_GPIO_APBxClkCmd(DEBUG_UART5_GPIO_CLK2, ENABLE);

	// �򿪴��������ʱ��
	DEBUG_UART5_APBxClkCmd(DEBUG_UART5_CLK, ENABLE);

	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_UART5_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEBUG_UART5_TX_GPIO_PORT, &GPIO_InitStructure);

  // ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = DEBUG_UART5_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(DEBUG_UART5_RX_GPIO_PORT, &GPIO_InitStructure);
	
	// ���ô��ڵĹ�������
	// ���ò�����
	USART_InitStructure.USART_BaudRate = DEBUG_UART5_BAUDRATE;
	// ���� �������ֳ�
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// ����ֹͣλ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// ����У��λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// ����Ӳ��������
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	// ���ù���ģʽ���շ�һ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// ��ɴ��ڵĳ�ʼ������
	USART_Init(DEBUG_UART5, &USART_InitStructure);
	
	// �����ж����ȼ�����
	NVIC_UART5_Configuration();
	// ʹ�ܴ���
	USART_Cmd(DEBUG_UART5, ENABLE);	    
}



/*****************  ����һ���ֽ� **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* ����һ���ֽ����ݵ�USART */
	USART_SendData(pUSARTx,ch);
		
	/* �ȴ��������ݼĴ���Ϊ�� */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/****************** ����8λ������ ************************/
void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num)
{
  uint8_t i;
	
	for(i=0; i<num; i++)
  {
	    /* ����һ���ֽ����ݵ�USART */
	    Usart_SendByte(pUSARTx,array[i]);	
  
  }
	/* �ȴ�������� */
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET);
}

/*****************  �����ַ��� **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* �ȴ�������� */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}

/*****************  ����һ��16λ�� **********************/
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* ȡ���߰�λ */
	temp_h = (ch&0XFF00)>>8;
	/* ȡ���Ͱ�λ */
	temp_l = ch&0XFF;
	
	/* ���͸߰�λ */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);

	/* ���͵Ͱ�λ */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

// void Usart_Send_uint32( USART_TypeDef * pUSARTx, uint32_t ch)
// {
// 	uint16_t temp_h, temp_l;
	
// 	/* ȡ���߰�λ */
// 	temp_h = (ch&0XFFFF0000)>>16;
// 	/* ȡ���Ͱ�λ */
// 	temp_l = ch&0XFFFF;
	
// 	/* ���͸߰�λ */
// 	Usart_SendHalfWord(pUSARTx,temp_h);	
	
// 	/* ���͵Ͱ�λ */
// 	Usart_SendHalfWord(pUSARTx,temp_l);	
// }


///�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ����� */
		USART_SendData(DEBUG_UART5, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(DEBUG_UART5, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		/* �ȴ������������� */
		while (USART_GetFlagStatus(DEBUG_UART5, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_UART5);
}


// // ����1�жϷ�����
// void DEBUG_USART1_IRQHandler(void)
// {
//   uint8_t ucTemp;
// 	if(USART_GetITStatus(DEBUG_USART1,USART_IT_RXNE)!=RESET)
// 	{		
// 		ucTemp = USART_ReceiveData(DEBUG_USART1);
//     USART_SendData(DEBUG_USART1,ucTemp);    
// 	}	 
// }

// ����2�жϷ�����
void DEBUG_USART2_IRQHandler(void)
{
  uint8_t ucTemp;
	if(USART_GetITStatus(DEBUG_USART2,USART_IT_RXNE)!=RESET)
	{		
		ucTemp = USART_ReceiveData(DEBUG_USART2);
          LED_BLUE;
		   	switch(flag_seq_yaw){
			case 0:		
				if(ucTemp==0xAA){
					yaw_recv_buff[flag_seq_yaw] = ucTemp;
					flag_seq_yaw++;
				}
				else flag_seq_yaw=0;
			break;
			case 1:
				if(ucTemp==0xAF){
					yaw_recv_buff[flag_seq_yaw] = ucTemp;
					flag_seq_yaw++;
				}
				else flag_seq_yaw=0;
			break;
			default:
				if(flag_seq_yaw<14){
					yaw_recv_buff[flag_seq_yaw] = ucTemp;
					flag_seq_yaw++;
				}
				if(flag_seq_yaw==14){ 
				Yaw_RecvArray_Process();
				flag_seq_yaw=0;
				}
			break;
			}
	}	 
}
// ����3�жϷ�����
//void DEBUG_UART3_IRQHandler(void)
//{
//  uint8_t ucTemp;
//	if(USART_GetITStatus(DEBUG_USART3,USART_IT_RXNE)!=RESET)
//	{		
//		ucTemp = USART_ReceiveData(DEBUG_USART3);
//    USART_SendData(DEBUG_USART3,ucTemp);    
//	}	 
//}

void DEBUG_UART4_IRQHandler(void)
{
  uint8_t ucTemp;
	if(USART_GetITStatus(DEBUG_UART4,USART_IT_RXNE)!=RESET)
	{		
		ucTemp = USART_ReceiveData(DEBUG_UART4);
		switch (ucTemp)
		{
		case '1':
        Forward(ok);
		printf("nihao");
		break;
		case '2':
		Backward(ok);

		break;
		case '3':
		R_Translation(ok);
		break;
		case '4':
		L_Translation(ok);
		break;
		case '6':
		L_Rotation();
		break;
		case '7':
		R_Rotation();
		break;
		case '9':

	
	q++;
	main_target=q;
	break;
		default:
		break;
		}
    USART_SendData(DEBUG_UART4,ucTemp);    
	}	 
}

void DEBUG_UART5_IRQHandler(void)
{
  uint8_t ucTemp;
	if(USART_GetITStatus(DEBUG_UART5,USART_IT_RXNE)!=RESET)
	{		
		ucTemp = USART_ReceiveData(DEBUG_UART5);
    USART_SendData(DEBUG_UART5,ucTemp);    
	
		}    
	}	 




