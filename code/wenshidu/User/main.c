#include "stm32f10x.h"                  // Device header
#include "string.h"
#include "delay.h"
#include "oled.h"
#include "Serial.h"

extern uint8_t Serial_RxData[64];
extern uint8_t Serial_RxFlag;
	
int main(void)
{
	uint8_t humidity[5] = {0,0,0,0,'%'};
	uint8_t temperature[5] = {0};
	
	OLED_Init();
	USART1_init();
	
	USART1_Send_String("Hand\r\n");
	
	while(1)
	{
		USART1_Send_String("Read\r\n");
		if(Serial_RxFlag == 2)
		{	
			
			memcpy(humidity, &Serial_RxData[3], 4);
			memcpy(temperature, &Serial_RxData[11], 5);
		
			OLED_ShowString(3, 1, "humi:");
			OLED_ShowString(4, 1, "temp:");
			OLED_ShowString(3, 6, (char *)humidity);
			OLED_ShowString(4, 6, (char *)temperature);
			
			Serial_RxData_clear();
			Serial_RxFlag = 0;
		}
	}
}
