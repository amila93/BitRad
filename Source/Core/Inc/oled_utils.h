/*******************************************************************************
  * File Name          : oled_utils.h
  * Description        :
  *    Includes utility functions related to SSD1331 RGB OLED display
  *
  * Author             : Amila Udara Abeygunasekara
  * Date               : 2022-03-19
  ******************************************************************************
  */
#ifndef INC_OLED_UTILS_H_
#define INC_OLED_UTILS_H_

#include <stdint.h>
#include "ssd1331.h"

typedef enum
{
  TOP_LEFT = 0,
  TOP_RIGHT,
  BOTTOM_LEFT,
  BOTTOM_RIGHT
} Corner;

typedef enum
{
  FONT_SMALL = FONT_1206,
  FONT_LARGE = FONT_1608
} FontSize;

void displayTextOnCorner(const char* text, FontSize fontSize, enum Color txtColour, Corner corner);
void displayTextOnANewLine(const char* text, FontSize fontSize, enum Color txtColour);
void appendDegreeSymbol(FontSize fontSize, enum Color colour);
void appendText(const char* text, FontSize fontSize, enum Color txtColour);
void quickClearDisplay(void);
void clearDisplay(void);

#endif /* INC_OLED_UTILS_H_ */
