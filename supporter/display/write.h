#ifndef __CSLSCR_DISPLAY_WRITE__
#define __CSLSCR_DISPLAY_WRITE__

#ifdef __cplusplus
extern "C" {
#endif

void WriteChar(char obj, position_tp, position_tp, color_tp, color_tp);
void WriteStr(const char *obj, position_tp, position_tp, color_tp, color_tp);
void WriteShort(short int obj, position_tp, position_tp, color_tp, color_tp);
void WriteInt(int obj, position_tp, position_tp, color_tp, color_tp);
void WriteLong(long long int obj, position_tp, position_tp, color_tp, color_tp);
void WriteUShort(unsigned short int obj, position_tp, position_tp, color_tp, color_tp);
void WriteUInt(unsigned int obj, position_tp, position_tp, color_tp, color_tp);
void WriteULong(unsigned long long int obj, position_tp, position_tp, color_tp, color_tp);
void WriteDate(time_t obj, position_tp, position_tp, color_tp, color_tp);

#include "write.cpp"

#ifdef __cplusplus
}
#endif

#endif
