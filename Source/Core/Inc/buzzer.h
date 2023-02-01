/*******************************************************************************
  * File Name          : buzzer.h
  * Description        : Includes functions to drive a buzzer/speaker.
  *
  * Author             : Amila Udara Abeygunasekara
  * Date               : 2022-03-05
  ******************************************************************************
  */
#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include <stdint.h>

void initBuzzer(void);

void buzzerOn(uint16_t freqHz);
void buzzerOff(void);

void updateBuzzerFrequency(uint16_t freqHz);
void muteBuzzer();
void unMuteBuzzer();

#endif /* INC_BUZZER_H_ */
