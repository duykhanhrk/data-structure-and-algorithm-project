#ifndef __FRAMES_MATERIAL_MATERIAL_LIST_VIEW__
#define __FRAMES_MATERIAL_MATERIAL_LIST_VIEW__

#ifdef __cplusplus
extern "C" {
#endif

// Render Header
void MTPRenderMaterialListViewHeader(ListView list_view) {
  position_tp position_x = list_view->position_x;
  position_tp position_y = list_view->position_y;
  color_tp foreground = PROGRAM_FOREGROUND;
  color_tp background = PROGRAM_BACKGROUND_LV1;

  DrawRecShape(
    list_view->width, 1,
    ' ',
    position_x, position_y,
    foreground, background
  );

  WriteStr("Mã", position_x + 2, position_y, foreground, background);
  WriteStr("Tên", position_x + 14, position_y, foreground, background);
  WriteStr("ĐVT", position_x + 72, position_y, foreground, background);
  WriteStr("Số lượng", position_x + 84, position_y, foreground, background);
}

// Render Footer
void MTPRenderMaterialListViewFooter(ListView list_view, int page) {
  position_tp position_x = list_view->position_x;
  position_tp position_y = list_view->position_y + list_view->height - 1;
  color_tp foreground = PROGRAM_FOREGROUND;
  color_tp background = PROGRAM_BACKGROUND_LV1;

  int material_list_count = MaterialListCount(archive->material_list);
  int total_page = material_list_count / ((list_view->height - 2) / list_view->item_context->height);
  if (material_list_count % ((list_view->height - 2) / list_view->item_context->height) != 0)
    total_page ++;

  DrawRecShape(
    list_view->width, 1,
    ' ',
    position_x, position_y,
    foreground, background
  );

  WriteStr("Tổng số: ", position_x + 2, position_y, foreground, background);
  WriteInt(material_list_count, CURSOR_POSITION_X, CURSOR_POSITION_Y, foreground, background);
  WriteStr("Trang: ", list_view->position_x + 72, CURSOR_POSITION_Y, foreground, background);
  WriteInt(page + 1, CURSOR_POSITION_X, CURSOR_POSITION_Y, foreground, background);
  WriteChar('/', CURSOR_POSITION_X, CURSOR_POSITION_Y, foreground, background);
  WriteInt(total_page, CURSOR_POSITION_X, CURSOR_POSITION_Y, foreground, background);
}

void RenderMaterialListView(ListView list_view, int page) {
  // Header
  MTPRenderMaterialListViewHeader(list_view);

  // List (exclude header and footer)
  list_view->position_y ++;
  list_view->height -= 2;
  int limit = (list_view->height / list_view->item_context->height);
  TakeMaterialsInArchive(list_view->linear_list, page * limit, limit);
  RenderListView(list_view);
  list_view->position_y --;
  list_view->height += 2;

  // Footer
  MTPRenderMaterialListViewFooter(list_view, page);
}

void MTPUpdatePageOnMaterialListViewFooter(ListView list_view, int page, int total_page) {
  WriteInt(page + 1, list_view->position_x + 79, list_view->position_y + list_view->height, PROGRAM_FOREGROUND, PROGRAM_BACKGROUND_LV1);
  WriteChar('/', CURSOR_POSITION_X, CURSOR_POSITION_Y, PROGRAM_FOREGROUND, PROGRAM_BACKGROUND_LV1);
  WriteInt(total_page, CURSOR_POSITION_X, CURSOR_POSITION_Y, PROGRAM_FOREGROUND, PROGRAM_BACKGROUND_LV1);
}

void MTPMaterialListViewTurnToPage(ListView list_view, int limit, int page, int total_page) {
  TakeMaterialsInArchive(list_view->linear_list, page * limit, limit);
  MTPUpdatePageOnMaterialListViewFooter(list_view, page, total_page);
  RenderListView(list_view);
}

keycode_tp ActiveMaterialListView(ListView list_view, int &page) {
  list_view->position_y ++;
  list_view->height -= 2;

  int material_list_count = MaterialListCount(archive->material_list);
  int total_page = material_list_count / (list_view->height / list_view->item_context->height);
  if (material_list_count % (list_view->height / list_view->item_context->height) != 0)
    total_page ++;
  int limit = (list_view->height / list_view->item_context->height);

  keycode_tp keycode;
  do {
    keycode = ActiveListViewStraight(list_view);

    if (keycode == KEY_UP) {
      if (page == 0) break;
      page --;
      MTPMaterialListViewTurnToPage(list_view, limit, page, total_page);
      list_view->selected_item = list_view->linear_list->count - 1;
    } else if (keycode == KEY_DOWN) {
      if ((page + 1) * limit >= material_list_count) continue;
      page ++;
      MTPMaterialListViewTurnToPage(list_view, limit, page, total_page);
      list_view->selected_item = 0;
    } else if (keycode == KEY_LEFT) {
      if (page == 0) {
        keycode = NULL_KEY;
        continue;
      }

      page --;
      MTPMaterialListViewTurnToPage(list_view, limit, page, total_page);
    } else if (keycode == KEY_RIGHT) {
      if ((page + 1) * limit >= material_list_count) {
        keycode = NULL_KEY;
        continue;
      }

      page ++;
      MTPMaterialListViewTurnToPage(list_view, limit, page, total_page);
    }
  } while (!list_view->console(keycode));

  list_view->position_y --;
  list_view->height += 2;
  return keycode;
}

/* includes */

// #include "list_view.cpp"

#ifdef __cplusplus
}
#endif

#endif
