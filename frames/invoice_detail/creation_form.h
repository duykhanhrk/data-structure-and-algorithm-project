#ifndef __FRAMES_INVOICE_DETAIL_CREATION_FORM__
#define __FRAMES_INVOICE_DETAIL_CREATION_FORM__

#define IDCP_INPUT_WIDTH 36
#define IDCP_INPUT_HEIGHT 3

#ifdef __cplusplus
extern "C" {
#endif

void IDCPRecovery(Frame frame) {
  DrawRecShape(
    frame->width, frame->height, ' ', frame->position_x, frame->position_y,
    CURRENT_FOREGROUND, PROGRAM_THEME_BACKGROUND_LV1
  );
}

void ActiveInvoiceDetailCreationFrame(Frame frame) {
  // Init form
  DrawRecShape(
    frame->width, frame->height, ' ', frame->position_x, frame->position_y,
    CURRENT_FOREGROUND, PROGRAM_THEME_BACKGROUND
  );

  WriteStr("Mã vật tư", frame->position_x + 2, frame->position_y + 2);
  WriteStr("Số lượng", frame->position_x + 2, frame->position_y + 6);
  WriteStr("Giá bán", frame->position_x + 2, frame->position_y + 10);
  WriteStr("VAT", frame->position_x + 2, frame->position_y + 14);

  // Init invoice_detail
  InvoiceDetail invoice_detail = NewInvoiceDetail();

  // Init templates
  EditStr edit_material_code = NewEditStr(
    invoice_detail->material_code,
    10, 1,
    IDCP_INPUT_WIDTH, IDCP_INPUT_HEIGHT,
    frame->position_x + 12, frame->position_y + 1,
    EDIT_STR_FOREGROUND, EDIT_STR_BACKGROUND,
    EDIT_STR_ACTIVE_FOREGROUND, EDIT_STR_ACTIVE_BACKGROUND,
    CODE_FORMAT_CHAR_SET
  );

  EditInt edit_amount = NewEditInt(
    &(invoice_detail->amount),
    100, 1,
    IDCP_INPUT_WIDTH, IDCP_INPUT_HEIGHT,
    frame->position_x + 12, frame->position_y + 5,
    EDIT_STR_FOREGROUND, EDIT_STR_BACKGROUND,
    EDIT_STR_ACTIVE_FOREGROUND, EDIT_STR_ACTIVE_BACKGROUND
  );

  EditInt edit_price = NewEditInt(
    &(invoice_detail->amount),
    99999999, 0,
    IDCP_INPUT_WIDTH, IDCP_INPUT_HEIGHT,
    frame->position_x + 12, frame->position_y + 9,
    EDIT_STR_FOREGROUND, EDIT_STR_BACKGROUND,
    EDIT_STR_ACTIVE_FOREGROUND, EDIT_STR_ACTIVE_BACKGROUND
  );

  EditInt edit_vat = NewEditInt(
    &(invoice_detail->amount),
    99999999, 0,
    IDCP_INPUT_WIDTH, IDCP_INPUT_HEIGHT,
    frame->position_x + 12, frame->position_y + 13,
    EDIT_STR_FOREGROUND, EDIT_STR_BACKGROUND,
    EDIT_STR_ACTIVE_FOREGROUND, EDIT_STR_ACTIVE_BACKGROUND
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

  // Render

  RenderEditStr(edit_material_code);
  RenderEditInt(edit_amount);
  RenderEditInt(edit_price);
  RenderEditInt(edit_vat);
  RenderButton(save_button);
  RenderButton(close_button);

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
      keycode = ActiveEditInt(edit_price);
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
      keycode = ActiveEditInt(edit_vat);
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
//       if (keycode == ENTER) {
//         message = SaveInvoiceDetailToArchive(invoice_detail);
//         if (message == OK) {
//           RenderNotify(notify, SUCCESS_NOTIFY, "Lưu thành công");
//           invoice_detail = NewInvoiceDetail();
//           edit_material_code->str = invoice_detail->code;
//           edit_amount->str = invoice_detail->last_name;
//           edit_price->str = invoice_detail->first_name;
//           SetButtonText(sex_button, "Nữ");
//           RenderEditStr(edit_material_code);
//           RenderEditStr(edit_amount);
//           RenderEditStr(edit_price);
//           RenderButton(sex_button);
//         } else {
//           if (message == M_CONFLICT) {
//             RenderNotify(notify, ERROR_NOTIFY, "Mã đã được sử dụng");
//             frame->active_element = 1;
//           }
//           else if (message == M_INVOICE_DETAIL_CODE_INVALID) {
//             RenderNotify(notify, ERROR_NOTIFY, "Mã không được để trắng");
//             frame->active_element = 1;
//           }
//           else if (message == M_INVOICE_DETAIL_LAST_NAME_INVALID) {
//             RenderNotify(notify, ERROR_NOTIFY, "Tên không được để trắng");
//             frame->active_element = 2;
//           }
//           else if (message == M_INVOICE_DETAIL_FIRST_NAME_INVALID) {
//             RenderNotify(notify, ERROR_NOTIFY, "ĐVT không được để trắng");
//             frame->active_element = 3;
//           }
//           else {
//             RenderNotify(notify, ERROR_NOTIFY, "Thông tin cung cấp không hợp lệ");
//           }
//         }
//       }
      if (keycode == KEY_RIGHT)
        frame->active_element = 6;
      else if (keycode == KEY_UP)
        frame->active_element = 4;
    } else if (frame->active_element == 6) {
      // Close
      keycode = ActiveButton(close_button);
      if (keycode == ENTER) {
//         DestroyInvoiceDetail(invoice_detail);
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
  DestroyEditInt(edit_price);
  DestroyEditInt(edit_vat);
  DestroyButton(save_button);
  DestroyButton(close_button);
  DestroyNotify(notify);

  IDCPRecovery(frame);
}

#ifdef __cplusplus
}
#endif

#endif
