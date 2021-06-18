#ifndef __CSLSCR_DISPLAY_ECHO__
#define __CSLSCR_DISPLAY_ECHO__

#ifdef __cplusplus
extern "C" {
#endif

void EchoChar(char obj, position_tp, position_tp, color_tp, color_tp);
void EchoStr(const char *obj, position_tp, position_tp, color_tp, color_tp);
void EchoShort(short int obj, position_tp, position_tp, color_tp, color_tp);
void EchoInt(int obj, position_tp, position_tp, color_tp, color_tp);
void EchoLong(long long int obj, position_tp, position_tp, color_tp, color_tp);
void EchoUShort(unsigned short int obj, position_tp, position_tp, color_tp, color_tp);
void EchoUInt(unsigned int obj, position_tp, position_tp, color_tp, color_tp);
void EchoULong(unsigned long long int obj, position_tp, position_tp, color_tp, color_tp);
void EchoDate(time_t obj, position_tp, position_tp, color_tp, color_tp);

#include "echo.cpp"

#ifdef __cplusplus
}
#endif

#endif
