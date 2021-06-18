#ifndef __SUPPORT_INPUT_CONSOLE__
#define __SUPPORT_INPUT_CONSOLE__

#define STANDARD_CONSOLE StandardConsole
#define LIST_VIEW_EE_CONSOLE ListViewEEConsole
#define LIST_VIEW_EB_CONSOLE ListViewEBConsole
#define LIST_VIEW_E_CONSOLE ListViewEBConsole

#ifdef __cplusplus
extern "C" {
#endif

bool StandardConsole(char c);
bool ListViewEEConsole(char c);
bool ListViewEBConsole(char c);
bool ListViewEConsole(char c);

#include "console.cpp"

#ifdef __cplusplus
}
#endif

#endif
