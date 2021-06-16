#ifndef __SUPPORT_INPUT_CONSOLE__
#define __SUPPORT_INPUT_CONSOLE__

#define STANDARD_CONSOLE StandardConsole
#define LIST_VIEW_EE_CONSOLE ListViewEEConsole

#ifdef __cplusplus
extern "C" {
#endif

bool StandardConsole(char c);
bool ListViewEEConsole(char c);

#include "console.cpp"

#ifdef __cplusplus
}
#endif

#endif
