#ifndef _HAL_INFRARED_H
#define _HAL_INFRARED_H

#include <stdio.h>
#include <stm32f10x.h>
#include "delay.h"
#include "hal_uart.h"

#define IR_BOARD 0
#define IR_BLUE 1
#define IR_RED 2

void IR_EXTI_Init(uint8_t id);
void IR_TIM_Init(uint8_t id);
void IR_TIM_Init(uint8_t id);

void IR_Init(uint8_t id);
void IR_Handle(uint8_t id);
void IR_GPIO_Init(uint8_t id);
#endif /*_HAL_INFRARED_H*/


