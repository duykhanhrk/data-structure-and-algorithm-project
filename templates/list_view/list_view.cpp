ListView NewListView(
  LinearList linear_list = NULL,
  size_tp width = LIST_VIEW_HEIGHT,
  size_tp height = LIST_VIEW_WIDTH,
  position_tp position_x = CURSOR_POSITION_X,
  position_tp position_y = CURSOR_POSITION_Y,
  color_tp foreground = LIST_VIEW_FOREGROUND,
  color_tp background = LIST_VIEW_BACKGROUND,
  color_tp active_foreground = LIST_VIEW_ACTIVE_FOREGROUND,
  color_tp active_background = LIST_VIEW_ACTIVE_BACKGROUND,
  ListViewItemContext item_context = LIST_VIEW_ITEM_CONTEXT,
  void (* render_item)(ListViewItemContext, status_tp) = LIST_VIEW_RENDER_ITEM,
  keycode_tp (* active_item)(ListViewItemContext) = LIST_VIEW_ACTIVE_ITEM,
  bool (* console)(char) = LIST_VIEW_CONSOLE,
  index_tp selected_item = 0
) {
  ListView list_view = (ListView) malloc(sizeof(ListViewT));

  list_view->linear_list = linear_list;
  list_view->position_x = position_x;
  list_view->position_y = position_y;
  list_view->width = width;
  list_view->height = height;
  list_view->foreground = foreground;
  list_view->background = background;
  list_view->active_background = active_background;
  list_view->active_foreground = active_foreground;
  list_view->item_context = item_context;
  list_view->render_item = render_item;
  list_view->active_item = active_item;
  list_view->console = console;
  list_view->selected_item = selected_item;

  return list_view;
}

void DestroyListView(ListView &list_view) {
  free(list_view);
  list_view = NULL;
}

void RenderListView(ListView list_view, status_tp status = NORMAL_LIST_VIEW) {
  color_tp foreground = list_view->foreground;
  color_tp background = list_view->background;

  if (status == ACTIVE_LIST_VIEW) {
    foreground = list_view->active_foreground;
    background = list_view->active_background;
  }

  DrawRecShape(
    list_view->width,
    list_view->height,
    ' ',
    list_view->position_x,
    list_view->position_y,
    foreground,
    background
  );

  // Render Items
  for (int interact = 0; interact < list_view->linear_list->count; interact ++) {
    list_view->item_context->position_x = list_view->position_x;
    list_view->item_context->position_y = list_view->position_y + interact * list_view->item_context->height;
    list_view->item_context->data = list_view->linear_list->data[interact];
    list_view->render_item(list_view->item_context, NORMAL_LIST_VIEW_ITEM);
  }
}

void LVPSelectItem(ListView list_view) {
  if (list_view->selected_item < 0 || list_view->selected_item >= list_view->linear_list->count)
    return;

  list_view->item_context->position_x = list_view->position_x;
  list_view->item_context->position_y = list_view->position_y + list_view->selected_item * list_view->item_context->height;
  list_view->item_context->data = list_view->linear_list->data[list_view->selected_item];
  list_view->active_item(list_view->item_context);
}

keycode_tp ActiveListView(ListView list_view) {
  list_view->item_context->console = NULL;
  LVPSelectItem(list_view);
  if (list_view->console == NULL) return NULL_KEY;

  keycode_tp keycode = Console();
  while (!list_view->console(keycode)) {
    if (keycode == KEY_DOWN) {
      list_view->render_item(list_view->item_context, NORMAL_LIST_VIEW_ITEM);
      if (list_view->selected_item == list_view->linear_list->count - 1)
        list_view->selected_item = -1;
      list_view->selected_item ++;
      LVPSelectItem(list_view);
    } else if (keycode == KEY_UP) {
      list_view->render_item(list_view->item_context, NORMAL_LIST_VIEW_ITEM);
      if (list_view->selected_item == 0)
        list_view->selected_item = list_view->linear_list->count;
      list_view->selected_item --;
      LVPSelectItem(list_view);
    }

    keycode = Console();
  }

  list_view->render_item(list_view->item_context, NORMAL_LIST_VIEW_ITEM);
  return keycode;
}

keycode_tp ActiveListViewStraight(ListView list_view) {
  list_view->item_context->console = NULL;
  LVPSelectItem(list_view);
  if (list_view->console == NULL) return NULL_KEY;

  keycode_tp keycode;
  while (true) {
    keycode = Console();
    if (list_view->console(keycode)) break;
    if (keycode == KEY_DOWN) {
      list_view->render_item(list_view->item_context, NORMAL_LIST_VIEW_ITEM);
      if (list_view->selected_item == list_view->linear_list->count - 1)
        break;
      list_view->selected_item ++;
      LVPSelectItem(list_view);
    } else if (keycode == KEY_UP) {
      list_view->render_item(list_view->item_context, NORMAL_LIST_VIEW_ITEM);
      if (list_view->selected_item == 0)
        break;
      list_view->selected_item --;
      LVPSelectItem(list_view);
    }
  }

  list_view->render_item(list_view->item_context, NORMAL_LIST_VIEW_ITEM);
  return keycode;
}
