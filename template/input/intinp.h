/* Int input */

/* Short */

// Limit
#define SHORT_MAX_VALUE 32767
#define SHORT_MIN_VALUE -32768

// Define
#define SHORT_INPUT_MAX_VALUE SHORT_MAX_VALUE
#define SHORT_INPUT_MIN_VALUE SHORT_MIN_VALUE
#define SHORT_INPUT_POSITION_X NUMBER_INPUT_POSITION_X
#define SHORT_INPUT_POSITION_Y NUMBER_INPUT_POSITION_Y
#define SHORT_INPUT_FOREGROUND NUMBER_INPUT_FOREGROUND
#define SHORT_INPUT_BACKGROUND NUMBER_INPUT_BACKGROUND
#define SHORT_INPUT_ON_ACTIVE_FOREGROUND NUMBER_INPUT_ON_ACTIVE_FOREGROUND
#define SHORT_INPUT_ON_ACTIVE_BACKGROUND NUMBER_INPUT_ON_ACTIVE_BACKGROUND
#define SHORT_INPUT_CONTAINER_SIZE 6
#define SHORT_INPUT_NAV_PANEL NUMBER_INPUT_NAV_PANEL
#define SHORT_INPUT_CHAR_SET NUMBER_INPUT_CHAR_SET
#define SHORT_INPUT_EXPRESS SHORT_STANDARD_EXPRESS
#define SHORT_INPUT_ON_CHANGE_EVENT NULL
#define SHORT_INPUT_ON_VIOLATE_EVENT NULL
#define SHORT_INPUT_ON_INVALID_EVENT NULL
#define SHORT_INPUT_ON_ENTER_EVENT NULL
#define SHORT_INPUT_ON_LEAVE_EVENT NULL

