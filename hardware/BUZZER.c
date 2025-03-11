#include "stm32f10x.h"                  // Device header

#define  BUZZER_CLK 	(RCC_APB2Periph_GPIOB)
#define  BUZZER_PORT	(GPIOB)
#define  BUZZER_PIN		(GPIO_Pin_12)

void BUZZER_Init(void)
{
	RCC_APB2PeriphClockCmd(BUZZER_CLK, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = BUZZER_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;	
	GPIO_Init(BUZZER_PORT, &GPIO_InitStruct);
	
	GPIO_SetBits(BUZZER_PORT, BUZZER_PIN);
}

void BUZZER_On(void)
{
	GPIO_ResetBits(BUZZER_PORT, BUZZER_PIN);
}

void BUZZER_Off(void)
{
	GPIO_SetBits(BUZZER_PORT, BUZZER_PIN);
}
