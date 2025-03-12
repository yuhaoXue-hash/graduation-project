#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "alarm_moduel.h"

#define  SW1801_CLK	 	 (RCC_APB2Periph_GPIOB)
#define  SW1801_PORT	 (GPIOB)
#define  SW1801_PIN 	 (GPIO_Pin_0)

static uint8_t vibration_high_flag = 0;

void SW1801_Init(void)
{
	RCC_APB2PeriphClockCmd(SW1801_CLK, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = SW1801_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(SW1801_PORT, &GPIO_InitStruct);
}

void Get_vibration_value(void)
{
	if(GPIO_ReadInputDataBit(SW1801_PORT, SW1801_PIN) == 0)
	{
		if(vibration_high_flag == 0)
		{
			set_alarm(E_HIGH_VIBRATION, 1);
			Delay_ms(1000);
			vibration_high_flag = 1;
		}
	}
	else
	{
		if(vibration_high_flag == 1)
		{
			set_alarm(E_HIGH_VIBRATION, 0);
			vibration_high_flag = 0;
		}
	}
}

