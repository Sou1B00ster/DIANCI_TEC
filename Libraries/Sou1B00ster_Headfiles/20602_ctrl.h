#ifndef __20602_CTRL_H
#define __20602_CTRL_H
#include "headfile.h"
#include "Parameter.h"

extern float Z_360;
extern float Z_0;
extern float Gyro_Offset_flag;
extern double ICM_value;
typedef struct{
        float Xdata;
        float Ydata;
        float Zdata;

        float acc_x;
        float acc_y;
        float acc_z;

        float mag_x;
        float mag_y;
        float mag_z;
}gyro_param_t;
typedef struct{
        float acc_x;
        float acc_y;
        float acc_z;

        float gyro_x;
        float gyro_y;
        float gyro_z;

        float mag_x;
        float mag_y;
        float mag_z;

}ICM_param_t;
extern ICM_param_t myglobalVar;

typedef struct {
    float q0, q1, q2, q3; 
} Quaternion;

typedef struct {
    float q0;
    float q1;
    float q2;
    float q3;
} quater_param_t;

typedef struct {
    float pitch;   
    float roll;    
    float yaw;     
} euler_param_t;

extern euler_param_t eulerAngle;

float ICM_gyro_Offset_Init(void);
void ICM_GetValues(void);
void ICM_YAW_integral(void);
void ICM_Init(void);
void ICM_getEulerianAngles(void) ;




#endif