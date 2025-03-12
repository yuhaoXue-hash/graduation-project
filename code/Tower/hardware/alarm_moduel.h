#ifndef __ALARM_MODUEL_H_
#define __ALARM_MODUEL_H_

typedef enum alarm_type
{
	E_HIGH_VIBRATION,		//高震动
	E_HIGH_WIND,			//风力过强
	E_HIGH_CRANE_ACCEL,		//加速度过大
	E_ALARM_TYPE_MAX
}ALARM_TYPE_t;

void set_alarm(ALARM_TYPE_t type, uint8_t enable);
uint8_t alarm_process(void);

#endif
