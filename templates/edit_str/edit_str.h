#ifndef __TEMPLATE_EDIT_STR__
#define __TEMPLATE_EDIT_STR__

#define EDIT_STR_MAX_LEN 24
#define EDIT_STR_MIN_LEN 0
#define EDIT_STR_WIDTH 24
#define EDIT_STR_HEIGHT 3
#define EDIT_STR_FOREGROUND PROGRAM_FOREGROUND_REVERSE
#define EDIT_STR_BACKGROUND PROGRAM_THEME_BACKGROUND_LV1
#define EDIT_STR_ACTIVE_FOREGROUND PROGRAM_FOREGROUND
#define EDIT_STR_ACTIVE_BACKGROUND PROGRAM_BACKGROUND

// status
#define NORMAL_EDIT_STR 1
#define ACTIVE_EDIT_STR 2

#ifdef __cplusplus
extern "C" {
#endif

typedef struct EditStrT {
  char * str;
  int max_len;
  int min_len;
  size_tp width;
  size_tp height;
  position_tp position_x;
  position_tp position_y;
  color_tp foreground;
  color_tp background;
  color_tp active_foreground;
  color_tp active_background;
  char (* char_set) (char, const char *);
  bool (* console) (char);
  void (* on_change) (char, EditStrT *);
  void (* miss_char_set) (char, EditStrT *);
  void (* exceed_max_len) (char, EditStrT *);
} EditStrT, * EditStr;

EditStr NewEditStr(
  char * str,
  int max_len = EDIT_STR_MAX_LEN,
  int min_len = EDIT_STR_MIN_LEN,
  size_tp width = EDIT_STR_WIDTH,
  size_tp height = EDIT_STR_HEIGHT,
  position_tp position_x = CURSOR_POSITION_X,
  position_tp position_y = CURSOR_POSITION_Y,
  color_tp foreground = EDIT_STR_FOREGROUND,
  color_tp background = EDIT_STR_BACKGROUND,
  color_tp active_foreground = EDIT_STR_ACTIVE_FOREGROUND,
  color_tp active_background = EDIT_STR_ACTIVE_BACKGROUND,
  char (* char_set) (char, const char *) = STANDARD_CHAR_SET,
  bool (* console) (char) = STANDARD_CONSOLE,
  void (* on_change) (char, EditStrT *) = NULL,
  void (* miss_char_set) (char, EditStrT *) = NULL,
  void (* exceed_max_len) (char, EditStrT *) = NULL
) {
  EditStr edit_str = (EditStr) malloc(sizeof(EditStrT));

  edit_str->str = str;
  edit_str->max_len = max_len;
  edit_str->min_len = min_len;
  edit_str->width = width;
  edit_str->height = height;
  edit_str->position_x = position_x;
  edit_str->position_y = position_y;
  edit_str->foreground = foreground;
  edit_str->background = background;
  edit_str->active_foreground = active_foreground;
  edit_str->active_background = active_background;
  edit_str->char_set = char_set;
  edit_str->console = console;
  edit_str->on_change = on_change;
  edit_str->miss_char_set = miss_char_set;
  edit_str->exceed_max_len = exceed_max_len;

  return edit_str;
}

void DestroyEditStr(EditStr &edit_str) {
  free(edit_str);
  edit_str = NULL;
}

void RenderEditStr(EditStr edit_str, status_tp status = NORMAL_EDIT_STR) {
  color_tp foreground = edit_str->foreground;
  color_tp background = edit_str->background;

  if (status == ACTIVE_EDIT_STR) {
    foreground = edit_str->active_foreground;
    background = edit_str->active_background;
  }

  // Draw container
  DrawRecShape(
    edit_str->width, edit_str->height,
    ' ',
    edit_str->position_x, edit_str->position_y,
    foreground, background
  );

  WriteStr(
    edit_str->str,
    edit_str->position_x + 2, edit_str->position_y + edit_str->height / 2,
    foreground, background
  );
}

keycode_tp ActiveEditStr(EditStr edit_str) {
  RenderEditStr(edit_str, ACTIVE_EDIT_STR);

  CursorVisible(true);
  int len = strlen(edit_str->str);
  char c = '\0';
  while (true) {
    if (edit_str->console(c)) break;
    c = Console();
    if (edit_str->console(c)) break;

    if (edit_str->char_set(c, edit_str->str) != '\0') {
      if (len >= edit_str->max_len) {
        if (edit_str->exceed_max_len != NULL)
          edit_str->exceed_max_len(c, edit_str);
        continue;
      }

      printf("%c", edit_str->char_set(c, edit_str->str));
      edit_str->str[len] = edit_str->char_set(c, edit_str->str);
      edit_str->str[len + 1] = '\0';
      len ++;

      if (edit_str->on_change != NULL)
        edit_str->on_change(c, edit_str);
    } else if (c == BACKSPACE) {
      if (len == 0) continue;
      else if (len > 0) edit_str->str[len - 1] = '\0';
      else edit_str->str[0] = '\0';
      printf("%c %c", BACKSPACE, BACKSPACE);
      len --;

      if (edit_str->on_change != NULL)
        edit_str->on_change(c, edit_str);
    } else {
      if (edit_str->miss_char_set != NULL)
        edit_str->miss_char_set(c, edit_str);
    }
  }
  CursorVisible(false);

  // Safe
  edit_str->str[edit_str->max_len] = '\0';

  RenderEditStr(edit_str, NORMAL_EDIT_STR);

  return c;
}

tpp_define_conceal_method(ConcealEditStr, EditStr)

#ifdef __cplusplus
}
#endif

#endif
