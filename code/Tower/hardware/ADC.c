#include "stm32f10x.h"                  // Device header
#include "ADC.h"
#include "oled.h"
#include "stdio.h"
#include "key.h"
#include "alarm_moduel.h"

#define   Wind_Sensor_CLK	 (RCC_APB2Periph_GPIOA)
#define   Wind_Sensor_PORT   (GPIOA)
#define   Wind_Sensor_PIN	 (GPIO_Pin_0)

extern int warning_flag;

static uint8_t display_type = 0;
static uint8_t wind_high_flag = 0; 

void ADC1_Init(void)
{
	RCC_APB2PeriphClockCmd(Wind_Sensor_CLK, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStruct.GPIO_Pin = Wind_Sensor_PIN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(Wind_Sensor_PORT, &GPIO_InitStruct);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	
	ADC_InitTypeDef ADC_InitStruct;
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStruct.ADC_NbrOfChannel = 1;
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;
	ADC_Init(ADC1, &ADC_InitStruct);
	
	ADC_Cmd(ADC1, ENABLE);
	
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1) == SET);
	ADC_GetResetCalibrationStatus(ADC1);
	while(ADC_GetCalibrationStatus(ADC1) == SET);
}

uint16_t AD_GetValue(void)
{
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	while(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
	return ADC_GetConversionValue(ADC1);
}

void Wind_Force_Level_Display(float level)
{
	char wind_level[16] = {0};
		
	if(level <= LIGHT_AIR)
	{
		sprintf(wind_level, "%s", "Calm");
	}
	else if(level > LIGHT_AIR && level <= LIGHT_BREEZE)
	{
		sprintf(wind_level, "%s", "Light air");
	}
	else if(level > LIGHT_BREEZE && level <= GENTLE_BREEZE)
	{
		sprintf(wind_level, "%s", "Light breeze");
	}
	else if(level > GENTLE_BREEZE && level <= MODERATE_BREEZE)
	{
		sprintf(wind_level, "%s", "Gentle breeze");
	}
	else if(level > MODERATE_BREEZE && level <= FRESH_BREEZE)
	{
		sprintf(wind_level, "%s", "Moderate breeze");
	}
	else if(level > FRESH_BREEZE && level <= STRONG_BREEZE)
	{
		sprintf(wind_level, "%s", "Fresh breeze");
	}
	else if(level > STRONG_BREEZE && level <= NEAR_GALE)
	{
		sprintf(wind_level, "%s", "Strong breeze");
	}
	else if(level > NEAR_GALE && level <= GALE)
	{
		sprintf(wind_level, "%s", "Near gale");
	}
	else if(level > GALE && level <= STRONG_GALE)
	{
		sprintf(wind_level, "%s", "Gale");
	}
	else if(level > STRONG_GALE && level <= STORM)
	{
		sprintf(wind_level, "%s", "Strong gale");
	}
	else if(level > STORM && level <= VIOLENT_STORM)
	{
		sprintf(wind_level, "%s", "Storm");
	}
	else if(level > VIOLENT_STORM && level <= TYPHOON)
	{
		sprintf(wind_level, "%s", "Violent storm");
	}
	else if(level > TYPHOON)
	{
		sprintf(wind_level, "%s", "Typhoon");
	}
	OLED_ShowString(2, 1, "Lv:");
	OLED_ShowString(2, 4, wind_level);
}

void Get_Wind_Force(float *wind_force)
{
	int i = 0;
	float sum = 0;
	uint16_t ADC_Value = 0;					//ADC采样值
	float F = 0;          					//风速
	
	for(i = 0; i < 10; i++)
	{
		ADC_Value = AD_GetValue();
		sum += ADC_Value;
		F = 0.027 * (sum / 10);
	}
	
	if(F > STRONG_BREEZE)
	{
		if(wind_high_flag == 0)
		{
			set_alarm(E_HIGH_WIND, 1);
			wind_high_flag = 1;
		}
	}
	else
	{
		if(wind_high_flag == 1)
		{
			set_alarm(E_HIGH_WIND, 0);
			wind_high_flag = 0;
		}
	}
}

void Display_wind_force(float F)
{
	int row = 2, line = 1;
	
	if(key_scan() == 1)
	{
		display_type = ~display_type;
		OLED_Clear();
	}
	if(display_type)
	{
		OLED_ShowString(row, line, "speed:");
		OLED_ShowNum(row, line+6, F, 2);
		OLED_ShowChar(row, line+8, '.');
		OLED_ShowNum(row, line+9, (int)(F*100)%100, 2);
	}
	else 
	{
		Wind_Force_Level_Display(F);
	}
}
