/*******************************************************************************
  * File Name          : pwm_utils.c
  * Description        : Includes utility functions to handle PWM signals.
  *
  * Author             : Amila Udara Abeygunasekara
  * Date               : 2022-02-27
  ******************************************************************************
  */
#include "pwm_utils.h"
#include <stdio.h>

#define TIM_CLOCK_DIVIDER 100000

// FUNCTION      : startPwmOutput
// DESCRIPTION   :
//    Starts PWM signal generation on the normal or complimentary output.
// PARAMETERS    :
//    TimerParams* params : Parameters related to the timer including
//                          TIM time base handle structure, TIM channel, and
//                          clock (APBx) frequency.
// RETURNS       : None
void startPwmOutput(TimerParams* params)
{
  // Checking if the output channel is complimentary (i.e., TIMx_CHxN)
  if (params->isComplimentary)
  {
    HAL_TIMEx_PWMN_Start_IT(params->timerHandle, params->timerChannel);
  }
  else
  {
    HAL_TIM_PWM_Start_IT(params->timerHandle, params->timerChannel);
  }
}

// FUNCTION      : stopPwmOutput
// DESCRIPTION   :
//    Stops PWM signal generation on the normal or complimentary output.
// PARAMETERS    :
//    TimerParams* params : Parameters related to the timer including
//                          TIM time base handle structure, TIM channel, and
//                          clock (APBx) frequency.
// RETURNS       : None
void stopPwmOutput(TimerParams* params)
{
  if (params->isComplimentary)
  {
    HAL_TIMEx_PWMN_Stop_IT(params->timerHandle, params->timerChannel);
  }
  else
  {
    HAL_TIM_PWM_Stop_IT(params->timerHandle, params->timerChannel);
  }
}

// FUNCTION      : updatePwmSignal
// DESCRIPTION   :
//    Update the frequency and the duty cycle of a running PWM signal on-the-fly
//    by updating TIMx_ARR and TIMx_CCRx registers.
// PARAMETERS    :
//    TimerParams* params : Parameters related to the timer including
//                          TIM time base handle structure, TIM channel, and
//                          clock (APBx) frequency.
//    uint32_t freqHz     : Frequency value in Hertz.
//    uint8_t dutyCycle   : Duty cycle value as a percentage.
//                          E.x., For a 50% duty cycle, dutyCycle = 50.
// RETURNS       : None
void updatePwmSignal(TimerParams* params, uint32_t freqHz, uint8_t dutyCycle)
{
  if (freqHz > params->clockFrequencyHz || dutyCycle > 100 /* 100% */)
  {
	printf("[updatePwmSignal] Error! Invalid parameters.\r\n");
	return;
  }

  const uint32_t prescaler = (params->clockFrequencyHz / TIM_CLOCK_DIVIDER) - 1;
  // Updating the clock divider by setting the period to the TIMx_PSC register
  __HAL_TIM_SET_PRESCALER(params->timerHandle, prescaler);

  const uint32_t period = params->clockFrequencyHz / (prescaler * freqHz);

  // Updating the frequency by setting the period to the TIMx_ARR register
  __HAL_TIM_SET_AUTORELOAD(params->timerHandle, period);

  const float dutyCyclePercentage = dutyCycle / 100.0;
  const uint16_t pulse = period * dutyCyclePercentage;

  // Updating the duty cycle by setting the pulse to the TIMx_CCRx register
  __HAL_TIM_SET_COMPARE(params->timerHandle, params->timerChannel, pulse);
}
