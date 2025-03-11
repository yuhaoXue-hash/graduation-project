#include "stm32f10x.h"                  // Device header
#include "string.h"
#include "delay.h"
#include "oled.h"
#include "Serial.h"
#include "BUZZER.h"
#include "SW1801.h"
#include "adc.h"
#include "adxl345.h"
#include "key.h"
#include "alarm_moduel.h"

int main(void)
{	
	uint8_t ret = 0;
	uint8_t humidity[5] = {0,0,0,0,'%'};
	uint8_t temperature[5] = {0};
	float wind_force = 0;
	float x_angle = 0;
	float y_angle = 0;
	float z_angle = 0;
	
	OLED_Init();
	USART1_init();
	SW1801_Init();
	BUZZER_Init();
	ADC1_Init();
	ADXL345_init(); 
	key_Init();
		
	while(1)
	{
		Get_temperature_humidity((char *)humidity, (char *)temperature);
		Get_vibration_value();
		Get_Wind_Force(&wind_force);
		Get_Angle_Value(&x_angle,&y_angle,&z_angle);
		
		ret = alarm_process();	//监测报警程序 
		
		//*****若未触发报警则正常执行显示功能****//
		if(ret == 0)			
		{
			Display_Angle_Value(x_angle,y_angle,z_angle);
			Display_temperature_humidity((char *)humidity, (char *)temperature);
			Display_wind_force(wind_force);
		}
	}
}
