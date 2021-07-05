#include "main.h"

void ActiveMainFrame(Frame frame) {
  // Initialize
  ClearScreenWithBackground(PROGRAM_THEME_BACKGROUND_LV1);

  ListView list_view = NewListView(
    5,
    MFP_NAVIGATE_LIST_WIDTH, MFP_NAVIGATE_LIST_HEIGHT,
    frame->position_x, frame->position_y,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    MFP_NAVIGATE_LIST_ITEM_WIDTH, MFP_NAVIGATE_LIST_ITEM_HEIGHT,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_THEME_FOREGROUND, PROGRAM_BACKGROUND,
    RENDER_LIST_VIEW_ITEM_WITH_DATA_AS_STRING,
    ACTIVE_LIST_VIEW_ITEM_WITH_DATA_AS_STRING,
    LIST_VIEW_E_CONSOLE,
    0
  );

  char item_1[] = "Vật tư";
  char item_2[] = "Nhân viên";
  char item_3[] = "Hóa đơn";
  char item_4[] = "Thống kê";
  char item_5[] = "Thoát";

  AddItemToListView(list_view, item_1);
  AddItemToListView(list_view, item_2);
  AddItemToListView(list_view, item_3);
  AddItemToListView(list_view, item_4);
  AddItemToListView(list_view, item_5);

  RenderListView(list_view, NORMAL_LIST_VIEW);

  // Content
  Frame content_frame = NewFrame(
    frame->width - MFP_NAVIGATE_LIST_WIDTH, frame->height,
    frame->position_x + MFP_NAVIGATE_LIST_WIDTH, frame->position_y
  );

  // Active
  keycode_tp keycode;
  while (frame->active_element != 0) {
    if (frame->active_element == 1) {
      // Navigate list
      keycode = ActiveListView(list_view);
      if (keycode == ENTER)
        frame->active_element = 2;
      else if (keycode == ESC)
        frame->active_element = 0;
    } else if (frame->active_element == 2) {
      // Content
      if (list_view->selected_item == 0) {
        // Material
        content_frame->active_element = 1;
        ActiveMaterialFrame(content_frame);
        frame->active_element = 1;
      } else if (list_view->selected_item == 1) {
        // Staff
        content_frame->active_element = 1;
        ActiveStaffFrame(content_frame);
        frame->active_element = 1;
      } else if (list_view->selected_item == 2) {
        // Invoice
        content_frame->active_element = 1;
        ActiveInvoiceFrame(content_frame);
        frame->active_element = 1;
      } else if (list_view->selected_item == 3) {
        // Statistics
        content_frame->active_element = 1;
        ActiveStatisticFrame(content_frame);
        frame->active_element = 1;
      } else if (list_view->selected_item == 4) {
        // Exit
        frame->active_element = 0;
      }
    }
  }

  // Release
  DestroyListView(list_view);
  DestroyFrame(content_frame);

  // Initialize
  ClearScreenWithBackground(BACKGROUND_BLACK);
}
