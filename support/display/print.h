#ifndef __CSLSCR_DISPLAY_PRINT__
#define __CSLSCR_DISPLAY_PRINT__

#ifdef __cplusplus
extern "C" {
#endif

void PrintChar(char obj, position_tp, position_tp, color_tp, color_tp);
void PrintStr(const char *obj, position_tp, position_tp, color_tp, color_tp);
void PrintShort(short int obj, position_tp, position_tp, color_tp, color_tp);
void PrintInt(int obj, position_tp, position_tp, color_tp, color_tp);
void PrintLong(long long int obj, position_tp, position_tp, color_tp, color_tp);
void PrintUShort(unsigned short int obj, position_tp, position_tp, color_tp, color_tp);
void PrintUInt(unsigned int obj, position_tp, position_tp, color_tp, color_tp);
void PrintULong(unsigned long long int obj, position_tp, position_tp, color_tp, color_tp);
void PrintDate(time_t obj, position_tp, position_tp, color_tp, color_tp);

#include "print.cpp"

#ifdef __cplusplus
}
#endif

#endif
