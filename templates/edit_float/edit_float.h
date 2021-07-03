#ifndef __TEMPLATE_EDIT_FLOAT__
#define __TEMPLATE_EDIT_FLOAT__

#define EDIT_FLOAT_MAX_VALUE 999999999
#define EDIT_FLOAT_MIN_VALUE 0
#define EDIT_FLOAT_WIDTH 24
#define EDIT_FLOAT_HEIGHT 3
#define EDIT_FLOAT_FOREGROUND PROGRAM_FOREGROUND_REVERSE
#define EDIT_FLOAT_BACKGROUND PROGRAM_THEME_BACKGROUND_LV1
#define EDIT_FLOAT_ACTIVE_FOREGROUND PROGRAM_FOREGROUND
#define EDIT_FLOAT_ACTIVE_BACKGROUND PROGRAM_BACKGROUND

// status
#define NORMAL_EDIT_FLOAT 1
#define ACTIVE_EDIT_FLOAT 2

#ifdef __cplusplus
extern "C" {
#endif

typedef struct EditFloatT {
  float * num;
  int round_to_digit;
  float max_value;
  float min_value;
  size_tp width;
  size_tp height;
  position_tp position_x;
  position_tp position_y;
  color_tp foreground;
  color_tp background;
  color_tp active_foreground;
  color_tp active_background;
  bool (* console) (char);
  void (* on_change) (char, EditFloatT *);
  void (* miss_char_set) (char, EditFloatT *);
  void (* out_of_bounds) (char, EditFloatT *);
} EditFloatT, * EditFloat;

EditFloat NewEditFloat(
  float * num,
  int round_to_digit = 2,
  float max_value = EDIT_FLOAT_MAX_VALUE,
  float min_value = EDIT_FLOAT_MIN_VALUE,
  size_tp width = EDIT_FLOAT_WIDTH,
  size_tp height = EDIT_FLOAT_HEIGHT,
  position_tp position_x = CURSOR_POSITION_X,
  position_tp position_y = CURSOR_POSITION_Y,
  color_tp foreground = EDIT_FLOAT_FOREGROUND,
  color_tp background = EDIT_FLOAT_BACKGROUND,
  color_tp active_foreground = EDIT_FLOAT_ACTIVE_FOREGROUND,
  color_tp active_background = EDIT_FLOAT_ACTIVE_BACKGROUND,
  bool (* console) (char) = STANDARD_CONSOLE,
  void (* on_change) (char, EditFloatT *) = NULL,
  void (* miss_char_set) (char, EditFloatT *) = NULL,
  void (* out_of_bounds) (char, EditFloatT *) = NULL
) {
  EditFloat edit_float = (EditFloat) malloc(sizeof(EditFloatT));

  edit_float->num = num;
  edit_float->round_to_digit = round_to_digit;
  edit_float->max_value = max_value;
  edit_float->min_value = min_value;
  edit_float->width = width;
  edit_float->height = height;
  edit_float->position_x = position_x;
  edit_float->position_y = position_y;
  edit_float->foreground = foreground;
  edit_float->background = background;
  edit_float->active_foreground = active_foreground;
  edit_float->active_background = active_background;
  edit_float->console = console;
  edit_float->on_change = on_change;
  edit_float->miss_char_set = miss_char_set;
  edit_float->out_of_bounds = out_of_bounds;
  return edit_float;
}

void DestroyEditFloat(EditFloat &edit_float) {
  free(edit_float);
  edit_float = NULL;
}

void RenderEditFloat(EditFloat edit_float, status_tp status = NORMAL_EDIT_FLOAT) {
  color_tp foreground = edit_float->foreground;
  color_tp background = edit_float->background;

  if (status == ACTIVE_EDIT_FLOAT) {
    foreground = edit_float->active_foreground;
    background = edit_float->active_background;
  }

  // Draw container
  DrawRecShape(
    edit_float->width, edit_float->height,
    ' ',
    edit_float->position_x, edit_float->position_y,
    foreground, background
  );

  // Round
  long long int pot = pow(10, edit_float->round_to_digit);
  float num = roundf(*(edit_float->num) * pot) / pot;

  // Re-create the context
  if (num < edit_float->min_value)
    num = edit_float->min_value;

  WriteFloat(
    num,
    edit_float->position_x + 2, edit_float->position_y + edit_float->height / 2,
    foreground, background,
    edit_float->round_to_digit
  );

  if (num == 0)
    WriteChar(
      BACKSPACE,
      CURSOR_POSITION_X, CURSOR_POSITION_Y,
      foreground, background
    );
}

keycode_tp ActiveEditFloat(EditFloat edit_float) {
  // Render
  RenderEditFloat(edit_float, ACTIVE_EDIT_FLOAT);

  // Visible currsor
  CursorVisible(true);

  // Convert - pot: power of ten
  long long int pot = pow(10, edit_float->round_to_digit);
  long long int num = (long long int) roundf(*(edit_float->num) * pot);
  long long int max_value = (long long int) roundf(edit_float->max_value * pot);
  long long int min_value = (long long int) roundf(edit_float->min_value * pot);

  int dsad = DigitOfIntExceptTrailingZeros((int) num % pot);
  bool dot = (dsad > 0);

  num = RemoveTrailingZerosOfLong(num);

  // Sign
  float sign = num < 0 ? -1 : 1;

  char c = '\0';
  // Input
  while (true) {
    if (edit_float->console(c)) break;
    c = Console();
    if (edit_float->console(c)) break;

    if (IsNumericChar(c)) {
      if ((sign == 1 && NumViolatesMaxValue(num, c, max_value)) || (sign == -1 && NumViolatesMinValue(num, c, min_value))) {
        if (edit_float->out_of_bounds != NULL)
          edit_float->out_of_bounds(c, edit_float);
        continue;
      }

      if (dot && dsad >= edit_float->round_to_digit) continue;

      if (num != num * 10 + CharToInt(c) * sign || (dot && num == 0 && c == '0')) {
        num = num * 10 + CharToInt(c) * sign;
        printf("%c", c);

        if (dot) dsad ++;

        // Call OnChange
        if (edit_float->on_change != NULL)
          edit_float->on_change('\0', edit_float);

        // Violates min_value value, Call OnViolate
        if (sign == 1 && num < min_value)
          if (edit_float->out_of_bounds != NULL)
            edit_float->out_of_bounds(c, edit_float);
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
      if (edit_float->on_change != NULL)
        edit_float->on_change('\0', edit_float);

      // Violates min_value value, Call OnViolate
      if (sign == 1 && num < min_value)
        if (edit_float->out_of_bounds != NULL)
          edit_float->out_of_bounds(c, edit_float);
    } else if (c == '-' && num == 0 && sign == 1 && min_value < 0) {
      sign = -1;
      printf("%c", '-');
    } else if (c == '.' && !dot) {
      if (num == 0) printf("0%c", '.');
      else printf("%c", '.');
      dot = true;
    } else {
      // Call OnInvalid
      if (edit_float->miss_char_set != NULL)
        edit_float->miss_char_set(c, edit_float);
    }

    if (num == 0 && !dot) printf("0%c", BACKSPACE);
  }

  CursorVisible(false);

  // Check min_value and re-create the context
  if (num < min_value) {
    num = min_value;
    if (edit_float->on_change != NULL)
      edit_float->on_change('\0', edit_float);
  }

  pot = pow(10, dsad);
  *(edit_float->num) = (float) num / (float) pot;

  RenderEditFloat(edit_float, NORMAL_EDIT_FLOAT);

  return c;
}


#ifdef __cplusplus
}
#endif

#endif
