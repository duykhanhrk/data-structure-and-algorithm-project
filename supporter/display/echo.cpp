#include "echo.h"

/* rapid - ecp */

#define ecp_context_arguments position_tp position_x = CURSOR_POSITION_X, \
                              position_tp position_y = CURSOR_POSITION_Y, \
                              color_tp f_color = CURRENT_FOREGROUND, \
                              color_tp b_color = CURRENT_BACKGROUND

#define ecp_apply_cursor_context_arguments GotoXY(position_x, position_y)

#define ecp_apply_color_context_arguments SetColor(f_color, b_color)

#define ecp_apply_context_arguments ecp_apply_cursor_context_arguments; \
                                    ecp_apply_color_context_arguments

#define ecp_save_cursor_position_context position_tp __cursor_position_x__ = CURSOR_POSITION_X; \
                                         position_tp __cursor_position_y__ = CURSOR_POSITION_Y

#define ecp_apply_cursor_position_context GotoXY(__cursor_position_x__, __cursor_position_y__)

#define ecp_save_color_context color_tp __current_foreground__ = CURRENT_FOREGROUND; \
                               color_tp __current_background__ = CURRENT_BACKGROUND

#define ecp_apply_color_context SetColor(__current_foreground__, __current_background__)

#define ecp_save_context ecp_save_cursor_position_context; \
                         ecp_save_color_context

#define ecp_apply_context ecp_apply_cursor_position_context; \
                          ecp_apply_color_context

void EchoChar(char obj, ecp_context_arguments) {
  ecp_save_context;
  ecp_apply_context_arguments;
  printf("%c", obj);
  ecp_apply_context;
}

void EchoStr(const char *obj, ecp_context_arguments) {
  ecp_save_context;
  ecp_apply_context_arguments;
  printf("%s", obj);
  ecp_apply_context;
}

void EchoShort(short int obj, ecp_context_arguments) {
  ecp_save_context;
  ecp_apply_context_arguments;
  printf("%hi", obj);
  ecp_apply_context;
}

void EchoInt(int obj, ecp_context_arguments) {
  ecp_save_context;
  ecp_apply_context_arguments;
  printf("%d", obj);
  ecp_apply_context;
}

void EchoLong(long long int obj, ecp_context_arguments) {
  ecp_save_context;
  ecp_apply_context_arguments;
  printf("%lld", obj);
  ecp_apply_context;
}

void EchoUShort(unsigned short int obj, ecp_context_arguments) {
  ecp_save_context;
  ecp_apply_context_arguments;
  printf("%hu", obj);
  ecp_apply_context;
}

void EchoUInt(unsigned int obj, ecp_context_arguments) {
  ecp_save_context;
  ecp_apply_context_arguments;
  printf("%u", obj);
  ecp_apply_context;
}

void EchoULong(unsigned long long int obj, ecp_context_arguments) {
  ecp_save_context;
  ecp_apply_context_arguments;
  printf("%llu", obj);
  ecp_apply_context;
}

void EchoDouble(double obj, ecp_context_arguments) {
  ecp_save_context;
  ecp_apply_context_arguments;
  std::cout << std::fixed << obj;
  ecp_apply_context;
}

void EchoDate(time_t obj, ecp_context_arguments) {
  struct tm time_info = *(localtime(&obj));
  ecp_save_context;
  ecp_apply_context_arguments;
  if (time_info.tm_mday < 10) printf("0%hu", time_info.tm_mday);
  else printf("%hu", time_info.tm_mday);

  if (time_info.tm_mon < 10) printf("/0%hu", time_info.tm_mon + 1);
  else printf("/%hu", time_info.tm_mon + 1);

  printf("/%hu", time_info.tm_year + 1900);
  ecp_apply_context;
}
