/*
 * LIS3MDLMagnitometer.h
 *
 *  Created on: Mar 12, 2017
 *      Author: Hesham
 */

#ifndef LIS3MDLMAGNITOMETER_H_
#define LIS3MDLMAGNITOMETER_H_

#include"project.h"
    
#define I2C_LIS3MDL_Address         (0x1E)
#define LIS3MDL_WHO_AM_I            (0x0F)
#define LIS3MDL_CTRL_REG3           (0x22)
#define LIS3MDL_OP_MD               (0x00)
#define LIS3MDL_CTRL_REG5           (0x24)
#define LIS3MDL_OUT_X_L             (0x28)
#define LIS3MDL_OUT_X_H             (0x29)
#define LIS3MDL_OUT_Y_L             (0x2A)
#define LIS3MDL_OUT_Y_H             (0x2B)
#define LIS3MDL_OUT_Z_L             (0x2C)
#define LIS3MDL_OUT_Z_H             (0x2D)
#define LIS3MDL_TEMP_OUT_L          (0x2E)
#define LIS3MDL_TEMP_OUT_H          (0x2F)
#define Init_LIS3MDL_WR_BUFFER_SIZE (2u)
#define LIS3MDL_WR_BUFFER_SIZE      (1u)
#define LIS3MDL_RD_BUFFER_SIZE      (1u)


uint8 I2C_LIS3MDL(uint8 Ref_Address);

void Init_LIS3MDL();

uint16 LIS3MDL_TEST();

void LIS3MDL_Read_Magnetiometer(signed short* X, signed short* Y ,signed short* Z);

#endif /* LIS3MDLMAGNITOMETER_H_ */
