/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "project.h"
#include "HTS221TempHumiditySensor.h"
#include "LIS3MDLMagnitometerSensor.h"
#include "LPS25HPressureSensor.h"
#include "LSM6DS0AccelerometerGyroscopeSensor.h"

#define RD_BUFFER_SIZE          (1u)
#define WR_BUFFER_SIZE          (1u)
#define WR_BUFFER_SIZE_DATA     (2u)
//LED's
static void LED_On(){
 
    PWM_1_WriteCompare(255);
    
}

static void LED_Off(){
 
    PWM_1_WriteCompare(0);
    
}

static void LED_Different(int value){
 
    PWM_1_WriteCompare(value);
    
}

static void LED_Breath(){

    static int Counter = 0;
    
    static int inc = 0;
        
    PWM_1_WriteCompare(Counter);  
  
    if(PIN_1_Read() == 1)
    
    {      
        
        if(inc == 0){
            if(Counter < 254)
                Counter++;   
            else
                inc = 1;
        }
 
        if(inc == 1){
            if(Counter > 0)
                Counter--;   
            else
                inc = 0;
        }

        else
        {
            
            LED_On();
            
            PWM_1_Stop();
                
            CyDelay(50u);
                
            PWM_1_Start();
    
            CyDelay(10u);
            
        }

    

    }
}

static void i8ToString(int8_t n, char *str)
{
    const uint8_t cint8_run[] = {100, 10, 1};
    const uint8_t cint8_run_len = 3;
    
    uint8_t i = 0, j = 0;
    uint8_t start_found = 0;
    
    if (0 > n)
      str[j++] = '-';  
    
    for (; i < cint8_run_len; i++)
    {
        if (start_found == 1)
        {
            str[j++] = '0' + (n / cint8_run[i]);
            n = n % cint8_run[i];
        }
        else
        {
           str[j] = '0' + (n / cint8_run[i]);
           if ('0' < str[j])
           {
                start_found = 1;
                n = n % cint8_run[i];
                j++;               
           }        
        }
    }
    
    if (start_found == 0)
        str[j++] = '0';
        
    str[j] = '\0';
}

static void i16ToString(int16_t n, char *str)
{
    volatile int temp_n = n;
    
    volatile char s = '+';
    
    if(0 > n)
    {
        temp_n = temp_n * -1;
        
        s = '-';
    }

    str[4] = '0' + (((temp_n%1000)%100)%10)/1;
    str[3] = '0' + ((temp_n%1000)%100)/10;
    str[2] = '0' + (temp_n%1000)/100;
    str[1] = '0' + temp_n/1000;
    str[0] = s;
    str[5] = '\0';
}


static uint8 I2C_Read(uint8 Address,uint8 Ref_Address){
    
    
    uint8 WR_Status = 0;
    uint8 RD_Status = 0;
    uint8 WR_Buffer[LPS25H_WR_BUFFER_SIZE];
    uint8 RD_Buffer[RD_BUFFER_SIZE];
    
    WR_Buffer[0] = Ref_Address;
    
            do
        {
            /* The syntax below automatically writes a buffer of data to a slave
             * device from start to stop.
              */
            WR_Status = I2C_1_MasterWriteBuf(Address, (uint8 *)WR_Buffer,
                                        WR_BUFFER_SIZE, I2C_1_MODE_COMPLETE_XFER);
        }
        while (WR_Status != I2C_1_MSTR_NO_ERROR);

        
        
        /* Wait for the data transfer to complete */
        while(I2C_1_MasterStatus() & I2C_1_MSTAT_XFER_INP);

        WR_Status = I2C_1_MasterClearStatus();
        
        RD_Status = I2C_1_MasterReadBuf(Address, (uint8 *)RD_Buffer,
                    RD_BUFFER_SIZE, I2C_1_MODE_COMPLETE_XFER);

        while (RD_Status != I2C_1_MSTR_NO_ERROR);

        /* Wait for the data transfer to complete */
        while(I2C_1_MasterStatus() & I2C_1_MSTAT_XFER_INP);

        RD_Status = I2C_1_MasterClearStatus();
        
        return RD_Buffer[0];
}

static void I2C_Write(uint8 Address,uint8 Ref_Address,uint8 Data){
    
    
    uint8 WR_Status = 0;
    uint8 RD_Status = 0;
    uint8 WR_Buffer[WR_BUFFER_SIZE_DATA];
    
    WR_Buffer[0] = Ref_Address;
    WR_Buffer[1] = Data;
    
            do
        {
            /* The syntax below automatically writes a buffer of data to a slave
             * device from start to stop.
              */
            WR_Status = I2C_1_MasterWriteBuf(Address, (uint8 *)WR_Buffer,
                                        WR_BUFFER_SIZE_DATA, I2C_1_MODE_COMPLETE_XFER);
        }
        while (WR_Status != I2C_1_MSTR_NO_ERROR);

        
        
        /* Wait for the data transfer to complete */
        while(I2C_1_MasterStatus() & I2C_1_MSTAT_XFER_INP);

        WR_Status = I2C_1_MasterClearStatus();
        
}

// Sending data via UART

static void UART_Send_8(char8* Data_Name, uint8 Data){

    UART_1_PutString(Data_Name);
    
    UART_1_PutString(" : ");
    
    UART_1_PutCRLF(Data);

}

