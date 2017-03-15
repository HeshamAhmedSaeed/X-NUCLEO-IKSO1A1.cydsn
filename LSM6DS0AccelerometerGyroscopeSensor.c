/*
 * LSM6DS0AccelerometerGyroscopeSensor.c
 *
 *  Created on: Mar 12, 2017
 *      Author: Hesham
 */

#include "LSM6DS0AccelerometerGyroscopeSensor.h"

// Accelerometer and Gyroscope Sensor

volatile signed short X_G_Abs = 0 ;

volatile signed short Y_G_Abs = 0 ;

volatile signed short Z_G_Abs = 0 ;

volatile signed short X_A_Abs = 0 ;

volatile signed short Y_A_Abs = 0 ;

volatile signed short Z_A_Abs = 0 ;

uint8 I2C_LSM6DS0(uint8 Ref_Address){

    uint8 WR_Status = 0;
    uint8 RD_Status = 0;
    uint8 WR_Buffer[LSM6DS0_WR_BUFFER_SIZE];
    uint8 RD_Buffer[LSM6DS0_RD_BUFFER_SIZE];

    WR_Buffer[0] = Ref_Address;

            do
        {
            /* The syntax below automatically writes a buffer of data to a slave
             * device from start to stop.
              */
            WR_Status = I2C_1_MasterWriteBuf(I2C_LSM6DS0_Address, (uint8 *)WR_Buffer,
                                        LSM6DS0_WR_BUFFER_SIZE, I2C_1_MODE_COMPLETE_XFER);
        }
        while (WR_Status != I2C_1_MSTR_NO_ERROR);



        /* Wait for the data transfer to complete */
        while(I2C_1_MasterStatus() & I2C_1_MSTAT_XFER_INP);

        WR_Status = I2C_1_MasterClearStatus();

        RD_Status = I2C_1_MasterReadBuf(I2C_LSM6DS0_Address, (uint8 *)RD_Buffer,
                    LSM6DS0_RD_BUFFER_SIZE, I2C_1_MODE_COMPLETE_XFER);

        while (RD_Status != I2C_1_MSTR_NO_ERROR);

        /* Wait for the data transfer to complete */
        while(I2C_1_MasterStatus() & I2C_1_MSTAT_XFER_INP);

        RD_Status = I2C_1_MasterClearStatus();

        return RD_Buffer[0];
}

//Testing LSM6DS0

uint16 LSM6DS0_TEST(){

    return I2C_LSM6DS0(LSM6DS0_WHO_AM_I); // should be 0x68

}

// Read Gyro
void LSM6DS0_Read_Gyrometer(signed short* X_G, signed short* Y_G ,signed short* Z_G){

    volatile uint8 X_L_G;
    volatile uint8 X_H_G;
    volatile uint8 Y_L_G;
    volatile uint8 Y_H_G;
    volatile uint8 Z_L_G;
    volatile uint8 Z_H_G;


    X_H_G = I2C_LSM6DS0(LSM6DS0_OUT_X_G_H);

    X_L_G = I2C_LSM6DS0(LSM6DS0_OUT_X_G_L);

    Y_H_G = I2C_LSM6DS0(LSM6DS0_OUT_Y_G_H);

    Y_L_G = I2C_LSM6DS0(LSM6DS0_OUT_Y_G_L);

    Z_H_G = I2C_LSM6DS0(LSM6DS0_OUT_Z_G_H);

    Z_L_G = I2C_LSM6DS0(LSM6DS0_OUT_Z_G_L);


    *X_G = (X_L_G | X_H_G << 8) - X_G_Abs;
    *Y_G = (Y_L_G | Y_H_G << 8) - Y_G_Abs;
    *Z_G = (Z_L_G | Z_H_G << 8) - Z_G_Abs;

}

// Read Accelerometer

void LSM6DS0_Read_Acelerometer(signed short* X_A, signed short* Y_A ,signed short* Z_A){

    volatile uint8 X_L_A;
    volatile uint8 X_H_A;
    volatile uint8 Y_L_A;
    volatile uint8 Y_H_A;
    volatile uint8 Z_L_A;
    volatile uint8 Z_H_A;

    X_H_A = I2C_LSM6DS0(LSM6DS0_OUT_X_A_H);

    X_L_A = I2C_LSM6DS0(LSM6DS0_OUT_X_A_L);

    Y_H_A = I2C_LSM6DS0(LSM6DS0_OUT_Y_A_H);

    Y_L_A = I2C_LSM6DS0(LSM6DS0_OUT_Y_A_L);

    Z_H_A = I2C_LSM6DS0(LSM6DS0_OUT_Z_A_H);

    Z_L_A = I2C_LSM6DS0(LSM6DS0_OUT_Z_A_L);

    *X_A = X_L_A | X_H_A << 8 - X_A_Abs;

    *Y_A = Y_L_A | Y_H_A << 8 - Y_A_Abs;

    *Z_A = Z_L_A | Z_H_A << 8 - Z_A_Abs;

}

// Init LSM6DS0

void Init_LSM6DS0(){

    uint8 WR_Status = 0;
    uint8 WR_Buffer[Init_LSM6DS0_WR_BUFFER_SIZE];

    WR_Buffer[0] = LSM6DS0_CTRL_REG1_G;
    WR_Buffer[1] = LSM6DS0_ODR_ON;

    // Access Register

    do
        {
            WR_Status = I2C_1_MasterWriteBuf(I2C_LSM6DS0_Address, (uint8 *)WR_Buffer,
                                        Init_LSM6DS0_WR_BUFFER_SIZE, I2C_1_MODE_COMPLETE_XFER);
        }
        while (WR_Status != I2C_1_MSTR_NO_ERROR);

        LSM6DS0_Read_Acelerometer(&X_A_Abs ,&Y_A_Abs ,&Z_A_Abs);

        LSM6DS0_Read_Gyrometer(&X_G_Abs ,&Y_G_Abs ,&Z_G_Abs);
        
}