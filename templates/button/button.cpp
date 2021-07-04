#include "button.h"

Button NewButton(
  const char * text = BUTTON_TEXT,
  align_tp text_align = BUTTON_TEXT_ALIGN,
  size_tp width = BUTTON_WIDTH,
  size_tp height = BUTTON_HEIGHT,
  size_tp size = BUTTON_SIZE,
  position_tp position_x = CURSOR_POSITION_X,
  position_tp position_y = CURSOR_POSITION_Y,
  color_tp foreground = BUTTON_FOREGROUND,
  color_tp background = BUTTON_BACKGROUND,
  color_tp active_foreground = BUTTON_ACTIVE_FOREGROUND,
  color_tp active_background = BUTTON_ACTIVE_BACKGROUND,
  bool (* console)(char) = BUTTON_CONSOLE
) {
  Button button = (Button) malloc(sizeof(ButtonT));

  button->text = (char *) malloc(sizeof(char) * strlen(text) + 1);
  strcpy(button->text, text);
  button->text_align = text_align;
  button->position_x = position_x,
  button->position_y = position_y,
  button->width = width;
  button->height = height;
  button->size = size;
  button->foreground = foreground;
  button->background = background;
  button->active_foreground = active_foreground;
  button->active_background = active_background;
  button->console = console;

  return button;
}

void DestroyButton(Button &button) {
  free(button->text);
  free(button);
  button = NULL;
}

void SetButtonText(Button button, const char * text) {
  free(button->text);
  button->text = (char *) malloc(sizeof(char) * strlen(text) + 1);
  strcpy(button->text, text);
}

void RenderButton(Button button, status_tp status = NORMAL_BUTTON) {
  color_tp foreground = button->foreground;
  color_tp background = button->background;

  if (status == ACTIVE_BUTTON) {
    foreground = button->active_foreground;
    background = button->active_background;
  }

  if (button->size > 0) {
    button->height = 2 * (button->size - 1) + 1;
    button->width = strlen(button->text) + 2;
  }

  DrawRecShape(
    button->width,
    button->height,
    ' ',
    button->position_x,
    button->position_y,
    foreground,
    background
  );

  size_tp position_x = button->position_x + 2;
  if (button->text_align == ALIGN_CENTER) {
    position_x = button->position_x + (button->width - strlen(button->text)) / 2;
    position_x = position_x >= 0 ? position_x : 0;
  }

  size_tp position_y = button->position_y + button->height / 2;
  WriteStr(
    button->text,
    position_x,
    position_y,
    foreground,
    background
  );
}

keycode_tp ActiveButton(Button button) {
  RenderButton(button, ACTIVE_BUTTON);

  char c;
  do {
    c = Console();
  } while (!button->console(c));

  RenderButton(button, NORMAL_BUTTON);
  return c;
}

tpp_define_conceal_method(ConcealButton, Button)
