/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/

#include "ADC_config.h"
#include "LCD.h"
#include <stm32f4xx.h>
			
#define Channel_8 8
int main(void)
{
//	initialize LCD bins
	LCD_Init();
	LCD_DisplayString("Welcome To Final");
	LCD_MoveCursor(1,5);
	LCD_DisplayString("Project");

/*
 * ----------------------------
 *  instantiate structure of type ADCConfigType
 * ----------------------------
 */
	ADCConfigType configParam;
//	initialize elements of configParam structure
	configParam.resolution = resoltion_12;
	configParam.conversion_mode = single_mode;
	configParam.ReferenceVoltage = 0;

/*
 * ADC_Init function needs pointer to structure
 * so, create a pointer that points to the address of configParam
 */
	ADCConfigType * configParamPtr = &configParam;
	ADC_Init(configParamPtr);

//	start conversion
	ADC_StartConv(Channel_8);

	/*
	 * create variable and make pointer that hold the address of that variable in order to pass
	   this ptr to function that need ptr as parameter.
	 */
	unsigned char conversionState;
	unsigned char* ConversionStatePtr = &conversionState;


	/*
	 * create variable and make pointer that hold the address of that variable in order to pass
 	 this ptr to function that need ptr as parameter.
	 */
	unsigned short int data;
	unsigned short int* DataPtr = &data;

	int Temp;
#if (POLLING==1)
	while(1){


		ADC_GETConversionState(ConversionStatePtr);

		if(conversionState){
			ADC_ReadData(DataPtr);
			LCD_ClearScreen();
			Temp = (int)((data/(1.5f * 4095.0f)) * 5 * 150);
			LCD_DisplayString("Temp Now Is: ");
			LCD_MoveCursor(1,7);
			LCD_DisplayString("\"");
			LCD_IntToStr(Temp);
			LCD_DisplayString("\"");

		}

	}
#endif

}

void ADC_IRQHandler (void){

	unsigned short int dataFromDR = ADC1 -> DR;
	LCD_ClearScreen();
	int Temperature = (int)((dataFromDR/(1.5f * 4095.0f)) * 5 * 150);
	LCD_DisplayString("Temp Now Is: ");
	LCD_MoveCursor(1,7);
	LCD_DisplayString("*");
	LCD_IntToStr(Temperature);
	LCD_DisplayString("*");

}
