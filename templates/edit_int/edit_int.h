#ifndef __TEMPLATE_EDIT_INT__
#define __TEMPLATE_EDIT_INT__

#define EDIT_INT_MAX_VALUE 999999999
#define EDIT_INT_MIN_VALUE 0
#define EDIT_INT_WIDTH 24
#define EDIT_INT_HEIGHT 3
#define EDIT_INT_FOREGROUND PROGRAM_FOREGROUND_REVERSE
#define EDIT_INT_BACKGROUND PROGRAM_THEME_BACKGROUND_LV1
#define EDIT_INT_ACTIVE_FOREGROUND PROGRAM_FOREGROUND
#define EDIT_INT_ACTIVE_BACKGROUND PROGRAM_BACKGROUND

// status
#define NORMAL_EDIT_INT 1
#define ACTIVE_EDIT_INT 2

#ifdef __cplusplus
extern "C" {
#endif

typedef struct EditIntT {
  int * num;
  int max_value;
  int min_value;
  size_tp width;
  size_tp height;
  position_tp position_x;
  position_tp position_y;
  color_tp foreground;
  color_tp background;
  color_tp active_foreground;
  color_tp active_background;
  bool (* console) (char);
  void (* on_change) (char, EditIntT *);
  void (* miss_char_set) (char, EditIntT *);
  void (* out_of_bounds) (char, EditIntT *);
} EditIntT, * EditInt;

EditInt NewEditInt(
  int * num,
  int max_value = EDIT_INT_MAX_VALUE,
  int min_value = EDIT_INT_MIN_VALUE,
  size_tp width = EDIT_INT_WIDTH,
  size_tp height = EDIT_INT_HEIGHT,
  position_tp position_x = CURSOR_POSITION_X,
  position_tp position_y = CURSOR_POSITION_Y,
  color_tp foreground = EDIT_INT_FOREGROUND,
  color_tp background = EDIT_INT_BACKGROUND,
  color_tp active_foreground = EDIT_INT_ACTIVE_FOREGROUND,
  color_tp active_background = EDIT_INT_ACTIVE_BACKGROUND,
  bool (* console) (char) = STANDARD_CONSOLE,
  void (* on_change) (char, EditIntT *) = NULL,
  void (* miss_char_set) (char, EditIntT *) = NULL,
  void (* out_of_bounds) (char, EditIntT *) = NULL
) {
  EditInt edit_int = (EditInt) malloc(sizeof(EditIntT));

  edit_int->num = num;
  edit_int->max_value = max_value;
  edit_int->min_value = min_value;
  edit_int->width = width;
  edit_int->height = height;
  edit_int->position_x = position_x;
  edit_int->position_y = position_y;
  edit_int->foreground = foreground;
  edit_int->background = background;
  edit_int->active_foreground = active_foreground;
  edit_int->active_background = active_background;
  edit_int->console = console;
  edit_int->on_change = on_change;
  edit_int->miss_char_set = miss_char_set;
  edit_int->out_of_bounds = out_of_bounds;
  return edit_int;
}

void DestroyEditInt(EditInt &edit_int) {
  free(edit_int);
  edit_int = NULL;
}

void RenderEditInt(EditInt edit_int, status_tp status = NORMAL_EDIT_INT) {
  color_tp foreground = edit_int->foreground;
  color_tp background = edit_int->background;

  if (status == ACTIVE_EDIT_INT) {
    foreground = edit_int->active_foreground;
    background = edit_int->active_background;
  }

  // Draw container
  DrawRecShape(
    edit_int->width, edit_int->height,
    ' ',
    edit_int->position_x, edit_int->position_y,
    foreground, background
  );

  // Re-create the context
  if (*(edit_int->num) < edit_int->min_value)
    *(edit_int->num) = edit_int->min_value;

  WriteInt(
    *(edit_int->num),
    edit_int->position_x + 2, edit_int->position_y + edit_int->height / 2,
    foreground, background
  );

  if (*(edit_int->num) == 0)
    WriteChar(
      BACKSPACE,
      CURSOR_POSITION_X, CURSOR_POSITION_Y,
      foreground, background
    );
}

keycode_tp ActiveEditInt(EditInt edit_int) {
  // Render
  RenderEditInt(edit_int, ACTIVE_EDIT_INT);

  CursorVisible(true);

  // Sign
  int sign = *(edit_int->num) < 0 ? -1 : 1;

  char c = '\0';
  // Input
  while (true) {
    if (edit_int->console(c) && c != BACKSPACE) break;
    c = Console();
    if (edit_int->console(c) && c != BACKSPACE) break;

    if (IsNumericChar(c)) {
      if ((sign == 1 && NumViolatesMaxValue(*(edit_int->num), c, edit_int->max_value)) || (sign == -1 && NumViolatesMinValue(*(edit_int->num), c, edit_int->min_value))) {
        if (edit_int->out_of_bounds != NULL)
          edit_int->out_of_bounds(c, edit_int);
        continue;
      }

      if (*(edit_int->num) != *(edit_int->num) * 10 + CharToInt(c) * sign) {
        *(edit_int->num) = *(edit_int->num) * 10 + CharToInt(c) * sign;
        printf("%c", c);

        // Call OnChange
        if (edit_int->on_change != NULL)
          edit_int->on_change('\0', edit_int);

        // Violates edit_int->min_value value, Call OnViolate
        if (sign == 1 && *(edit_int->num) < edit_int->min_value)
          if (edit_int->out_of_bounds != NULL)
            edit_int->out_of_bounds(c, edit_int);
      }
    } else if (c == BACKSPACE) {
      if (*(edit_int->num) != 0) printf("%c %c", BACKSPACE, BACKSPACE);
      else if (*(edit_int->num) == 0 && sign == -1) {
        printf("%c  %c%c", BACKSPACE, BACKSPACE, BACKSPACE, BACKSPACE);
        sign = 1;
      }
      *(edit_int->num) /= 10;

      // Call OnChange
      if (edit_int->on_change != NULL)
        edit_int->on_change('\0', edit_int);

      // Violates edit_int->min_value value, Call OnViolate
      if (sign == 1 && *(edit_int->num) < edit_int->min_value)
        if (edit_int->out_of_bounds != NULL)
          edit_int->out_of_bounds(c, edit_int);
    } else if (c == '-' && *(edit_int->num) == 0 && sign == 1 && edit_int->min_value < 0) {
      sign = -1;
      printf("%c", '-');
    } else {
      // Call OnInvalid
      if (edit_int->miss_char_set != NULL)
        edit_int->miss_char_set(c, edit_int);
    }

    if (*(edit_int->num) == 0) printf("0%c", BACKSPACE);
  }

  CursorVisible(false);

  // Check edit_int->min_value and re-create the context
  if (*(edit_int->num) < edit_int->min_value) {
    *(edit_int->num) = edit_int->min_value;
    if (edit_int->on_change != NULL)
      edit_int->on_change('\0', edit_int);
  }

  RenderEditInt(edit_int, NORMAL_EDIT_INT);

  return c;
}


#ifdef __cplusplus
}
#endif

#endif
