#ifndef __TEMPLATE_LIST_VIEW_ITEM_CONTEXT__
#define __TEMPLATE_LIST_VIEW_ITEM_CONTEXT__

#define RENDER_LIST_VIEW_ITEM_WITH_DATA_AS_STRING RenderListViewItemWithDataAsString
#define ACTIVE_LIST_VIEW_ITEM_WITH_DATA_AS_STRING ActiveListViewItemWithDataAsString

/* default value */
#define LIST_VIEW_ITEM_FOREGROUND PROGRAM_FOREGROUND_REVERSE
#define LIST_VIEW_ITEM_BACKGROUND PROGRAM_THEME_BACKGROUND
#define LIST_VIEW_ITEM_ACTIVE_FOREGROUND PROGRAM_THEME_FOREGROUND
#define LIST_VIEW_ITEM_ACTIVE_BACKGROUND PROGRAM_BACKGROUND

#define LIST

#define LIST_VIEW_ITEM_WIDTH 20
#define LIST_VIEW_ITEM_HEIGHT 3
#define LIST_VIEW_ITEM_CONSOLE STANDARD_CONSOLE

#define NORMAL_LIST_VIEW_ITEM 0
#define ACTIVE_LIST_VIEW_ITEM 1

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ListViewItemContextT {
  position_tp position_x;
  position_tp position_y;
  size_tp height;
  size_tp width;
  color_tp foreground;
  color_tp background;
  color_tp active_foreground;
  color_tp active_background;
  bool (* console)(char);
  void * data;
} ListViewItemContextT, * ListViewItemContext;

ListViewItemContext NewListViewItemContext(
  size_tp,
  size_tp,
  position_tp,
  position_tp,
  color_tp,
  color_tp,
  color_tp,
  color_tp,
  bool (*)(char),
  void * data
);

void DestroyListViewItemContext(ListViewItemContext &);
void RenderListViewItemWithDataAsString(ListViewItemContext, status_tp);
keycode_tp ActiveListViewItemWithDataAsString(ListViewItemContext);

/* includes */

#include "list_view_item_context.cpp"

#ifdef __cplusplus
}
#endif

#endif
