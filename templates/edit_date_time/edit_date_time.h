#ifndef __TEMPLATE_EDIT_DATETIME__
#define __TEMPLATE_EDIT_DATETIME__

#define EDIT_DATETIME_MAX_VALUE 999999999
#define EDIT_DATETIME_MIN_VALUE 0
#define EDIT_DATETIME_WIDTH 24
#define EDIT_DATETIME_HEIGHT 3
#define EDIT_DATETIME_FOREGROUND PROGRAM_FOREGROUND_REVERSE
#define EDIT_DATETIME_BACKGROUND PROGRAM_THEME_BACKGROUND_LV1
#define EDIT_DATETIME_ACTIVE_FOREGROUND PROGRAM_FOREGROUND
#define EDIT_DATETIME_ACTIVE_BACKGROUND PROGRAM_BACKGROUND

// status
#define NORMAL_EDIT_DATETIME 1
#define ACTIVE_EDIT_DATETIME 2

#ifdef __cplusplus
extern "C" {
#endif

typedef struct EditDateTimeT {
  time_t * datetime;
  time_t max_value;
  time_t min_value;
  size_tp width;
  size_tp height;
  position_tp position_x;
  position_tp position_y;
  color_tp foreground;
  color_tp background;
  color_tp active_foreground;
  color_tp active_background;
  bool (* console) (char);
  EditInt edit_year;
  EditInt edit_month;
  EditInt edit_day;
  void * active_element;
} EditDateTimeT, * EditDateTime;

EditDateTime NewEditDateTime(
  time_t * datetime,
  time_t max_value = EDIT_DATETIME_MAX_VALUE,
  time_t min_value = EDIT_DATETIME_MIN_VALUE,
  size_tp width = EDIT_DATETIME_WIDTH,
  size_tp height = EDIT_DATETIME_HEIGHT,
  position_tp position_x = CURSOR_POSITION_X,
  position_tp position_y = CURSOR_POSITION_Y,
  color_tp foreground = EDIT_DATETIME_FOREGROUND,
  color_tp background = EDIT_DATETIME_BACKGROUND,
  color_tp active_foreground = EDIT_DATETIME_ACTIVE_FOREGROUND,
  color_tp active_background = EDIT_DATETIME_ACTIVE_BACKGROUND,
  bool (* console) (char) = STANDARD_CONSOLE
) {
  EditDateTime edit_datetime = (EditDateTime) malloc(sizeof(EditDateTimeT));

  edit_datetime->datetime = datetime;
  edit_datetime->max_value = max_value;
  edit_datetime->min_value = min_value;
  edit_datetime->width = width;
  edit_datetime->height = height;
  edit_datetime->position_x = position_x;
  edit_datetime->position_y = position_y;
  edit_datetime->foreground = foreground;
  edit_datetime->background = background;
  edit_datetime->active_foreground = active_foreground;
  edit_datetime->active_background = active_background;
  edit_datetime->console = console;
  edit_datetime->edit_year = NewEditInt(
    NULL,
    0, 0,
    6, height,
    position_x + 5, position_y,
    EDIT_INT_FOREGROUND, EDIT_INT_BACKGROUND,
    EDIT_INT_ACTIVE_FOREGROUND, EDIT_INT_ACTIVE_BACKGROUND
  );

  edit_datetime->edit_month = NewEditInt(
    NULL,
    0, 0,
    4, height,
    position_x + 13, position_y,
    EDIT_INT_FOREGROUND, EDIT_INT_BACKGROUND,
    EDIT_INT_ACTIVE_FOREGROUND, EDIT_INT_ACTIVE_BACKGROUND
  );

  edit_datetime->edit_day = NewEditInt(
    NULL,
    0, 0,
    4, height,
    position_x + 26, position_y,
    EDIT_INT_FOREGROUND, EDIT_INT_BACKGROUND,
    EDIT_INT_ACTIVE_FOREGROUND, EDIT_INT_ACTIVE_BACKGROUND
  );
  return edit_datetime;
}

void DestroyEditDateTime(EditDateTime &edit_datetime) {
  DestroyEditInt(edit_datetime->edit_year);
  DestroyEditInt(edit_datetime->edit_month);
  DestroyEditInt(edit_datetime->edit_day);
  free(edit_datetime);
  edit_datetime = NULL;
}

void RenderEditDateTime(EditDateTime edit_datetime, status_tp status = NORMAL_TEMPLATE) {
  color_tp foreground = edit_datetime->foreground;
  color_tp background = edit_datetime->background;

  // Draw container
  DrawRecShape(
    edit_datetime->width, edit_datetime->height,
    ' ',
    edit_datetime->position_x, edit_datetime->position_y,
    foreground, background
  );

  // Input
  WriteStr(
    "Năm:",
    edit_datetime->position_x, edit_datetime->position_y + edit_datetime->height / 2,
    foreground, background
  );

  WriteStr(
    "Tháng:",
    edit_datetime->position_x + 15, edit_datetime->position_y + edit_datetime->height / 2,
    foreground, background
  );

  WriteStr(
    "Ngày",
    edit_datetime->position_x + 21, edit_datetime->position_y + edit_datetime->height / 2,
    foreground, background
  );

  if (*(edit_datetime->datetime) < edit_datetime->min_value)
    *(edit_datetime->datetime) = edit_datetime->min_value;

  DateTime datetime = NewDateTimeByTimeT(*(edit_datetime->datetime), false);

  edit_datetime->edit_year->num = &(datetime->year);
  edit_datetime->edit_month->num = &(datetime->month);
  edit_datetime->edit_day->num = &(datetime->day);

  RenderEditInt(edit_datetime->edit_year, NORMAL_TEMPLATE);
  RenderEditInt(edit_datetime->edit_month, NORMAL_TEMPLATE);
  RenderEditInt(edit_datetime->edit_day, NORMAL_TEMPLATE);

  DestroyDateTime(datetime);
}

keycode_tp ActiveEditDateTime(EditDateTime edit_datetime) {
  int days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
  int max_day, max_month;
  int min_day, min_month;

  DateTime _dt = NewDateTimeByTimeT(*(edit_datetime->datetime), false);
  DateTime _max = NewDateTimeByTimeT(edit_datetime->max_value, false);
  DateTime _min = NewDateTimeByTimeT(edit_datetime->min_value, false);

  edit_datetime->edit_year->max_value = _max->year;
  edit_datetime->edit_year->min_value = _min->year;

  edit_datetime->edit_year->num = &(_dt->year);
  edit_datetime->edit_month->num = &(_dt->month);
  edit_datetime->edit_day->num = &(_dt->day);

  keycode_tp keycode;
  while (true) {
    // Navigate
    if (edit_datetime->console(keycode)) break;

    if (edit_datetime->active_element == edit_datetime->edit_day) {
      days[1] = IsLeapYear(_dt->year) ? 29 : 28;

      // Set max day
      if (_dt->year == _max->year && _dt->month == _max->year) max_day = _max->day;
      else max_day = days[_dt->month - 1];

      // Set min day
      if (_dt->year == _min->year && _dt->month == _min->month) min_day = _min->day;
      else min_day = 1;

      edit_datetime->edit_day->max_value = max_day;
      edit_datetime->edit_day->min_value = min_day;

      // Day input
      keycode = ActiveEditInt(edit_datetime->edit_day);

      // Navigate
      if (keycode == KEY_RIGHT)
        edit_datetime->active_element = edit_datetime->edit_year;
      else if (keycode == KEY_LEFT)
        edit_datetime->active_element = edit_datetime->edit_month;
    } else if (edit_datetime->active_element == edit_datetime->edit_month) {
      // Set February
      days[1] = IsLeapYear(_dt->year) ? 29 : 28;

      // Set max month
      if (_dt->year == _max->year) max_month = _max->month;
      else max_month = 12;

      // Set min month
      if (_dt->year == _min->year) min_month = _min->month;
      else min_month = 1;

      edit_datetime->edit_month->max_value = max_month;
      edit_datetime->edit_month->min_value = min_month;

      // Month input
      keycode = ActiveEditInt(edit_datetime->edit_month);

      /* Violate */
      if (_dt->day > days[_dt->month - 1]) {
        _dt->day = days[_dt->month - 1];
        RenderEditInt(edit_datetime->edit_day, NORMAL_TEMPLATE);
      }

      if (_dt->year == _max->year && _dt->month == _max->month && _dt->day > _max->day) {
        _dt->day = _max->day;
        RenderEditInt(edit_datetime->edit_day, NORMAL_TEMPLATE);
      }

      if (_dt->year == _min->year && _dt->month == _min->month && _dt->day < _min->day) {
        _dt->day = _min->day;
        RenderEditInt(edit_datetime->edit_day, NORMAL_TEMPLATE);
      }

      // Navigate
      if (keycode == KEY_RIGHT || keycode == SLASH || keycode == ENTER)
        edit_datetime->active_element = edit_datetime->edit_day;
      else if (keycode == KEY_LEFT)
        edit_datetime->active_element = edit_datetime->edit_year;
    } else if (edit_datetime->active_element == edit_datetime->edit_day) {
      // Year input
      keycode = ActiveEditInt(edit_datetime->edit_year);

      // February
      if (_dt->month == 2 && _dt->day == 29 && !IsLeapYear(_dt->year)) {
        _dt->day = 28;
        RenderEditInt(edit_datetime->edit_day, NORMAL_TEMPLATE);
      }

      // Validate max date
      if (_dt->year == _max->year) {
        if (_dt->month > _max->month) {
          _dt->month = _max->month;
          RenderEditInt(edit_datetime->edit_month, NORMAL_TEMPLATE);
        }

        if (_dt->month == _max->month && _dt->day > _max->day) {
          _dt->day = _max->day;
          RenderEditInt(edit_datetime->edit_day, NORMAL_TEMPLATE);
        }
      }

      // Validate min date
      if (_dt->year == _min->year) {
        if (_dt->month < _min->month) {
          _dt->month = _min->month;
          RenderEditInt(edit_datetime->edit_month, NORMAL_TEMPLATE);
        }

        if (_dt->month == _min->month && _dt->day < _min->day) {
          _dt->day = _max->day;
          RenderEditInt(edit_datetime->edit_day, NORMAL_TEMPLATE);
        }
      }

      // Navigate
      if (keycode == KEY_RIGHT || keycode == SLASH || keycode == ENTER)
        edit_datetime->active_element = edit_datetime->edit_day;
      else if (keycode == KEY_LEFT)
        edit_datetime->active_element = edit_datetime->edit_day;
    }

    *(edit_datetime->datetime) = DateTimeToTimeT(_dt);
  }

  DestroyDateTime(_dt);
  DestroyDateTime(_max);
  DestroyDateTime(_min);
  return keycode;
}


#ifdef __cplusplus
}
#endif

#endif
