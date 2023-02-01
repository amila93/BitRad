/*******************************************************************************
  * File Name          : buzzer.c
  * Description        : Includes functions to drive a buzzer/speaker.
  *
  * Author             : Amila Udara Abeygunasekara
  * Date               : 2022-03-05
  ******************************************************************************
  */
#include "buzzer.h"
#include "pwm_utils.h"
#include "tim.h"
#include <stdio.h>

// Private definitions
#define TONE_DUTY_CYCLE         50
#define BUZZER_CHANNEL          TIM_CHANNEL_4
#define BUZZER_CH_COMPLIMENT    0

void coldStart(void);

static TimerParams buzzerParams = { 0 };

static uint8_t isInitialized = 0;

static uint16_t _freqHz = 100;

// FUNCTION      : initBuzzer
// DESCRIPTION   :
//    Initialize the buzzer by initializing timer parameters. It is mandatory
//    to call this function before using other functions in this file.
// PARAMETERS    : None
// RETURNS       : None
void initBuzzer(void)
{
  buzzerParams.timerHandle = &htim1;
  buzzerParams.timerChannel = BUZZER_CHANNEL;
  buzzerParams.isComplimentary = BUZZER_CH_COMPLIMENT;
  buzzerParams.clockFrequencyHz = HAL_RCC_GetPCLK2Freq();

  isInitialized = 1;
}

// FUNCTION      : buzzerOn
// DESCRIPTION   : Sound the buzzer with a desired frequency.
// PARAMETERS    :
//    uint16_t freqHz : Ringing frequency in Hertz.
// RETURNS       : None
void buzzerOn(uint16_t freqHz)
{
  if(!isInitialized)
  {
    printf("[buzzer::buzzerOn] Error! Buzzer is not initialized.\r\n");
    return;
  }

  startPwmOutput(&buzzerParams);
  updateBuzzerFrequency(freqHz);
}

// FUNCTION      : buzzerOff
// DESCRIPTION   : Turn off the buzzer.
// PARAMETERS    : None
// RETURNS       : None
void buzzerOff(void)
{
  if(!isInitialized)
  {
    printf("[buzzer::buzzerOff] Error! Buzzer is not initialized.\r\n");
    return;
  }

  stopPwmOutput(&buzzerParams);
}

// FUNCTION      : updateBuzzerFrequency
// DESCRIPTION   : Update the buzzer frequency on the fly.
// PARAMETERS    :
//    uint16_t freqHz : New frequency in Hertz.
// RETURNS       : None
void updateBuzzerFrequency(uint16_t freqHz)
{
  if(!isInitialized)
  {
    printf("[buzzer::updateBuzzerFrequency] Error! Buzzer is not initialized.\r\n");
    return;
  }

  _freqHz = freqHz;

  // Dynamically update the frequency and the duty cycle of the PWM signal
  updatePwmSignal(&buzzerParams, _freqHz, TONE_DUTY_CYCLE);
}

void muteBuzzer()
{
  if(!isInitialized)
  {
    printf("[buzzer::muteBuzzer] Error! Buzzer is not initialized.\r\n");
    return;
  }

  updatePwmSignal(&buzzerParams, _freqHz, 0);
}

void unMuteBuzzer()
{
  if(!isInitialized)
  {
    printf("[buzzer::unMuteBuzzer] Error! Buzzer is not initialized.\r\n");
    return;
  }

  updatePwmSignal(&buzzerParams, _freqHz, TONE_DUTY_CYCLE);
}
