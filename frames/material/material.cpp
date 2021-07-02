
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
    " Thêm", ALIGN_CENTER,
    MTP_ADD_BUTTON_WIDTH, MTP_ADD_BUTTON_HEIGHT, 0,
    frame->position_x + 2, frame->position_y + 1,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_THEME_FOREGROUND, PROGRAM_BACKGROUND,
    MTPAddButtonConsole
  );

  // Material list view
  ListViewScroll list_view_scroll = NewListViewScroll(
    MATERIAL_LIST_IN_ARCHIVE, // data
    NULL,
    0, 4, // page, fields count
    CountMaterials, // items count
    TakeMaterials, // take items
    MTP_MATERIAL_LIST_WIDTH, MTP_MATERIAL_LIST_HEIGHT,
    frame->position_x + 2, frame->position_y + 5,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    MTP_MATERIAL_LIST_ITEM_WIDTH, MTP_MATERIAL_LIST_ITEM_HEIGHT,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_THEME_FOREGROUND, PROGRAM_BACKGROUND,
    RENDER_LIST_VIEW_ITEM_WITH_DATA_AS_MATERIAL,
    ACTIVE_LIST_VIEW_ITEM_WITH_DATA_AS_MATERIAL,
    LIST_VIEW_SCROLL_EB_CONSOLE,
    0
  );

  AddFieldForListViewScroll(list_view_scroll, "Mã", 10);
  AddFieldForListViewScroll(list_view_scroll, "Tên", 56);
  AddFieldForListViewScroll(list_view_scroll, "ĐVT", 10);
  AddFieldForListViewScroll(list_view_scroll, "Số lượng", 10);

  // creation
  Frame creation_frame = NewFrame(
    MTP_CREATION_FORM_WIDTH, MTP_CREATION_FORM_HEIGHT,
    frame->position_x + (frame->width - MTP_CREATION_FORM_WIDTH) / 2,
    frame->position_y + (frame->height - MTP_CREATION_FORM_HEIGHT) / 2
  );

  // updated
  Frame updated_frame = NewFrame(
    MTP_UPDATED_FORM_WIDTH, MTP_UPDATED_FORM_HEIGHT,
    frame->position_x + (frame->width - MTP_UPDATED_FORM_WIDTH) / 2,
    frame->position_y + (frame->height - MTP_UPDATED_FORM_HEIGHT) / 2
  );

  RenderButton(add_button);
  RenderListViewScroll(list_view_scroll);

  // Active
  Material material;
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
        RenderListViewScroll(list_view_scroll);
        frame->active_element = 1;
      } else if (keycode == BACKSPACE) {
         frame->active_element = 0;
      }
    } else if (frame->active_element == 2) {
      // List
      keycode = ActiveListViewScroll(list_view_scroll);
      if (keycode == ENTER) {
        updated_frame->active_element = 2;
        MTPRecovery(frame);
        material = (Material) GetItemInLinearListByIndex(
          list_view_scroll->list_view->linear_list,
          list_view_scroll->list_view->selected_item
        );
        if (material == NULL) continue;
        ActiveMaterialUpdatedFrame(updated_frame, material);
        RenderButton(add_button);
        RenderListViewScroll(list_view_scroll);
        frame->active_element = 2;
      } else if (keycode == BACKSPACE) {
        frame->active_element = 1;
      } else if (keycode == KEY_UP) {
        frame->active_element = 1;
      } else if (keycode == NULL_KEY) {
        frame->active_element = 1;
      }
    }
  }

  // Release
  DestroyButton(add_button);
  DestroyListViewScroll(list_view_scroll);
  DestroyFrame(creation_frame);
  DestroyFrame(updated_frame);

  // Recovery
  MTPRecovery(frame);
}
