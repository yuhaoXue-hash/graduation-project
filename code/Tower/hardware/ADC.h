#ifndef __ADC_H_
#define __ADC_H_

#define  CALM				0		//Calm
#define  LIGHT_AIR			0.2		//Light air
#define  LIGHT_BREEZE		1.6		//Light breeze
#define  GENTLE_BREEZE  	3.4		//Gentle breeze
#define  MODERATE_BREEZE	5.5		//Moderate breeze
#define  FRESH_BREEZE		8.0		//Fresh breeze
#define  STRONG_BREEZE		10.8	//Strong breeze
#define	 NEAR_GALE			13.9	//Near gale
#define	 GALE				17.2	//Gale
#define	 STRONG_GALE		20.8	//Strong gale
#define	 STORM				24.5	//Storm
#define	 VIOLENT_STORM		28.5	//Violent storm
#define	 TYPHOON			32.7	//Typhoon

void wind_force_sensor_init(void);
uint16_t AD_GetValue(void);
void Wind_Force_Level_Display(float level);
void Get_Wind_Force(float *wind_force);
void Display_wind_force(float F);

#endif
