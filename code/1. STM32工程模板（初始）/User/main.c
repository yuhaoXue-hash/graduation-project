#include "stm32f10x.h"                  // Device header
#include "oled.h"

int main(void)
{
	
	OLED_Init();
	
	OLED_ShowString(1, 1, "1234567890123456789012345678901234567890");
	
	while(1)
	{
	
	}
}
