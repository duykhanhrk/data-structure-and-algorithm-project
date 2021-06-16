/* DateTime input */

#define IsLeapYear(year) (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))

#define TimeTToDayMonthYear(obj, time_info, day, month, year) uh_tp day, month, year; \
                                                              time_info = *(localtime(&obj)); \
                                                              year = time_info.tm_year + 1900; \
                                                              month = time_info.tm_mon + 1; \
                                                              day = time_info.tm_mday;

#define SetDay(value) SaveCursorPositionContext; \
                      day = value; \
                      GotoXY(position_x, position_y); \
                      if (day < 10) printf("0%u", day); \
                      else printf("%u", day); \
                      ApplyCursorPositionContext;

#define SetMonth(value) SaveCursorPositionContext; \
                        month = value; \
                        GotoXY(position_x + 3, position_y); \
                        if (month < 10) printf("0%u", month); \
                        else printf("%u", day); \
                        ApplyCursorPositionContext


// Define
#define CURRENT_DATETIME time(NULL)

// Limit
#define DATETIME_MAX_VALUE CURRENT_DATETIME
#define DATETIME_MIN_VALUE DateParse(1, 1, 2001)

// ..
#define DATE_INPUT_MAX_VALUE DATETIME_MAX_VALUE
#define DATE_INPUT_MIN_VALUE DATETIME_MIN_VALUE
#define DATE_INPUT_POSITION_X INPUT_POSITION_X
#define DATE_INPUT_POSITION_Y INPUT_POSITION_Y
#define DATE_INPUT_FOREGROUND INPUT_FOREGROUND
#define DATE_INPUT_BACKGROUND INPUT_BACKGROUND
#define DATE_INPUT_CONTAINER_SIZE 9
#define DATE_INPUT_ON_ACTIVE_FOREGROUND INPUT_ON_ACTIVE_FOREGROUND
#define DATE_INPUT_ON_ACTIVE_BACKGROUND INPUT_ON_ACTIVE_BACKGROUND
#define DATE_INPUT_NAV_PANEL STANDARD_NAV_PANEL
#define DATE_INPUT_EXPRESS DATE_STANDARD_EXPRESS
#define DATE_INPUT_ON_CHANGE_EVENT NULL
#define DATE_INPUT_ON_VIOLATE_EVENT NULL
#define DATE_INPUT_ON_INVALID_EVENT NULL
#define DATE_INPUT_ON_ENTER_EVENT NULL
#define DATE_INPUT_ON_LEAVE_EVENT NULL

time_t DateParse(uh_tp day, uh_tp month, uh_tp year) {
  tm time_info;
  time_info.tm_year = year - 1900;
  time_info.tm_mon = month - 1;
  time_info.tm_mday = day;
  return mktime(&time_info);
}

