#ifndef __TEMPLATE_LIST_VIEW__
#define __TEMPLATE_LIST_VIEW__

/* default value */
#define LIST_VIEW_FOREGROUND PROGRAM_FOREGROUND
#define LIST_VIEW_BACKGROUND PROGRAM_BACKGROUND
#define LIST_VIEW_ACTIVE_FOREGROUND PROGRAM_FOREGROUND
#define LIST_VIEW_ACTIVE_BACKGROUND PROGRAM_BACKGROUND

#define LIST_VIEW_WIDTH 0
#define LIST_VIEW_HEIGHT 0
#define LIST_VIEW_CONSOLE STANDARD_CONSOLE

#define LIST_VIEW_ITEM_CONTEXT NewListViewItemContext()
#define LIST_VIEW_RENDER_ITEM RenderListViewItemWithDataAsString
#define LIST_VIEW_ACTIVE_ITEM ActiveListViewItemWithDataAsString

#define NORMAL_LIST_VIEW 0
#define ACTIVE_LIST_VIEW 1

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ListViewT {
  position_tp position_x;
  position_tp position_y;
  size_tp width;
  size_tp height;
  color_tp foreground;
  color_tp background;
  color_tp active_foreground;
  color_tp active_background;
  ListViewItemContext item_context;
  LinearList linear_list;
  bool (* console)(char);
  index_tp selected_item;
  void (* render_item)(ListViewItemContext, status_tp);
  keycode_tp (* active_item)(ListViewItemContext);
} ListViewT, * ListView;

void DestroyListView(ListView &);

void RenderListView(ListView, status_tp);
keycode_tp ActiveListView(ListView);

/* includes */

#include "list_view.cpp"

#ifdef __cplusplus
}
#endif

#endif
