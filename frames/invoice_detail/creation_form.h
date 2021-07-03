#ifndef __FRAMES_INVOICE_DETAIL_CREATION_FORM__
#define __FRAMES_INVOICE_DETAIL_CREATION_FORM__

#define IDCP_INPUT_WIDTH 36
#define IDCP_INPUT_HEIGHT 3

#define IDCP_INPUT_FOREGOURND EDIT_STR_FOREGROUND
#define IDCP_INPUT_BACKGROUND EDIT_STR_BACKGROUND
#define IDCP_INPUT_ACTIVE_FOREGOURND EDIT_STR_ACTIVE_FOREGROUND
#define IDCP_INPUT_ACTIVE_BACKGROUND EDIT_STR_ACTIVE_BACKGROUND

#define IDCP_FLOAT_ROUND 2

// rapid - idcp
#define idcp_form_background\
        DrawRecShape(\
          frame->width, frame->height, ' ', frame->position_x, frame->position_y,\
          CURRENT_FOREGROUND, PROGRAM_THEME_BACKGROUND\
        );

#define idcp_form_label(text, y)\
        WriteStr(text, frame->position_x + 2, frame->position_y + 2 + 4 * y)

#define idcp_render_form\
        IDCPRenderInvoiceDetailFrame(\
          edit_material_code,\
          edit_amount,\
          edit_price,\
          edit_vat,\
          save_button,\
          close_button\
        )

