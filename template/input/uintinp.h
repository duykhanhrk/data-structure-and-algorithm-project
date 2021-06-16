/* Int input */

/* UShort */

// Limit
#define USHORT_MAX_VALUE 65535u
#define USHORT_MIN_VALUE 0

// Define
#define USHORT_INPUT_MAX_VALUE USHORT_MAX_VALUE
#define USHORT_INPUT_MIN_VALUE USHORT_MIN_VALUE
#define USHORT_INPUT_POSITION_X NUMBER_INPUT_POSITION_X
#define USHORT_INPUT_POSITION_Y NUMBER_INPUT_POSITION_Y
#define USHORT_INPUT_FOREGROUND NUMBER_INPUT_FOREGROUND
#define USHORT_INPUT_BACKGROUND NUMBER_INPUT_BACKGROUND
#define USHORT_INPUT_ON_ACTIVE_FOREGROUND NUMBER_INPUT_ON_ACTIVE_FOREGROUND
#define USHORT_INPUT_ON_ACTIVE_BACKGROUND NUMBER_INPUT_ON_ACTIVE_BACKGROUND
#define USHORT_INPUT_CONTAINER_SIZE 5
#define USHORT_INPUT_NAV_PANEL NUMBER_INPUT_NAV_PANEL
#define USHORT_INPUT_CHAR_SET NUMBER_INPUT_CHAR_SET
#define USHORT_INPUT_EXPRESS USHORT_STANDARD_EXPRESS
#define USHORT_INPUT_ON_CHANGE_EVENT NULL
#define USHORT_INPUT_ON_VIOLATE_EVENT NULL
#define USHORT_INPUT_ON_INVALID_EVENT NULL
#define USHORT_INPUT_ON_ENTER_EVENT NULL
#define USHORT_INPUT_ON_LEAVE_EVENT NULL

