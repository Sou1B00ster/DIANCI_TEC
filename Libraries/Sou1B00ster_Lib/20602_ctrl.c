#include "20602_CTRL.h"

gyro_param_t Gyro_Offset;
ICM_param_t ICM_Data;
float Gyro_Offset_flag=1;
float Z_360=1;
float Z_0=1;
double ICM_value=1;

float ICM_gyro_Offset_Init()
{
	uint16 i;
    Gyro_Offset.Zdata=0;
    for(i=0;i<3000;i++)
    {
        Gyro_Offset.Xdata+=icm20602_gyro_x;
        Gyro_Offset.Ydata+=icm20602_gyro_y;
        Gyro_Offset.Zdata+=icm20602_gyro_z;
    }
    Gyro_Offset.Xdata/=30;
    Gyro_Offset.Ydata/=30;
    Gyro_Offset.Zdata/=30;

    Gyro_Offset.acc_x=0;
    Gyro_Offset.acc_y=0;
    Gyro_Offset.acc_z=0;
    for(i=0;i<30;i++)
    {
        Gyro_Offset.acc_x+=icm20602_acc_x;
        Gyro_Offset.acc_y+=icm20602_acc_y;
        Gyro_Offset.acc_z+=icm20602_acc_z;
    }
    Gyro_Offset.acc_x/=30;
    Gyro_Offset.acc_y/=30;
    Gyro_Offset.acc_z/=30;

    return Gyro_Offset_flag=0;

}
void ICM_GetValues()
{

    ICM_Data.gyro_x=((float)icm20602_gyro_x- Gyro_Offset.Xdata)*PI/180/14.3f;
    ICM_Data.gyro_y=((float)icm20602_gyro_y- Gyro_Offset.Ydata)*PI/180/14.3f;
    ICM_Data.gyro_z=((float)icm20602_gyro_z- Gyro_Offset.Zdata)*PI/180/14.3f;

    ICM_Data.acc_x=((float)icm20602_acc_x)*PI/180/4098.0f;
    ICM_Data.acc_y=((float)icm20602_acc_y)*PI/180/4098.0f;
    ICM_Data.acc_z=((float)icm20602_acc_z)*PI/180/4098.0f;
		
}
void ICM_Handle_180()
{
    ICM_value=-1*RAD_TO_ANGLE(ICM_Data.gyro_z*0.00989);
    Z_360+=-1*RAD_TO_ANGLE(ICM_Data.gyro_z*0.008700);
    if(Z_360>=180){ Z_360-=360;}
    if(Z_360<=-180){Z_360+=360;}
}

void ICM_YAW_integral()
{
    if(ICM_Data.gyro_z<0.02&&ICM_Data.gyro_z>-0.02)
    {
        Z_360-=0;
    }
    else
    {
        ICM_Handle_180();
    }
}
#define delt_T     0.01f  
#define M_PI        3.141f

float I_ex, I_ey, I_ez; 
float gyro_max=0.001;
float acc_max=0.01;

quater_param_t Q_info = {1, 0, 0};  
euler_param_t eulerAngle; 

int GyroOffset_init = 0;

float param_Kp = 0;   
float param_Ki = 0;   


float fast_sqrt(float x) {
    float halfx = 0.5f * x;
    float y = x;
    long i = *(long *) &y;
    i = 0x5f3759df - (i >> 1);
    y = *(float *) &i;
    y = y * (1.5f - (halfx * y * y));
    return y;
}
void ICM_AHRSupdate(float gx, float gy, float gz, float ax, float ay, float az) 
{
		float halfT = 0.5 * delt_T;
    float vx, vy, vz;    
    float ex, ey, ez;    
    float q0 = Q_info.q0;
    float q1 = Q_info.q1;
    float q2 = Q_info.q2;
    float q3 = Q_info.q3;
    float q0q0 = q0 * q0;
    float q0q1 = q0 * q1;
    float q0q2 = q0 * q2;
    float q0q3 = q0 * q3;
    float q1q1 = q1 * q1;
    float q1q2 = q1 * q2;
    float q1q3 = q1 * q3;
    float q2q2 = q2 * q2;
    float q2q3 = q2 * q3;
    float q3q3 = q3 * q3;
	float qa,qb,qc;

    float norm = fast_sqrt(ax * ax + ay * ay + az * az);
    param_Kp=0.017;   
		param_Ki=0.004;

    ax = ax * norm;
    ay = ay * norm;
    az = az * norm;

    vx = 2 * (q1q3 - q0q2);
    vy = 2 * (q0q1 + q2q3);
    vz = (q0*q0-0.5f+q3 * q3) * 2;

    ex = ay * vz - az * vy;
    ey = az * vx - ax * vz;
    ez = ax * vy - ay * vx;

    I_ex += halfT * ex;   
    I_ey += halfT * ey;
    I_ez += halfT * ez;

    gx = gx + param_Kp * ex + param_Ki * I_ex;
    gy = gy + param_Kp * ey + param_Ki * I_ey;
    gz = gz + param_Kp * ez + param_Ki * I_ez;



		qa=q0;
		qb=q1;
		qc=q2;
    q0 = q0 + (-qb * gx - qc * gy - q3 * gz) * halfT;
    q1 = q1 + (qa * gx + qc * gz - q3 * gy) * halfT;
    q2 = q2 + (qa * gy - qb * gz + q3 * gx) * halfT;
    q3 = q3 + (qa * gz + qb * gy - qc * gx) * halfT;


    norm = fast_sqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
    Q_info.q0 = q0 * norm;
    Q_info.q1 = q1 * norm;
    Q_info.q2 = q2 * norm;
    Q_info.q3 = q3 * norm;
}

void ICM_getEulerianAngles(void) 
{
    float  q0 = Q_info.q0;
    float  q1 = Q_info.q1;
    float  q2 = Q_info.q2;
    float  q3 = Q_info.q3;
    
    ICM_AHRSupdate(ICM_Data.gyro_x, ICM_Data.gyro_y, ICM_Data.gyro_z, ICM_Data.acc_x, ICM_Data.acc_y, ICM_Data.acc_z);
    
    eulerAngle.roll = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2 * q2 + 1) * 180 / M_PI; // roll
    eulerAngle.yaw = -atan2(2 * q1 * q2 + 2 * q0 * q3, -2 * q2 * q2 - 2 * q3 * q3 + 1) * 180 / M_PI; // yaw


    if (eulerAngle.yaw > 180) {
        eulerAngle.yaw -= 360;
    } else if (eulerAngle.yaw < -180) {
        eulerAngle.yaw += 360;
    }
		Z_0=eulerAngle.roll;
}

void ICM_Init(void)
{
    icm20602_init();
    ICM_gyro_Offset_Init();
}


