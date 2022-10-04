/*
 * ADC_config.h
 *
 *  Created on: May 31, 2022
 *      Author: Omar Mansour
 */

#ifndef INC_ADC_CONFIG_H_
#define INC_ADC_CONFIG_H_
#define POLLING 0
typedef enum resolution {
		resoltion_12,
		resoltion_10,
		resoltion_8 ,
		resoltion_6
	}resolution;

typedef enum conversionMode {
	single_mode,
	continous_mode

}conversionMode;



typedef struct ADCConfigType{
	resolution resolution ;
	conversionMode conversion_mode;
	char ReferenceVoltage;

} ADCConfigType;






void ADC_Init(ADCConfigType * configParamPtr);
void ADC_StartConv(unsigned char ChannelNum);
void ADC_GETConversionState(unsigned char* ConversionStatePtr);
unsigned char ADC_ReadData(unsigned short int* DataPtr);

#endif /* INC_ADC_CONFIG_H_ */
