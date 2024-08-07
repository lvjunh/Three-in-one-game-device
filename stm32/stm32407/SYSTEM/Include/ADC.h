#ifndef __ADC_H
#define __ADC_H

#include <sys.h>
void AD_Init(void);
uint16_t Get_Battery_Voltage(uint8_t ch);
uint16_t Get_Adc_Average(uint8_t ch,uint8_t times);

#endif
