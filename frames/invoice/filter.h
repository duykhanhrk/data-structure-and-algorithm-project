#ifndef __FRAMES_INVOICE_FILTER_FORM__
#define __FRAMES_INVOICE_FILTER_FORM__

/* includes */
#include "invoice_list_by_from_to.h"

/* Private key - IFP */

/* Rapid - ifp */
#define ifp_templates_args\
        EditDateTime edit_form,\
        EditDateTime edit_to,\
        Button filter_button,\
        Button close_button,\
        Notify notify

#define ifp_templates_params\
        edit_form,\
        edit_to,\
        filter_button,\
        close_button,\
        notify

#define ifp_render_templates RenderInvoiceFilterFormTemplates(ifp_templates_params)

#define ifp_form_background\
        DrawRecShape(\
          frame->width, frame->height, ' ', frame->position_x, frame->position_y,\
          CURRENT_FOREGROUND, PROGRAM_THEME_BACKGROUND\
        )

#define ifp_form_label(text, y)\
        WriteStr(text, frame->position_x + 2, frame->position_y + 2 + 4 * y)

#define ifp_render\
        ifp_form_background;\
        ifp_form_label("Từ", 0);\
        ifp_form_label("Đến", 1);\
        ifp_render_templates

// Config
#define IFP_FORM_WIDTH 50
#define IFP_FORM_HEIGHT 17

#define IFP_INPUT_WIDTH 36
#define IFP_INPUT_HEIGHT 3

#ifdef __cplusplus
extern "C" {
#endif

// Conceal - using rapid
tpp_define_conceal_method(ConcealInvoiceFilterForm, Frame)

void RenderInvoiceFilterFormTemplates(ifp_templates_args) {
  RenderEditDateTime(edit_to);
  RenderEditDateTime(edit_form);
  RenderButton(filter_button);
  RenderButton(close_button);
  RenderNotify(notify, NORMAL_NOTIFY, "Nhập ngày tháng sau đó chọn lọc");
}

void DestroyInvoiceFilterFormTemplates(ifp_templates_args) {
  DestroyEditDateTime(edit_to);
  DestroyEditDateTime(edit_form);
  DestroyButton(filter_button);
  DestroyButton(close_button);
  DestroyNotify(notify);
}

void ActiveInvoiceFilterForm(Frame frame) {
  // default
  frame->active_element = 1;

  // Variable
  LinearList linear_list;
  Invoice invoice;
  time_t from = 1388534400; // 2014-01-01
  time_t to = TimeNow();

  // Init templates
  EditDateTime edit_form = NewEditDateTime(
    &(from),
    TimeNow(), 1388534400,
    IFP_INPUT_WIDTH, IFP_INPUT_HEIGHT,
    frame->position_x + 12, frame->position_y + 1,
    EDIT_STR_FOREGROUND, EDIT_STR_BACKGROUND,
    EDIT_STR_ACTIVE_FOREGROUND, EDIT_STR_ACTIVE_BACKGROUND
  );

  EditDateTime edit_to = NewEditDateTime(
    &(to),
    TimeNow(), 1388534400,
    IFP_INPUT_WIDTH, IFP_INPUT_HEIGHT,
    frame->position_x + 12, frame->position_y + 5,
    EDIT_STR_FOREGROUND, EDIT_STR_BACKGROUND,
    EDIT_STR_ACTIVE_FOREGROUND, EDIT_STR_ACTIVE_BACKGROUND
  );

  Button filter_button = NewButton(
    " Lọc", ALIGN_CENTER,
    (frame->width - 6) / 2, 3, 0,
    frame->position_x + 2, frame->position_y + 9,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND_LV1,
    PROGRAM_THEME_FOREGROUND_LV1, PROGRAM_BACKGROUND,
    STANDARD_CONSOLE
  );

  Button close_button = NewButton(
    " Thoát", ALIGN_CENTER,
    (frame->width - 6) / 2, 3, 0,
    frame->position_x + (frame->width - 6) / 2 + 4, frame->position_y + 9,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND_LV1,
    PROGRAM_THEME_FOREGROUND_LV1, PROGRAM_BACKGROUND,
    STANDARD_CONSOLE
  );

  Notify notify = NewNotify(
    frame->width - 4, 3, 0,
    frame->position_x + 2, frame->position_y + 13,
    PROGRAM_FOREGROUND, BACKGROUND_LIGHT_AQUA
  );

  Frame support_frame = NewFrame(
    100, 30,
    20, 0
  );

  // Render
  ifp_render;

  // Active
  keycode_tp keycode;
  while (frame->active_element != 0) {
    if (frame->active_element == 1) {
      keycode = ActiveEditDateTime(edit_form);
      if (keycode == ENTER || keycode == KEY_DOWN)
        frame->active_element = 2;
    } else if (frame->active_element == 2) {
      keycode = ActiveEditDateTime(edit_to);
      if (keycode == ENTER || keycode == KEY_DOWN)
        frame->active_element = 3;
      else if (keycode == KEY_UP)
        frame->active_element = 1;
    } else if (frame->active_element == 3) {
      keycode = ActiveButton(filter_button);
      if (keycode == ENTER) {
        if (from > to) {
          RenderNotify(notify, ERROR_NOTIFY, "Thời gian không hợp lệ");
          continue;
        }

        from = BeginningOfDayTimeT(from);
        to = EndOfDayTimeT(to);

        ConcealInvoiceFilterForm(frame);
        ActiveInvoiceListByFromTo(support_frame, from, to);

        ifp_render;
      }
      else if (keycode == KEY_RIGHT)
        frame->active_element = 4;
      else if (keycode == KEY_UP)
        frame->active_element = 2;
    } else if (frame->active_element == 4) {
      keycode = ActiveButton(close_button);
      if (keycode == ENTER)
        frame->active_element = 0;
      else if (keycode == KEY_UP)
        frame->active_element = 2;
      else if (keycode == KEY_LEFT)
        frame->active_element = 3;
    }
  }

  // Recovery
  ConcealInvoiceFilterForm(frame);

  // Release
  DestroyInvoiceFilterFormTemplates(ifp_templates_params);
}

#ifdef __cplusplus
}
#endif

#endif
