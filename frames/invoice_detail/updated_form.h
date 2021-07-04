#ifndef __FRAMES_INVOICE_DETAIL_UPDATED_FORM__
#define __FRAMES_INVOICE_DETAIL_UPDATED_FORM__

#define IDUP_INPUT_WIDTH 36
#define IDUP_INPUT_HEIGHT 3

#define IDUP_INPUT_FOREGOURND EDIT_STR_FOREGROUND
#define IDUP_INPUT_BACKGROUND EDIT_STR_BACKGROUND
#define IDUP_INPUT_ACTIVE_FOREGOURND EDIT_STR_ACTIVE_FOREGROUND
#define IDUP_INPUT_ACTIVE_BACKGROUND EDIT_STR_ACTIVE_BACKGROUND

#define IDUP_DOUBLE_ROUND 2

// rapid - idup
#define idup_form_background\
        DrawRecShape(\
          frame->width, frame->height, ' ', frame->position_x, frame->position_y,\
          CURRENT_FOREGROUND, PROGRAM_THEME_BACKGROUND\
        );

#define idup_form_label(text, y)\
        WriteStr(text, frame->position_x + 2, frame->position_y + 2 + 4 * y)

#define idup_render_form\
        IDUPRenderInvoiceDetailFrame(\
          edit_amount,\
          edit_price,\
          edit_vat,\
          save_button,\
          delete_button,\
          close_button\
        )

