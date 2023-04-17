/*
 * mpu6050.c
 *
 *  Created on: 14 Şub 2023
 *      Author: Caner
 */

#include "mpu6050.h"
#include <stdlib.h>

struct Mpu6050_Config_Tag
    {
    uint8_t i2cAddrs;
    Mpu6050_AccelFullScale_e accelFullScale;

    int16_t accelX;
    int16_t accelY;
    int16_t accelZ;
    };
Mpu6050_Config_t *mpu6050_init(uint8_t addrs, Mpu6050_AccelFullScale_e fullScale)
    {
	Mpu6050_Config_t *pConfig = malloc(sizeof(Mpu6050_Config_t));
	pConfig->i2cAddrs	= addrs;
	pConfig->accelFullScale	= fullScale;
	return pConfig;
    }

void    mpu6050_updateAccelDate(Mpu6050_Config_t *pConfig)
    {
	//Read from MPU6050, Emulate
	pConfig->accelX = 20;
	pConfig->accelY = 40;
	pConfig->accelZ = 940;
    }

int16_t mpu6050_getAccelX(Mpu6050_Config_t *pConfig)
    {
	return pConfig->accelX;
    }
int16_t mpu6050_getAccelY(Mpu6050_Config_t *pConfig)
    {
	return pConfig->accelY;
    }
int16_t mpu6050_getAccelZ(Mpu6050_Config_t *pConfig)
    {
	return pConfig->accelZ;
    }

void    mpu6050_deInit(Mpu6050_Config_t *pConfig)
    {
	free(pConfig);
    }
