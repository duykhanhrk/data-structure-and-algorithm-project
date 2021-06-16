/* main */

#ifndef __HANDLER_MAIN__
#define __HANDLER_MAIN__

#define MENU_WIDTH 20

#ifdef __cplusplus
extern "C" {
#endif

void ActiveMainFrame(Frame frame) {
  // Initialize
  ClearScreenWithBackground(PROGRAM_THEME_BACKGROUND_LV1);

  // Menu
  LinearList linear_list = NewLinearList(5);
  char item_1[] = "Giới thiệu";
  char item_2[] = "Vật tư";
  char item_3[] = "Nhân viên";
  char item_4[] = "Đơn hàng";
  char item_5[] = "Top vật tư";

  AddItemToLinearList(linear_list, item_1);
  AddItemToLinearList(linear_list, item_2);
  AddItemToLinearList(linear_list, item_3);
  AddItemToLinearList(linear_list, item_4);
  AddItemToLinearList(linear_list, item_5);

  ListViewItemContext list_view_item_context = NewListViewItemContext(
    MENU_WIDTH, 3, 0, 0,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_THEME_FOREGROUND, PROGRAM_BACKGROUND,
    NULL, NULL
  );

  ListView list_view = NewListView(
    linear_list, MENU_WIDTH, WINDOW_ROWS,
    frame->position_x, frame->position_y,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    list_view_item_context,
    RENDER_LIST_VIEW_ITEM_WITH_DATA_AS_STRING,
    ACTIVE_LIST_VIEW_ITEM_WITH_DATA_AS_STRING,
    LIST_VIEW_EE_CONSOLE,
    0
  );

  RenderListView(list_view, NORMAL_LIST_VIEW);

  // Material
  Frame material_frame = NewFrame(
    frame->width - MENU_WIDTH,
    frame->height,
    frame->position_x + MENU_WIDTH,
    frame->position_y,
    1
  );

  // Active
  keycode_tp keycode;
  while (frame->active_element != 0) {
    if (frame->active_element == 1) {
      keycode = ActiveListView(list_view);
      if (keycode == ENTER)
        frame->active_element = 2;
      else if (keycode == ESC)
        frame->active_element = 0;
    } else if (frame->active_element == 2) {
      if (list_view->selected_item == 0) {
        material_frame->active_element = 1;
        ActiveMaterialFrame(material_frame);
        frame->active_element = 1;
      } else if (list_view->selected_item == 1) {
        frame->active_element = 0;
      } else if (list_view->selected_item == 2) {
        frame->active_element = 1;
      } else if (list_view->selected_item == 3) {
        frame->active_element = 1;
      } else if (list_view->selected_item == 4) {
        frame->active_element = 1;
      }
    }
  }

  // Release
  DestroyLinearList(linear_list);
  DestroyListView(list_view);
}

#ifdef __cplusplus
}
#endif

#endif
