#include "console.h"

bool StandardConsole(char c) {
  return (c == ENTER || c == ESC || c == KEY_UP || c == KEY_DOWN);
}

bool ListViewEEConsole(char c) {
  return (c == ENTER || c == ESC);
}
