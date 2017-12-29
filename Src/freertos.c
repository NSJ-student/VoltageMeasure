/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2017 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "includes.h"

/* USER CODE BEGIN Includes */     

/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/

osThreadId defaultTaskHandle;
osThreadId ButtonTaskHandle;
osThreadId TouchTaskHandle;
osThreadId VoltTaskHandle;
osThreadId UartTaskHandle;
/*
osMessageQDef(VoltQueue, 16, draw_param_t);
osMessageQId  VoltQueue;
*/
static const GUI_ConstString MENU_str[] = {
	"Speed",
	"Measure",
	"Channel"
};

static const GUI_ConstString speed[] = {
	"50 ms/div",	// 1 
	"250 ms/div",	// 5
	"500 ms/div", 	// 10
	"2.5 s/div", 	// 50
	"5.0 s/div", 	// 100
	NULL 
};
static const int delay_s[] = {
	1,
	5,
	10,
	50,
	100
};

static const char * measure_c[] ={
	"Period",
	"Freq.",
	"Mean",
	"Channel"
};

static const GUI_ConstString Channel_check_str[] = {
	"CH1",
	"CH2",
};
static const GUI_ConstString Channel_btn_str[] = {
	"UP",
	"DN"
};


int AdcSpeed = 1;
int measure_ch=0;
int measure_sel[CHECKBOX_NUMBER];
int channel_sel[ADC_CHANNEL_NUM];
int graph_base[ADC_CHANNEL_NUM] = {YSIZE, YSIZE};
float mean[ADC_CHANNEL_NUM];
float freq[ADC_CHANNEL_NUM];
float period[ADC_CHANNEL_NUM];

//char	adc_char[50]={0};
//char	touch_char[50]={0};

/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/

extern void _ExecCalibration (void);
void StartDefaultTask(void const * argument);
void StartTButtonTask(void const * argument);
void StartTouchTask(void const * argument);
void StartVoltTask(void const * argument);
void StartUartTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
//  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
//  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);
  
  osThreadDef(touchTask, StartTouchTask, osPriorityHigh, 0, 256);
  TouchTaskHandle = osThreadCreate(osThread(touchTask), NULL);
  
  osThreadDef(buttonTask, StartTButtonTask, osPriorityAboveNormal, 0, 512);
  ButtonTaskHandle = osThreadCreate(osThread(buttonTask), NULL);

//  osThreadDef(uartTask, StartUartTask, osPriorityAboveNormal, 0, 512);
//  UartTaskHandle = osThreadCreate(osThread(uartTask), NULL);
  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
		osDelay(100);
	  /*
		LCD_Clear(Red);
		GUI_Text(132,104,"Open407V-C",White,Red);
		osDelay(100);
		
		LCD_Clear(Red);
		GUI_Text(60,120,"STM32F407V Development Board",White,Red);
		osDelay(100);
	  */
  }
  /* USER CODE END 5 */ 
}

void StartTouchTask(void const * argument)
{
//	uint16_t tempx=0,tempy=0;
//	uint32_t count=0;

  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
		GUI_TOUCH_Exec();
		osDelay(100);
	  /*
		getDisplayPoint(&display, Read_Ads7846(), &matrix );
	    TP_DrawPoint(display.x,display.y);
		if(tempx != display.x || tempy != display.y)
		{
			count++;
			sprintf(touch_char,"X:%3d,Y:%3d  ",tempx,tempy);
			GUI_Text(200,15,(uint8_t*)touch_char,Red,Black);
			tempx = display.x;
			tempy = display.y;
		}	
		osDelay(1);
	  */

	  // if(!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5))
	  {
	  }
  }
  /* USER CODE END 5 */ 
}



