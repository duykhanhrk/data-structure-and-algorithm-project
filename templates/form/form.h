#ifndef __TEMPLATE_FORM__
#define __TEMPLATE_FORM__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct FrameT {
  size_tp height;
  size_tp width;
  position_tp position_x;
  position_tp position_y;
  index_tp active_element;
} FrameT, * Frame;

Frame NewFrame(size_tp, size_tp, position_tp, position_tp, index_tp);
void DestroyFrame(Frame &);

/* includes */

#include "frame.cpp"

#ifdef __cplusplus
}
#endif

#endif
