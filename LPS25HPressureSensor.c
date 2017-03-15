/*
 * LPS25HPressureSensor.cpp
 *
 *  Created on: Mar 12, 2017
 *      Author: Hesham
 */

#include "LPS25HPressureSensor.h"


uint8 I2C_LPS25H(uint8 Ref_Address){

    uint8 WR_Status = 0;
    uint8 RD_Status = 0;
    uint8 WR_Buffer[LPS25H_WR_BUFFER_SIZE];
    uint8 RD_Buffer[LPS25H_RD_BUFFER_SIZE];

    WR_Buffer[0] = Ref_Address;

            do
        {
            /* The syntax below automatically writes a buffer of data to a slave
             * device from start to stop.
              */
            WR_Status = I2C_1_MasterWriteBuf(I2C_LPS25H_Address, (uint8 *)WR_Buffer,
                                        LPS25H_WR_BUFFER_SIZE, I2C_1_MODE_COMPLETE_XFER);
        }
        while (WR_Status != I2C_1_MSTR_NO_ERROR);



        /* Wait for the data transfer to complete */
        while(I2C_1_MasterStatus() & I2C_1_MSTAT_XFER_INP);

        WR_Status = I2C_1_MasterClearStatus();

        RD_Status = I2C_1_MasterReadBuf(I2C_LPS25H_Address, (uint8 *)RD_Buffer,
                    LPS25H_RD_BUFFER_SIZE, I2C_1_MODE_COMPLETE_XFER);

        while (RD_Status != I2C_1_MSTR_NO_ERROR);

        /* Wait for the data transfer to complete */
        while(I2C_1_MasterStatus() & I2C_1_MSTAT_XFER_INP);

        RD_Status = I2C_1_MasterClearStatus();

        return RD_Buffer[0];
}


void Init_LPS25H(){

    uint8 WR_Status = 0;
    uint8 RD_Status = 0;
    uint8 WR_Buffer[Init_LPS25H_WR_BUFFER_SIZE];

    WR_Buffer[0] = LPS25H_CTRL_REG1;
    WR_Buffer[1] = LPS25H_PW_ACTIVE|LPS25H_ODR;

            do
        {
            /* The syntax below automatically writes a buffer of data to a slave
             * device from start to stop.
              */
            WR_Status = I2C_1_MasterWriteBuf(I2C_LPS25H_Address, (uint8 *)WR_Buffer,
                                        Init_LPS25H_WR_BUFFER_SIZE, I2C_1_MODE_COMPLETE_XFER);
        }
        while (WR_Status != I2C_1_MSTR_NO_ERROR);



        /* Wait for the data transfer to complete */
        while(I2C_1_MasterStatus() & I2C_1_MSTAT_XFER_INP);

        WR_Status = I2C_1_MasterClearStatus();

}


//Read PRESSURE

uint16 LPS25H_Read_PRESSURE(){

    uint8 PRESS_OUT_XL = 0;

    uint8 PRESS_OUT_L = 0;

    uint8 PRESS_OUT_H = 0;

    int PRESS_OUT = 0;

    int PRESSURE = 0;

    PRESS_OUT_XL = I2C_LPS25H(LPS25H_PRESS_POUT_XL);

    PRESS_OUT_L = I2C_LPS25H(LPS25H_PRESS_OUT_L);

    PRESS_OUT_H = I2C_LPS25H(LPS25H_PRESS_OUT_H );

    PRESS_OUT = PRESS_OUT_XL | PRESS_OUT_L << 8 | PRESS_OUT_H << 16;

    PRESSURE = PRESS_OUT / 4096;

    return PRESSURE;
}

//Testing LPS25H

uint16 LPS25H_TEST(){

    return I2C_LPS25H(LPS25H_WHO_AM_I); // should be 0xBD

}

