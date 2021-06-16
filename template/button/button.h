#ifndef __TEMPLATE_BUTTON__
#define __TEMPLATE_BUTTON__

/* default value */
#define BUTTON_FOREGROUND PROGRAM_THEME_FOREGROUND
#define BUTTON_BACKGROUND PROGRAM_BACKGROUND
#define BUTTON_ACTIVE_FOREGROUND PROGRAM_FOREGROUND_REVERSE
#define BUTTON_ACTIVE_BACKGROUND PROGRAM_THEME_BACKGROUND

#define BUTTON_TEXT "Button\0"
#define BUTTON_SIZE 1
#define BUTTON_WIDTH 0
#define BUTTON_HEIGHT 0
#define BUTTON_CONSOLE STANDARD_CONSOLE

#define NORMAL_BUTTON 0
#define ACTIVE_BUTTON 1

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ButtonT {
  char * text;
  position_tp position_x;
  position_tp position_y;
  size_tp width;
  size_tp height;
  size_tp size;
  color_tp foreground;
  color_tp background;
  color_tp active_foreground;
  color_tp active_background;
  bool (* console)(char);
} ButtonT, * Button;

Button NewButton(const char *, position_tp, position_tp, size_tp, size_tp, size_tp, color_tp, color_tp, color_tp, color_tp, bool (*)(char));
void DestroyButton(Button &);

void RenderButton(Button, status_tp);
keycode_tp ActiveButton(Button);

/* includes */

#include "button.cpp"

#ifdef __cplusplus
}
#endif

#endif
