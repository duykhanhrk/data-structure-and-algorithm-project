# include "frame.h"

Frame NewFrame(
  size_tp width = 0,
  size_tp height = 0,
  position_tp position_x = 0,
  position_tp position_y = 0,
  index_tp active_element = 0
) {
  Frame frame = (Frame) malloc(sizeof(FrameT));
  frame->width = width;
  frame->height = height;
  frame->position_x = position_x;
  frame->position_y = position_y;
  frame->active_element = active_element;

  return frame;
}

void DestroyFrame(Frame &frame) {
  free(frame);
  frame = NULL;
}
