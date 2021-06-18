
#include "material.h"
bool MTPAddButtonConsole(keycode_tp c) {
  return (c == KEY_LEFT || c == KEY_DOWN || c == ENTER || c == BACKSPACE);
}

void MTPRecovery(Frame frame) {
  DrawRecShape(
    MTP_MATERIAL_LIST_ITEM_WIDTH, 3, ' ',
    frame->position_x + 2, frame->position_y + 1,
    CURRENT_FOREGROUND, PROGRAM_THEME_BACKGROUND_LV1
  );

  DrawRecShape(
    MTP_MATERIAL_LIST_ITEM_WIDTH, WINDOW_ROWS - 6, ' ',
    frame->position_x + 2, frame->position_y + 5,
    CURRENT_FOREGROUND, PROGRAM_THEME_BACKGROUND_LV1
  );
}

void ActiveMaterialFrame(Frame frame) {
  // Button
  Button add_button = NewButton(
    "Thêm",
    MTP_ADD_BUTTON_WIDTH, MTP_ADD_BUTTON_HEIGHT, 0,
    frame->position_x + 2, frame->position_y + 1,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_THEME_FOREGROUND, PROGRAM_BACKGROUND,
    MTPAddButtonConsole
  );

  // Material List
  LinearList linear_list = NewLinearList(MTP_MATERIAL_LIST_ITEMS);

  ListViewItemContext list_view_item_context = NewListViewItemContext(
    MTP_MATERIAL_LIST_ITEM_WIDTH, MTP_MATERIAL_LIST_ITEM_HEIGHT,
    0, 0,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_THEME_FOREGROUND, PROGRAM_BACKGROUND,
    NULL, NULL
  );

  ListView list_view = NewListView(
    linear_list,
    MTP_MATERIAL_LIST_WIDTH, MTP_MATERIAL_LIST_HEIGHT,
    frame->position_x + 2, frame->position_y + 5,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    list_view_item_context,
    RENDER_LIST_VIEW_ITEM_WITH_DATA_AS_MATERIAL,
    ACTIVE_LIST_VIEW_ITEM_WITH_DATA_AS_MATERIAL,
    LIST_VIEW_EB_CONSOLE,
    0
  );

  int page = 0;

  RenderButton(add_button);
  RenderMaterialListView(list_view, page);

  // creation
  Frame creation_frame = NewFrame(50, 17, frame->position_x + 25, frame->position_y + frame->height / 2 - 9, 1);

  // Active
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
        creation_frame->active_element = 1;
        MTPRecovery(frame);
        ActiveMaterialCreationFrame(creation_frame);
        RenderButton(add_button);
        RenderMaterialListView(list_view, page);
        frame->active_element = 1;
      } else if (keycode == BACKSPACE) {
         frame->active_element = 0;
      }
    } else if (frame->active_element == 2) {
      // List
      keycode = ActiveMaterialListView(list_view, page);
      if (keycode == ENTER) {
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
  DestroyLinearList(linear_list);
  DestroyListView(list_view);
  DestroyFrame(creation_frame);

  // Recovery
  MTPRecovery(frame);
}
