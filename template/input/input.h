/* Input */

// Key code
// Keys
#define ENTER 13
#define ESC 27
#define BACKSPACE 8
#define SLASH 47
#define KEY_UP -1
#define KEY_DOWN -2
#define KEY_LEFT -3
#define KEY_RIGHT -4

/* Console */
char Console() {
  char c = getch();

  if (c == 13) return ENTER;
  else if (c == 27) return ESC;
  else if (c == 8) return BACKSPACE;
  else if (c == -32) {
    c = getch();
    if (c == 75) return KEY_LEFT;
    else if (c == 77) return KEY_RIGHT;
    else if (c == 80) return KEY_DOWN;
    else if (c == 72) return KEY_UP;
    return '\0';
  }

  return c;
}

/* Inlucde features */
// #include "navpn.h"
// #include "charset.h"
// #include "express.h"

#define INPUT_POSITION_X CURSOR_POSITION_X
#define INPUT_POSITION_Y CURSOR_POSITION_Y
#define INPUT_FOREGROUND CURRENT_FOREGROUND
#define INPUT_BACKGROUND CURRENT_BACKGROUND
#define INPUT_ON_ACTIVE_FOREGROUND CURRENT_FOREGROUND
#define INPUT_ON_ACTIVE_BACKGROUND CURRENT_BACKGROUND
#define INPUT_NAV_PANEL STANDARD_NAV_PANEL

// Number

#define  NUMBER_INPUT_MAX_VALUE USHORT_MAX_VALUE
#define  NUMBER_INPUT_MIN_VALUE USHORT_MIN_VALUE
#define  NUMBER_INPUT_POSITION_X INPUT_POSITION_X
#define  NUMBER_INPUT_POSITION_Y INPUT_POSITION_Y
#define  NUMBER_INPUT_FOREGROUND INPUT_FOREGROUND
#define  NUMBER_INPUT_BACKGROUND INPUT_BACKGROUND
#define  NUMBER_INPUT_ON_ACTIVE_FOREGROUND INPUT_ON_ACTIVE_FOREGROUND
#define  NUMBER_INPUT_ON_ACTIVE_BACKGROUND INPUT_ON_ACTIVE_BACKGROUND
#define  NUMBER_INPUT_NAV_PANEL INPUT_NAV_PANEL
#define  NUMBER_INPUT_CHAR_SET NUMERIC_CHAR_SET

#include "uintinp.h"
#include "intinp.h"
#include "dtinp.h"

