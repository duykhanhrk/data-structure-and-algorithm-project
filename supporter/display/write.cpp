#include "write.h"

/* rapid - wrp */

#define wrp_context_arguments position_tp position_x = CURSOR_POSITION_X, \
                              position_tp position_y = CURSOR_POSITION_Y, \
                              color_tp f_color = CURRENT_FOREGROUND, \
                              color_tp b_color = CURRENT_BACKGROUND

#define wrp_save_color_context color_tp __current_foreground__ = CURRENT_FOREGROUND; \
                               color_tp __current_background__ = CURRENT_BACKGROUND

#define wrp_apply_color_context SetColor(__current_foreground__, __current_background__)

#define wrp_apply_cursor_context_arguments GotoXY(position_x, position_y)

#define wrp_apply_color_context_arguments SetColor(f_color, b_color)

#define wrp_apply_context_arguments wrp_apply_cursor_context_arguments; \
                                    wrp_apply_color_context_arguments

#define wrp_end_line GotoXY(position_x, position_y + 1)

void WriteChar(char obj, wrp_context_arguments) {
  wrp_save_color_context;
  wrp_apply_context_arguments;
  printf("%c", obj);
  wrp_apply_color_context;
}

void WriteStr(const char *obj, wrp_context_arguments) {
  wrp_save_color_context;
  wrp_apply_context_arguments;
  printf("%s", obj);
  wrp_apply_color_context;
}

// OPTIMIZE: notify, only int
void WriteStrTypeI(const char *obj , int num, wrp_context_arguments) {
  wrp_save_color_context;
  wrp_apply_context_arguments;
  printf(obj, num);
  wrp_apply_color_context;
}

void WriteStrTypeSI(const char *obj , const char * str, int num, wrp_context_arguments) {
  wrp_save_color_context;
  wrp_apply_context_arguments;
  printf(obj, str, num);
  wrp_apply_color_context;
}

void WriteDoubleStrV(const char *obj, const char *_obj, int max_len, wrp_context_arguments) {
  wrp_save_color_context;
  wrp_apply_context_arguments;

  int obj_len = strlen(obj);
  int _obj_len = strlen(_obj);
  if (obj_len + _obj_len + 1 > max_len) {
    printf("N/A");
  } else {
    char * __obj = (char *) malloc(strlen(obj) + strlen(_obj) + 2);
    strcpy(__obj, obj);
    strcat(__obj, " ");
    strcat(__obj, _obj);
    printf("%s", __obj);
    free(__obj);
  }
  wrp_apply_color_context;
}

void WriteShort(short int obj, wrp_context_arguments) {
  wrp_save_color_context;
  wrp_apply_context_arguments;
  printf("%hi", obj);
  wrp_apply_color_context;
}

void WriteInt(int obj, wrp_context_arguments) {
  wrp_save_color_context;
  wrp_apply_context_arguments;
  printf("%d", obj);
  wrp_apply_color_context;
}

void WriteLong(long long int obj, wrp_context_arguments) {
  wrp_save_color_context;
  wrp_apply_context_arguments;
  printf("%lld", obj);
  wrp_apply_color_context;
}

void WriteUShort(unsigned short int obj, wrp_context_arguments) {
  wrp_save_color_context;
  wrp_apply_context_arguments;
  printf("%hu", obj);
  wrp_apply_color_context;
}

void WriteUInt(unsigned int obj, wrp_context_arguments) {
  wrp_save_color_context;
  wrp_apply_context_arguments;
  printf("%u", obj);
  wrp_apply_color_context;
}

void WriteULong(unsigned long long int obj, wrp_context_arguments) {
  wrp_save_color_context;
  wrp_apply_context_arguments;
  printf("%llu", obj);
  wrp_apply_color_context;
}

void WriteDouble(double obj, wrp_context_arguments, int round_to_digit = 2) {
  wrp_save_color_context;
  wrp_apply_context_arguments;
  char format[6] = "%.2lf";
  format[2] = IntToChar(DigitsOfDoubleAfterDot(obj, round_to_digit));
  printf(format, obj);
  wrp_apply_color_context;
}

void WriteDoubleP(double obj, int round_to_digit = 2, wrp_context_arguments) {
  wrp_save_color_context;
  wrp_apply_context_arguments;
  char format[6] = "%.0lf";
  format[2] = IntToChar(DigitsOfDoubleAfterDot(obj, round_to_digit));
  printf(format, obj);
  wrp_apply_color_context;
}

void WriteDoubleV(double obj, int round_to_digit = 2, int max_len = 10, wrp_context_arguments) {
  wrp_save_color_context;
  wrp_apply_context_arguments;
  if (DigitsOfDoubleIncludeDot(obj, round_to_digit) > max_len) {
    printf("N/A");
  } else {
    char format[6] = "%.2lf";
    format[2] = IntToChar(DigitsOfDoubleAfterDot(obj, round_to_digit));
    printf(format, obj);
  }
  wrp_apply_color_context;
}

void WriteDate(time_t obj, wrp_context_arguments) {
  tm time_info = *(localtime(&obj));
  wrp_save_color_context;
  wrp_apply_context_arguments;
  if (time_info.tm_mday < 10) printf("0%hu", time_info.tm_mday);
  else printf("%hu", time_info.tm_mday);

  if (time_info.tm_mon < 10) printf("/0%hu", time_info.tm_mon + 1);
  else printf("/%hu", time_info.tm_mon + 1);

  printf("/%hu", time_info.tm_year + 1900);
  wrp_apply_color_context;
}
