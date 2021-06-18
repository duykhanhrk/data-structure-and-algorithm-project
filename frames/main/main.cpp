#include "main.h"

void ActiveMainFrame(Frame frame) {
  // Initialize
  ClearScreenWithBackground(PROGRAM_THEME_BACKGROUND_LV1);

  // Menu
  LinearList linear_list = NewLinearList(5);
  char item_1[] = "Vật tư";
  char item_2[] = "Nhân viên";
  char item_3[] = "Hóa đơn";
  char item_4[] = "Thống kê";
  char item_5[] = "Thoát";

  AddItemToLinearList(linear_list, item_1);
  AddItemToLinearList(linear_list, item_2);
  AddItemToLinearList(linear_list, item_3);
  AddItemToLinearList(linear_list, item_4);
  AddItemToLinearList(linear_list, item_5);

  ListViewItemContext list_view_item_context = NewListViewItemContext(
    MFP_NAVIGATE_LIST_ITEM_WIDTH, MFP_NAVIGATE_LIST_ITEM_HEIGHT,
    0, 0,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_THEME_FOREGROUND, PROGRAM_BACKGROUND,
    NULL,
    NULL
  );

  ListView list_view = NewListView(
    linear_list,
    MFP_NAVIGATE_LIST_WIDTH, MFP_NAVIGATE_LIST_HEIGHT,
    frame->position_x, frame->position_y,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    list_view_item_context,
    RENDER_LIST_VIEW_ITEM_WITH_DATA_AS_STRING,
    ACTIVE_LIST_VIEW_ITEM_WITH_DATA_AS_STRING,
    LIST_VIEW_E_CONSOLE,
    0
  );

  RenderListView(list_view, NORMAL_LIST_VIEW);

  // Material
  Frame material_frame = NewFrame(
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
        material_frame->active_element = 1;
        ActiveMaterialFrame(material_frame);
        frame->active_element = 1;
      } else if (list_view->selected_item == 1) {
        // Staff
        frame->active_element = 1;
      } else if (list_view->selected_item == 2) {
        // Invoice
        frame->active_element = 1;
      } else if (list_view->selected_item == 3) {
        // Statistics
        frame->active_element = 1;
      } else if (list_view->selected_item == 4) {
        // Exit
        frame->active_element = 0;
      }
    }
  }

  // Release
  DestroyLinearList(linear_list);
  DestroyListView(list_view);
  DestroyFrame(material_frame);
}