static void UART_Send_16(char8* Data_Name, signed short Data ){

    UART_1_PutString(Data_Name);
    
    UART_1_PutString(" : ");
    
    signed short Data_L = 0;
    
    if(Data < 0)
    {
        
        Data_L = -1*Data;
         
        UART_1_PutChar('-');
    
    }
    else
    {
    
        Data_L = Data;
        
        UART_1_PutChar('+');
    
    }    

    
    UART_1_PutChar(Data_L>>8);

    UART_1_PutCRLF(Data_L);
    
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
   
  
    UART_1_Start();

    PWM_1_Start();

	I2C_1_Start();
      
    
    Init_LSM6DS0(); // Gyrometer and Acelerometer
    
    Init_HTS221();  // Temperature and Hyumidity
    
    Init_LIS3MDL(); // Magnitometer

    Init_LPS25H();  // Pressure

    //I2C_Write(I2C_LIS3MDL_Address,0x21,0x0C);
    
    //I2C_Write(I2C_LSM6DS0_Address,0x10,0x80);
    
    //I2C_Write(I2C_LIS3MDL_Address,0x22,0x00);
    
    
    /* Temperature and Humidity Sensor */ 
    
    volatile uint8 Temperature = 0;
    volatile uint16 Humidity = 0;
    
    /* Pressure Sensor */
    
    volatile uint16 Pressure = 0;

    /* Magentometer Sensor */
    
    signed short X_Mageneto = 0;
    signed short Y_Mageneto = 0;
    signed short Z_Mageneto = 0;
    
    /* Accelerometer and Gyroscope Sensor */
    
    signed short X_Gyro = 0;
    signed short Y_Gyro = 0;
    signed short Z_Gyro = 0;
    
    signed short X_Accelerator = 0;
    signed short Y_Accelerator = 0;
    signed short Z_Accelerator = 0;
    
    /* Strings for the values */
    
    char temperature_str[5] = {0};
    char Humidity_str[5] = {0};
    
    char Pressure_str[5] = {0};
    
    char X_Mageneto_str[5] = {0};
    char Y_Mageneto_str[5] = {0};
    char Z_Mageneto_str[5] = {0};
    
    char X_Gyro_str[5] = {0};
    char Y_Gyro_str[5] = {0};
    char Z_Gyro_str[5] = {0};
    
    char X_Accelerator_str[5] = {0};
    char Y_Accelerator_str[5] = {0};
    char Z_Accelerator_str[5] = {0};
    
    for(;;)
    {
        Temperature = HTS221_Read_Temperature();
 
        Humidity = HTS221_Read_Humidity();

        Pressure = LPS25H_Read_PRESSURE();
  
        LIS3MDL_Read_Magnetiometer(&X_Mageneto,&Y_Mageneto,&Z_Mageneto);

        LSM6DS0_Read_Gyrometer(&X_Gyro,&Y_Gyro ,&Z_Gyro);
        
        LSM6DS0_Read_Acelerometer(&X_Accelerator ,&Y_Accelerator,&Z_Accelerator);

        
        
        i8ToString(Temperature, temperature_str);
        UART_1_PutString("\nTemperature : ");
        UART_1_PutString(temperature_str);

        
        i16ToString(X_Mageneto, X_Mageneto_str);
        UART_1_PutString("\nX_Mageneto : ");
        UART_1_PutString(X_Mageneto_str);               
           
        i16ToString(Y_Mageneto, Y_Mageneto_str);
        UART_1_PutString("\nY_Mageneto : ");
        UART_1_PutString(Y_Mageneto_str);
         
        i16ToString(Z_Mageneto, Z_Mageneto_str);
        UART_1_PutString("\nZ_Mageneto : ");
        UART_1_PutString(Z_Mageneto_str); 
                
        i16ToString(X_Gyro, X_Gyro_str);
        UART_1_PutString("\nX_Gyro : ");
        UART_1_PutString(X_Gyro_str); 
                        
        i16ToString(Y_Gyro, Y_Gyro_str);
        UART_1_PutString("\nY_Gyro : ");
        UART_1_PutString(Y_Gyro_str); 
                        
        i16ToString(Z_Gyro, Z_Gyro_str);
        UART_1_PutString("\nZ_Gyro : ");
        UART_1_PutString(Z_Gyro_str); 
                
        i16ToString(X_Accelerator, X_Accelerator_str);
        UART_1_PutString("\nX_Accelerator : ");
        UART_1_PutString(X_Accelerator_str); 
                        
        i16ToString(Y_Accelerator, Y_Accelerator_str);
        UART_1_PutString("\nY_Accelerator : ");
        UART_1_PutString(Y_Accelerator_str); 
                        
        i16ToString(Z_Accelerator, Z_Accelerator_str);
        UART_1_PutString("\nZ_Accelerator : ");
        UART_1_PutString(Z_Accelerator_str); 
                
        //UART_Send_8("Temperature", Temperature);

        //UART_Send_8("Humidity", Humidity);
    
        //UART_Send_8("Pressure", Pressure);
/*        
        UART_Send_16("Magnetometer X",X_Mageneto);
        UART_Send_16("Magnetometer Y",Y_Mageneto);
        UART_Send_16("Magnetometer Z",Z_Mageneto);
        
        UART_Send_16("Gyrometer X",X_Gyro);
        UART_Send_16("Gyrometer Y",Y_Gyro);
        UART_Send_16("Gyrometer Z",Z_Gyro); 
        
        
        UART_Send_16("Acelerometer X",X_Accelerator);
        UART_Send_16("Acelerometer Y",Y_Accelerator);
        UART_Send_16("Acelerometer Z",Z_Accelerator);    
*/
        LED_On();
        
        CyDelay(10000u);
   
        
    }
}

/* [] END OF FILE */
