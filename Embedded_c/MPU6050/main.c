#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "mpu6050.h"

int main(void)
    {
     Mpu6050_AccelFullScale_e accelFullScale = Mpu6050_AccelFullScale_4g;

     switch(accelFullScale){
     case Mpu6050_AccelFullScale_2g:
	 {
	 int mySelect = 2;
	 printf("Select = %d",mySelect);
	 }
	 break;
     case Mpu6050_AccelFullScale_4g:
	 break;
     case Mpu6050_AccelFullScale_8g:
	 break;
     case Mpu6050_AccelFullScale_16g:
	 break;
     case Mpu6050_AccelFullScale_32g:

     }

     getchar();
     return 0;
    }
