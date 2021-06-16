#include "print.h"

/* rapid - ptp */

#define ptp_context_arguments position_tp position_x = CURSOR_POSITION_X, \
                              position_tp position_y = CURSOR_POSITION_Y, \
                              color_tp f_color = CURRENT_FOREGROUND, \
                              color_tp b_color = CURRENT_BACKGROUND

#define ptp_save_color_context color_tp __current_foreground__ = CURRENT_FOREGROUND; \
                               color_tp __current_background__ = CURRENT_BACKGROUND

#define ptp_apply_color_context SetColor(__current_foreground__, __current_background__)

#define ptp_apply_cursor_context_arguments GotoXY(position_x, position_y)

#define ptp_apply_color_context_arguments SetColor(f_color, b_color)

#define ptp_apply_context_arguments ptp_apply_cursor_context_arguments; \
                                    ptp_apply_color_context_arguments

#define ptp_end_line GotoXY(position_x, position_y + 1)

/* Define */

/* Print */

void PrintChar(char obj, ptp_context_arguments) {
  ptp_save_color_context;
  ptp_apply_context_arguments;
  printf("%c\n", obj);
  ptp_end_line;
  ptp_apply_color_context;
}

void PrintStr(const char *obj, ptp_context_arguments) {
  ptp_save_color_context;
  ptp_apply_context_arguments;
  printf("%s\n", obj);
  ptp_end_line;
  ptp_apply_color_context;
}

void PrintShort(short int obj, ptp_context_arguments) {
  ptp_save_color_context;
  ptp_apply_context_arguments;
  printf("%hi\n", obj);
  ptp_end_line;
  ptp_apply_color_context;
}

void PrintInt(int obj, ptp_context_arguments) {
  ptp_save_color_context;
  ptp_apply_context_arguments;
  printf("%d\n", obj);
  ptp_end_line;
  ptp_apply_color_context;
}

void PrintLong(long long int obj, ptp_context_arguments) {
  ptp_save_color_context;
  ptp_apply_context_arguments;
  printf("%lld\n", obj);
  ptp_end_line;
  ptp_apply_color_context;
}

void PrintUShort(unsigned short int obj, ptp_context_arguments) {
  ptp_save_color_context;
  ptp_apply_context_arguments;
  printf("%hu\n", obj);
  ptp_end_line;
  ptp_apply_color_context;
}

void PrintUInt(unsigned int obj, ptp_context_arguments) {
  ptp_save_color_context;
  ptp_apply_context_arguments;
  printf("%u\n", obj);
  ptp_end_line;
  ptp_apply_color_context;
}

void PrintULong(unsigned long long int obj, ptp_context_arguments) {
  ptp_save_color_context;
  ptp_apply_context_arguments;
  printf("%llu\n", obj);
  ptp_end_line;
  ptp_apply_color_context;
}

void PrintDate(time_t obj, ptp_context_arguments) {
  struct tm time_info = *(localtime(&obj));
  ptp_save_color_context;
  ptp_apply_context_arguments;
  if (time_info.tm_mday < 10) printf("0%hu", time_info.tm_mday);
  else printf("%hu", time_info.tm_mday);

  if (time_info.tm_mon < 10) printf("/0%hu", time_info.tm_mon + 1);
  else printf("/%hu", time_info.tm_mon + 1);

  printf("/%hu", time_info.tm_year + 1900);
  ptp_end_line;
  ptp_apply_color_context;
}
