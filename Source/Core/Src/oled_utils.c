/*******************************************************************************
  * File Name          : oled_utils.c
  * Description        :
  *    Includes utility functions related to SSD1331 RGB OLED display
  *
  * Author             : Amila Udara Abeygunasekara
  * Date               : 2022-03-19
  ******************************************************************************
  */
#include "oled_utils.h"
#include <stdio.h>
#include <string.h>

// Private defines
#define SSD1331_WIDTH     96
#define SSD1331_HEIGHT    64

// Private data types
typedef struct
{
  uint16_t posX;
  uint8_t posY;
} Cursor;

// Private global variables
// The Cursor is used to keep track of the last written position on the display.
// It is global since multiple functions refer to this and also should persist in the
// program lifecycle.
static Cursor cursor = { 0 };

// FUNCTION      : displayTextOnCorner
// DESCRIPTION   :
//    This function prints a message on a specified corner of the SSD1331 OLED display.
//    Note: Total length of the message must be less than the width of the display.
// PARAMETERS    :
//    const char* text     : Message to be printed
//    FontSize txtSize     : Font size of the message.
//    enum Color txtColour : Font colour.
//    Corner corner        : The corner which the message gets printed.
// RETURNS       : None
void displayTextOnCorner(const char* text, FontSize fontSize, enum Color txtColour, Corner corner)
{
  const uint8_t txtLength = strlen(text);
  const uint8_t fontWidth = fontSize / 2;
  const uint16_t lenOnDisplay = txtLength * fontWidth;
  uint8_t txtXPos = 0;
  uint8_t txtYPos = 0;

  if (SSD1331_WIDTH < lenOnDisplay)
  {
    printf("[oled_utils::displayTextOnCorner] Error! Text is too long to display\r\n");
    return;
  }

  switch (corner)
  {
    case TOP_LEFT:
      // Keep txtXPos and txtYPos as 0
      break;

    case TOP_RIGHT:
      txtXPos = SSD1331_WIDTH - lenOnDisplay;
      break;

    case BOTTOM_LEFT:
      txtYPos = SSD1331_HEIGHT - fontSize;
      break;

    case BOTTOM_RIGHT:
      txtXPos = SSD1331_WIDTH - lenOnDisplay;
      txtYPos = SSD1331_HEIGHT - fontSize;
      break;

    default:
      printf("[oled_utils::displayTextOnCorner] Error! Invalid corner parameter\r\n");
      return;
  }

  ssd1331_display_string(txtXPos, txtYPos, text, fontSize, txtColour);
}

// FUNCTION      : displayTextOnANewLine
// DESCRIPTION   :
//    Prints a message on a new line of the SSD1331 OLED display.
//    Note: This function is only compatible with displayTextOnANewLine(),
//    appendDegreeSymbol() and appendText() functions. If a message is printed
//    using, for an example, ssd1331_display_string(), the previous message
//    will get overwritten.
// PARAMETERS    :
//    const char* text     : Message to be printed
//    FontSize txtSize     : Font size of the message.
//    enum Color txtColour : Font colour.
// RETURNS       : None
void displayTextOnANewLine(const char* text, FontSize fontSize, enum Color txtColour)
{
  const uint8_t txtLength = strlen(text);
  const uint8_t fontWidth = fontSize / 2;
  const uint16_t lenOnDisplay = txtLength * fontWidth;

  uint8_t txtXPos = 0;

  if (cursor.posX != 0 || cursor.posY != 0)
  {
    // If something is written, move the cursor to the next line
    cursor.posY += fontSize;
  }

  if (cursor.posY >= SSD1331_HEIGHT)
  {
    printf("[oled_utils::displayTextOnANewLine] Error! Exceeding maximum number of lines\r\n");
    return;
  }

  ssd1331_display_string(txtXPos, cursor.posY, text, fontSize, txtColour);

  // Update the cursor position
  cursor.posX = lenOnDisplay;

  // If the text is long and occupies multiple lines, update the cursor accordingly
  while (cursor.posX > SSD1331_WIDTH)
  {
    cursor.posX -= SSD1331_WIDTH;
    cursor.posY += fontSize;
  }
}

