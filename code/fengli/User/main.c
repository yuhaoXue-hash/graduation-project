#include "stm32f10x.h"                  // Device header
#include "oled.h"
#include "delay.h"
#include "ADC.h"

int main(void)
{
	uint16_t ADC_Value = 0;			//ADC采样值
	float F = 0;          			//风速
	
	OLED_Init();
	ADC1_Init();
	
	
	while(1)
	{
		ADC_Value = AD_GetValue();
		F = 0.027 * ADC_Value;
		OLED_ShowNum(1, 1, F, 2);
		OLED_ShowChar(1, 3, '.');
		OLED_ShowNum(1, 4, (int)(F*100)%100, 2);
 
	}
}
