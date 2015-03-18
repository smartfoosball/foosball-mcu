#include "hal_infrared.h"

#define IR_EXTI

#ifdef IR_EXTI

void IR_GPIO_Init(uint8_t id)
{
  GPIO_InitTypeDef   GPIO_InitStructure;  
	if (id == IR_BOARD || id == IR_RED) 
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //开启IO 时钟   
	else
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  
	if (id == IR_BLUE) 
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	else if (id == IR_RED)
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	else
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	/* Configure PA.00 pin as input floating */   
	//GPIO_InitStructure.GPIO_Pin = pin;     //设置IO模式   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    //必须要上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	     

	if (id == IR_BOARD || id == IR_RED) 
		GPIO_Init(GPIOA, &GPIO_InitStructure); 
	else
		GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void IR_EXTI_Init(uint8_t id)
{
  EXTI_InitTypeDef   EXTI_InitStructure;  
	NVIC_InitTypeDef   NVIC_InitStructure; 
	
	uint32_t extiLine;
  /* Connect EXTI0 Line to PA.00 pin */    
	if (id == IR_BOARD) {
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource12); //设定外设中断线
		extiLine = EXTI_Line12;
	} else if (id == IR_BLUE) {
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource10);
		extiLine = EXTI_Line10;
	} else if (id == IR_RED) {
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource4);
		extiLine = EXTI_Line4;
	}

	EXTI_ClearITPendingBit(extiLine);       //清除线路挂起位  
/* Configure EXTI0 line */    
	EXTI_InitStructure.EXTI_Line = extiLine;     //设置中断类型   
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;    
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;    //上升沿触发   EXTI_Trigger_Rising EXTI_Trigger_Rising_Falling
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;   
	EXTI_Init(&EXTI_InitStructure); 
	
	
	/* Enable and set EXTI0 Interrupt to the lowest priority */   
	if (id == IR_BOARD) {
		NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	} else if (id == IR_BLUE) {
		NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	} else if (id == IR_RED) {
		NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
	}
	//NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;      //设置中断优先级    
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;   
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;   
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   
	NVIC_Init(&NVIC_InitStructure);
	
}



void IR_Init(uint8_t id)
{
	IR_GPIO_Init(id);
	IR_EXTI_Init(id);

}

//EXTI15_10_IRQHandler
#else

void IR_GPIO_Init(uint8_t id)
{
  GPIO_InitTypeDef   GPIO_InitStructure;  
	uint16_t pin;
	if (id == IR_BOARD) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //开启IO 时钟  
		pin = GPIO_Pin_12;
	} else if (id == IR_BLUE) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);  //开启IO 时钟  
		pin = GPIO_Pin_10;
  } else if (id == IR_RED) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);  //开启IO 时钟  
		pin = GPIO_Pin_4;
	}
	/* Configure PA.00 pin as input floating */   
	GPIO_InitStructure.GPIO_Pin = pin;     //设置IO模式   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;    //必须要上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);     
	/* Enable AFIO clock */    
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  //开启AFIO时钟

}
#endif

