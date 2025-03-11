#include "stm32f10x.h"                  // Device header
#include "alarm_moduel.h"
#include "oled.h"
#include "BUZZER.h"
#include "delay.h"

static uint8_t vibration_flag = 0;
static uint8_t wind_flag = 0;
static uint8_t crane_accel = 0;
static uint8_t alarm_num = 0;

static uint8_t cur_alarm_flag = 0;

void set_alarm(ALARM_TYPE_t type, uint8_t enable)
{
	switch(type)
	{
		case E_HIGH_VIBRATION:
			vibration_flag = enable;
			break;
		
		case E_HIGH_WIND:
			wind_flag = enable;
			break;
		
		case E_HIGH_CRANE_ACCEL:
			crane_accel = enable;
			break;
		
		default:	
			return;		
	}
	
	if(enable == 1)
	{
		if(alarm_num < 3)
		{
			alarm_num++;
		}
	}
	else if(enable == 0)
	{
		if(alarm_num > 0)
		{
			alarm_num--;
		}
	}	
}
	
uint8_t alarm_process(void)
{	
	uint8_t temp = alarm_num;
	
	if(alarm_num == cur_alarm_flag)
	{
		return alarm_num;
	}
	else 
	{
		cur_alarm_flag = alarm_num;
	}
	
	if(temp > 0)
	{
		BUZZER_On();
		OLED_Clear();
		OLED_ShowString(1, 4, "Danger!!!");
			
		if(vibration_flag == 1)
		{
			OLED_ShowString((alarm_num-temp)+1, 1, "High Vibration");
			temp--;
		}
		if(wind_flag == 1)
		{
			OLED_ShowString((alarm_num-temp)+1, 1, "High Wind");
			temp--;
		}
		if(crane_accel == 1)
		{
			OLED_ShowString((alarm_num-temp)+1, 1, "Crane Accel Alarm");
			temp--;
		}
	}
	else if(temp == 0)
	{
		BUZZER_Off();
		OLED_Clear();
	}
	
	return alarm_num;
}	
