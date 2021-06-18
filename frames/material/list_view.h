#ifndef __FRAMES_MATERIAL_LIST_VIEW__
#define __FRAMES_MATERIAL_LIST_VIEW__

#ifdef __cplusplus
extern "C" {
#endif

void RenderMaterialListView(ListView list_view, int page) {
  // Header
  DrawRecShape(
    list_view->width, 1,
    ' ',
    list_view->position_x, list_view->position_y,
    PROGRAM_FOREGROUND, PROGRAM_BACKGROUND_LV1
  );

  position_tp position_x = list_view->position_x;
  position_tp position_y = list_view->position_y;
  color_tp foreground = PROGRAM_FOREGROUND;
  color_tp background = PROGRAM_BACKGROUND_LV1;

  WriteStr("Mã", position_x + 2, position_y, foreground, background);
  WriteStr("Tên", position_x + 14, position_y, foreground, background);
  WriteStr("ĐVT", position_x + 72, position_y, foreground, background);
  WriteStr("Số lượng", position_x + 84, position_y, foreground, background);

  // List
  list_view->position_y ++;
  list_view->height -= 2;
  TakeMaterialsInArchive(list_view->linear_list, page * (list_view->height), list_view->height);
  RenderListView(list_view);
  list_view->position_y --;
  list_view->height += 2;

  // Footer
  DrawRecShape(
    list_view->width, 1,
    ' ',
    list_view->position_x, list_view->position_y + list_view->height - 1,
    PROGRAM_FOREGROUND, PROGRAM_BACKGROUND_LV1
  );

  int material_list_count = MaterialListCount(archive->material_list);
  int total_page = material_list_count / (list_view->height - 2);
  if (material_list_count % (list_view->height - 2) != 0)
    total_page ++;

  WriteStr("Tổng số: ", list_view->position_x + 2, list_view->position_y + list_view->height - 1, PROGRAM_FOREGROUND, PROGRAM_BACKGROUND_LV1);
  WriteInt(material_list_count);
  WriteStr("Trang: ", list_view->position_x + 72);
  WriteInt(page + 1);
  WriteChar('/');
  WriteInt(total_page);
}

keycode_tp ActiveMaterialListView(ListView list_view, int &page) {
  int material_list_count = MaterialListCount(archive->material_list);
  int total_page = material_list_count / (list_view->height - 2);
  if (material_list_count % (list_view->height - 2) != 0)
    total_page ++;
  list_view->position_y ++;
  list_view->height -= 2;

  keycode_tp keycode;
  do {
    keycode = ActiveListViewStraight(list_view);
    if (keycode == KEY_UP) {
      if (page == 0) break;
      page --;
      TakeMaterialsInArchive(list_view->linear_list, page * (list_view->height), list_view->height);
      WriteInt(page + 1, list_view->position_x + 79, list_view->position_y + list_view->height, PROGRAM_FOREGROUND, PROGRAM_BACKGROUND_LV1);
      WriteChar('/', CURSOR_POSITION_X, CURSOR_POSITION_Y, PROGRAM_FOREGROUND, PROGRAM_BACKGROUND_LV1);
      WriteInt(total_page, CURSOR_POSITION_X, CURSOR_POSITION_Y, PROGRAM_FOREGROUND, PROGRAM_BACKGROUND_LV1);
      RenderListView(list_view);
      list_view->selected_item = list_view->linear_list->count - 1;
    } else if (keycode == KEY_DOWN) {
      if ((page + 1) * (list_view->height - 2) >= material_list_count) continue;
      page ++;
      TakeMaterialsInArchive(list_view->linear_list, page * (list_view->height), list_view->height);
      WriteInt(page + 1, list_view->position_x + 79, list_view->position_y + list_view->height, PROGRAM_FOREGROUND, PROGRAM_BACKGROUND_LV1);
      WriteChar('/', CURSOR_POSITION_X, CURSOR_POSITION_Y, PROGRAM_FOREGROUND, PROGRAM_BACKGROUND_LV1);
      WriteInt(total_page, CURSOR_POSITION_X, CURSOR_POSITION_Y, PROGRAM_FOREGROUND, PROGRAM_BACKGROUND_LV1);
      RenderListView(list_view);
      list_view->selected_item = 0;
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
