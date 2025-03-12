#include "stm32f10x.h"                  // Device header
#include "delay.h"

void SW1801_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(GPIOB, &GPIO_InitStruct);
}

uint8_t Get_vibration_value(void)
{
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
