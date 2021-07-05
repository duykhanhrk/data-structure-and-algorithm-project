#ifndef __FRAMES_STATISTIC_TOP_TEN_MATERIALS__
#define __FRAMES_STATISTIC_TOP_TEN_MATERIALS__

/* Private key - STTM */
#include "top_materials.h"

#define STTM_MAX_ITEMS 10

// Custom console
bool STTMListViewConsole(keycode_tp keycode) {
  return (keycode == BACKSPACE);
}

#ifdef __cplusplus
extern "C" {
#endif

void ActiveTopTenMaterialsFrame(Frame frame, time_t from, time_t to) {
  // default
  frame->active_element = 1;
  from = BeginningOfDayTimeT(from);
  to = EndOfDayTimeT(to);

  // Templates
  ListView list_view = NewListView(
    STTM_MAX_ITEMS,
    frame->width - 4, frame->height - 7,
    frame->position_x + 2, frame->position_y + 6,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    frame->width - 4, 1,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_THEME_FOREGROUND, PROGRAM_BACKGROUND,
    RENDER_LIST_VIEW_ITEM_WITH_DATA_AS_MATERIAL,
    ACTIVE_LIST_VIEW_ITEM_WITH_DATA_AS_MATERIAL,
    STTMListViewConsole,
    0
  );

  STMTakeTopMaterials(from, to, list_view->linear_list, STTM_MAX_ITEMS);

  // Render
  DrawRecShape(
    frame->width - 4, 2, ' ',
    frame->position_x + 2, frame->position_y + 1,
    PROGRAM_FOREGROUND, PROGRAM_THEME_BACKGROUND
  );
  WriteStr(
    "BẢNG LIỆT KÊ MƯỜI VẬT TƯ CÓ DOANH THU CAO NHẤT",
    frame->position_x + 26,
    frame->position_y + 1,
    PROGRAM_FOREGROUND_REVERSE,
    PROGRAM_THEME_BACKGROUND
  );
  WriteStr("Từ ngày:", frame->position_x + 30, frame->position_y + 2, PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND);
  WriteDate(from, frame->position_x + 39, frame->position_y + 2, PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND);
  WriteStr("Từ ngày:", frame->position_x + 50, frame->position_y + 2, PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND);
  WriteDate(to, frame->position_x + 59, frame->position_y + 2, PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND);

  // Header
  DrawRecShape(frame->width - 4, 1, ' ', frame->position_x + 2, frame->position_y + 5, LIST_VIEW_SCROLL_HEADER_FOREGROUND, LIST_VIEW_SCROLL_HEADER_BACKGROUND);
  WriteStr("Mã", frame->position_x + 4, frame->position_y + 5, LIST_VIEW_SCROLL_HEADER_FOREGROUND, LIST_VIEW_SCROLL_HEADER_BACKGROUND);
  WriteStr("Tên", frame->position_x + 16, frame->position_y + 5, LIST_VIEW_SCROLL_HEADER_FOREGROUND, LIST_VIEW_SCROLL_HEADER_BACKGROUND);
  WriteStr("ĐVT", frame->position_x + 74, frame->position_y + 5, LIST_VIEW_SCROLL_HEADER_FOREGROUND, LIST_VIEW_SCROLL_HEADER_BACKGROUND);
  WriteStr("Số lượng", frame->position_x + 86, frame->position_y + 5, LIST_VIEW_SCROLL_HEADER_FOREGROUND, LIST_VIEW_SCROLL_HEADER_BACKGROUND);

  // List
  RenderListView(list_view);

  // Active
  keycode_tp keycode;
  while (frame->active_element != 0) {
    if (frame->active_element == 1) {
      if (list_view->linear_list->count == 0) {
        keycode = Console();
        if (keycode == ENTER || keycode == BACKSPACE)
          frame->active_element = 0;
      } else {
        keycode = ActiveListView(list_view);
        if (keycode == BACKSPACE)
          frame->active_element = 0;
      }
    }
  }

  // Recovery
  DrawRecShape(
    frame->width - 4, 2, ' ',
    frame->position_x + 2, frame->position_y + 1,
    PROGRAM_FOREGROUND, PROGRAM_THEME_BACKGROUND_LV1
  );
  DrawRecShape(
    frame->width - 4, 1, ' ',
    frame->position_x + 2, frame->position_y + 5,
    PROGRAM_FOREGROUND, PROGRAM_THEME_BACKGROUND_LV1
  );
  ConcealListView(list_view);

  // Release
  DestroyListView(list_view);
}

#ifdef __cplusplus
}
#endif

#endif
