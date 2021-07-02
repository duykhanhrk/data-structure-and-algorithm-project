#include "staff_selection_list.h"

void SLPRecovery(Frame frame) {
  DrawRecShape(
    SLP_STAFF_LIST_ITEM_WIDTH, WINDOW_ROWS - 6, ' ',
    frame->position_x + 2, frame->position_y + 5,
    CURRENT_FOREGROUND, PROGRAM_THEME_BACKGROUND_LV1
  );
}

Staff ActiveStaffSelectionListFrame(Frame frame) {
  // Material list view
  ListViewScroll list_view_scroll = NewListViewScroll(
    STAFF_LIST_IN_ARCHIVE, // data
    NULL, // filter
    0, 4, // page, fields count
    CountStaffsInArchive, // items count
    TakeStaffsInArchive, // take items
    SLP_STAFF_LIST_WIDTH, SLP_STAFF_LIST_HEIGHT,
    frame->position_x + 2, frame->position_y + 5,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    SLP_STAFF_LIST_ITEM_WIDTH, SLP_STAFF_LIST_ITEM_HEIGHT,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_THEME_FOREGROUND, PROGRAM_BACKGROUND,
    RENDER_LIST_VIEW_ITEM_WITH_DATA_AS_STAFF,
    ACTIVE_LIST_VIEW_ITEM_WITH_DATA_AS_STAFF,
    LIST_VIEW_SCROLL_EB_CONSOLE,
    0
  );

  AddFieldForListViewScroll(list_view_scroll, "Mã", 10);
  AddFieldForListViewScroll(list_view_scroll, "Tên", 32);
  AddFieldForListViewScroll(list_view_scroll, "Họ", 32);
  AddFieldForListViewScroll(list_view_scroll, "Giới tính", 12);

  // Render

  RenderListViewScroll(list_view_scroll);

  // Active
  Staff staff = NULL;
  keycode_tp keycode;
  while (frame->active_element != 0) {
    if (frame->active_element == 1) {
      keycode = ActiveListViewScroll(list_view_scroll);
      if (keycode == ENTER) {
        staff = (Staff) GetSelectedItemInListViewScroll(list_view_scroll);
        frame->active_element = 0;
      } else if (keycode == BACKSPACE) {
        frame->active_element = 0;
      }
    }
  }

  // Release
  DestroyListViewScroll(list_view_scroll);

  // Recovery
  SLPRecovery(frame);

  return staff;
}
