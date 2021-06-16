#include "draw.h"

#define DRAW_CHR_DEFAULT ' '

#define dwp_context_arguments position_tp position_x = CURSOR_POSITION_X, \
                              position_tp position_y = CURSOR_POSITION_Y, \
                              color_tp f_color = CURRENT_FOREGROUND, \
                              color_tp b_color = CURRENT_BACKGROUND

#define dwp_save_color_context color_tp __current_foreground__ = CURRENT_FOREGROUND; \
                               color_tp __current_background__ = CURRENT_BACKGROUND

#define dwp_apply_color_context SetColor(__current_foreground__, __current_background__)

#define dwp_apply_cursor_context_arguments GotoXY(position_x, position_y)

#define dwp_apply_color_context_arguments SetColor(f_color, b_color)

#define dwp_apply_context_arguments dwp_apply_cursor_context_arguments; \
                                    dwp_apply_color_context_arguments

#define dwp_end_line GotoXY(position_x, position_y + 1)

// Draw a line
void DrawVerLine(size_tp size, char chr = DRAW_CHR_DEFAULT, dwp_context_arguments) {
  dwp_save_color_context;
  dwp_apply_context_arguments;
  for (int i = 0; i < size - 1; i ++) {
    GotoXY(position_x, position_y + i);
    printf("%c\n", chr);
  }
  GotoXY(position_x, position_y + size - 1);
  printf("%c", chr);
  dwp_apply_color_context;
}

void DrawHorLine(size_tp size, char chr = DRAW_CHR_DEFAULT, dwp_context_arguments) {
  dwp_save_color_context;
  dwp_apply_context_arguments;

  char *line = new char[size + 1];
  for (int i = 0; i < size; i ++) {
    line[i] = chr;
  }
  line[size] = '\0';

  printf("%s", line);

  delete [] line;
  dwp_apply_color_context;
}

// Draw a rectangle

void DrawRec(size_tp width, size_tp height, char chr = DRAW_CHR_DEFAULT, dwp_context_arguments) {
  dwp_save_color_context;
  dwp_apply_context_arguments;

  char *line = new char[width + 1];

  for (int i = 0; i < width; i ++) {
    line[i] = chr;
  }
  line[width] = '\0';

  printf("%s", line);
  GotoXY(position_x, position_y + height - 1);
  printf("%s", line);
  delete [] line;

  for (int i = 1; i < height - 1; i ++) {
    GotoXY(position_x, position_y + i);
    printf("%c", chr);

    GotoXY(position_x + width - 1, position_y + i);
    printf("%c", chr);
  }

  GotoXY(position_x, position_y + height);
  dwp_apply_color_context;
}

// Draw rectangle shape

void DrawRecShape(size_tp width, size_tp height, char chr = DRAW_CHR_DEFAULT, dwp_context_arguments) {
  dwp_save_color_context;
  dwp_apply_context_arguments;

  char *line = new char[width + 1];

  for (int i = 0; i < width; i ++) {
    line[i] = chr;
  }
  line[width] = '\0';

  for (int i = 0; i < height; i ++) {
    GotoXY(position_x, position_y + i);
    printf("%s", line);
  }

  delete [] line;

  dwp_apply_context_arguments;
}
