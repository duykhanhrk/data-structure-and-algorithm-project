#ifndef __TEMPLATES_LIST_VIEW_SCROLL__
#define __TEMPLATES_LIST_VIEW_SCROLL__

#define LIST_VIEW_SCROLL_FOOTER_HEIGHT 1
#define LIST_VIEW_SCROLL_HEADER_HEIGHT 1

#define LIST_VIEW_SCROLL_FOOTER_FOREGROUND PROGRAM_FOREGROUND
#define LIST_VIEW_SCROLL_FOOTER_BACKGROUND PROGRAM_BACKGROUND_LV1

#define LIST_VIEW_SCROLL_HEADER_FOREGROUND PROGRAM_FOREGROUND
#define LIST_VIEW_SCROLL_HEADER_BACKGROUND PROGRAM_BACKGROUND_LV1


#ifdef __cplusplus
extern "C" {
#endif

typedef struct ListViewScrollFieldT {
  char * name;
  size_tp width;
} ListViewScrollFieldT, * ListViewScrollField;

ListViewScrollField NewListViewScrollField(const char * name, int width) {
  ListViewScrollField field = (ListViewScrollField) malloc(sizeof(ListViewScrollFieldT));
  field->name = (char *) malloc(strlen(name) + 1);
  strcpy(field->name, name);
  field->width = width;

  return field;
}

void DestroyListViewScrollField(ListViewScrollField &field) {
  free(field->name);
  free(field);
  field =NULL;
}

typedef struct ListViewScrollT {
  void * data;
  void * filter;
  int page;
  LinearList fields;
  int (* items_count) (void *, void *);
  void (* take_items) (void *, void *, LinearList, int, int);
  ListView list_view;
} ListViewScrollT, * ListViewScroll;

ListViewScroll NewListViewScroll(
  void * data,
  void * filter,
  int page,
  int fields_count,
  int (* items_count) (void *, void *),
  void (* take_items) (void *, void *, LinearList, int, int),
  size_tp width = LIST_VIEW_WIDTH,
  size_tp height = LIST_VIEW_HEIGHT,
  position_tp position_x = CURSOR_POSITION_X,
  position_tp position_y = CURSOR_POSITION_Y,
  color_tp foreground = LIST_VIEW_FOREGROUND,
  color_tp background = LIST_VIEW_BACKGROUND,
  color_tp active_foreground = LIST_VIEW_ACTIVE_FOREGROUND,
  color_tp active_background = LIST_VIEW_ACTIVE_BACKGROUND,
  size_tp item_width = LIST_VIEW_ITEM_HEIGHT,
  size_tp item_height = LIST_VIEW_ITEM_WIDTH,
  color_tp item_foreground = LIST_VIEW_ITEM_FOREGROUND,
  color_tp item_background = LIST_VIEW_ITEM_BACKGROUND,
  color_tp item_active_foreground = LIST_VIEW_ITEM_ACTIVE_FOREGROUND,
  color_tp item_active_background = LIST_VIEW_ITEM_ACTIVE_BACKGROUND,
  void (* render_item)(ListViewItemContext, status_tp) = LIST_VIEW_RENDER_ITEM,
  keycode_tp (* active_item)(ListViewItemContext) = LIST_VIEW_ACTIVE_ITEM,
  bool (* console)(char) = LIST_VIEW_CONSOLE,
  index_tp selected_item = 0
) {
  ListViewScroll list_view_scroll = (ListViewScroll) malloc(sizeof(ListViewScrollT));
  list_view_scroll->data = data;
  list_view_scroll->filter = filter;
  list_view_scroll->page = page;
  list_view_scroll->fields = NewLinearList(fields_count);
  list_view_scroll->items_count = items_count;
  list_view_scroll->take_items = take_items;
  list_view_scroll->list_view = NewListView(
    height, // max_items
    width, height - (LIST_VIEW_SCROLL_HEADER_HEIGHT + LIST_VIEW_SCROLL_FOOTER_HEIGHT),
    position_x, position_y + LIST_VIEW_SCROLL_HEADER_HEIGHT,
    foreground, background,
    active_foreground, active_foreground,
    item_width, item_height,
    item_foreground, item_background,
    item_active_foreground, item_active_background,
    render_item, active_item,
    console,
    selected_item
  );

  return list_view_scroll;
}

void DestroyListViewScroll(ListViewScroll &list_view_scroll) {
  for (int interact = 0; interact < LinearListCount(list_view_scroll->fields); interact ++)
    free((ListViewScrollField) GetItemInLinearListByIndex(list_view_scroll->fields, interact));
  DestroyLinearList(list_view_scroll->fields);
  DestroyListView(list_view_scroll->list_view);
  free(list_view_scroll);
  list_view_scroll = NULL;
}

void AddFieldForListViewScroll(ListViewScroll list_view_scroll, const char * name, int width) {
  AddItemToLinearList(list_view_scroll->fields, NewListViewScrollField(name, width));
}

void * GetSelectedItemInListViewScroll(ListViewScroll list_view_scroll) {
  return GetItemInLinearListByIndex(list_view_scroll->list_view->linear_list, list_view_scroll->list_view->selected_item);
}

// Render Header
void LVPRenderListViewScrollHeader(ListViewScroll list_view_scroll) {
  size_tp width = list_view_scroll->list_view->width;
  size_tp height = LIST_VIEW_SCROLL_HEADER_HEIGHT;
  position_tp position_x = list_view_scroll->list_view->position_x;
  position_tp position_y = list_view_scroll->list_view->position_y - height;
  color_tp foreground = LIST_VIEW_SCROLL_HEADER_FOREGROUND;
  color_tp background = LIST_VIEW_SCROLL_HEADER_BACKGROUND;

  DrawRecShape(width, height, ' ', position_x, position_y, foreground, background);

  ListViewScrollField field;
  int used_width = 2;
  for (int interact = 0; interact < LinearListCount(list_view_scroll->fields); interact ++) {
    field = (ListViewScrollField) GetItemInLinearListByIndex(list_view_scroll->fields, interact);
    WriteStr(field->name, position_x + used_width, position_y + height / 2, foreground, background);
    used_width += field->width + 2;
  }
}

// Render Footer
void LVPRenderListViewScrollFooter(ListViewScroll list_view_scroll) {
  size_tp width = list_view_scroll->list_view->width;
  size_tp height = LIST_VIEW_SCROLL_FOOTER_HEIGHT;
  position_tp position_x = list_view_scroll->list_view->position_x;
  position_tp position_y = list_view_scroll->list_view->position_y
    + list_view_scroll->list_view->height;
  color_tp foreground = LIST_VIEW_SCROLL_FOOTER_FOREGROUND;
  color_tp background = LIST_VIEW_SCROLL_FOOTER_BACKGROUND;

  int items_count = list_view_scroll->items_count(list_view_scroll->data, list_view_scroll->filter);
  int total_page = items_count / ((list_view_scroll->list_view->height) / list_view_scroll->list_view->item_context->height);
  if (items_count % ((list_view_scroll->list_view->height) / list_view_scroll->list_view->item_context->height) != 0)
    total_page ++;

  DrawRecShape(width, height, ' ', position_x, position_y, foreground, background);

  WriteStr("Tổng số: ", position_x + 2, position_y, foreground, background);
  WriteInt(items_count, CURSOR_POSITION_X, position_y, foreground, background);
  WriteStr("Trang: ", position_x + width - 24, position_y, foreground, background);
  WriteInt(list_view_scroll->page + 1, CURSOR_POSITION_X, position_y, foreground, background);
  WriteChar('/', CURSOR_POSITION_X, position_y, foreground, background);
  WriteInt(total_page, CURSOR_POSITION_X, position_y, foreground, background);
}

void RenderListViewScroll(ListViewScroll list_view_scroll) {
  // Header
  LVPRenderListViewScrollHeader(list_view_scroll);

  // List (exclude header and footer)
  int limit = (list_view_scroll->list_view->height / list_view_scroll->list_view->item_context->height);

  // OPTIMIZE: Blank page
  int items_count = list_view_scroll->items_count(list_view_scroll->data, list_view_scroll->filter);
  if (list_view_scroll->page * limit >= items_count) {
    list_view_scroll->page = items_count / ((list_view_scroll->list_view->height) / list_view_scroll->list_view->item_context->height) - 1;
    list_view_scroll->list_view->selected_item = limit;
  }
  list_view_scroll->page = list_view_scroll->page < 0 ? 0 : list_view_scroll->page;

  // FIXME: Empty linear list with linear list's items are linear lists
//   EmptyLinearList(list_view_scroll->list_view->linear_list);

  list_view_scroll->take_items(list_view_scroll->data, list_view_scroll->filter, list_view_scroll->list_view->linear_list, list_view_scroll->page * limit, limit);
  RenderListView(list_view_scroll->list_view);

  // Footer
  LVPRenderListViewScrollFooter(list_view_scroll);
}

void LVPUpdatePageOnListViewScrollFooter(ListViewScroll list_view_scroll, int total_page) {
  size_tp width = list_view_scroll->list_view->width;
  size_tp height = LIST_VIEW_SCROLL_FOOTER_HEIGHT;
  position_tp position_x = list_view_scroll->list_view->position_x;
  position_tp position_y = list_view_scroll->list_view->position_y
    + list_view_scroll->list_view->height;
  color_tp foreground = LIST_VIEW_SCROLL_FOOTER_FOREGROUND;
  color_tp background = LIST_VIEW_SCROLL_FOOTER_BACKGROUND;

  WriteInt(list_view_scroll->page + 1, position_x + width - 17, position_y, foreground, background);
  WriteChar('/', CURSOR_POSITION_X, position_y, foreground, background);
  WriteInt(total_page, CURSOR_POSITION_X, position_y, foreground, background);
}

void LVPListViewScrollTurnToPage(ListViewScroll list_view_scroll, int limit, int total_page) {
  list_view_scroll->take_items(list_view_scroll->data, list_view_scroll->filter, list_view_scroll->list_view->linear_list, list_view_scroll->page * limit, limit);
  LVPUpdatePageOnListViewScrollFooter(list_view_scroll, total_page);
  RenderListView(list_view_scroll->list_view);
}

keycode_tp ActiveListViewScroll(ListViewScroll list_view_scroll) {
  if (list_view_scroll->items_count(list_view_scroll->data, list_view_scroll->filter) == 0)
    return NULL_KEY;

  int items_count = list_view_scroll->items_count(list_view_scroll->data, list_view_scroll->filter);
  int total_page = items_count / ((list_view_scroll->list_view->height) / list_view_scroll->list_view->item_context->height);
  if (items_count % ((list_view_scroll->list_view->height) / list_view_scroll->list_view->item_context->height) != 0)
    total_page ++;
  int limit = (list_view_scroll->list_view->height / list_view_scroll->list_view->item_context->height);

  keycode_tp keycode;
  do {
    keycode = ActiveListViewStraight(list_view_scroll->list_view);

    if (keycode == KEY_UP) {
      if (list_view_scroll->page == 0) break;
      list_view_scroll->page --;
      LVPListViewScrollTurnToPage(list_view_scroll, limit, total_page);
      list_view_scroll->list_view->selected_item = list_view_scroll->list_view->linear_list->count - 1;
    } else if (keycode == KEY_DOWN) {
      if ((list_view_scroll->page + 1) * limit >= items_count) continue;
      list_view_scroll->page ++;
      LVPListViewScrollTurnToPage(list_view_scroll, limit, total_page);
      list_view_scroll->list_view->selected_item = 0;
    } else if (keycode == KEY_LEFT) {
      if (list_view_scroll->page == 0) {
        keycode = NULL_KEY;
        continue;
      }

      list_view_scroll->page --;
      LVPListViewScrollTurnToPage(list_view_scroll, limit, total_page);
    } else if (keycode == KEY_RIGHT) {
      if ((list_view_scroll->page + 1) * limit >= items_count) {
        keycode = NULL_KEY;
        continue;
      }

      list_view_scroll->page ++;
      LVPListViewScrollTurnToPage(list_view_scroll, limit, total_page);
    }
  } while (!list_view_scroll->list_view->console(keycode));

  return keycode;
}

// conceal
tpp_define_conceal_method_type_a(
  ConcealListViewScroll,
  ListViewScroll,
  list_view->width,
  list_view->height + LIST_VIEW_SCROLL_HEADER_HEIGHT + LIST_VIEW_SCROLL_FOOTER_HEIGHT,
  list_view->position_x,
  list_view->position_y - LIST_VIEW_SCROLL_HEADER_HEIGHT
)

/* includes */

// #include "list_view.cpp"

#ifdef __cplusplus
}
#endif

#endif
