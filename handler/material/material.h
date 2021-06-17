/* main */

#ifndef __HANDLER_MATERIAL__
#define __HANDLER_MATERIAL__

#include "creation.h"

#define MATERIAL_LIST_WIDTH 96

#ifdef __cplusplus
extern "C" {
#endif

bool MTPAddButtonConsole(keycode_tp c) {
  return (c == KEY_LEFT || c == KEY_DOWN || c == ENTER || c == ESC);
}

void MTPRecovery(Frame frame) {
  DrawRecShape(
    MATERIAL_LIST_WIDTH, 3, ' ',
    frame->position_x + 2, frame->position_y + 1,
    CURRENT_FOREGROUND, PROGRAM_THEME_BACKGROUND_LV1
  );

  DrawRecShape(
    MATERIAL_LIST_WIDTH, WINDOW_ROWS - 6, ' ',
    frame->position_x + 2, frame->position_y + 5,
    CURRENT_FOREGROUND, PROGRAM_THEME_BACKGROUND_LV1
  );
}

void ActiveMaterialFrame(Frame frame) {
  // Button
  Button add_button = NewButton(
    "Thêm", 48, 3, 0, frame->position_x + 2, frame->position_y + 1,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_THEME_FOREGROUND, PROGRAM_BACKGROUND,
    MTPAddButtonConsole
  );

  LinearList linear_list = NewLinearList(24);
  GetMaterialsInArchive(linear_list, 1, 24);

  ListViewItemContext list_view_item_context = NewListViewItemContext(
    MATERIAL_LIST_WIDTH, 1, 0, 0,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_THEME_FOREGROUND, PROGRAM_BACKGROUND,
    NULL, NULL
  );

  ListView list_view = NewListView(
    linear_list, MATERIAL_LIST_WIDTH, WINDOW_ROWS - 6,
    frame->position_x + 2, frame->position_y + 5,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    list_view_item_context,
    RenderListViewItemWithDataAsMaterial,
    ActiveListViewItemWithDataAsMaterial,
    LIST_VIEW_EE_CONSOLE,
    0
  );

  RenderButton(add_button);
  RenderListView(list_view, NORMAL_LIST_VIEW);

  // creation
  Frame creation_frame = NewFrame(50, 17, frame->position_x + 25, frame->position_y + frame->height / 2 - 9, 1);

  // Active
  keycode_tp keycode;
  while (frame->active_element != 0) {
    if (frame->active_element == 1) {
      // Add button
      keycode = ActiveButton(add_button);
      if (keycode == KEY_LEFT)
        frame->active_element = 0;
      else if (keycode == KEY_DOWN)
        frame->active_element = 2;
      else if (keycode == ENTER) {
        creation_frame->active_element = 1;
        MTPRecovery(frame);
        ActiveMaterialCreationFrame(creation_frame);
        RenderButton(add_button);
        RenderListView(list_view, NORMAL_LIST_VIEW);
        frame->active_element = 1;
      } else if (keycode == ESC)
        frame->active_element = 0;
    } else if (frame->active_element == 2) {
      // List
      keycode = ActiveListView(list_view);
      if (keycode == ENTER)
        frame->active_element = 2;
      else if (keycode == ESC)
        frame->active_element = 1;
    }
  }

  // Release
  DestroyButton(add_button);
  DestroyLinearList(linear_list);
  DestroyListView(list_view);
  DestroyFrame(creation_frame);

  // Recovery
  MTPRecovery(frame);
}

#ifdef __cplusplus
}
#endif

#endif
