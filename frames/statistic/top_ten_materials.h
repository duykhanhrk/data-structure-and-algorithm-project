#ifndef __FRAMES_STATISTIC_TOP_TEN_MATERIAL__
#define __FRAMES_STATISTIC_TOP_TEN_MATERIAL__

/* Private key - STTM */

#ifdef __cplusplus
extern "C" {
#endif

void ActiveTopTenMaterialFrame(Frame frame, time_t from, time_t to) {
  // default
  frame->active_element = 1;

  // Variable
  LinearList linear_list;
  Invoice invoice;
  LinearList carrier = NewLinearList(2);
  AddItemToLinearList(carrier, &from);
  AddItemToLinearList(carrier, &to);

  // Templates
  ListViewScroll list_view_scroll = NewListViewScroll(
    STAFF_LIST_IN_ARCHIVE, // data,
    carrier, // filter
    0, 4, // page, fields count
    CountInvoicesInArchiveWithFilter, // items count
    TakeInvoicesInArchiveWithFilter, // take items
    frame->width - 4, frame->height - 5,
    frame->position_x + 2, frame->position_y + 4,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    frame->width - 4, 1,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_THEME_FOREGROUND, PROGRAM_BACKGROUND,
    RENDER_LIST_VIEW_ITEM_WITH_DATA_AS_INVOICE,
    ACTIVE_LIST_VIEW_ITEM_WITH_DATA_AS_INVOICE,
    LIST_VIEW_SCROLL_EB_CONSOLE,
    0
  );

  // Render
  DrawRecShape(
    frame->width - 4, 2, ' ',
    frame->position_x + 2, frame->position_y + 1,
    PROGRAM_FOREGROUND, PROGRAM_THEME_BACKGROUND
  );
  WriteStr(
    "BẢNG LIỆT KÊ CÁC HÓA ĐƠN TRONG KHOẢNG THỜI GIAN",
    frame->position_x + 26,
    frame->position_y + 1,
    PROGRAM_FOREGROUND_REVERSE,
    PROGRAM_THEME_BACKGROUND
  );
  WriteStr("Từ ngày:", frame->position_x + 30, frame->position_y + 2, PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND);
  WriteDate(from, frame->position_x + 39, frame->position_y + 2, PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND);
  WriteStr("Từ ngày:", frame->position_x + 50, frame->position_y + 2, PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND);
  WriteDate(to, frame->position_x + 59, frame->position_y + 2, PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND);

  RenderListViewScroll(list_view_scroll);

  // Active
  keycode_tp keycode;
  while (frame->active_element != 0) {
    if (frame->active_element == 1) {
      keycode = ActiveListViewScroll(list_view_scroll);
      if (keycode == BACKSPACE) {
        frame->active_element = 0;
      } else if (keycode == NULL_KEY) {
        keycode = Console();
        if (keycode == ENTER || keycode == BACKSPACE) {
          frame->active_element = 0;
        }
      }
    }
  }

  // Recovery
    DrawRecShape(
    frame->width - 4, 2, ' ',
    frame->position_x + 2, frame->position_y + 1,
    PROGRAM_FOREGROUND, PROGRAM_THEME_BACKGROUND_LV1
  );
  ConcealListViewScroll(list_view_scroll);

  // Release
  DestroyLinearList(carrier);
  DestroyListViewScroll(list_view_scroll);
}

#ifdef __cplusplus
}
#endif

#endif