char DateInput(
  time_t &obj,
  time_t max = DATE_INPUT_MAX_VALUE,
  time_t min = DATE_INPUT_MIN_VALUE,
  position_tp position_x = DATE_INPUT_POSITION_X,
  position_tp position_y = DATE_INPUT_POSITION_Y,
  color_tp f_color = DATE_INPUT_FOREGROUND,
  color_tp b_color = DATE_INPUT_BACKGROUND,
  size_tp container_size = DATE_INPUT_CONTAINER_SIZE,
  color_tp on_active_f_color = DATE_INPUT_ON_ACTIVE_FOREGROUND,
  color_tp on_active_b_color = DATE_INPUT_ON_ACTIVE_BACKGROUND,
  NavigationPanelPrototype(NavigationPanel) = DATE_INPUT_NAV_PANEL,
  ExpressPrototype(Express) = DATE_INPUT_EXPRESS,
  InputEventTriggerPrototype(OnChange) = DATE_INPUT_ON_CHANGE_EVENT,
  InputEventTriggerPrototype(OnViolate) = DATE_INPUT_ON_VIOLATE_EVENT,
  InputEventTriggerPrototype(OnInvalid) = DATE_INPUT_ON_INVALID_EVENT,
  InputEventTriggerPrototype(OnEnter) = DATE_INPUT_ON_ENTER_EVENT,
  InputEventTriggerPrototype(OnLeave) = DATE_INPUT_ON_LEAVE_EVENT
) {
  // Be strict with triggers
  if (NavigationPanel == NULL) NavigationPanel = DATE_INPUT_NAV_PANEL;
  if (Express == NULL) Express = DATE_INPUT_EXPRESS;

  // Initialize
  SaveColorContext;
  SaveCursorVisibleContext;

  // Setup color
  SetColor(f_color, b_color);

  // Draw container
  DrawHorLine(container_size, ' ', position_x, position_y, f_color, b_color);

  // Setup cursor position
  GotoXY(position_x, position_y);

  // Init stash
  InitStash;

  // Define c
  char c = '\0';

  // Call OnEnter
  InputEventTriggerHandle(OnEnter);

  // Re-create the context
  if (obj < min) {
    obj = min;
    InputEventTriggerHandle(OnChange);
  }

  WriteDate(obj);

  tm time_info;
  TimeTToDayMonthYear(obj, time_info, day, month, year);
  TimeTToDayMonthYear(max, time_info, a_day, a_month, a_year);
  TimeTToDayMonthYear(min, time_info, i_day, i_month, i_year);

  uh_tp days[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

  uh_tp max_day, max_month;
  uh_tp min_day, min_month;

  char edit = 'd';
  while (true) {
    // Navigate
    if (NavigationPanelHandle(NavigationPanel)) break;

    if (edit == 'd') {
      days[1] = IsLeapYear(year) ? 29 : 28;

      // Set max day
      if (year == a_year && month == a_month) max_day = a_day;
      else max_day = days[month - 1];

      // Set min day
      if (year == i_year && month == i_month) min_day = i_day;
      else min_day = 1;

      // Day input
      c = Input(
        day, max_day, min_day, position_x, position_y,
        f_color, b_color, 2, on_active_f_color, on_active_b_color,
        DATETIME_INPUT_NAV_PANEL, TWO_DIGITS_USHORT_EXPRESS, NULL, NULL, NULL, NULL, NULL
      );

      // Navigate
      if (c == KEY_RIGHT || c == SLASH) edit = 'm';
      else if (c == KEY_LEFT) edit = 'y';
    } else if (edit == 'm') {
      // Set February
      days[1] = IsLeapYear(year) ? 29 : 28;

      // Set max month
      if (year == a_year) max_month = a_month;
      else max_month = 12;

      // Set min month
      if (year == i_year) min_month = i_month;
      else min_month = 1;

      // Month input
      c = Input(
        month, max_month, min_month, position_x + 3, position_y,
        f_color, b_color, 2, on_active_f_color, on_active_b_color,
        DATETIME_INPUT_NAV_PANEL, TWO_DIGITS_USHORT_EXPRESS, NULL, NULL, NULL, NULL, NULL
      );

      /* Violate */
      if (day > days[month - 1]) {
        SetDay(days[month - 1]);
      }

      if (year == a_year && month == a_month && day > a_day) {
        SetDay(a_day);
      }

      if (year == i_year && month == i_month && day < i_day) {
        SetDay(i_day);
      }

      // Navigate
      if (c == KEY_RIGHT || c == SLASH) edit = 'y';
      else if (c == KEY_LEFT) edit = 'd';
    } else if (edit == 'y') {
      // Year input
      c = Input(
        year, a_year, i_year, position_x + 6, position_y,
        f_color, b_color, 4, on_active_f_color, on_active_b_color,
        DATETIME_INPUT_NAV_PANEL, TWO_DIGITS_USHORT_EXPRESS, NULL, NULL, NULL, NULL, NULL
      );

      // February
      if (month == 2 && day == 29 && !IsLeapYear(year)) {
        SetDay(28u);
      }

      // Validate max date
      if (year == a_year) {
        if (month > a_month) {
          SetMonth(a_month);
        }

        if (month == a_month && day > a_day) {
          SetDay(a_day);
        }
      }

      // Validate min date
      if (year == i_year) {
        if (month < i_month) {
          SetMonth(i_month);
        }

        if (month == i_month && day < i_day) {
          SetDay(i_day);
        }
      }

      // Navigate
      if (c == KEY_RIGHT) edit = 'd';
      else if (c == KEY_LEFT) edit = 'm';
    }

    if (obj != DateParse(day, month, year)) {
      obj = DateParse(day, month, year);
      InputEventTriggerHandle(OnChange);
    }
  }

  // Setup color
  SetColor(f_color, b_color);

  // DrawHorLine
  DrawHorLine(container_size, ' ', position_x, position_y, f_color, b_color);
  GotoXY(position_x, position_y);

  // Call Express
  ExpressHandle(Express);

  // Call OnEnd
  InputEventTriggerHandle(OnLeave);

  ApplyColorContext;
  ApplyCursorVisibleContext;
  return c;
}
