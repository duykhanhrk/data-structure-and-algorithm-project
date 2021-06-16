/* main */

#ifndef __HANDLER_MATERIAL__
#define __HANDLER_MATERIAL__

#define MATERIAL_LIST_WIDTH 40

#ifdef __cplusplus
extern "C" {
#endif

void ActiveMaterialFrame(Frame frame) {
  // Menu
  LinearList linear_list = NewLinearList(5);
  char item_1[] = "item 1";
  char item_2[] = "item 2";
  char item_3[] = "item 3";
  char item_4[] = "item 4";
  char item_5[] = "imte 5";

  AddItemToLinearList(linear_list, item_1);
  AddItemToLinearList(linear_list, item_2);
  AddItemToLinearList(linear_list, item_3);
  AddItemToLinearList(linear_list, item_4);
  AddItemToLinearList(linear_list, item_5);

  ListViewItemContext list_view_item_context = NewListViewItemContext(
    MATERIAL_LIST_WIDTH, 1, 0, 0,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_THEME_FOREGROUND, PROGRAM_BACKGROUND,
    NULL, NULL
  );

  ListView list_view = NewListView(
    linear_list, MATERIAL_LIST_WIDTH, WINDOW_ROWS - 6,
    WINDOW_COLUMNS - MATERIAL_LIST_WIDTH, frame->position_y + 5,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    list_view_item_context,
    RENDER_LIST_VIEW_ITEM_WITH_DATA_AS_STRING,
    ACTIVE_LIST_VIEW_ITEM_WITH_DATA_AS_STRING,
    LIST_VIEW_EE_CONSOLE,
    0
  );

  RenderListView(list_view, NORMAL_LIST_VIEW);

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
        frame->active_element = 1;
      } else if (list_view->selected_item == 1) {
        frame->active_element = 1;
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