// FUNCTION      : appendDegreeSymbol
// DESCRIPTION   :
//    Prints a degree symbol/sign by appending a circle to the existing text
//    (if available) of the SSD1331 OLED display.
//    Note: This function is only compatible with displayTextOnANewLine(),
//    appendDegreeSymbol() and appendText() functions. If a message is printed
//    using, for an example, ssd1331_display_string(), the previous message
//    will get overwritten.
// PARAMETERS    :
//    FontSize txtSize     : Font size of the symbol.
//    enum Color txtColour : Font colour.
// RETURNS       : None
void appendDegreeSymbol(FontSize fontSize, enum Color colour)
{
  uint8_t circleRadius = 0;
  switch (fontSize)
  {
    case FONT_SMALL:
      circleRadius = 2;
      break;

    case FONT_LARGE:
      circleRadius = 3;
      break;
  }

  const uint8_t circleDiameter = circleRadius * 2;

  // Width of the circle including the 1 pixel space in front
  const uint8_t widthOfCircleIncludingSpace = circleDiameter + 1;

  if ((SSD1331_WIDTH - cursor.posX) < widthOfCircleIncludingSpace)
  {
    // If there's not enough space, move the cursor to the start of a new line
    cursor.posX = 0;
    cursor.posY += fontSize;
  }
  else
  {
    // Move the cursor 1 pixel to the right
    cursor.posX++;
  }

  const uint8_t circleXPos = (uint8_t)cursor.posX + circleRadius;
  const uint8_t circleYPos = cursor.posY + circleRadius;

  ssd1331_draw_circle(circleXPos, circleYPos, circleRadius, colour);

  // Update the cursor position
  cursor.posX += widthOfCircleIncludingSpace;
}

// FUNCTION      : appendText
// DESCRIPTION   :
//    Prints a message by appending to the existing text (if available) of
//    the SSD1331 OLED display.
//    Note: This function is only compatible with displayTextOnANewLine(),
//    appendDegreeSymbol() and appendText() functions. If a message is printed
//    using, for an example, ssd1331_display_string(), the previous message
//    will get overwritten.
// PARAMETERS    :
//    const char* text     : Message to be printed
//    FontSize txtSize     : Font size of the message.
//    enum Color txtColour : Font colour.
// RETURNS       : None
void appendText(const char* text, FontSize fontSize, enum Color txtColour)
{
  const uint8_t txtLength = strlen(text);
  const uint8_t fontWidth = fontSize / 2;
  const uint16_t lenOnDisplay = txtLength * fontWidth;

  if ((SSD1331_WIDTH - cursor.posX) < fontWidth)
  {
    // If there's not enough space, move the cursor to the start of a new line
    cursor.posX = 0;
    cursor.posY += fontSize;
  }
  else
  {
    // Move the cursor 1 pixel to the right
    cursor.posX++;
  }

  ssd1331_display_string(cursor.posX, cursor.posY, text, fontSize, txtColour);

  // Update the cursor position
  cursor.posX += lenOnDisplay + 1;

  // If the text is long and occupies multiple lines, update the cursor accordingly
  while (cursor.posX > SSD1331_WIDTH)
  {
    cursor.posX -= SSD1331_WIDTH;
    cursor.posY += fontSize;
  }
}

// FUNCTION      : quickClearDisplay
// DESCRIPTION   :
//    Clears the SSD1331 OLED display relatively quickly by only erasing the lines
//    that has been written. If all the lines are occupied, this will perform same
//    as ssd1331_clear_screen() driver function. This function will be faster in all
//    other scenarios.
//    Note: This function is only compatible with displayTextOnANewLine(),
//    appendDegreeSymbol() and appendText() functions. This function can not
//    determine the number of lines written if the user use driver functions such as
//    ssd1331_display_string().
// PARAMETERS    : None
// RETURNS       : None
void quickClearDisplay(void)
{
  const uint16_t maxHeightOfWrittenLines = cursor.posY + FONT_LARGE;

  ssd1331_fill_rect(0, 0, SSD1331_WIDTH, maxHeightOfWrittenLines, BLACK);

  cursor.posX = 0;
  cursor.posY = 0;
}

// FUNCTION      : clearDisplay
// DESCRIPTION   :
//    Clears the SSD1331 OLED display.
//    Note: If you only use displayTextOnANewLine(), appendDegreeSymbol()
//    or appendText() functions, please consider quickClearDisplay() function
//    instead.
// PARAMETERS    : None
// RETURNS       : None
void clearDisplay(void)
{
  cursor.posX = 0;
  cursor.posY = 0;

  ssd1331_clear_screen(BLACK);
}