void StartUartTask(void const * argument)
{
	uint8_t recvBuf[100];
	int i = 0;
	/* USER CODE BEGIN 5 */
	/* Infinite loop */
	for(;;)
	{
		if(HAL_ERROR != HAL_UART_Receive(&huart4, recvBuf, 2, 1))
		{
			HAL_UART_Transmit(&huart4, recvBuf, 2, 0);
			HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
		}
		i++;
		if(i>10)
		{
			HAL_UART_Transmit(&huart4, "test", 4, 1);
			i=0;
		}
		osDelay(50);
	}
	/* USER CODE END 5 */ 
}

void StartTButtonTask(void const * argument)
{
	char temp[30];
	BUTTON_Handle   hMenuBtn[MENU_NUM];
	
	LISTBOX_Handle hListBox;
	
	RADIO_Handle hRadio;
	CHECKBOX_Handle hCheckBox[CHECKBOX_NUMBER];
	
	CHECKBOX_Handle hChannelCheckBox[2];
	BUTTON_Handle   hChannelBtn[2];
	int button_result;
	int speed_sel = 0;
	int led_on = 0;
	int delay = 100;
#if DEBUG_ENABLE == 1
	int pretime, curtime;
#endif
	int i;
		
	graph_axis_t axis = {0,6,0,5};
	GUI_HMEM hMem_ch1, hMem_ch2;
	draw_param_t draw;
	draw.axis = &axis;
	int value;
	
	hMem_ch1 = GUI_ALLOC_AllocZero(GRAPH_SIZE*GRAPH_STEP);
	hMem_ch2 = GUI_ALLOC_AllocZero(GRAPH_SIZE*GRAPH_STEP);
	draw.p.aY = (I16*)GUI_ALLOC_h2p(hMem_ch1);
	draw.p2.aY = (I16*)GUI_ALLOC_h2p(hMem_ch2);
	draw.p_num = 1;
	for (i=0; i < GRAPH_SIZE; i++)
	{
		*(draw.p.aY + i) = YSIZE;
		*(draw.p2.aY + i) = 0;
	}
	
   _ExecCalibration();
	
	for(i=0; i<MENU_NUM; i++)
	{
		hMenuBtn[i] = BUTTON_Create(MENU_BUTTON_LEFT, 
									MENU_BUTTON_TOP + i*MENU_BUTTON_H, 
									MENU_BUTTON_W, 
									MENU_BUTTON_H, 
									BUTTON_SPEED_ID+i,BUTTON_CF_SHOW );
		BUTTON_SetText (hMenuBtn[i], MENU_str[i]);
	}
	
   	hListBox = LISTBOX_Create(speed, 
							SPD_LISTBOX_LEFT, SPD_LISTBOX_TOP, 
							SPD_LISTBOX_W, SPD_LISTBOX_H, WM_CF_SHOW);
	LISTBOX_SetFont(hListBox, &GUI_Font13_ASCII);
	SCROLLBAR_CreateAttached(hListBox, SCROLLBAR_CF_VERTICAL);
	
	hRadio = RADIO_Create(CH_RADIO_LEFT, CH_RADIO_TOP, 
				CH_RADIO_W, CH_RADIO_H, WM_HBKWIN, 
				RADIO_CH1_ID+i, WM_CF_HIDE, ADC_CHANNEL_NUM);
	RADIO_SetBkColor(hRadio, GUI_RED);
	RADIO_SetFont(hRadio, &GUI_Font6x8);
	RADIO_SetText(hRadio, Channel_check_str[0], 0);
	RADIO_SetText(hRadio, Channel_check_str[1], 1);
	RADIO_SetValue(hRadio, 0);
	
	for(i=0; i<CHECKBOX_NUMBER; i++)
	{
		hCheckBox[i] = CHECKBOX_Create(MEASURE_CHECK_LEFT, 
					MEASURE_CHECK_TOP + MEASURE_CHECK_H*i, 
					MEASURE_CHECK_W, MEASURE_CHECK_H, 
					WM_HBKWIN, CHECKBOX_PERIOD_ID+i, WM_CF_HIDE);
		CHECKBOX_SetText(hCheckBox[i], measure_c[i]);
		CHECKBOX_SetBkColor(hCheckBox[i], GUI_RED);
		CHECKBOX_SetFont(hCheckBox[i], &GUI_Font13_ASCII);
	}
	
	for(i=0; i<2; i++)
	{
		hChannelCheckBox[i] = CHECKBOX_Create(
								CHANNEL_CHECK_LEFT, 
								CHANNEL_GAP*(i+1) + (CHANNEL_GAP+CHANNEL_CHECK_H)*i, 
								CHANNEL_CHECK_W, 
								CHANNEL_CHECK_H, 
								WM_HBKWIN, CHANNEL_CH1_CHECK_ID+i, WM_CF_HIDE);
		CHECKBOX_SetText (hChannelCheckBox[i], Channel_check_str[i]);
		CHECKBOX_SetBkColor(hChannelCheckBox[i], GUI_RED);
		CHECKBOX_SetFont(hChannelCheckBox[i], &GUI_Font13_ASCII);
	}
	
	for(i=0; i<2; i++)
	{
		hChannelBtn[i] =  BUTTON_Create( 
								CHANNEL_BTN_LEFT, 
								CHANNEL_GAP*(i+1) + (CHANNEL_GAP+CHANNEL_CHECK_H)*i,
								CHANNEL_BTN_W, 
								CHANNEL_BTN_H, 
								CHANNEL_UP_BTN_ID+i,WM_CF_HIDE );
		BUTTON_SetText (hChannelBtn[i], Channel_btn_str[i]);
	}
	
	WM_ExecIdle();
	
//    VoltQueue = osMessageCreate(osMessageQ(VoltQueue), NULL);
	osThreadDef(voltTask, StartVoltTask, osPriorityHigh, 0, 512);
	VoltTaskHandle = osThreadCreate(osThread(voltTask), &draw);
//	HAL_TIM_Base_Start_IT(&htim6);
	
#if DEBUG_ENABLE == 1
	pretime = GUI_X_GetTime();
	curtime = GUI_X_GetTime();
#endif
	
	/* Infinite loop */
	for(;;)
	{
		button_result = GUI_GetKey();
		//WM_ExecIdle();
		switch(button_result)
		{
			case BUTTON_SPEED_ID:
				if(!WM_IsVisible(hListBox))
				{
					WM_HideWindow(hRadio);
					for(i=0; i<CHECKBOX_NUMBER; i++)
					{
						WM_HideWindow(hCheckBox[i]);
					}
					for(i=0; i<2; i++)
					{
						WM_HideWindow(hChannelCheckBox[i]);
					}
					for(i=0; i<2; i++)
					{
						WM_HideWindow(hChannelBtn[i]);
					}
					WM_ShowWindow(hListBox);
					GUI_SetBkColor(GUI_RED);
					GUI_ClearRect(CHILD_LEFT, CHILD_TOP, 320, 60);
				}
				break;
			case BUTTON_MEASURE_ID:
				if(!WM_IsVisible(hCheckBox[0]))
				{
					WM_HideWindow(hListBox);
					for(i=0; i<2; i++)
					{
						WM_HideWindow(hChannelBtn[i]);
					}
					for(i=0; i<2; i++)
					{
						WM_HideWindow(hChannelCheckBox[i]);
					}
					WM_ShowWindow(hRadio);
					for(i=0; i<CHECKBOX_NUMBER; i++)
					{
						WM_ShowWindow(hCheckBox[i]);
					}
					GUI_SetBkColor(GUI_RED);
					GUI_ClearRect(CHILD_LEFT, CHILD_TOP, 320, 60);
				}
				break;
			case BUTTON_CHANNEL_ID:
				if(!WM_IsVisible(hChannelBtn[0]))
				{
					WM_HideWindow(hListBox);
					WM_HideWindow(hRadio);
					for(i=0; i<CHECKBOX_NUMBER; i++)
					{
						WM_HideWindow(hCheckBox[i]);
					}
					for(i=0; i<2; i++)
					{
						WM_ShowWindow(hChannelBtn[i]);
					}
					for(i=0; i<2; i++)
					{
						WM_ShowWindow(hChannelCheckBox[i]);
					}
					GUI_SetBkColor(GUI_RED);
					GUI_ClearRect(CHILD_LEFT, CHILD_TOP, 320, 60);
				}
				if(led_on)	led_on = 0;
				else		led_on = 1;
				break;
			case CHANNEL_UP_BTN_ID:
				graph_base[measure_ch] -= GRAPH_BASE_STEP;
				if(graph_base[measure_ch] < 0)
					graph_base[measure_ch] = 0;
				Draw_CH_Base(draw.p_num, graph_base[0], graph_base[1]);
				break;
			case CHANNEL_DN_BTN_ID:
				graph_base[measure_ch] += GRAPH_BASE_STEP;
				if(graph_base[measure_ch] > YSIZE)
					graph_base[measure_ch] = YSIZE;
				Draw_CH_Base(draw.p_num, graph_base[0], graph_base[1]);
				break;
		}
		
		if(WM_IsVisible(hListBox))
		{
			speed_sel = LISTBOX_GetSel(hListBox);
			AdcSpeed = delay_s[speed_sel];
		}
		
		if(WM_IsVisible(hRadio))
		{
			measure_ch = RADIO_GetValue(hRadio);
		}
		if(WM_IsVisible(hCheckBox[0]))
		{
			for(i=0; i<CHECKBOX_NUMBER; i++)
			{
				measure_sel[i] = CHECKBOX_IsChecked(hCheckBox[i]);
			}
		}
		
		if(WM_IsVisible(hChannelCheckBox[0]))
		{
			for(i=0; i<2; i++)
			{ 
				value = CHECKBOX_IsChecked(hChannelCheckBox[i]);
				if(value != channel_sel[i])
				{
					channel_sel[i] = value;
					draw.p_num = (channel_sel[1]<<1) | (channel_sel[0]);
					Draw_CH_Base(draw.p_num, graph_base[0], graph_base[1]);
				}
			}
		}
		
		if(led_on)
			HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
		//msg = evt.value.p;
		delay = Draw_Graph(&draw);
#if	DEBUG_ENABLE == 1
		curtime = GUI_X_GetTime();
		sprintf(temp,"disp: %d", curtime-pretime);
		GUI_Text(0,0,(uint8_t*)temp,Red,Black);
#endif
		
		GUI_SetFont(&GUI_Font6x8);
		GUI_SetColor(GUI_WHITE);
		GUI_SetBkColor(GUI_BLACK);
		
		for(i=0;i<CHECKBOX_NUMBER;i++)
		{
			if(measure_sel[i])
			{
				switch(i)
				{
					case 0:
						sprintf(temp, "%s: TBD", measure_c[i]);
						break;
					case 1:
						sprintf(temp, "%s: TBD", measure_c[i]);
						break;
					case 2:
						sprintf(temp, "%s: %1.2f", measure_c[i], mean[measure_ch]);
						break;
					case 3:
						if(channel_sel[measure_ch])
							sprintf(temp, "%s: %d", measure_c[i], measure_ch+1);
						else
							sprintf(temp, "%s: X", measure_c[i]);
						break;
				}
				GUI_DispStringAt(temp, i*GRAPH_MEASURE_WIDTH, GRAPH_MEASURE_TOP);
			}
			else
			{
				GUI_ClearRect(i*GRAPH_MEASURE_WIDTH, GRAPH_MEASURE_TOP, 
								(i+1)*GRAPH_MEASURE_WIDTH, GRAPH_MEASURE_TOP+8);
			}
		}
#if	DEBUG_ENABLE == 1
		pretime = GUI_X_GetTime();
#endif
		GUI_Delay(delay);
	}
}

