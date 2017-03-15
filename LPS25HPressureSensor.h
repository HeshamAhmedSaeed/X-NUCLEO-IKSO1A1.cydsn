/*
 * LPS25HPressureSensor.h
 *
 *  Created on: Mar 12, 2017
 *      Author: Hesham
 */

#ifndef LPS25HPRESSURESENSOR_H_
#define LPS25HPRESSURESENSOR_H_

#define I2C_LPS25H_Address          (0x5D)
#define LPS25H_WHO_AM_I             (0x0F)
#define LPS25H_CTRL_REG1            (0x20)
#define LPS25H_ODR                  (0x40)
#define LPS25H_PW_ACTIVE            (0x80)
#define LPS25H_PRESS_POUT_XL        (0x28)
#define LPS25H_PRESS_OUT_L          (0x29)
#define LPS25H_PRESS_OUT_H          (0x2A)
#define LPS25H_TEMP_OUT_L           (0x2B)
#define LPS25H_TEMP_OUT_H           (0x2C)
#define LPS25H_REF_P_XL             (0x08)
#define LPS25H_REF_P_L              (0x09)
#define LPS25H_REF_P_H              (0x0A)
#define Init_LPS25H_WR_BUFFER_SIZE  (2u)
#define LPS25H_WR_BUFFER_SIZE       (1u)
#define LPS25H_RD_BUFFER_SIZE       (1u)
    
#include "project.h"
    
	uint8 I2C_LPS25H(uint8 Ref_Address);

	void Init_LPS25H();

	uint16 LPS25H_Read_PRESSURE();

	uint16 LPS25H_TEST();

#endif /* LPS25HPRESSURESENSOR_H_ */
