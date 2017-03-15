/*
 * HTS221TempHumidity.cpp
 *
 *  Created on: Mar 12, 2017
 *      Author: Hesham
 */

#include "HTS221TempHumiditySensor.h"

//Temperature and Humidity Sensor

static uint8 I2C_HTS221(uint8 Ref_Address){

    uint8 WR_Status = 0;
    uint8 RD_Status = 0;
    uint8 WR_Buffer[HTS221_WR_BUFFER_SIZE];
    uint8 RD_Buffer[HTS221_RD_BUFFER_SIZE];

    WR_Buffer[0] = Ref_Address;

            do
        {
            /* The syntax below automatically writes a buffer of data to a slave
             * device from start to stop.
              */
            WR_Status = I2C_1_MasterWriteBuf(I2C_HTS221_Address, (uint8 *)WR_Buffer,
                                        HTS221_WR_BUFFER_SIZE, I2C_1_MODE_COMPLETE_XFER);
        }
        while (WR_Status != I2C_1_MSTR_NO_ERROR);



        /* Wait for the data transfer to complete */
        while(I2C_1_MasterStatus() & I2C_1_MSTAT_XFER_INP);

        WR_Status = I2C_1_MasterClearStatus();

        RD_Status = I2C_1_MasterReadBuf(I2C_HTS221_Address, (uint8 *)RD_Buffer,
                    HTS221_RD_BUFFER_SIZE, I2C_1_MODE_COMPLETE_XFER);

        while (RD_Status != I2C_1_MSTR_NO_ERROR);

        /* Wait for the data transfer to complete */
        while(I2C_1_MasterStatus() & I2C_1_MSTAT_XFER_INP);

        RD_Status = I2C_1_MasterClearStatus();

        return RD_Buffer[0];
}

static void Init_HTS221(){

    uint8 WR_Status = 0;
    uint8 RD_Status = 0;
    uint8 WR_Buffer[Init_HTS221_WR_BUFFER_SIZE];

    WR_Buffer[0] = HTS221_CTRL_REG1;
    WR_Buffer[1] = HTS221_TEMP_EN | HTS221_OM_UH_PERF | HTS221_Fast_ODR | HTS221_ST_EN;

            do
        {
            /* The syntax below automatically writes a buffer of data to a slave
             * device from start to stop.
              */
            WR_Status = I2C_1_MasterWriteBuf(I2C_HTS221_Address, (uint8 *)WR_Buffer,
                                        Init_HTS221_WR_BUFFER_SIZE, I2C_1_MODE_COMPLETE_XFER);
        }
        while (WR_Status != I2C_1_MSTR_NO_ERROR);



        /* Wait for the data transfer to complete */
        while(I2C_1_MasterStatus() & I2C_1_MSTAT_XFER_INP);

        WR_Status = I2C_1_MasterClearStatus();

}

//Read Temperature

static double HTS221_Read_Temperature(){

        int16 T0_OUT = (int16) I2C_HTS221(HTS221_T0_OUT_0) | (int16)(I2C_HTS221(HTS221_T0_OUT_1) << 8);

        int16 T1_OUT = (int16) I2C_HTS221(HTS221_T1_OUT_0) | (int16)(I2C_HTS221(HTS221_T1_OUT_1) << 8);

        int16 T_OUT = (int16) I2C_HTS221(HTS221_TEMP_OUT_L) | (int16)(I2C_HTS221(HTS221_TEMP_OUT_H) << 8);

        uint16 MSB = I2C_HTS221(HTS221_T1_T0_MSB);

        uint16 MSB_T0 = MSB & 0x03;

        uint16 MSB_T1 = MSB & 0x0C;

        uint8 T0_DegC_x8 =  I2C_HTS221(HTS221_T0_degC_x8);

        double T0_DegC = (T0_DegC_x8 | (MSB_T0 << 8))/8.0;

        uint8 T1_DegC_x8 =  I2C_HTS221(HTS221_T1_degC_x8);

        double T1_DegC = (T1_DegC_x8 | (MSB_T1 << 6))/8.0;

        double Diff_DegC = T1_DegC - T0_DegC;

        double Diff_OUT = T1_OUT - T0_OUT;

        double slope =(double) (Diff_DegC/Diff_OUT);

        return (slope*(T_OUT - T0_OUT)) + T0_DegC;


}

//Read Humidity

static uint16 HTS221_Read_Humidity(){


    int16 H0_T0_OUT = (int16)I2C_HTS221(HTS221_H0_OUT_0) | (int16)(I2C_HTS221(HTS221_H0_OUT_1)<<8) ;

    int16 H1_T0_OUT = (int16)I2C_HTS221(HTS221_H1_OUT_0) | (int16)(I2C_HTS221(HTS221_H1_OUT_1)<<8) ;

    int16 H_T_OUT = (int16)I2C_HTS221(HTS221_HUMIDITY_OUT_L) | (int16)(I2C_HTS221(HTS221_HUMIDITY_OUT_H)<<8) ;

    uint8 H0_rH_x2 = I2C_HTS221(HTS221_H0_rH_x2);

    double H0_rH = H0_rH_x2/2;

    uint8 H1_rH_x2 = I2C_HTS221(HTS221_H1_rH_x2);

    double H1_rH = H1_rH_x2/2;

    double Diff_H0_H1_rH = H1_rH - H0_rH;

    double Diff_H0_H1_OUT = H1_T0_OUT - H0_T0_OUT;

    double slope = Diff_H0_H1_rH/Diff_H0_H1_OUT;

    return (slope)*(H_T_OUT-H0_T0_OUT)+H0_rH;


}

//Testing HTS221

static uint16 HTS221_Test(){

    return   I2C_HTS221(HTS221_WHO_AM_I); // should be 0xBC

}