#ifdef __cplusplus
extern "C" {
#endif

void IDCPRecovery(Frame frame) {
  DrawRecShape(
    frame->width, frame->height, ' ', frame->position_x, frame->position_y,
    CURRENT_FOREGROUND, PROGRAM_THEME_BACKGROUND_LV1
  );
}

void IDCPRenderInvoiceDetailFrame(
  EditStr edit_material_code,
  EditInt edit_amount,
  EditFloat edit_price,
  EditFloat edit_vat,
  Button save_button,
  Button close_button
) {
  RenderEditStr(edit_material_code);
  RenderEditInt(edit_amount);
  RenderEditFloat(edit_price);
  RenderEditFloat(edit_vat);
  RenderButton(save_button);
  RenderButton(close_button);
}

void ActiveInvoiceDetailCreationFrame(Frame frame, InvoiceDetailList invoice_detail_list, char invoice_type) {
  // Varialbes
  InvoiceDetail invoice_detail = NewInvoiceDetail();

  // Init templates
  EditStr edit_material_code = NewEditStr(
    invoice_detail->material_code,
    MATERIAL_CODE_MAX_LEN, 1,
    IDCP_INPUT_WIDTH, IDCP_INPUT_HEIGHT,
    frame->position_x + 12, frame->position_y + 1,
    IDCP_INPUT_FOREGOURND, IDCP_INPUT_BACKGROUND,
    IDCP_INPUT_ACTIVE_FOREGOURND, IDCP_INPUT_ACTIVE_BACKGROUND,
    CODE_FORMAT_CHAR_SET
  );

  EditInt edit_amount = NewEditInt(
    &(invoice_detail->amount),
    INVOICE_DETAIL_AMOUNT_MAX_VALUE, 0,
    IDCP_INPUT_WIDTH, IDCP_INPUT_HEIGHT,
    frame->position_x + 12, frame->position_y + 5,
    IDCP_INPUT_FOREGOURND, IDCP_INPUT_BACKGROUND,
    IDCP_INPUT_ACTIVE_FOREGOURND, IDCP_INPUT_ACTIVE_BACKGROUND
  );

  EditFloat edit_price = NewEditFloat(
    &(invoice_detail->price), IDCP_FLOAT_ROUND,
    INVOICE_DETAIL_PRICE_MAX_VALUE, 0,
    IDCP_INPUT_WIDTH, IDCP_INPUT_HEIGHT,
    frame->position_x + 12, frame->position_y + 9,
    IDCP_INPUT_FOREGOURND, IDCP_INPUT_BACKGROUND,
    IDCP_INPUT_ACTIVE_FOREGOURND, IDCP_INPUT_ACTIVE_BACKGROUND
  );

  EditFloat edit_vat = NewEditFloat(
    &(invoice_detail->vat), IDCP_FLOAT_ROUND,
    INVOICE_DETAIL_VAT_MAX_VALUE, INVOICE_DETAIL_VAT_MIN_VALUE,
    IDCP_INPUT_WIDTH, IDCP_INPUT_HEIGHT,
    frame->position_x + 12, frame->position_y + 13,
    IDCP_INPUT_FOREGOURND, IDCP_INPUT_BACKGROUND,
    IDCP_INPUT_ACTIVE_FOREGOURND, IDCP_INPUT_ACTIVE_BACKGROUND
  );

  Button save_button = NewButton(
    " Lưu", ALIGN_CENTER,
    (frame->width - 6) / 2, 3, 0,
    frame->position_x + 2, frame->position_y + 17,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND_LV1,
    PROGRAM_THEME_FOREGROUND_LV1, PROGRAM_BACKGROUND,
    STANDARD_CONSOLE
  );

  Button close_button = NewButton(
    " Thoát", ALIGN_CENTER,
    (frame->width - 6) / 2, 3, 0,
    frame->position_x + (frame->width - 6) / 2 + 4, frame->position_y + 17,
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
  idcp_form_background;
  idcp_form_label("Mã vật tư", 0);
  idcp_form_label("Số lượng", 1);
  idcp_form_label("Giá bán", 2);
  idcp_form_label("VAT", 3);

  // Render - using rapid
  idcp_render_form;

  // Active
  message_tp message;
  keycode_tp keycode;
  while (frame->active_element != 0) {
    if (frame->active_element == 1) {
      // Code
      keycode = ActiveEditStr(edit_material_code);
      if (keycode == ENTER) {
        if (IsBlankString(edit_material_code->str))
          RenderNotify(notify, WARNING_NOTIFY, "Mã không được để trắng");
        else frame->active_element = 2;
      }
      else if (keycode == KEY_DOWN)
        frame->active_element = 2;
      else if (keycode == KEY_LEFT)
        frame->active_element = 5;
      else if (keycode == KEY_RIGHT)
        frame->active_element = 6;
    } else if (frame->active_element == 2) {
      // Name
      keycode = ActiveEditInt(edit_amount);
      if (keycode == ENTER) {
        frame->active_element = 3;
      }
      else if (keycode == KEY_DOWN)
        frame->active_element = 3;
      else if (keycode == KEY_UP)
        frame->active_element = 1;
      else if (keycode == KEY_LEFT)
        frame->active_element = 5;
      else if (keycode == KEY_RIGHT)
        frame->active_element = 6;
    } else if (frame->active_element == 3) {
      // Unit
      keycode = ActiveEditFloat(edit_price);
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
      keycode = ActiveEditFloat(edit_vat);
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
          message = AddItemToInvoiceDetailList(invoice_detail_list, invoice_detail);
          if (message == OK) {
            RenderNotify(notify, SUCCESS_NOTIFY, "Lưu thành công");
            invoice_detail = NewInvoiceDetail();
            edit_material_code->str = invoice_detail->material_code;
            edit_amount->num = &(invoice_detail->amount);
            edit_price->num = &(invoice_detail->price);
            edit_vat->num = &(invoice_detail->vat);
            idcp_render_form;
          } else if (message == M_CONFLICT) {
            RenderNotify(notify, ERROR_NOTIFY, "Vật tư đã tồn tại");
            frame->active_element = 1;
          } else if (message == M_LIST_IS_FULL) {
            RenderNotify(notify, ERROR_NOTIFY, "Chỉ tối đa hai mươi vật tư");
          } else {
            RenderNotify(notify, ERROR_NOTIFY, "Thông tin cung cấp không hợp lệ");
          }
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
        frame->active_element = 6;
      else if (keycode == KEY_UP)
        frame->active_element = 4;
    } else if (frame->active_element == 6) {
      // Close
      keycode = ActiveButton(close_button);
      if (keycode == ENTER) {
        DestroyInvoiceDetail(invoice_detail);
        frame->active_element = 0;
      }
      else if (keycode == KEY_UP)
        frame->active_element = 4;
      else if (keycode == KEY_LEFT)
        frame->active_element = 5;
    }
  }

  // Release
  DestroyEditStr(edit_material_code);
  DestroyEditInt(edit_amount);
  DestroyEditFloat(edit_price);
  DestroyEditFloat(edit_vat);
  DestroyButton(save_button);
  DestroyButton(close_button);
  DestroyNotify(notify);

  IDCPRecovery(frame);
}

#ifdef __cplusplus
}
#endif

#endif
