/*
 * error_led.c
 *
 *  Created on: Mar 29, 2023
 *      Author: Amila Abeygunasekara
 */
#include "error_led.h"
#include "pwm_utils.h"
#include "tim.h"
#include <stdio.h>

#define LED_CHANNEL          TIM_CHANNEL_4
#define LED_CH_COMPLIMENT    0
#define LED_DUTY_CYCLE_ON    50
#define LED_DUTY_CYCLE_OFF   0
#define DEFAULT_FREQUENCY_HZ 100
#define BLINK_FREQUENCY_HZ   2

typedef enum
{
  ON,
  BLINK,
  OFF
} ErrLedState;

static TimerParams ledParams = { 0 };
static uint8_t isInitialized = 0;
static ErrLedState currentLedState = OFF;

static void setCurrentLedState(ErrLedState state);

void initErrorLed(void)
{
  ledParams.timerHandle = &htim1;
  ledParams.timerChannel = LED_CHANNEL;
  ledParams.isComplimentary = LED_CH_COMPLIMENT;
  ledParams.clockFrequencyHz = HAL_RCC_GetPCLK2Freq();

  startPwmOutput(&ledParams);

  isInitialized = 1;
}

void errorLedOn(void)
{
  if(!isInitialized)
  {
    printf("\r[error_led::errorLedOn] Error! ErrorLed is not initialized.\n");
    return;
  }

  if (currentLedState != ON)
  {
    updatePwmSignal(&ledParams, DEFAULT_FREQUENCY_HZ, LED_DUTY_CYCLE_ON);
    setCurrentLedState(ON);
  }
}

void errorLedOff(void)
{
  if(!isInitialized)
  {
    printf("\r[error_led::errorLedOff] Error! ErrorLed is not initialized.\n");
    return;
  }

  if (currentLedState != OFF)
  {
    updatePwmSignal(&ledParams, DEFAULT_FREQUENCY_HZ, LED_DUTY_CYCLE_OFF);
    setCurrentLedState(OFF);
  }
}

void errorLedBlink(void)
{
  if(!isInitialized)
  {
    printf("\r[error_led::updateErrorLedFrequency] Error! ErrorLed is not initialized.\n");
    return;
  }

  if (currentLedState != BLINK)
  {
    startPwmOutput(&ledParams);
    updatePwmSignal(&ledParams, BLINK_FREQUENCY_HZ, LED_DUTY_CYCLE_ON);

    setCurrentLedState(BLINK);
  }
}

void setCurrentLedState(ErrLedState state)
{
  printf("\r[error_led::setCurrentLedState] Setting state: %d\n", state);
  currentLedState = state;
}

void deinitErrorLed(void)
{
  stopPwmOutput(&ledParams);
  isInitialized = 0;
}
