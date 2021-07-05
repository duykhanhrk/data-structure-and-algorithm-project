#ifndef __FRAMES_STATISTIC___
#define __FRAMES_STATISTIC___

/* includes */
#include "top_materials.h"
#include "list.h"
#include "filter.h"

/* Private key - STTP */

#define STTP_FILTER_FORM_WIDTH 50
#define STTP_FILTER_FORM_HEIGHT 17

#ifdef __cplusplus
extern "C" {
#endif

void ActiveStatisticFrame(Frame frame) {
  // filter form
  Frame filter_form = NewFrame(
    STTP_FILTER_FORM_WIDTH, STTP_FILTER_FORM_HEIGHT,
    frame->position_x + (frame->width - STTP_FILTER_FORM_WIDTH) / 2,
    frame->position_y + (frame->height - STTP_FILTER_FORM_HEIGHT) / 2
  );

  ActiveStatisticFilterForm(filter_form);

  DestroyFrame(filter_form);
}

#ifdef __cplusplus
}
#endif

#endif
