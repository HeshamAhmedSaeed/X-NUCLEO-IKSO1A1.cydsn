/*
 * HTS221TempHumidity.h
 *
 *  Created on: Mar 12, 2017
 *      Author: Hesham
 */

#ifndef HTS221TEMPHUMIDITY_H_
#define HTS221TEMPHUMIDITY_H_
    
#include "project.h"

#define I2C_HTS221_Address          (0x5F)
#define HTS221_WHO_AM_I             (0x0F)
#define HTS221_CTRL_REG1            (0x20)
#define HTS221_TEMP_EN              (0x80)
#define HTS221_Fast_ODR             (0x02)
#define HTS221_ST_EN                (0x01)
#define HTS221_OM_M_PERF            (0x20)
#define HTS221_OM_H_PERF            (0x40)
#define HTS221_OM_UH_PERF           (0x60)
#define HTS221_HUMIDITY_OUT_L       (0x28)
#define HTS221_HUMIDITY_OUT_H       (0x29)
#define HTS221_TEMP_OUT_L           (0x2A)
#define HTS221_TEMP_OUT_H           (0x2B)
#define HTS221_Status               (0x27)
#define HTS221_T0_degC_x8           (0x32)
#define HTS221_T1_degC_x8           (0x33)
#define HTS221_T1_T0_MSB            (0x35)
#define HTS221_T0_OUT_0             (0x3C)
#define HTS221_T0_OUT_1             (0x3D)
#define HTS221_T1_OUT_0             (0x3E)
#define HTS221_T1_OUT_1             (0x3F)
#define HTS221_H0_OUT_0             (0x36)
#define HTS221_H0_OUT_1             (0x37)
#define HTS221_H1_OUT_0             (0x3A)
#define HTS221_H1_OUT_1             (0x3B)
#define HTS221_H0_rH_x2             (0x30)
#define HTS221_H1_rH_x2             (0x31)
#define Init_HTS221_WR_BUFFER_SIZE  (2u)
#define HTS221_WR_BUFFER_SIZE       (1u)
#define HTS221_RD_BUFFER_SIZE       (1u)

    
uint8 I2C_HTS221(uint8 Ref_Address);

void Init_HTS221();

uint8 HTS221_Read_Temperature();

uint16 HTS221_Read_Humidity();

uint16 HTS221_Test();


#endif /* HTS221TEMPHUMIDITY_H_ */
