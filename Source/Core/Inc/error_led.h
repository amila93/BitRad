/*
 * error_led.h
 *
 *  Created on: Mar 29, 2023
 *      Author: Amila Abeygunasekara
 */

#ifndef INC_ERROR_LED_H_
#define INC_ERROR_LED_H_

#include <stdint.h>

void initErrorLed(void);
void errorLedOn(void);
void errorLedOff(void);
void updateErrorLedFrequency(uint16_t freqHz);

#endif /* INC_ERROR_LED_H_ */
