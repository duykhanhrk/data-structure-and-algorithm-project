#ifndef __CSLSCR_DISPLAY_DRAW__
#define __CSLSCR_DISPLAY_DRAW__

#ifdef __cplusplus
extern "C" {
#endif

void DrawVerLine(size_tp, char, position_tp, position_tp, color_tp, color_tp);
void DrawHorLine(size_tp, char, position_tp, position_tp, color_tp, color_tp);
void DrawRec(size_tp, size_tp, char, position_tp, position_tp, color_tp, color_tp);
void DrawRecShape(size_tp, size_tp, char, position_tp, position_tp, color_tp, color_tp);

#include "draw.cpp"

#ifdef __cplusplus
}
#endif

#endif
