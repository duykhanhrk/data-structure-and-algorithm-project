#include "staff.h"

bool STPAddButtonConsole(keycode_tp c) {
  return (c == KEY_LEFT || c == KEY_DOWN || c == ENTER || c == BACKSPACE);
}

void STPRecovery(Frame frame) {
  DrawRecShape(
    STP_STAFF_LIST_ITEM_WIDTH, 3, ' ',
    frame->position_x + 2, frame->position_y + 1,
    CURRENT_FOREGROUND, PROGRAM_THEME_BACKGROUND_LV1
  );

  DrawRecShape(
    STP_STAFF_LIST_ITEM_WIDTH, WINDOW_ROWS - 6, ' ',
    frame->position_x + 2, frame->position_y + 5,
    CURRENT_FOREGROUND, PROGRAM_THEME_BACKGROUND_LV1
  );
}

void ActiveStaffFrame(Frame frame) {
  // Button
  Button add_button = NewButton(
    "Thêm", ALIGN_CENTER,
    STP_ADD_BUTTON_WIDTH, STP_ADD_BUTTON_HEIGHT, 0,
    frame->position_x + 2, frame->position_y + 1,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_THEME_FOREGROUND, PROGRAM_BACKGROUND,
    STPAddButtonConsole
  );

  // Material list view
  ListViewScroll list_view_scroll = NewListViewScroll(
    STAFF_LIST_IN_ARCHIVE, // data
    0, 4, // page, fields count
    CountStaffsInArchive, // items count
    TakeStaffsInArchive, // take items
    STP_STAFF_LIST_WIDTH, STP_STAFF_LIST_HEIGHT,
    frame->position_x + 2, frame->position_y + 5,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    STP_STAFF_LIST_ITEM_WIDTH, STP_STAFF_LIST_ITEM_HEIGHT,
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

  // creation
  Frame creation_form = NewFrame(
    STP_CREATION_FORM_WIDTH, STP_CREATION_FORM_HEIGHT,
    frame->position_x + (frame->width - STP_CREATION_FORM_WIDTH) / 2,
    frame->position_y + (frame->height - STP_CREATION_FORM_HEIGHT) / 2
  );

  // updated
  Frame updated_form = NewFrame(
    STP_UPDATED_FORM_WIDTH, STP_UPDATED_FORM_HEIGHT,
    frame->position_x + (frame->width - STP_UPDATED_FORM_WIDTH) / 2,
    frame->position_y + (frame->height - STP_UPDATED_FORM_HEIGHT) / 2
  );

  // Render

  RenderButton(add_button);
  RenderListViewScroll(list_view_scroll);

  // Active
  Staff staff;
  keycode_tp keycode;
  while (frame->active_element != 0) {
    if (frame->active_element == 1) {
      // Add button
      keycode = ActiveButton(add_button);
      if (keycode == KEY_LEFT) {
        frame->active_element = 0;
      } else if (keycode == KEY_DOWN)
        frame->active_element = 2;
      else if (keycode == ENTER) {
        creation_form->active_element = 1;
        STPRecovery(frame);
        ActiveStaffCreationFrame(creation_form);
        RenderButton(add_button);
        RenderListViewScroll(list_view_scroll);
        frame->active_element = 1;
      } else if (keycode == BACKSPACE) {
         frame->active_element = 0;
      }
    } else if (frame->active_element == 2) {
      // List
      keycode = ActiveListViewScroll(list_view_scroll);
      if (keycode == ENTER) {
        updated_form->active_element = 2;
        STPRecovery(frame);
        staff = (Staff) GetItemInLinearListByIndex(
          list_view_scroll->list_view->linear_list,
          list_view_scroll->list_view->selected_item
        );
        if (staff == NULL) continue;
        ActiveStaffUpdatedFrame(updated_form, staff);
        RenderButton(add_button);
        RenderListViewScroll(list_view_scroll);
        frame->active_element = 2;
      } else if (keycode == BACKSPACE) {
        frame->active_element = 1;
      } else if (keycode == KEY_UP) {
        frame->active_element = 1;
      }
    }
  }

  // Release
  DestroyButton(add_button);
  DestroyListViewScroll(list_view_scroll);
  DestroyFrame(creation_form);
  DestroyFrame(updated_form);

  // Recovery
  STPRecovery(frame);
}