#ifdef __cplusplus
extern "C" {
#endif

void IDUPRecovery(Frame frame) {
  DrawRecShape(
    frame->width, frame->height, ' ', frame->position_x, frame->position_y,
    CURRENT_FOREGROUND, PROGRAM_THEME_BACKGROUND_LV1
  );
}

void IDUPRenderInvoiceDetailFrame(
  EditInt edit_amount,
  EditDouble edit_price,
  EditDouble edit_vat,
  Button save_button,
  Button delete_button,
  Button close_button
) {
  RenderEditInt(edit_amount);
  RenderEditDouble(edit_price);
  RenderEditDouble(edit_vat);
  RenderButton(save_button);
  RenderButton(delete_button);
  RenderButton(close_button);
}

void ActiveInvoiceDetailUpdatedFrame(
  Frame frame,
  InvoiceDetailList invoice_detail_list,
  char invoice_type,
  InvoiceDetail _invoice_detail
) {
  // Default
  frame->active_element = 2;

  // Variables
  InvoiceDetail invoice_detail = DuplicateInvoiceDetail(_invoice_detail);

  // Init templates
  EditInt edit_amount = NewEditInt(
    &(invoice_detail->amount),
    INVOICE_DETAIL_AMOUNT_MAX_VALUE, 0,
    IDUP_INPUT_WIDTH, IDUP_INPUT_HEIGHT,
    frame->position_x + 12, frame->position_y + 1,
    IDUP_INPUT_FOREGOURND, IDUP_INPUT_BACKGROUND,
    IDUP_INPUT_ACTIVE_FOREGOURND, IDUP_INPUT_ACTIVE_BACKGROUND
  );

  EditDouble edit_price = NewEditDouble(
    &(invoice_detail->price), IDUP_DOUBLE_ROUND,
    INVOICE_DETAIL_PRICE_MAX_VALUE, 0,
    IDUP_INPUT_WIDTH, IDUP_INPUT_HEIGHT,
    frame->position_x + 12, frame->position_y + 5,
    IDUP_INPUT_FOREGOURND, IDUP_INPUT_BACKGROUND,
    IDUP_INPUT_ACTIVE_FOREGOURND, IDUP_INPUT_ACTIVE_BACKGROUND
  );

  EditDouble edit_vat = NewEditDouble(
    &(invoice_detail->vat), IDUP_DOUBLE_ROUND,
    INVOICE_DETAIL_VAT_MAX_VALUE, INVOICE_DETAIL_VAT_MIN_VALUE,
    IDUP_INPUT_WIDTH, IDUP_INPUT_HEIGHT,
    frame->position_x + 12, frame->position_y + 9,
    IDUP_INPUT_FOREGOURND, IDUP_INPUT_BACKGROUND,
    IDUP_INPUT_ACTIVE_FOREGOURND, IDUP_INPUT_ACTIVE_BACKGROUND
  );

  Button save_button = NewButton(
    " Lưu", ALIGN_CENTER,
    (frame->width - 6) / 2, 3, 0,
    frame->position_x + 2, frame->position_y + 13,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND_LV1,
    PROGRAM_THEME_FOREGROUND_LV1, PROGRAM_BACKGROUND,
    STANDARD_CONSOLE
  );

  Button delete_button = NewButton(
    " Xóa", ALIGN_CENTER,
    (frame->width - 6) / 2, 3, 0,
    frame->position_x + (frame->width - 6) / 2 + 4, frame->position_y + 13,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND_LV1,
    PROGRAM_THEME_FOREGROUND_LV1, PROGRAM_BACKGROUND,
    STANDARD_CONSOLE
  );

  Button close_button = NewButton(
    " Thoát", ALIGN_CENTER,
    frame->width - 4, 3, 0,
    frame->position_x + 2, frame->position_y + 17,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND_LV1,
    PROGRAM_THEME_FOREGROUND_LV1, PROGRAM_BACKGROUND,
    STANDARD_CONSOLE
  );

  Notify notify = NewNotify(
    frame->width - 4, 3, 0,
    frame->position_x + 2, frame->position_y + 21,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_FOREGROUND_REVERSE
  );

  // Draw
  idup_form_background;
  idup_form_label("Số lượng", 0);
  idup_form_label("Giá bán", 1);
  idup_form_label("VAT", 2);

  // Render - using rapid
  idup_render_form;

  // Active
  message_tp message;
  keycode_tp keycode;
  while (frame->active_element != 0) {
    if (frame->active_element == 2) {
      // Name
      keycode = ActiveEditInt(edit_amount);
      if (keycode == ENTER) {
        frame->active_element = 3;
      }
      else if (keycode == KEY_DOWN)
        frame->active_element = 3;
      else if (keycode == KEY_LEFT)
        frame->active_element = 5;
      else if (keycode == KEY_RIGHT)
        frame->active_element = 6;
    } else if (frame->active_element == 3) {
      // Unit
      keycode = ActiveEditDouble(edit_price);
      if (keycode == ENTER) {
        frame->active_element = 4;
      }
      else if (keycode == KEY_DOWN)
        frame->active_element = 4;
      else if (keycode == KEY_UP)
        frame->active_element = 2;
      else if (keycode == KEY_LEFT)
        frame->active_element = 5;
      else if (keycode == KEY_RIGHT)
        frame->active_element = 6;
    } else if (frame->active_element == 4) {
      keycode = ActiveEditDouble(edit_vat);
      if (keycode == ENTER) {
        frame->active_element = 5;
      }
      else if (keycode == KEY_DOWN)
        frame->active_element = 5;
      else if (keycode == KEY_UP)
        frame->active_element = 3;
      else if (keycode == KEY_LEFT)
        frame->active_element = 5;
      else if (keycode == KEY_RIGHT)
        frame->active_element = 6;
    } else if (frame->active_element == 5) {
      // Save
      keycode = ActiveButton(save_button);
      if (keycode == ENTER) {
        message = InvoiceDetailValidation(invoice_detail, true, invoice_type);
        if (message == OK) {
          CopyInvoiceDetail(_invoice_detail, invoice_detail);
          RenderNotify(notify, SUCCESS_NOTIFY, "Lưu thành công");
        } else if (message == M_INVOICE_DETAIL_MATERIAL_CODE_INVALID) {
          RenderNotify(notify, ERROR_NOTIFY, "Mã vật tư không tồn tại");
          frame->active_element = 1;
        } else if (message == M_INVOICE_DETAIL_AMOUNT_INVALID) {
          RenderNotify(notify, ERROR_NOTIFY, "Số lượng không hợp lệ");
          frame->active_element = 2;
        } else if (message == M_INVOICE_DETAIL_PRICE_INVALID) {
          RenderNotify(notify, ERROR_NOTIFY, "Giá bán không hợp lệ");
          frame->active_element = 3;
        } else if (message == M_INVOICE_DETAIL_VAT_INVALID) {
          RenderNotify(notify, ERROR_NOTIFY, "VAT không hợp lệ");
          frame->active_element = 4;
        } else {
          RenderNotify(notify, ERROR_NOTIFY, "Thông tin cung cấp không hợp lệ");
        }
      }
      else if (keycode == KEY_RIGHT)
        frame->active_element = 7;
      else if (keycode == KEY_UP)
        frame->active_element = 4;
      else if (keycode == KEY_DOWN)
        frame->active_element = 6;
    } else if (frame->active_element == 6) {
      // Close
      keycode = ActiveButton(close_button);
      if (keycode == ENTER) {
        RevokeInvoiceDetail(invoice_detail);
        frame->active_element = 0;
      }
      else if (keycode == KEY_UP)
        frame->active_element = 5;
      else if (keycode == KEY_LEFT)
        frame->active_element = 5;
      else if (keycode == KEY_RIGHT)
        frame->active_element = 7;
    } else if (frame->active_element == 7) {
      // Delete
      keycode = ActiveButton(delete_button);
      if (keycode == ENTER) {
        message = DeleteItemInInvoiceDetailList(invoice_detail_list, _invoice_detail);
        if (message == OK) {
          frame->active_element = 0;
        } else if (message == M_NOT_FOUND) {
          RenderNotify(notify, ERROR_NOTIFY, "Không tìm thấy");
        }
      }
      else if (keycode == KEY_UP)
        frame->active_element = 4;
      else if (keycode == KEY_LEFT)
        frame->active_element = 5;
      else if (keycode == KEY_DOWN)
        frame->active_element = 6;
    }
  }

  // Release
  DestroyEditInt(edit_amount);
  DestroyEditDouble(edit_price);
  DestroyEditDouble(edit_vat);
  DestroyButton(save_button);
  DestroyButton(delete_button);
  DestroyButton(close_button);
  DestroyNotify(notify);

  IDUPRecovery(frame);
}

#ifdef __cplusplus
}
#endif

#endif
