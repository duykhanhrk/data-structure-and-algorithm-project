#ifndef __FRAMES_INVOICE_CREATION_FORM__
#define __FRAMES_INVOICE_CREATION_FORM__

#include "staff_selection_list.h"

#define ICP_INPUT_WIDTH 36
#define ICP_INPUT_HEIGHT 3

#ifdef __cplusplus
extern "C" {
#endif

void ICPRecovery(Frame frame) {
  DrawRecShape(
    frame->width, frame->height, ' ', frame->position_x, frame->position_y,
    CURRENT_FOREGROUND, PROGRAM_THEME_BACKGROUND_LV1
  );
}

void ICPRender(
  Frame frame,
  Invoice invoice,
  Staff staff,
  EditStr edit_number,
  EditDateTime edit_created_at,
  Button type_button,
  Button staff_button,
  Button ivd_list_button,
  Button save_button,
  Button close_button
) {
  // Init form
  DrawRecShape(
    frame->width, frame->height, ' ', frame->position_x, frame->position_y,
    CURRENT_FOREGROUND, PROGRAM_THEME_BACKGROUND
  );

  WriteStr("Số", frame->position_x + 2, frame->position_y + 2);
  WriteStr("Ngày lập", frame->position_x + 2, frame->position_y + 6);
  WriteStr("Loại", frame->position_x + 2, frame->position_y + 10);
  WriteStr("Người lập", frame->position_x + 2, frame->position_y + 14);

  if (staff != NULL) SetButtonText(staff_button, staff->first_name);
  else SetButtonText(staff_button, "Chọn người lập");

  if (invoice->type == IMPORT_INVOICE) {
    SetButtonText(type_button, "Nhập");
  } else if (invoice->type == EXPORT_INVOICE) {
    SetButtonText(type_button, "Xuất");
  }

  RenderEditStr(edit_number);
  RenderEditDateTime(edit_created_at);
  RenderButton(type_button);
  RenderButton(staff_button);
  RenderButton(ivd_list_button);
  RenderButton(save_button);
  RenderButton(close_button);
}

void ActiveInvoiceCreationFrame(Frame frame) {
  // Init invoice and staff
  Invoice invoice = NewInvoice();
  Staff staff = NULL;

  // Init templates
  EditStr edit_number = NewEditStr(
    invoice->number,
    INVOICE_NUMBER_MAX_LEN, 1,
    ICP_INPUT_WIDTH, ICP_INPUT_HEIGHT,
    frame->position_x + 12, frame->position_y + 1,
    EDIT_STR_FOREGROUND, EDIT_STR_BACKGROUND,
    EDIT_STR_ACTIVE_FOREGROUND, EDIT_STR_ACTIVE_BACKGROUND,
    CODE_FORMAT_CHAR_SET
  );

  EditDateTime edit_created_at = NewEditDateTime(
    &(invoice->created_at),
    TimeNow(), 1388534400,
    ICP_INPUT_WIDTH, ICP_INPUT_HEIGHT,
    frame->position_x + 12, frame->position_y + 5,
    EDIT_STR_FOREGROUND, EDIT_STR_BACKGROUND,
    EDIT_STR_ACTIVE_FOREGROUND, EDIT_STR_ACTIVE_BACKGROUND
  );

  Button type_button = NewButton(
    "Nhập", ALIGN_LEFT,
    ICP_INPUT_WIDTH, ICP_INPUT_HEIGHT, 0,
    frame->position_x + 12, frame->position_y + 9,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND_LV1,
    PROGRAM_THEME_FOREGROUND_LV1, PROGRAM_BACKGROUND,
    STANDARD_CONSOLE
  );

  Button staff_button = NewButton(
    "Fuuka Kikuchi", ALIGN_LEFT,
    ICP_INPUT_WIDTH, ICP_INPUT_HEIGHT, 0,
    frame->position_x + 12, frame->position_y + 13,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND_LV1,
    PROGRAM_THEME_FOREGROUND_LV1, PROGRAM_BACKGROUND,
    STANDARD_CONSOLE
  );

  Button ivd_list_button = NewButton(
    "Chỉnh sửa chi tiết hóa đơn", ALIGN_LEFT,
    frame->width - 4, ICP_INPUT_HEIGHT, 0,
    frame->position_x + 2, frame->position_y + 17,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND_LV1,
    PROGRAM_THEME_FOREGROUND_LV1, PROGRAM_BACKGROUND,
    STANDARD_CONSOLE
  );

  Button save_button = NewButton(
    " Lưu", ALIGN_CENTER,
    (frame->width - 6) / 2, 3, 0,
    frame->position_x + 2, frame->position_y + 21,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND_LV1,
    PROGRAM_THEME_FOREGROUND_LV1, PROGRAM_BACKGROUND,
    STANDARD_CONSOLE
  );

  Button close_button = NewButton(
    " Thoát", ALIGN_CENTER,
    (frame->width - 6) / 2, 3, 0,
    frame->position_x + (frame->width - 6) / 2 + 4, frame->position_y + 21,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND_LV1,
    PROGRAM_THEME_FOREGROUND_LV1, PROGRAM_BACKGROUND,
    STANDARD_CONSOLE
  );

  Notify notify = NewNotify(
    frame->width - 4, 3, 0,
    frame->position_x + 2, frame->position_y + 25,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_FOREGROUND_REVERSE
  );

  Frame support_frame = NewFrame(
    WINDOW_COLUMNS - 20, WINDOW_ROWS,
    20, frame->position_y
  );

  ICPRender(
    frame,
    invoice,
    staff,
    edit_number,
    edit_created_at,
    type_button,
    staff_button,
    ivd_list_button,
    save_button,
    close_button
  );

  // Active
  message_tp message;
  keycode_tp keycode;
  while (frame->active_element != 0) {
    if (frame->active_element == 1) {
      // Code
      keycode = ActiveEditStr(edit_number);
      if (keycode == ENTER) {
        if (IsBlankString(edit_number->str))
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
      keycode = ActiveEditDateTime(edit_created_at);
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
      // Type
      keycode = ActiveButton(type_button);
      if (keycode == ENTER) {
        if (invoice->type == IMPORT_INVOICE) {
          invoice->type = EXPORT_INVOICE;
          SetButtonText(type_button, "Xuất");
        } else if (invoice->type == EXPORT_INVOICE) {
          invoice->type = IMPORT_INVOICE;
          SetButtonText(type_button, "Nhập");
        }
      } else if (keycode == KEY_DOWN)
        frame->active_element = 4;
      else if (keycode == KEY_UP)
        frame->active_element = 2;
      else if (keycode == KEY_LEFT)
        frame->active_element = 6;
      else if (keycode == KEY_RIGHT)
        frame->active_element = 7;
    } else if (frame->active_element == 4) {
      // Staff
      // TODO: re-render (important!)
      keycode = ActiveButton(staff_button);
      if (keycode == ENTER) {
        ICPRecovery(frame);
        support_frame->active_element = 1;
        staff = ActiveStaffSelectionListFrame(support_frame);
        ICPRender(
          frame,
          invoice,
          staff,
          edit_number,
          edit_created_at,
          type_button,
          staff_button,
          ivd_list_button,
          save_button,
          close_button
        );
      } else if (keycode == KEY_DOWN)
        frame->active_element = 5;
      else if (keycode == KEY_UP)
        frame->active_element = 3;
      else if (keycode == KEY_LEFT)
        frame->active_element = 6;
      else if (keycode == KEY_RIGHT)
        frame->active_element = 7;
    } else if (frame->active_element == 5) {
      // Invoice detail list
      keycode = ActiveButton(ivd_list_button);
      if (keycode == ENTER) {
        ICPRecovery(frame);
        support_frame->active_element = 1;
        ActiveInvoiceDetailFrame(support_frame, invoice->invoice_detail_list);
        ICPRender(
          frame,
          invoice,
          staff,
          edit_number,
          edit_created_at,
          type_button,
          staff_button,
          ivd_list_button,
          save_button,
          close_button
        );
      } else if (keycode == KEY_DOWN)
        frame->active_element = 6;
      else if (keycode == KEY_UP)
        frame->active_element = 4;
      else if (keycode == KEY_LEFT)
        frame->active_element = 6;
      else if (keycode == KEY_RIGHT)
        frame->active_element = 7;
    } else if (frame->active_element == 6) {
      // Save
      keycode = ActiveButton(save_button);
      if (keycode == ENTER) {
//         message = SaveInvoiceToArchive(invoice);
//         if (message == OK) {
//           RenderNotify(notify, SUCCESS_NOTIFY, "Lưu thành công");
//           invoice = NewInvoice();
//           edit_code->str = invoice->code;
//           edit_last_name->str = invoice->last_name;
//           edit_first_name->str = invoice->first_name;
//           SetButtonText(sex_button, "Nữ");
//           RenderEditStr(edit_code);
//           RenderEditStr(edit_last_name);
//           RenderEditStr(edit_first_name);
//           RenderButton(sex_button);
//         } else {
//           if (message == M_CONFLICT) {
//             RenderNotify(notify, ERROR_NOTIFY, "Mã đã được sử dụng");
//             frame->active_element = 1;
//           }
//           else if (message == M_INVOICE_CODE_INVALID) {
//             RenderNotify(notify, ERROR_NOTIFY, "Mã không được để trắng");
//             frame->active_element = 1;
//           }
//           else if (message == M_INVOICE_LAST_NAME_INVALID) {
//             RenderNotify(notify, ERROR_NOTIFY, "Tên không được để trắng");
//             frame->active_element = 2;
//           }
//           else if (message == M_INVOICE_FIRST_NAME_INVALID) {
//             RenderNotify(notify, ERROR_NOTIFY, "ĐVT không được để trắng");
//             frame->active_element = 3;
//           }
//           else {
//             RenderNotify(notify, ERROR_NOTIFY, "Thông tin cung cấp không hợp lệ");
//           }
//         }
      }
      else if (keycode == KEY_RIGHT)
        frame->active_element = 7;
      else if (keycode == KEY_UP)
        frame->active_element = 5;
    } else if (frame->active_element == 7) {
      // Close
      keycode = ActiveButton(close_button);
      if (keycode == ENTER) {
//         DestroyInvoice(invoice);
        frame->active_element = 0;
      }
      else if (keycode == KEY_UP)
        frame->active_element = 5;
      else if (keycode == KEY_LEFT)
        frame->active_element = 6;
    }
  }

  // Release
  DestroyEditStr(edit_number);
  DestroyEditDateTime(edit_created_at);
  DestroyButton(type_button);
  DestroyButton(staff_button);
  DestroyButton(ivd_list_button);
  DestroyButton(save_button);
  DestroyButton(close_button);
  DestroyNotify(notify);
  DestroyFrame(support_frame);

  ICPRecovery(frame);
}

#ifdef __cplusplus
}
#endif

#endif
