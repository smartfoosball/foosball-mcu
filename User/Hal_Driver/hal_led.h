#ifndef _HAL_LED4_H
#define _HAL_LED4_H

#include <stdio.h>
#include <stm32f10x.h>
#include "protocol.h"

#define DIO_LOW GPIO_ResetBits(GPIOA,GPIO_Pin_6) // 通过 PA6 发送低电平 给 DIO 
#define DIO_HIGH GPIO_SetBits(GPIOA,GPIO_Pin_6) // 通过 PA6 发送高电平 给 DIO   
#define RCLK_LOW GPIO_ResetBits(GPIOA,GPIO_Pin_7) // 通过 PA7 发送低电平 给 RCLK
#define RCLK_HIGH GPIO_SetBits(GPIOA,GPIO_Pin_7)  // 通过 PA7 发送高电平 给 RCLK

#define SCLK_LOW GPIO_ResetBits(GPIOA,GPIO_Pin_5) // 通过 PA5 发送低电平 给 SCLK
#define SCLK_HIGH GPIO_SetBits(GPIOA,GPIO_Pin_5)  // 通过 PA5 发送高电平 给 RCLK

void LED4_Init(void); // 初始化 IO 口信息

// 输出 4 个 数字到 LED 显示屏，取值范围 从 0 到 15(F)
void LED4_Display(uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4);
#endif /*_HAL_LED4_H*/
