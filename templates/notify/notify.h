#ifndef __TEMPLATE_NOTIFY__
#define __TEMPLATE_NOTIFY__

/* default value */
#define NOTIFY_FOREGROUND PROGRAM_FOREGROUND_REVERSE
#define NOTIFY_BACKGROUND PROGRAM_THEME_BACKGROUND
#define NOTIFY_ERROR_FOREGROUND PROGRAM_FOREGROUND_REVERSE
#define NOTIFY_ERROR_BACKGROUND BACKGROUND_LIGHT_RED
#define NOTIFY_WARNING_FOREGROUND PROGRAM_FOREGROUND_REVERSE
#define NOTIFY_WARNING_BACKGROUND BACKGROUND_YELLOW
#define NOTIFY_SUCCESS_FOREGROUND PROGRAM_FOREGROUND_REVERSE
#define NOTIFY_SUCCESS_BACKGROUND BACKGROUND_LIGHT_GREEN

#define NOTIFY_SIZE 1
#define NOTIFY_WIDTH 0
#define NOTIFY_HEIGHT 0

#define NORMAL_NOTIFY 0
#define ERROR_NOTIFY 1
#define WARNING_NOTIFY 2
#define SUCCESS_NOTIFY 3

#ifdef __cplusplus
extern "C" {
#endif

typedef struct NotifyT {
  size_tp width;
  size_tp height;
  size_tp size;
  position_tp position_x;
  position_tp position_y;
  color_tp foreground;
  color_tp background;
  color_tp error_foreground;
  color_tp error_background;
  color_tp warning_foreground;
  color_tp warning_background;
  color_tp success_foreground;
  color_tp success_background;
} NotifyT, * Notify;

Notify NewNotify(
  size_tp width = NOTIFY_WIDTH,
  size_tp height = NOTIFY_HEIGHT,
  size_tp size = NOTIFY_SIZE,
  position_tp position_x = CURSOR_POSITION_X,
  position_tp position_y = CURSOR_POSITION_Y,
  color_tp foreground = NOTIFY_FOREGROUND,
  color_tp background = NOTIFY_BACKGROUND,
  color_tp error_foreground = NOTIFY_ERROR_FOREGROUND,
  color_tp error_background = NOTIFY_ERROR_BACKGROUND,
  color_tp warning_foreground = NOTIFY_WARNING_FOREGROUND,
  color_tp warning_background = NOTIFY_WARNING_BACKGROUND,
  color_tp success_foreground = NOTIFY_SUCCESS_FOREGROUND,
  color_tp success_background = NOTIFY_SUCCESS_BACKGROUND
) {
  Notify notify = (Notify) malloc(sizeof(NotifyT));
  notify->width = width;
  notify->height = height;
  notify->size = size;
  notify->position_x = position_x;
  notify->position_y = position_y;
  notify->foreground = foreground;
  notify->background = background;
  notify->error_foreground = error_foreground;
  notify->error_background = error_background;
  notify->warning_foreground = warning_foreground;
  notify->warning_background = warning_background;
  notify->success_foreground = success_foreground;
  notify->success_background = success_background;
  return notify;
}

void DestroyNotify(Notify &notify) {
  free(notify);
  notify = NULL;
}

void RenderNotify(Notify notify, status_tp status, const char * message) {
  color_tp foreground = notify->foreground;
  color_tp background = notify->background;

  if (status == ERROR_NOTIFY) {
    foreground = notify->error_foreground;
    background = notify->error_background;
  } else if (status == WARNING_NOTIFY) {
    foreground = notify->warning_foreground;
    background = notify->warning_background;
  } else if (status == SUCCESS_NOTIFY) {
    foreground = notify->success_foreground;
    background = notify->success_background;
  }

  if (notify->size > 0) {
    notify->height = 2 * (notify->size - 1) + 1;
    notify->width = strlen(message) + 2;
  }

  DrawRecShape(
    notify->width, notify->height,
    ' ',
    notify->position_x, notify->position_y,
    foreground, background
  );

  position_tp position_x = notify->position_x + 2;
  position_tp position_y = notify->position_y + (notify->height / 2);

  WriteStr(
    message,
    position_x, position_y,
    foreground, background
  );
}


#ifdef __cplusplus
}
#endif

#endif
