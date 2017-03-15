/*
 * LSM6DS0AccelerometerGyroscopeSensor.h
 *
 *  Created on: Mar 12, 2017
 *      Author: Hesham
 */

#ifndef LSM6DS0ACCELEROMETERGYROSCOPESENSOR_H_
#define LSM6DS0ACCELEROMETERGYROSCOPESENSOR_H_

#include "project.h"
    
#define I2C_LSM6DS0_Address         (0x6B)
#define LSM6DS0_WHO_AM_I            (0x0F)
#define LSM6DS0_OUT_X_G_L           (0x18)
#define LSM6DS0_OUT_X_G_H           (0x19)
#define LSM6DS0_OUT_Y_G_L           (0x1A)
#define LSM6DS0_OUT_Y_G_H           (0x1B)
#define LSM6DS0_OUT_Z_G_L           (0x1C)
#define LSM6DS0_OUT_Z_G_H           (0x1D)
#define LSM6DS0_OUT_X_A_L           (0x28)
#define LSM6DS0_OUT_X_A_H           (0x29)
#define LSM6DS0_OUT_Y_A_L           (0x2A)
#define LSM6DS0_OUT_Y_A_H           (0x2B)
#define LSM6DS0_OUT_Z_A_L           (0x2C)
#define LSM6DS0_OUT_Z_A_H           (0x2D)
#define LSM6DS0_CTRL_REG1_G         (0x10)
#define LSM6DS0_CTRL_REG6_XL        (0x20)
#define LSM6DS0_ACT_THS             (0x04)
#define LSM6DS0_REFERENCE_G         (0x0B)
#define LSM6DS0_ODR_ON              (0x80)
#define LSM6DS0_GYRO_SCOPE_SCALE    (0x18)
#define Init_LSM6DS0_WR_BUFFER_SIZE (2u)
#define LSM6DS0_WR_BUFFER_SIZE      (1u)
#define LSM6DS0_RD_BUFFER_SIZE      (1u)

static uint8 I2C_LSM6DS0(uint8 Ref_Address);

static void Init_LSM6DS0();

static uint16 LSM6DS0_TEST();

static void LSM6DS0_Read_Gyrometer(signed short* X_G, signed short* Y_G ,signed short* Z_G);

static void LSM6DS0_Read_Acelerometer(signed short* X_A, signed short* Y_A ,signed short* Z_A);

#endif /* LSM6DS0ACCELEROMETERGYROSCOPESENSOR_H_ */
