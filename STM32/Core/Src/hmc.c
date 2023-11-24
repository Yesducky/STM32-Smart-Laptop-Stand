#include "hmc.h"
#include "lcd.h"

int8_t mz, lz, status;
int16_t z;

int init = 0;
int16_t init_z;


uint16_t HMC5883L_Addr = 0x1E;
uint8_t CRA = 0x70;
uint8_t CRB = 0xA0;
uint8_t mode = 0x00;



void HMC5883L_Init(I2C_HandleTypeDef *hi2c2){
    HAL_I2C_Mem_Write(hi2c2,HMC5883L_Addr<<1,0x00,1,&CRA,1,100);
    HAL_I2C_Mem_Write(hi2c2,HMC5883L_Addr<<1,0x01,1,&CRB,1,100);
    HAL_I2C_Mem_Write(hi2c2,HMC5883L_Addr<<1,0x02,1,&mode,1,100);
}

int HMC5883L_Read(I2C_HandleTypeDef *hi2c2){
    //read status
    HAL_I2C_Mem_Read(hi2c2,HMC5883L_Addr<<1,0x09,1,&status,1,100);

    if(status%2 == 0){
		return 0;
    }
    else{
//        HAL_I2C_Mem_Read(hi2c2,HMC5883L_Addr<<1,0x05,1,&mz,1,100);
//        HAL_I2C_Mem_Read(hi2c2,HMC5883L_Addr<<1,0x06,1,&lz,1,100);
//        z = lz + (mz << 8);
//
//        if(init == 0){
//        	init = 1;
//        	init_z = z;
//        }
        //z = z-init_z;

        return 1;
    }

}