void StartVoltTask(void const * argument)
{
#if	DEBUG_ENABLE == 1
	char temp[30];
	int pretime, curtime;
#endif
	float AD_value_ch1, AD_value_ch2;
	unsigned int ADC_ConvertedValue_pre_ch1=0, ADC_ConvertedValue_pre_ch2=0;
	volatile unsigned int ADC_ConvertedValue_ch1=0, ADC_ConvertedValue_ch2=0;
	
	draw_param_t * pDraw = (draw_param_t *)argument;
	I16 * pMem[ADC_CHANNEL_NUM];
	
#if	DEBUG_ENABLE == 1
	int sample_count = 0;
#endif
	int subs;
	int raw_data_ch1, raw_data_ch2;
	float graph_alpha = (YSIZE)/(GRAPH_Y_STEP);
	int i;
  /* USER CODE BEGIN 5 */
	
	//GUIDEMO_Graph();
//	Init_FFT();
	Graph_Init("VoltageMeter", (pDraw->axis));
	
	pMem[0] = pDraw->p.aY;
	pMem[1] = pDraw->p2.aY;
	
  /* Infinite loop */
	for(;;)
	{
		//HAL_ADC_Start_DMA(&hadc1, &ADC_ConvertedValue,  1);
		if(channel_sel[0])
		{
			HAL_ADC_Start(&hadc1);
			if(HAL_ADC_PollForConversion(&hadc1, 10000) == HAL_OK)
			{
				ADC_ConvertedValue_ch1 = HAL_ADC_GetValue(&hadc1);
			}
			if(ADC_ConvertedValue_ch1 != ADC_ConvertedValue_pre_ch1)
			{
				ADC_ConvertedValue_pre_ch1 = ADC_ConvertedValue_ch1;
				AD_value_ch1 = (ADC_ConvertedValue_ch1*3.3/4096);
				subs = AD_value_ch1*graph_alpha;
				raw_data_ch1 = graph_base[0] - subs;
			}
			/*
			for(i=0;i<255;i++)
			{
				Input_test[i] = Input_test[i+1];
			}
			Input_test[255] = AD_value_ch1;
			*/
			memmove(pMem[0], (I16 *)pMem[0]+1, (GRAPH_SIZE-1)*GRAPH_STEP);
			*((I16 *)pMem[0] + GRAPH_SIZE-1) = raw_data_ch1;
		}
		if(channel_sel[1])
		{
			HAL_ADC_Start(&hadc2);
			if(HAL_ADC_PollForConversion(&hadc2, 10000) == HAL_OK)
			{
				ADC_ConvertedValue_ch2 = HAL_ADC_GetValue(&hadc2);
			}
			if(ADC_ConvertedValue_ch2 != ADC_ConvertedValue_pre_ch2)
			{
				ADC_ConvertedValue_pre_ch2 = ADC_ConvertedValue_ch2;
				AD_value_ch2 = (ADC_ConvertedValue_ch2*3.3/4096);
				subs = AD_value_ch2*graph_alpha;
				raw_data_ch2 = graph_base[1] - subs;
			}
			memmove(pMem[1], (I16 *)pMem[1]+1, (GRAPH_SIZE-1)*GRAPH_STEP);
			*((I16 *)pMem[1] + GRAPH_SIZE-1) = raw_data_ch2;
			
//			mean[1] = Measure_FFT(pMem[0], pMem[1], 256);
		}
		
		if(measure_sel[2])
		{
			mean[measure_ch] = Measure_Mean(pMem[measure_ch], GRAPH_SIZE, 
									graph_base[measure_ch], graph_alpha);
		}
		
#if	DEBUG_ENABLE == 1
		sample_count++;
		if(sample_count >= 50)
		{
			sample_count = 0;
			curtime = GUI_X_GetTime();
			sprintf(temp,"adc: %d  ", curtime-pretime);
			GUI_Text(90,0,(uint8_t*)temp,Red,Black);
			pretime = GUI_X_GetTime();
		}
#endif
		osDelay(AdcSpeed);
	}
  /* USER CODE END 5 */ 
}

/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
