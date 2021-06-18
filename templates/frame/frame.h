#ifndef __TEMPLATE_FRAME__
#define __TEMPLATE_FRAME__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct FrameT {
  size_tp height;
  size_tp width;
  position_tp position_x;
  position_tp position_y;
  color_tp foreground;
  color_tp background;
  index_tp active_element;
} FrameT, * Frame;

Frame NewFrame(size_tp, size_tp, position_tp, position_tp, color_tp, color_tp, index_tp);
void DestroyFrame(Frame &);

/* includes */

#include "frame.cpp"

#ifdef __cplusplus
}
#endif

#endif
