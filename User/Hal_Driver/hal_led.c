#include "hal_led.h"

//-----------------------------------------------------------------------------
// 函数原形定义
#define uchar unsigned char

void LED_OUT(uchar X);				// LED单字节串行移位函数

unsigned char LED_0F[];		// LED字模表

void LED_OUT(uchar X)
{
	uchar i;
	for(i=8;i>=1;i--)
	{
		if (X&0x80) DIO_HIGH; else DIO_LOW;
		X<<=1;
		SCLK_LOW;
		SCLK_HIGH;
	}
}

unsigned char LED_0F[] = 
{// 0	 1	  2	   3	4	 5	  6	   7	8	 9	  A	   b	C    d	  E    F    -
	0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x8C,0xBF,0xC6,0xA1,0x86,0xFF,0xbf
};


void LED4_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	LED4_Display(8, 8, 8, 8);
}

void LED4_Display(uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4)
{
	unsigned char *led_table;          // 查表指针
	uchar i;
	//显示第1位
	led_table = LED_0F + d1;
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x01);		

	RCLK_LOW;
	RCLK_HIGH;
	//显示第2位
	led_table = LED_0F + d2;
	i = *led_table;

	LED_OUT(i);		
	LED_OUT(0x02);		

	RCLK_LOW;
	RCLK_HIGH;
	//显示第3位
	led_table = LED_0F + d3;
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x04);	

	RCLK_LOW;
	RCLK_HIGH;
	//显示第4位
	led_table = LED_0F + d4;
	i = *led_table;

	LED_OUT(i);			
	LED_OUT(0x08);		

	RCLK_LOW;
	RCLK_HIGH;
}
