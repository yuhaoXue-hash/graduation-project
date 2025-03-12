#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "delay.h"
#include "SW1801.h"
#include "BUZZER.h"


int main(void)
{
	
	OLED_Init();
	SW1801_Init();
	BUZZER_Init();
	
	while(1)
	{
		if(Get_vibration_value() == 1)
		{
			BUZZER_On();
			Delay_ms(100);
			BUZZER_Off();
		}
	}
}