char Input(
  h_tp &obj,
  h_tp max = SHORT_INPUT_MAX_VALUE,
  h_tp min = SHORT_INPUT_MIN_VALUE,
  position_tp position_x = SHORT_INPUT_POSITION_X,
  position_tp position_y = SHORT_INPUT_POSITION_Y,
  color_tp f_color = SHORT_INPUT_FOREGROUND,
  color_tp b_color = SHORT_INPUT_BACKGROUND,
  size_tp container_size = SHORT_INPUT_CONTAINER_SIZE,
  color_tp on_active_f_color = SHORT_INPUT_ON_ACTIVE_FOREGROUND,
  color_tp on_active_b_color = SHORT_INPUT_ON_ACTIVE_BACKGROUND,
  NavigationPanelPrototype(NavigationPanel) = SHORT_INPUT_NAV_PANEL,
  ExpressPrototype(Express) = SHORT_INPUT_EXPRESS,
  InputEventTriggerPrototype(OnChange) = SHORT_INPUT_ON_CHANGE_EVENT,
  InputEventTriggerPrototype(OnViolate) = SHORT_INPUT_ON_VIOLATE_EVENT,
  InputEventTriggerPrototype(OnInvalid) = SHORT_INPUT_ON_INVALID_EVENT,
  InputEventTriggerPrototype(OnEnter) = SHORT_INPUT_ON_ENTER_EVENT,
  InputEventTriggerPrototype(OnLeave) = SHORT_INPUT_ON_LEAVE_EVENT
) {
  // Be strict with triggers
  if (NavigationPanel == NULL) NavigationPanel = SHORT_INPUT_NAV_PANEL;
  if (Express == NULL) Express =SHORT_INPUT_EXPRESS;

  // Initialize
  SaveColorContext;
  SaveCursorVisibleContext;

  // Show cursor
  ShowCursor;

  // Setup color
  SetColor(on_active_f_color, on_active_b_color);

  // Draw container
  DrawHorLine(container_size, ' ', position_x, position_y, on_active_f_color, on_active_b_color);

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
  printf("%hi", obj);
  if (obj == 0) printf("%c", BACKSPACE);

  // Sign
  h_tp sign = obj < 0 ? -1 : 1;

  // Input
  while (true) {
    // Navigate
    if (NavigationPanelHandle(NavigationPanel)) break;

    // Input from ControlPanel
    c = ControlPanel();

    // Navigate
    if (NavigationPanelHandle(NavigationPanel)) break;

    if (IsNumericChar(c)) {
      // Violates max or min value, Call OnViolate
      if ((sign == 1 && NumViolatesMaxValue(obj, c, max)) || (sign == -1 && NumViolatesMinValue(obj, c, min))) {
        InputEventTriggerHandle(OnViolate);
        continue;
      }

      if (obj != obj * 10 + CharToInt(c) * sign) {
        obj = obj * 10 + CharToInt(c) * sign;
        printf("%c", c);

        // Call OnChange
        InputEventTriggerHandle(OnChange);

        // Violates min value, Call OnViolate
        if (sign == 1 && obj < min) InputEventTriggerHandle(OnViolate);
      }
    } else if (c == BACKSPACE) {
      if (obj != 0) printf("%c %c", BACKSPACE, BACKSPACE);
      else if (obj == 0 && sign == -1) {
        printf("%c%c  %c%c", BACKSPACE, BACKSPACE, BACKSPACE, BACKSPACE);
        sign = 1;
      }
      obj /= 10;

      // Call OnChange
      InputEventTriggerHandle(OnChange);

      // Violates min value, Call OnViolate
      if (sign == 1 && obj < min) InputEventTriggerHandle(OnViolate);
    } else if (c == 45 && obj == 0 && sign == 1) {
      sign = -1;
      printf("%c", '-');
    } else {
      // Call OnInvalid
      InputEventTriggerHandle(OnInvalid);
    }

    if (obj == 0) printf("0%c", BACKSPACE);
  }

  // Check min and re-create the context
  if (obj < min) {
    obj = min;
    InputEventTriggerHandle(OnChange);
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

/* Int */

// Limit
#define INT_MAX_VALUE 2147483647
#define INT_MIN_VALUE -2147483648

// Define
#define INT_INPUT_MAX_VALUE INT_MAX_VALUE
#define INT_INPUT_MIN_VALUE INT_MIN_VALUE
#define INT_INPUT_POSITION_X NUMBER_INPUT_POSITION_X
#define INT_INPUT_POSITION_Y NUMBER_INPUT_POSITION_Y
#define INT_INPUT_FOREGROUND NUMBER_INPUT_FOREGROUND
#define INT_INPUT_BACKGROUND NUMBER_INPUT_BACKGROUND
#define INT_INPUT_ON_ACTIVE_FOREGROUND NUMBER_INPUT_ON_ACTIVE_FOREGROUND
#define INT_INPUT_ON_ACTIVE_BACKGROUND NUMBER_INPUT_ON_ACTIVE_BACKGROUND
#define INT_INPUT_CONTAINER_SIZE 11
#define INT_INPUT_NAV_PANEL NUMBER_INPUT_NAV_PANEL
#define INT_INPUT_CHAR_SET NUMBER_INPUT_CHAR_SET
#define INT_INPUT_EXPRESS INT_STANDARD_EXPRESS
#define INT_INPUT_ON_CHANGE_EVENT NULL
#define INT_INPUT_ON_VIOLATE_EVENT NULL
#define INT_INPUT_ON_INVALID_EVENT NULL
#define INT_INPUT_ON_ENTER_EVENT NULL
#define INT_INPUT_ON_LEAVE_EVENT NULL

char Input(
  i_tp &obj,
  i_tp max = INT_INPUT_MAX_VALUE,
  i_tp min = INT_INPUT_MIN_VALUE,
  position_tp position_x = INT_INPUT_POSITION_X,
  position_tp position_y = INT_INPUT_POSITION_Y,
  color_tp f_color = INT_INPUT_FOREGROUND,
  color_tp b_color =INT_INPUT_BACKGROUND,
  size_tp container_size = INT_INPUT_CONTAINER_SIZE,
  color_tp on_active_f_color = INT_INPUT_ON_ACTIVE_FOREGROUND,
  color_tp on_active_b_color = INT_INPUT_ON_ACTIVE_BACKGROUND,
  NavigationPanelPrototype(NavigationPanel) = INT_INPUT_NAV_PANEL,
  ExpressPrototype(Express) = INT_INPUT_EXPRESS,
  InputEventTriggerPrototype(OnChange) = INT_INPUT_ON_CHANGE_EVENT,
  InputEventTriggerPrototype(OnViolate) = INT_INPUT_ON_VIOLATE_EVENT,
  InputEventTriggerPrototype(OnInvalid) = INT_INPUT_ON_INVALID_EVENT,
  InputEventTriggerPrototype(OnEnter) = INT_INPUT_ON_ENTER_EVENT,
  InputEventTriggerPrototype(OnLeave) = INT_INPUT_ON_LEAVE_EVENT
) {
  // Be strict with triggers
  if (NavigationPanel == NULL) NavigationPanel = INT_INPUT_NAV_PANEL;
  if (Express == NULL) Express =INT_INPUT_EXPRESS;

  // Initialize
  SaveColorContext;
  SaveCursorVisibleContext;

  // Show cursor
  ShowCursor;

  // Setup color
  SetColor(on_active_f_color, on_active_b_color);

  // Draw container
  DrawHorLine(container_size, ' ', position_x, position_y, on_active_f_color, on_active_b_color);

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
  printf("%d", obj);
  if (obj == 0) printf("%c", BACKSPACE);

  // Sign
  i_tp sign = obj < 0 ? -1 : 1;

  // Input
  while (true) {
    // Navigate
    if (NavigationPanelHandle(NavigationPanel)) break;

    // Input from ControlPanel
    c = ControlPanel();

    // Navigate
    if (NavigationPanelHandle(NavigationPanel)) break;

    if (IsNumericChar(c)) {
      // Violates max or min value, Call OnViolate
      if ((sign == 1 && NumViolatesMaxValue(obj, c, max)) || (sign == -1 && NumViolatesMinValue(obj, c, min))) {
        InputEventTriggerHandle(OnViolate);
        continue;
      }

      if (obj != obj * 10 + CharToInt(c) * sign) {
        obj = obj * 10 + CharToInt(c) * sign;
        printf("%c", c);

        // Call OnChange
        InputEventTriggerHandle(OnChange);

        // Violates min value, Call OnViolate
        if (sign == 1 && obj < min) InputEventTriggerHandle(OnViolate);
      }
    } else if (c == BACKSPACE) {
      if (obj != 0) printf("%c %c", BACKSPACE, BACKSPACE);
      else if (obj == 0 && sign == -1) {
        printf("%c%c  %c%c", BACKSPACE, BACKSPACE, BACKSPACE, BACKSPACE);
        sign = 1;
      }
      obj /= 10;

      // Call OnChange
      InputEventTriggerHandle(OnChange);

      // Violates min value, Call OnViolate
      if (sign == 1 && obj < min) InputEventTriggerHandle(OnViolate);
    } else if (c == 45 && obj == 0 && sign == 1) {
      sign = -1;
      printf("%c", '-');
    } else {
      // Call OnInvalid
      InputEventTriggerHandle(OnInvalid);
    }

    if (obj == 0) printf("0%c", BACKSPACE);
  }

  // Check min and re-create the context
  if (obj < min) {
    obj = min;
    InputEventTriggerHandle(OnChange);
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

/* Int */

// Limit
#define LONG_MAX_VALUE 9223372036854775807
#define LONG_MIN_VALUE -9223372036854775807

// Define
#define LONG_INPUT_MAX_VALUE LONG_MAX_VALUE
#define LONG_INPUT_MIN_VALUE LONG_MIN_VALUE
#define LONG_INPUT_POSITION_X NUMBER_INPUT_POSITION_X
#define LONG_INPUT_POSITION_Y NUMBER_INPUT_POSITION_Y
#define LONG_INPUT_FOREGROUND NUMBER_INPUT_FOREGROUND
#define LONG_INPUT_BACKGROUND NUMBER_INPUT_BACKGROUND
#define LONG_INPUT_ON_ACTIVE_FOREGROUND NUMBER_INPUT_ON_ACTIVE_FOREGROUND
#define LONG_INPUT_ON_ACTIVE_BACKGROUND NUMBER_INPUT_ON_ACTIVE_BACKGROUND
#define LONG_INPUT_CONTAINER_SIZE 21
#define LONG_INPUT_NAV_PANEL NUMBER_INPUT_NAV_PANEL
#define LONG_INPUT_CHAR_SET NUMBER_INPUT_CHAR_SET
#define LONG_INPUT_EXPRESS LONG_STANDARD_EXPRESS
#define LONG_INPUT_ON_CHANGE_EVENT NULL
#define LONG_INPUT_ON_VIOLATE_EVENT NULL
#define LONG_INPUT_ON_INVALID_EVENT NULL
#define LONG_INPUT_ON_ENTER_EVENT NULL
#define LONG_INPUT_ON_LEAVE_EVENT NULL

char Input(
  l_tp &obj,
  l_tp max = LONG_INPUT_MAX_VALUE,
  l_tp min = LONG_INPUT_MIN_VALUE,
  position_tp position_x = LONG_INPUT_POSITION_X,
  position_tp position_y = LONG_INPUT_POSITION_Y,
  color_tp f_color = LONG_INPUT_FOREGROUND,
  color_tp b_color =LONG_INPUT_BACKGROUND,
  size_tp container_size = LONG_INPUT_CONTAINER_SIZE,
  color_tp on_active_f_color = LONG_INPUT_ON_ACTIVE_FOREGROUND,
  color_tp on_active_b_color = LONG_INPUT_ON_ACTIVE_BACKGROUND,
  NavigationPanelPrototype(NavigationPanel) = INT_INPUT_NAV_PANEL,
  ExpressPrototype(Express) = LONG_INPUT_EXPRESS,
  InputEventTriggerPrototype(OnChange) = LONG_INPUT_ON_CHANGE_EVENT,
  InputEventTriggerPrototype(OnViolate) = LONG_INPUT_ON_VIOLATE_EVENT,
  InputEventTriggerPrototype(OnInvalid) = LONG_INPUT_ON_INVALID_EVENT,
  InputEventTriggerPrototype(OnEnter) = LONG_INPUT_ON_ENTER_EVENT,
  InputEventTriggerPrototype(OnLeave) = LONG_INPUT_ON_LEAVE_EVENT
) {
  // Be strict with triggers
  if (NavigationPanel == NULL) NavigationPanel = LONG_INPUT_NAV_PANEL;
  if (Express == NULL) Express = LONG_INPUT_EXPRESS;

  // Initialize
  SaveColorContext;
  SaveCursorVisibleContext;

  // Show cursor
  ShowCursor;

  // Setup color
  SetColor(on_active_f_color, on_active_b_color);

  // Draw container
  DrawHorLine(container_size, ' ', position_x, position_y, on_active_f_color, on_active_b_color);

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
  printf("%lld", obj);
  if (obj == 0) printf("%c", BACKSPACE);

  // Sign
  l_tp sign = obj < 0 ? -1 : 1;

  // Input
  while (true) {
    // Navigate
    if (NavigationPanelHandle(NavigationPanel)) break;

    // Input from ControlPanel
    c = ControlPanel();

    // Navigate
    if (NavigationPanelHandle(NavigationPanel)) break;

    if (IsNumericChar(c)) {
      // Violates max or min value, Call OnViolate
      if ((sign == 1 && NumViolatesMaxValue(obj, c, max)) || (sign == -1 && NumViolatesMinValue(obj, c, min))) {
        InputEventTriggerHandle(OnViolate);
        continue;
      }

      if (obj != obj * 10 + CharToInt(c) * sign) {
        obj = obj * 10 + CharToInt(c) * sign;
        printf("%c", c);

        // Call OnChange
        InputEventTriggerHandle(OnChange);

        // Violates min value, Call OnViolate
        if (sign == 1 && obj < min) InputEventTriggerHandle(OnViolate);
      }
    } else if (c == BACKSPACE) {
      if (obj != 0) printf("%c %c", BACKSPACE, BACKSPACE);
      else if (obj == 0 && sign == -1) {
        printf("%c%c  %c%c", BACKSPACE, BACKSPACE, BACKSPACE, BACKSPACE);
        sign = 1;
      }
      obj /= 10;

      // Call OnChange
      InputEventTriggerHandle(OnChange);

      // Violates min value, Call OnViolate
      if (sign == 1 && obj < min) InputEventTriggerHandle(OnViolate);
    } else if (c == 45 && obj == 0 && sign == 1) {
      sign = -1;
      printf("%c", '-');
    } else {
      // Call OnInvalid
      InputEventTriggerHandle(OnInvalid);
    }

    if (obj == 0) printf("0%c", BACKSPACE);
  }

  // Check min and re-create the context
  if (obj < min) {
    obj = min;
    InputEventTriggerHandle(OnChange);
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
