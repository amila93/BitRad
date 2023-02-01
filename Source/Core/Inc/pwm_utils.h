/*******************************************************************************
  * File Name          : pwm_utils.h
  * Description        : Includes utility functions to handle PWM signals.
  *
  * Author             : Amila Udara Abeygunasekara
  * Date               : 2022-02-27
  ******************************************************************************
  */
#ifndef INC_PWM_UTILS_H_
#define INC_PWM_UTILS_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"

// Structure to store some parameters related to the timer
typedef struct
{
  TIM_HandleTypeDef* timerHandle;
  uint32_t timerChannel;
  uint8_t isComplimentary; // 1 when timer channel is complimentary (i.e., TIMx_CHxN)
  uint32_t clockFrequencyHz;
} TimerParams;

void startPwmOutput(TimerParams* timParams);
void stopPwmOutput(TimerParams* timParams);
void updatePwmSignal(TimerParams* params, uint32_t freqHz, uint8_t dutyCycle);

#endif /* INC_PWM_UTILS_H_ */
