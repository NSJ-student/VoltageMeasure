
#ifndef _MEASURE_H_
#define _MEASURE_H_

#include <GUI.h>
#include "LCD_ConfDefaults.h"      /* valid LCD configuration */
#include "WMDemo/uCGUI_User_Graph.h"

float Measure_Mean(I16 * data, int size, int base, float graph_alpha);
void Init_FFT(void);
unsigned int Measure_FFT(I16 * Input, I16 * Output, int size);

extern float Input_test[512];
extern float Output_test[256];

#endif
