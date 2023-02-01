/*
 * buzzer_player.c
 *
 *  Created on: 12 Aug 2022
 *      Author: auabe
 */
#include <audio_player.h>
#include "buzzer.h"
#include "tim.h"
#include <stdio.h>

#define BUZZER_FREQ_HZ   500
#define BEEP_MULTIPLIER  100

static uint32_t itrs = 0;
static uint32_t onItrs = 50;
static uint32_t offItrs = 0;

static uint8_t initialized = 0;
static uint8_t isOn = 1;
static uint8_t isPaused = 0;

void playAudio(double distance)
{
  offItrs = distance * BEEP_MULTIPLIER;

  if (!initialized)
  {
    printf("buzzerOn\r\n");
    buzzerOn(BUZZER_FREQ_HZ);
    muteBuzzer(); // Playback will be handled in the interrupt callback

    initialized = 1;
  }

  isPaused = 0;
}

void pauseAudio(void)
{
  isPaused = 1;
  itrs = 0;
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
  if (isPaused == 1)
  {
    muteBuzzer();
    return;
  }

  if (itrs > onItrs && itrs > offItrs)
  {
    isOn = 1;
    itrs = 0;
    return;
  }

  if (isOn == 1 && itrs < onItrs)
  {
    unMuteBuzzer();
//    printf("ON: itrs: %ld\r\n", itrs);
  }
  else if (isOn == 1 && itrs == onItrs)
  {
    isOn = 0;
    itrs = 0;
  }
  else if (isOn == 0 && itrs < offItrs)
  {
    muteBuzzer();
//    printf("OFF: itrs: %ld\r\n", itrs);
  }
  else if (isOn == 0  && itrs == offItrs)
  {
    isOn = 1;
    itrs = 0;
  }

  itrs++;
}
