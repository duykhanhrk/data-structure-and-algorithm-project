/* Navigation Panel */

#define STANDARD_NAV_PANEL StandardNavPanel
#define DATETIME_INPUT_NAV_PANEL DateTimeInputNavPanel

#define NavigationPanelPrototype(nvp_name) char (*nvp_name)(char)
#define NavigationPanelInit(nvp_name) char nvp_name(char c)
#define NavigationPanelCall(nvp_name) nvp_name(c)
#define NavigationPanelHandle(nvp_name) \
        NavigationPanelCall(nvp_name)

// ENTER | ESC | KEY_UP | KEY_DOWN
NavigationPanelInit(StandardNavPanel) {
  return (c == ENTER || c == ESC || c == KEY_UP || c == KEY_DOWN);
}

// Using for DateTime input
NavigationPanelInit(DateTimeInputNavPanel) {
  return (c == ENTER || c == ESC || c == KEY_UP || c == KEY_DOWN || c == KEY_LEFT || c == KEY_RIGHT || c == SLASH);
}
