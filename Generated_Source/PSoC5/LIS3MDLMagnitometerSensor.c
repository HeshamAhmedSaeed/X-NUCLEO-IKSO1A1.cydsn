/*
 * LIS3MDLMagnitometer.c
 *
 *  Created on: Mar 12, 2017
 *      Author: Hesham
 */

#include "LIS3MDLMagnitometerSensor.h"

static uint8 I2C_LIS3MDL(uint8 Ref_Address){

    uint8 WR_Status = 0;
    uint8 RD_Status = 0;
    uint8 WR_Buffer[LIS3MDL_WR_BUFFER_SIZE];
    uint8 RD_Buffer[LIS3MDL_RD_BUFFER_SIZE];

    WR_Buffer[0] = Ref_Address;

            do
        {
            /* The syntax below automatically writes a buffer of data to a slave
             * device from start to stop.
              */
            WR_Status = I2C_1_MasterWriteBuf(I2C_LIS3MDL_Address, (uint8 *)WR_Buffer,
                                        LIS3MDL_WR_BUFFER_SIZE, I2C_1_MODE_COMPLETE_XFER);
        }
        while (WR_Status != I2C_1_MSTR_NO_ERROR);



        /* Wait for the data transfer to complete */
        while(I2C_1_MasterStatus() & I2C_1_MSTAT_XFER_INP);

        WR_Status = I2C_1_MasterClearStatus();

        RD_Status = I2C_1_MasterReadBuf(I2C_LIS3MDL_Address, (uint8 *)RD_Buffer,
                    LIS3MDL_RD_BUFFER_SIZE, I2C_1_MODE_COMPLETE_XFER);

        while (RD_Status != I2C_1_MSTR_NO_ERROR);

        /* Wait for the data transfer to complete */
        while(I2C_1_MasterStatus() & I2C_1_MSTAT_XFER_INP);

        RD_Status = I2C_1_MasterClearStatus();

        return RD_Buffer[0];
}


static void Init_LIS3MDL(){

    uint8 WR_Status = 0;
    uint8 RD_Status = 0;
    uint8 WR_Buffer[Init_LIS3MDL_WR_BUFFER_SIZE];

    WR_Buffer[0] = LIS3MDL_CTRL_REG3;
    WR_Buffer[1] = LIS3MDL_OP_MD;

            do
        {
            /* The syntax below automatically writes a buffer of data to a slave
             * device from start to stop.
              */
            WR_Status = I2C_1_MasterWriteBuf(I2C_LIS3MDL_Address, (uint8 *)WR_Buffer,
                                        Init_LIS3MDL_WR_BUFFER_SIZE, I2C_1_MODE_COMPLETE_XFER);
        }
        while (WR_Status != I2C_1_MSTR_NO_ERROR);



        /* Wait for the data transfer to complete */
        while(I2C_1_MasterStatus() & I2C_1_MSTAT_XFER_INP);

        WR_Status = I2C_1_MasterClearStatus();

}


//Testing LIS3MDL

static uint16 LIS3MDL_TEST(){

    return I2C_LIS3MDL(LIS3MDL_WHO_AM_I); // should be 0x3D

}

//Read Magentometer

static void LIS3MDL_Read_Magnetiometer(signed short* X, signed short* Y ,signed short* Z){

    volatile uint8 X_L = 0;

    volatile uint8 X_H = 0;

    volatile uint8 Y_L = 0;

    volatile uint8 Y_H = 0;

    volatile uint8 Z_L = 0;

    volatile uint8 Z_H = 0;

    X_L = I2C_LIS3MDL(LIS3MDL_OUT_X_L);

    X_H = I2C_LIS3MDL(LIS3MDL_OUT_X_H);

    Y_L = I2C_LIS3MDL(LIS3MDL_OUT_Y_L);

    Y_H = I2C_LIS3MDL(LIS3MDL_OUT_Y_H);

    Z_L = I2C_LIS3MDL(LIS3MDL_OUT_Z_L);

    Z_H = I2C_LIS3MDL(LIS3MDL_OUT_Z_H);

    *X = X_L | X_H<<8;

    *Y = Y_L | Y_H<<8;

    *Z = Z_L | Z_H<<8;

}
