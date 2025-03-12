#include "stm32f10x.h"                  // Device header
#include "ADXL345.h"
#include "oled.h"
#include "delay.h"

int main(void)
{
	float angleX, angleY, angleZ;
	
	OLED_Init();
	ADXL345_init(); // 初始化
	
	while(1) 
	{
		get_angle(&angleX, &angleY, &angleZ);   // 获取三轴偏移角度
		OLED_ShowSignedNum(1, 1, angleX, 4);
		OLED_ShowSignedNum(2, 1, angleY, 4);
		OLED_ShowSignedNum(3, 1, angleZ, 4);
		Delay_ms(1000);//
	}
}
