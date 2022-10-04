#include "ADC_config.h"
#include "gpio.h"
#include "LCD.h"
#include <stm32f4xx.h>




 /*
  * -------------------------------------
  * This function is to initialize the configuration of ADC
  * -------------------------------------
  */
void ADC_Init(ADCConfigType * configParamPtr){
 /*
  * -------------------------------------
  * Make Pin0 as analog mode  & enable ADC clock
  * -------------------------------------
  */
	GPIOB -> MODER |=(1u<<0);
	GPIOB -> MODER |=(1u<<1);
	RCC -> APB2ENR |=(1u<<8);

 /*
  * -----------------------------------------
  * configure resolution
  * -----------------------------------------
  */
	resolution resolution = configParamPtr -> resolution ;
	switch (resolution){
		case resoltion_12:
			ADC1 -> CR1 &= ~(1u << 24);
			ADC1 -> CR1 &= ~(1u << 25);
			break;
		case 	resoltion_10:
			ADC1 -> CR1 |= (1u << 24);
			ADC1 -> CR1 &= ~(1u << 25);
			break;
		case resoltion_8:
			ADC1 -> CR1 &= ~(1u << 14);
			ADC1 -> CR1 |= (1u << 15);
			break;
		case 	resoltion_6:
			ADC1 -> CR1 |= (1u << 14);
			ADC1 -> CR1 |= (1u << 15);
			break;
		default:
			ADC1 -> CR1 &= ~(1u << 14);
			ADC1 -> CR1 &= ~(1u << 15);
	}

	 /*
	  * -----------------------------------------
	  * configure conversion mode
	  * -----------------------------------------
	  */

	conversionMode conversion_mode = configParamPtr ->conversion_mode;
	switch (conversion_mode){
		case single_mode:
			ADC1 -> CR2 &= ~(1u <<1);
			break;
		case continous_mode:
			ADC1 -> CR2 |= (1u <<1);
			break;
		default :
			ADC1 -> CR2 &= ~(1u <<1);
	}

	 /*
	  * -----------------------------------------
	  * configure reference voltage and temp
	  * -----------------------------------------
	  */
 /*char referenceVoltage = configParamPtr -> ReferenceVoltage;

			if(referenceVoltage)
				ADC -> CCR |= (1u<<23);
			else
				ADC -> CCR &= ~(1u<<23);

			GPIOB -> MODER |=(1u<<0);
			GPIOB -> MODER |=(1u<<1);
			RCC -> APB2ENR |=(1u<<8);
*/
	 	 /*
		  * -----------------------------------------
		  * In Case of interrupt -> Enable EOCIE bit & enable ADC interrupt using NVIC
		  * -----------------------------------------
		  */
			if(!POLLING){
				ADC1->CR1 |=(1u<<5);
				NVIC ->ISER[0] |= (1u<<18);
			}


}

/*
 * -------------------------------------
 * This Function is to setup the channel to be converted & To start conversion
 * -------------------------------------
 */
void ADC_StartConv(unsigned char ChannelNum){
	/*
	 *  ADON = 1
	 */
	ADC1 -> CR2 |= (1u<<0);


	/*
	 * make Channel number as 1st conversion
	 */

	ADC1 -> SQR3 |=(ChannelNum<<0);  // 0000100

	/*
	 * SWSTART: Start conversion of regular channels
	 */
	ADC1 -> CR2 |= (1u<<30);



}

/*
 * -------------------------------------
 *This function is to check whether the ADC is ended or not
 *This function is enabled only in case of polling==1
 * -------------------------------------
 */
#if (POLLING==1)
	void ADC_GETConversionState(unsigned char* ConversionStatePtr){

		*ConversionStatePtr = (ADC1 -> SR & (1u<<1)) ? 1 : 0;


	}
#endif

	 /*
	  * -------------------------------------
	  * This function is to read data and return 0 in case of the conversion is done
	  * -------------------------------------
	  */
unsigned char ADC_ReadData(unsigned short int* DataPtr){

	if((ADC1-> SR & (1u<<1))){      00000010                 1
		*DataPtr = ADC1 ->DR;		10101000

		return 0;
	}

	else
		return 1;

}





