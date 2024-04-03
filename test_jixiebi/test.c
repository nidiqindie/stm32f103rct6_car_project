#include <math.h>
#include <stdio.h>

int main()
{
    float H = 5.1; //底座高度
    float A1 = 8;   //大臂长度
    float A2 = 8.3;  //小臂长度
    float delat_L = 7.5;  //小臂长度

//车身坐标
    float CAR_X = -10;
    float CAR_Y = 14;     
    float CAR_Z = 7; 

//机械臂坐标
    float ARM_X = 0;
    float ARM_Y = 0;     
    float ARM_Z = 0; 

    float j1 = 0; //底座旋转角度
    float j2 = 0; //大臂旋转角度
    float j3 = 0; //小臂旋转角度

//计算过程中，为简化运算定义的中间变量
    float z1 = 0;
    float z2 = 0;
    float z3 = 0;
    float z4 = 0;
    float z5 = 0;

    unsigned int CCR_Val1 = 0;//
    unsigned int CCR_Val2 = 0;//
    unsigned int CCR_Val3 = 0;//

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

        if((j2 > 90) || (j2 < -30)){
            printf("舵机2角度超出安全限制范围(-10°--90°),%f\r\n",j2); 
            }
        if((j3 > 90) || (j3 < 0)){
            printf("舵机3角度超出安全限制范围(0°--90°),%f\r\n",j3); 
            }

  	    CCR_Val1 = (20 + j1); //
 	    CCR_Val2 = (155 - j2); //
        CCR_Val3 = (50 + j3); //

        printf("%f,%f,%f\r\n",j1,j2,j3);
        printf("%d,%d,%d\r\n",CCR_Val1,CCR_Val2,CCR_Val3);//
    }    
    else    printf("超量程\r\n");
}
