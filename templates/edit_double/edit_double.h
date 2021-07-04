#ifndef __TEMPLATE_EDIT_DOUBLE__
#define __TEMPLATE_EDIT_DOUBLE__

#define EDIT_DOUBLE_MAX_VALUE 999999999
#define EDIT_DOUBLE_MIN_VALUE 0
#define EDIT_DOUBLE_WIDTH 24
#define EDIT_DOUBLE_HEIGHT 3
#define EDIT_DOUBLE_FOREGROUND PROGRAM_FOREGROUND_REVERSE
#define EDIT_DOUBLE_BACKGROUND PROGRAM_THEME_BACKGROUND_LV1
#define EDIT_DOUBLE_ACTIVE_FOREGROUND PROGRAM_FOREGROUND
#define EDIT_DOUBLE_ACTIVE_BACKGROUND PROGRAM_BACKGROUND

// status
#define NORMAL_EDIT_DOUBLE 1
#define ACTIVE_EDIT_DOUBLE 2

#ifdef __cplusplus
extern "C" {
#endif

typedef struct EditDoubleT {
  double * num;
  int round_to_digit;
  double max_value;
  double min_value;
  size_tp width;
  size_tp height;
  position_tp position_x;
  position_tp position_y;
  color_tp foreground;
  color_tp background;
  color_tp active_foreground;
  color_tp active_background;
  bool (* console) (char);
  void (* on_change) (char, EditDoubleT *);
  void (* miss_char_set) (char, EditDoubleT *);
  void (* out_of_bounds) (char, EditDoubleT *);
} EditDoubleT, * EditDouble;

EditDouble NewEditDouble(
  double * num,
  int round_to_digit = 2,
  double max_value = EDIT_DOUBLE_MAX_VALUE,
  double min_value = EDIT_DOUBLE_MIN_VALUE,
  size_tp width = EDIT_DOUBLE_WIDTH,
  size_tp height = EDIT_DOUBLE_HEIGHT,
  position_tp position_x = CURSOR_POSITION_X,
  position_tp position_y = CURSOR_POSITION_Y,
  color_tp foreground = EDIT_DOUBLE_FOREGROUND,
  color_tp background = EDIT_DOUBLE_BACKGROUND,
  color_tp active_foreground = EDIT_DOUBLE_ACTIVE_FOREGROUND,
  color_tp active_background = EDIT_DOUBLE_ACTIVE_BACKGROUND,
  bool (* console) (char) = STANDARD_CONSOLE,
  void (* on_change) (char, EditDoubleT *) = NULL,
  void (* miss_char_set) (char, EditDoubleT *) = NULL,
  void (* out_of_bounds) (char, EditDoubleT *) = NULL
) {
  EditDouble edit_double = (EditDouble) malloc(sizeof(EditDoubleT));

  edit_double->num = num;
  edit_double->round_to_digit = round_to_digit;
  edit_double->max_value = max_value;
  edit_double->min_value = min_value;
  edit_double->width = width;
  edit_double->height = height;
  edit_double->position_x = position_x;
  edit_double->position_y = position_y;
  edit_double->foreground = foreground;
  edit_double->background = background;
  edit_double->active_foreground = active_foreground;
  edit_double->active_background = active_background;
  edit_double->console = console;
  edit_double->on_change = on_change;
  edit_double->miss_char_set = miss_char_set;
  edit_double->out_of_bounds = out_of_bounds;
  return edit_double;
}

void DestroyEditDouble(EditDouble &edit_double) {
  free(edit_double);
  edit_double = NULL;
}

void RenderEditDouble(EditDouble edit_double, status_tp status = NORMAL_EDIT_DOUBLE) {
  color_tp foreground = edit_double->foreground;
  color_tp background = edit_double->background;

  if (status == ACTIVE_EDIT_DOUBLE) {
    foreground = edit_double->active_foreground;
    background = edit_double->active_background;
  }

  // Draw container
  DrawRecShape(
    edit_double->width, edit_double->height,
    ' ',
    edit_double->position_x, edit_double->position_y,
    foreground, background
  );

  // Round
  long long int pot = pow(10, edit_double->round_to_digit);
  double num = roundf(*(edit_double->num) * pot) / pot;

  // Re-create the context
  if (num < edit_double->min_value)
    num = edit_double->min_value;

  WriteDoubleP(
    num, edit_double->round_to_digit,
    edit_double->position_x + 2, edit_double->position_y + edit_double->height / 2,
    foreground, background
  );

  if (num == 0)
    WriteChar(
      BACKSPACE,
      CURSOR_POSITION_X, CURSOR_POSITION_Y,
      foreground, background
    );
}

keycode_tp ActiveEditDouble(EditDouble edit_double) {
  // Render
  RenderEditDouble(edit_double, ACTIVE_EDIT_DOUBLE);

  // Visible currsor
  CursorVisible(true);

  // Convert - pot: power of ten
  long long int pot = pow(10, edit_double->round_to_digit);
  long long int num = (long long int) roundf(*(edit_double->num) * pot);
  long long int max_value = (long long int) roundf(edit_double->max_value * pot);
  long long int min_value = (long long int) roundf(edit_double->min_value * pot);

  int dsad = DigitsOfDoubleAfterDot(*(edit_double->num), edit_double->round_to_digit);
  bool dot = (dsad > 0);

  num = RemoveTrailingZerosOfLong(num, edit_double->round_to_digit - dsad); // num , limit

  // Sign
  double sign = num < 0 ? -1 : 1;

  char c = '\0';
  // Input
  while (true) {
    if (edit_double->console(c)) break;
    c = Console();
    if (edit_double->console(c)) break;

    if (IsNumericChar(c)) {
      if ((sign == 1 && NumViolatesMaxValue(num, c, max_value)) || (sign == -1 && NumViolatesMinValue(num, c, min_value))) {
        if (edit_double->out_of_bounds != NULL)
          edit_double->out_of_bounds(c, edit_double);
        continue;
      }

      if (dot && dsad >= edit_double->round_to_digit) continue;

      if (num != num * 10 + CharToInt(c) * sign || (dot && num == 0 && c == '0')) {
        num = num * 10 + CharToInt(c) * sign;
        printf("%c", c);

        if (dot) dsad ++;

        // Call OnChange
        if (edit_double->on_change != NULL)
          edit_double->on_change('\0', edit_double);

        // Violates min_value value, Call OnViolate
        if (sign == 1 && num < min_value)
          if (edit_double->out_of_bounds != NULL)
            edit_double->out_of_bounds(c, edit_double);
      }
    } else if (c == BACKSPACE) {
      if (num == 0 && dot && dsad == 0) {
        printf("%c%c  %c%c", BACKSPACE, BACKSPACE, BACKSPACE, BACKSPACE);
        dot = false;
      } else if (num != 0 || (dot && num ==0)) printf("%c %c", BACKSPACE, BACKSPACE);
      else if (num == 0 && sign == -1) {
        printf("%c  %c%c", BACKSPACE, BACKSPACE, BACKSPACE, BACKSPACE);
        sign = 1;
      }

      if (dot && dsad == 0)
        dot = false;
      else {
        num /= 10;
        if (dot) dsad --;
      }

      // Call OnChange
      if (edit_double->on_change != NULL)
        edit_double->on_change('\0', edit_double);

      // Violates min_value value, Call OnViolate
      if (sign == 1 && num < min_value)
        if (edit_double->out_of_bounds != NULL)
          edit_double->out_of_bounds(c, edit_double);
    } else if (c == '-' && num == 0 && sign == 1 && min_value < 0) {
      sign = -1;
      printf("%c", '-');
    } else if (c == '.' && !dot) {
      if (num == 0) printf("0%c", '.');
      else printf("%c", '.');
      dot = true;
    } else {
      // Call OnInvalid
      if (edit_double->miss_char_set != NULL)
        edit_double->miss_char_set(c, edit_double);
    }

    if (num == 0 && !dot) printf("0%c", BACKSPACE);
  }

  CursorVisible(false);

  // Check min_value and re-create the context
  if (num < min_value) {
    num = min_value;
    if (edit_double->on_change != NULL)
      edit_double->on_change('\0', edit_double);
  }

  pot = pow(10, dsad);
  *(edit_double->num) = num / (double) pot;

  RenderEditDouble(edit_double, NORMAL_EDIT_DOUBLE);

  return c;
}


#ifdef __cplusplus
}
#endif

#endif
