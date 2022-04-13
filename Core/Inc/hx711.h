#ifndef __HX711_H_
#define __HX711_H_

#define HX711_SCK_PORT	 GPIOA
#define HX711_SCK_PIN		 GPIO_PIN_2
#define HX711_DOUT_PORT	 GPIOA
#define HX711_DOUT_PIN 	 GPIO_PIN_3

#include <stm32g0xx_hal.h>

unsigned long HX711_Read(void);
void Get_Maopi(void);
uint16_t Get_Weight(void);
void Delay_ms(uint8_t time);

#endif
