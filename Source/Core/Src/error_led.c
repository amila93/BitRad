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
#define LED_DUTY_CYCLE       100
#define DEFAULT_FREQUENCY_HZ 100

static TimerParams ledParams = { 0 };
static uint8_t isInitialized = 0;

void initErrorLed(void)
{
  ledParams.timerHandle = &htim1;
  ledParams.timerChannel = LED_CHANNEL;
  ledParams.isComplimentary = LED_CH_COMPLIMENT;
  ledParams.clockFrequencyHz = HAL_RCC_GetPCLK2Freq();

  isInitialized = 1;
}

void errorLedOn(void)
{
  if(!isInitialized)
  {
    printf("[error_led::errorLedOn] Error! ErrorLed is not initialized.\r\n");
    return;
  }

  startPwmOutput(&ledParams);
  updateErrorLedFrequency(DEFAULT_FREQUENCY_HZ);
}

void errorLedOff(void)
{
  if(!isInitialized)
  {
    printf("[error_led::errorLedOff] Error! ErrorLed is not initialized.\r\n");
    return;
  }

  stopPwmOutput(&ledParams);
}

void updateErrorLedFrequency(uint16_t freqHz)
{
  if(!isInitialized)
  {
    printf("[error_led::updateErrorLedFrequency] Error! ErrorLed is not initialized.\r\n");
    return;
  }

  // Dynamically update the frequency and the duty cycle of the PWM signal
  updatePwmSignal(&ledParams, freqHz, LED_DUTY_CYCLE);
}
