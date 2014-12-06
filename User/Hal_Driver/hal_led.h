#ifndef _HAL_LED4_H
#define _HAL_LED4_H

#include <stdio.h>
#include <stm32f10x.h>
#include "protocol.h"

#define DIO_LOW GPIO_ResetBits(GPIOA,GPIO_Pin_6)
#define DIO_HIGH GPIO_SetBits(GPIOA,GPIO_Pin_6)	

#define RCLK_LOW GPIO_ResetBits(GPIOA,GPIO_Pin_7)
#define RCLK_HIGH GPIO_SetBits(GPIOA,GPIO_Pin_7)	

#define SCLK_LOW GPIO_ResetBits(GPIOA,GPIO_Pin_5)
#define SCLK_HIGH GPIO_SetBits(GPIOA,GPIO_Pin_5)

// sbit DIO = P1^0; //串行数据输入
// sbit RCLK  = P1^1;				//时钟脉冲信号——上升沿有效
// sbit SCLK = P1^2;				//打入信号————上升沿有效


void LED4_Init(void);
void LED4_Display(uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4);


#endif /*_HAL_LED4_H*/

