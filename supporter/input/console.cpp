#include "console.h"

bool StandardConsole(char c) {
  return (c == ENTER || c == KEY_UP || c == KEY_DOWN || c == KEY_RIGHT || c == KEY_LEFT);
}

bool ListViewEEConsole(char c) {
  return (c == ENTER || c == ESC);
}

bool ListViewEConsole(char c) {
  return (c == ENTER);
}

bool ListViewEBConsole(char c) {
  return (c == ENTER || c == BACKSPACE);
}
