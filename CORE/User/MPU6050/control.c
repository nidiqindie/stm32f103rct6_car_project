#include "control.h"
#include "bsp_led.h"
// extern  int A_encoder=0;
// extern	int B_encoder=0;
// extern	int C_encoder=0;
// extern	int D_encoder=0;
// 	int Yaw1=0;
// 	float 
// 	Velocity_Kp=-10,//�ٶȻ�KP��KI0.16
// 	Velocity_Ki=1;
// void EXTI4_IRQHandler(void)
// {

// 	if(EXTI_GetITStatus(EXTI_Line4)!=0)//һ���ж�
// 	{
// 		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)==0)//�����ж�
// 		{
// 			EXTI_ClearITPendingBit(EXTI_Line4);//����жϱ�־λ
			
// 			//1���ɼ�����������&MPU6050�Ƕ���Ϣ��
// 			A_encoder=-Read_encoder(2);//�������԰�װ���պ����180�ȣ�Ϊ�˱������������һ�£�����Ҫ������һ��ȡ����
// 			B_encoder=Read_encoder(3);
// 			A_encoder=-Read_encoder(4);
// 			B_encoder=Read_encoder(5);
// 		// 	mpu_dmp_get_data(&Pitch,&Roll,&Yaw);			//�Ƕ�
// 		// printf("the_first%f %f %f<<endl\n",Pitch,Roll,Yaw);
//     //   Yaw=0.0004*Yaw-0.49;
// //			Incremental_PI (A_encoder,int Target);
// //			Incremental_PI (B_encoder,int Target);
// //			Incremental_PI (C_encoder,int Target);
// //			Incremental_PI (D_e+ncoder,int Target);
			
			
// LED_BLUE;	
// 	 }
// 	}
// }

// ///**************************************************************************
// //�������ܣ�����PI������
// //��ڲ���������������ֵ��Ŀ���ٶ�
// //����  ֵ�����PWM
// //��������ʽ��ɢPID��ʽ 
// //pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
// //e(k)��������ƫ�� 
// //e(k-1)������һ�ε�ƫ��  �Դ����� 
// //pwm�����������
// //�����ǵ��ٶȿ��Ʊջ�ϵͳ���棬ֻʹ��PI����      
// //pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)
// //**************************************************************************/
int Incremental_PI (int Encoder,int Target)
{ 	
     float Kp=150,Ki=0;	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                //����ƫ��
	 Pwm+=Kp*(Bias-Last_bias)+Ki*Bias;   //����ʽPI������
	 Last_bias=Bias;	                 //������һ��ƫ�� 
	 return Pwm;                         //�������
}
