#include "stm32f10x.h"                  // Device header
#include "Delay.h"

#define   KEY_1_CLK	 (RCC_APB2Periph_GPIOB)
#define   KEY_1_PORT  (GPIOB)
#define   KEY_1_PIN	 (GPIO_Pin_4)

void key_Init(void)
{
	RCC_APB2PeriphClockCmd(KEY_1_CLK, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = KEY_1_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(KEY_1_PORT, &GPIO_InitStruct);
}

int key_scan(void)
{	
	if(GPIO_ReadInputDataBit(KEY_1_PORT, KEY_1_PIN) == 0)
	{
		Delay_ms(10);
		if(GPIO_ReadInputDataBit(KEY_1_PORT, KEY_1_PIN) == 0)
		{
			while(GPIO_ReadInputDataBit(KEY_1_PORT, KEY_1_PIN) == 0);
			return 1;
		}
		else 
		{
			return 0;   
		}
	}
	return 0;
}
