#include "material_selection_list.h"

void MLPRecovery(Frame frame) {
  DrawRecShape(
    MLP_MATERIAL_LIST_ITEM_WIDTH, WINDOW_ROWS - 6, ' ',
    frame->position_x + 2, frame->position_y + 5,
    CURRENT_FOREGROUND, PROGRAM_THEME_BACKGROUND_LV1
  );
}

Material ActiveMaterialSelectionListFrame(Frame frame) {
  // Default
  frame->active_element = 1;
  // Material list view
  ListViewScroll list_view_scroll = NewListViewScroll(
    MATERIAL_LIST_IN_ARCHIVE, // data
    NULL, // filter
    0, 4, // page, fields count
    CountMaterials, // items count
    TakeMaterials, // take items
    MLP_MATERIAL_LIST_WIDTH, frame->height - 2,
    frame->position_x + 2, frame->position_y + 1,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND,
    MLP_MATERIAL_LIST_ITEM_WIDTH, MLP_MATERIAL_LIST_ITEM_HEIGHT,
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

  // Render
  RenderListViewScroll(list_view_scroll);

  // Active
  Material material = NULL;
  keycode_tp keycode;
  while (frame->active_element != 0) {
    if (frame->active_element == 1) {
      keycode = ActiveListViewScroll(list_view_scroll);
      if (keycode == ENTER) {
        material = (Material) GetSelectedItemInListViewScroll(list_view_scroll);
        frame->active_element = 0;
      } else if (keycode == BACKSPACE) {
        frame->active_element = 0;
      }
    }
  }

  // Recovery
  ConcealListViewScroll(list_view_scroll);

  // Release
  DestroyListViewScroll(list_view_scroll);

  return material;
}