char Input(
  uh_tp &obj,
  uh_tp max = USHORT_INPUT_MAX_VALUE,
  uh_tp min = USHORT_INPUT_MIN_VALUE,
  position_tp position_x = USHORT_INPUT_POSITION_X,
  position_tp position_y = USHORT_INPUT_POSITION_Y,
  color_tp f_color = USHORT_INPUT_FOREGROUND,
  color_tp b_color = USHORT_INPUT_BACKGROUND,
  size_tp container_size = USHORT_INPUT_CONTAINER_SIZE,
  color_tp on_active_f_color = USHORT_INPUT_ON_ACTIVE_FOREGROUND,
  color_tp on_active_b_color = USHORT_INPUT_ON_ACTIVE_BACKGROUND,
  NavigationPanelPrototype(NavigationPanel) = USHORT_INPUT_NAV_PANEL,
  ExpressPrototype(Express) = USHORT_INPUT_EXPRESS,
  InputEventTriggerPrototype(OnChange) = USHORT_INPUT_ON_CHANGE_EVENT,
  InputEventTriggerPrototype(OnViolate) = USHORT_INPUT_ON_VIOLATE_EVENT,
  InputEventTriggerPrototype(OnInvalid) = USHORT_INPUT_ON_INVALID_EVENT,
  InputEventTriggerPrototype(OnEnter) = USHORT_INPUT_ON_ENTER_EVENT,
  InputEventTriggerPrototype(OnLeave) = USHORT_INPUT_ON_LEAVE_EVENT
) {
  // Be strict with triggers
  if (NavigationPanel == NULL) NavigationPanel = USHORT_INPUT_NAV_PANEL;
  if (Express == NULL) Express = USHORT_INPUT_EXPRESS;

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
  printf("%hu", obj);
  if (obj == 0) printf("%c", BACKSPACE);

  // Input
  while (true) {
    // Navigate
    if (NavigationPanelHandle(NavigationPanel)) break;

    // Input from ControlPanel
    c = ControlPanel();

    // Navigate
    if (NavigationPanelHandle(NavigationPanel)) break;

    if (IsNumericChar(c)) {
      // Violates max value, Call OnViolate
      if (NumViolatesMaxValue(obj, c, max)) {
        InputEventTriggerHandle(OnViolate);
        continue;
      }

      if (obj != obj * 10 + CharToInt(c)) {
        obj = obj * 10 + CharToInt(c);
        printf("%c", c);

        // Call OnChange
        InputEventTriggerHandle(OnChange);

        // Violates min value, Call OnViolate
        if (obj < min) InputEventTriggerHandle(OnViolate);
      }
    } else if (c == BACKSPACE) {
      if (obj != 0) printf("%c %c", BACKSPACE, BACKSPACE);
      obj /= 10;

      // Call OnChange
      InputEventTriggerHandle(OnChange);

      // Violates min value, Call OnViolate
      if (obj < min) InputEventTriggerHandle(OnViolate);
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

/* UInt */

// Limit
#define UINT_MAX_VALUE 4294967295u
#define UINT_MIN_VALUE 0

// Define
#define UINT_INPUT_MAX_VALUE UINT_MAX_VALUE
#define UINT_INPUT_MIN_VALUE UINT_MIN_VALUE
#define UINT_INPUT_POSITION_X NUMBER_INPUT_POSITION_X
#define UINT_INPUT_POSITION_Y NUMBER_INPUT_POSITION_Y
#define UINT_INPUT_FOREGROUND NUMBER_INPUT_FOREGROUND
#define UINT_INPUT_BACKGROUND NUMBER_INPUT_BACKGROUND
#define UINT_INPUT_ON_ACTIVE_FOREGROUND NUMBER_INPUT_ON_ACTIVE_FOREGROUND
#define UINT_INPUT_ON_ACTIVE_BACKGROUND NUMBER_INPUT_ON_ACTIVE_BACKGROUND
#define UINT_INPUT_CONTAINER_SIZE 10
#define UINT_INPUT_NAV_PANEL NUMBER_INPUT_NAV_PANEL
#define UINT_INPUT_CHAR_SET NUMBER_INPUT_CHAR_SET
#define UINT_INPUT_EXPRESS UINT_STANDARD_EXPRESS
#define UINT_INPUT_ON_CHANGE_EVENT NULL
#define UINT_INPUT_ON_VIOLATE_EVENT NULL
#define UINT_INPUT_ON_INVALID_EVENT NULL
#define UINT_INPUT_ON_ENTER_EVENT NULL
#define UINT_INPUT_ON_LEAVE_EVENT NULL

char Input(
  ui_tp &obj,
  ui_tp max = UINT_INPUT_MAX_VALUE,
  ui_tp min = UINT_INPUT_MIN_VALUE,
  position_tp position_x = UINT_INPUT_POSITION_X,
  position_tp position_y = UINT_INPUT_POSITION_Y,
  color_tp f_color = UINT_INPUT_FOREGROUND,
  color_tp b_color = UINT_INPUT_BACKGROUND,
  size_tp container_size = UINT_INPUT_CONTAINER_SIZE,
  color_tp on_active_f_color = UINT_INPUT_ON_ACTIVE_FOREGROUND,
  color_tp on_active_b_color = UINT_INPUT_ON_ACTIVE_BACKGROUND,
  NavigationPanelPrototype(NavigationPanel) = UINT_INPUT_NAV_PANEL,
  ExpressPrototype(Express) = UINT_INPUT_EXPRESS,
  InputEventTriggerPrototype(OnChange) = UINT_INPUT_ON_CHANGE_EVENT,
  InputEventTriggerPrototype(OnViolate) = UINT_INPUT_ON_VIOLATE_EVENT,
  InputEventTriggerPrototype(OnInvalid) = UINT_INPUT_ON_INVALID_EVENT,
  InputEventTriggerPrototype(OnEnter) = UINT_INPUT_ON_ENTER_EVENT,
  InputEventTriggerPrototype(OnLeave) = UINT_INPUT_ON_LEAVE_EVENT
) {
  // Be strict with triggers
  if (NavigationPanel == NULL) NavigationPanel = UINT_INPUT_NAV_PANEL;
  if (Express == NULL) Express = UINT_INPUT_EXPRESS;

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
  printf("%u", obj);
  if (obj == 0) printf("%c", BACKSPACE);

  // Input
  while (true) {
    // Navigate
    if (NavigationPanelHandle(NavigationPanel)) break;

    // Input from ControlPanel
    c = ControlPanel();

    // Navigate
    if (NavigationPanelHandle(NavigationPanel)) break;

    if (IsNumericChar(c)) {
      // Violates max value, Call OnViolate
      if (NumViolatesMaxValue(obj, c, max)) {
        InputEventTriggerHandle(OnViolate);
        continue;
      }

      if (obj != obj * 10 + CharToInt(c)) {
        obj = obj * 10 + CharToInt(c);
        printf("%c", c);

        // Call OnChange
        InputEventTriggerHandle(OnChange);

        // Violates min value, Call OnViolate
        if (obj < min) InputEventTriggerHandle(OnViolate);
      }
    } else if (c == BACKSPACE) {
      if (obj != 0) printf("%c %c", BACKSPACE, BACKSPACE);
      obj /= 10;

      // Call OnChange
      InputEventTriggerHandle(OnChange);

      // Violates min value, Call OnViolate
      if (obj < min) InputEventTriggerHandle(OnViolate);
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

/* ULong */

// Limit
#define ULONG_MAX_VALUE 18446744073709551615u
#define ULONG_MIN_VALUE 0

// Define
#define ULONG_INPUT_MAX_VALUE ULONG_MAX_VALUE
#define ULONG_INPUT_MIN_VALUE ULONG_MIN_VALUE
#define ULONG_INPUT_POSITION_X NUMBER_INPUT_POSITION_X
#define ULONG_INPUT_POSITION_Y NUMBER_INPUT_POSITION_Y
#define ULONG_INPUT_FOREGROUND NUMBER_INPUT_FOREGROUND
#define ULONG_INPUT_BACKGROUND NUMBER_INPUT_BACKGROUND
#define ULONG_INPUT_ON_ACTIVE_FOREGROUND NUMBER_INPUT_ON_ACTIVE_FOREGROUND
#define ULONG_INPUT_ON_ACTIVE_BACKGROUND NUMBER_INPUT_ON_ACTIVE_BACKGROUND
#define ULONG_INPUT_CONTAINER_SIZE 20
#define ULONG_INPUT_NAV_PANEL NUMBER_INPUT_NAV_PANEL
#define ULONG_INPUT_CHAR_SET NUMBER_INPUT_CHAR_SET
#define ULONG_INPUT_EXPRESS ULONG_STANDARD_EXPRESS
#define ULONG_INPUT_ON_CHANGE_EVENT NULL
#define ULONG_INPUT_ON_VIOLATE_EVENT NULL
#define ULONG_INPUT_ON_INVALID_EVENT NULL
#define ULONG_INPUT_ON_ENTER_EVENT NULL
#define ULONG_INPUT_ON_LEAVE_EVENT NULL

char Input(
  ul_tp &obj,
  ul_tp max = ULONG_INPUT_MAX_VALUE,
  ul_tp min = ULONG_INPUT_MIN_VALUE,
  position_tp position_x = ULONG_INPUT_POSITION_X,
  position_tp position_y = ULONG_INPUT_POSITION_Y,
  color_tp f_color = ULONG_INPUT_FOREGROUND,
  color_tp b_color = ULONG_INPUT_BACKGROUND,
  size_tp container_size = ULONG_INPUT_CONTAINER_SIZE,
  color_tp on_active_f_color = ULONG_INPUT_ON_ACTIVE_FOREGROUND,
  color_tp on_active_b_color = ULONG_INPUT_ON_ACTIVE_BACKGROUND,
  NavigationPanelPrototype(NavigationPanel) = ULONG_INPUT_NAV_PANEL,
  ExpressPrototype(Express) = ULONG_INPUT_EXPRESS,
  InputEventTriggerPrototype(OnChange) = ULONG_INPUT_ON_CHANGE_EVENT,
  InputEventTriggerPrototype(OnViolate) = ULONG_INPUT_ON_VIOLATE_EVENT,
  InputEventTriggerPrototype(OnInvalid) = ULONG_INPUT_ON_INVALID_EVENT,
  InputEventTriggerPrototype(OnEnter) = ULONG_INPUT_ON_ENTER_EVENT,
  InputEventTriggerPrototype(OnLeave) = ULONG_INPUT_ON_LEAVE_EVENT
) {
  // Be strict with triggers
  if (NavigationPanel == NULL) NavigationPanel = ULONG_INPUT_NAV_PANEL;
  if (Express == NULL) Express = ULONG_INPUT_EXPRESS;

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
  printf("%llu", obj);
  if (obj == 0) printf("%c", BACKSPACE);

  // Input
  while (true) {
    // Navigate
    if (NavigationPanelHandle(NavigationPanel)) break;

    // Input from ControlPanel
    c = ControlPanel();

    // Navigate
    if (NavigationPanelHandle(NavigationPanel)) break;

    if (IsNumericChar(c)) {
      // Violates max value, Call OnViolate
      if (NumViolatesMaxValue(obj, c, max)) {
        InputEventTriggerHandle(OnViolate);
        continue;
      }

      if (obj != obj * 10 + CharToInt(c)) {
        obj = obj * 10 + CharToInt(c);
        printf("%c", c);

        // Call OnChange
        InputEventTriggerHandle(OnChange);

        // Violates min value, Call OnViolate
        if (obj < min) InputEventTriggerHandle(OnViolate);
      }
    } else if (c == BACKSPACE) {
      if (obj != 0) printf("%c %c", BACKSPACE, BACKSPACE);
      obj /= 10;

      // Call OnChange
      InputEventTriggerHandle(OnChange);

      // Violates min value, Call OnViolate
      if (obj < min) InputEventTriggerHandle(OnViolate);
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
