#ifndef __SUPPORT_INPUT__
#define __SUPPORT_INPUT__

#include <conio.h>

// Key code
// Keys
#define ENTER 13
#define ESC 27
#define BACKSPACE 8
#define SLASH 47
#define NULL_KEY 0
#define KEY_UP -1
#define KEY_DOWN -2
#define KEY_LEFT -3
#define KEY_RIGHT -4

#ifdef __cplusplus
extern "C" {
#endif

/* Console */
char Console() {
  unsigned char c = getch();

  if (c == 13) return ENTER;
  else if (c == 27) return ESC;
  else if (c == 8) return BACKSPACE;
  else if (c == 224) {
    c = getch();
    if (c == 75) return KEY_LEFT;
    else if (c == 77) return KEY_RIGHT;
    else if (c == 80) return KEY_DOWN;
    else if (c == 72) return KEY_UP;
    return NULL_KEY;
  }

  return c;
}

/* includes */
#include "console.h"
#include "char_set.h"

#ifdef __cplusplus
}
#endif

#endif
