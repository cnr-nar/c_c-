/*
 * mpu6050.h
 *
 *  Created on: 14 Şub 2023
 *      Author: Caner
 */

#ifndef SENSORS_MPU6050_H_
#define SENSORS_MPU6050_H_

#include <stdint.h>
#include <stdbool.h>

typedef enum
{
    Mpu6050_AccelFullScale_2g = 0,
    Mpu6050_AccelFullScale_4g,
    Mpu6050_AccelFullScale_8g,
    Mpu6050_AccelFullScale_16g,
    Mpu6050_AccelFullScale_32g
}Mpu6050_AccelFullScale_e;

typedef struct Mpu6050_Config_Tag Mpu6050_Config_t;

typedef struct
{
 uint8_t reserved : 3;//LeftSignicantBit(LSB)
 uint8_t afs_sel  : 2;
 uint8_t z_st 	  : 1;
 uint8_t y_st	  : 1;
 uint8_t x_st 	  : 1;
}Mpu6050_AccelConfigReg_t;

Mpu6050_Config_t *mpu6050_init(uint8_t addrs, Mpu6050_AccelFullScale_e fullScale);

void    mpu6050_updateAccelDate(Mpu6050_Config_t *pConfig);

int16_t mpu6050_getAccelX(Mpu6050_Config_t *pConfig);
int16_t mpu6050_getAccelY(Mpu6050_Config_t *pConfig);
int16_t mpu6050_getAccelZ(Mpu6050_Config_t *pConfig);

void    mpu6050_deInit(Mpu6050_Config_t *pConfig);

#endif /* SENSORS_MPU6050_H_ */
