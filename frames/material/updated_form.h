#ifndef __FRAMES_MATERIAL_UPDATED_FORM__
#define __FRAMES_MATERIAL_UPDATED_FORM__

#ifdef __cplusplus
extern "C" {
#endif

void MUPRecovery(Frame frame) {
  DrawRecShape(
    frame->width, frame->height, ' ', frame->position_x, frame->position_y,
    CURRENT_FOREGROUND, PROGRAM_THEME_BACKGROUND_LV1
  );
}

void ActiveMaterialUpdatedFrame(Frame frame, Material _material) {
  // Init form
  DrawRecShape(
    frame->width, frame->height, ' ', frame->position_x, frame->position_y,
    CURRENT_FOREGROUND, PROGRAM_THEME_BACKGROUND
  );

  WriteStr("Tên", frame->position_x + 2, frame->position_y + 2);
  WriteStr("ĐVT", frame->position_x + 2, frame->position_y + 6);
  WriteStr("Số lượng", frame->position_x + 2, frame->position_y + 10);

  Material material = DuplicateMaterial(_material);

  EditStr edit_name = NewEditStr(
    material->name,
    32, 1,
    36, 3,
    frame->position_x + 12, frame->position_y + 1,
    EDIT_STR_FOREGROUND, EDIT_STR_BACKGROUND,
    EDIT_STR_ACTIVE_FOREGROUND, EDIT_STR_ACTIVE_BACKGROUND,
    STANDARD_CHAR_SET
  );

  EditStr edit_unit = NewEditStr(
    material->unit,
    10, 1,
    36, 3,
    frame->position_x + 12, frame->position_y + 5,
    EDIT_STR_FOREGROUND, EDIT_STR_BACKGROUND,
    EDIT_STR_ACTIVE_FOREGROUND, EDIT_STR_ACTIVE_BACKGROUND,
    STANDARD_CHAR_SET
  );

  EditInt edit_quantity = NewEditInt(
    &(material->quantity),
    MATERIAL_QUANTITY_MAX_VALUE, 0,
    36, 3,
    frame->position_x + 12, frame->position_y + 9,
    EDIT_INT_FOREGROUND, EDIT_INT_BACKGROUND,
    EDIT_INT_ACTIVE_FOREGROUND, EDIT_INT_ACTIVE_BACKGROUND
  );

  Button save_button = NewButton(
    " Lưu",
    (frame->width - 6) / 2, 3, 0,
    frame->position_x + 2, frame->position_y + 13,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND_LV1,
    PROGRAM_THEME_FOREGROUND_LV1, PROGRAM_BACKGROUND,
    STANDARD_CONSOLE
  );

  Button delete_button = NewButton(
    " Xóa",
    (frame->width - 6) / 2, 3, 0,
    frame->position_x + (frame->width - 6) / 2 + 4, frame->position_y + 13,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND_LV1,
    PROGRAM_THEME_FOREGROUND_LV1, PROGRAM_BACKGROUND,
    STANDARD_CONSOLE
  );

  Button close_button = NewButton(
    " Thoát",
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

  // Render

  RenderEditStr(edit_name);
  RenderEditStr(edit_unit);
  RenderEditInt(edit_quantity);
  RenderButton(save_button);
  RenderButton(delete_button);
  RenderButton(close_button);

  // Active
  message_tp message;
  keycode_tp keycode;
  while (frame->active_element != 0) {
    if (frame->active_element == 2) {
      // Name
      keycode = ActiveEditStr(edit_name);
      if (keycode == ENTER) {
        if (IsBlankString(edit_name->str))
          RenderNotify(notify, WARNING_NOTIFY, "Tên không được để trắng");
        else frame->active_element = 3;
      }
      else if (keycode == KEY_DOWN)
        frame->active_element = 3;
      else if (keycode == KEY_LEFT)
        frame->active_element = 5;
      else if (keycode == KEY_RIGHT)
        frame->active_element = 6;
    } else if (frame->active_element == 3) {
      // Unit
      keycode = ActiveEditStr(edit_unit);
      if (keycode == ENTER) {
        if (IsBlankString(edit_unit->str))
          RenderNotify(notify, WARNING_NOTIFY, "ĐVT không được để trắng");
        else frame->active_element = 4;
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
      // Quantity
      keycode = ActiveEditInt(edit_quantity);
      if (keycode == ENTER || keycode == KEY_DOWN)
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
        message = UpdateMaterialInArchive(_material->code, material);
        if (message == OK) {
          RenderNotify(notify, SUCCESS_NOTIFY, "Lưu thành công");
        } else {
          if (message == M_CONFLICT) {
            RenderNotify(notify, ERROR_NOTIFY, "Mã đã được sử dụng");
            frame->active_element = 1;
          }
          else if (message == M_MATERIAL_CODE_INVALID) {
            RenderNotify(notify, ERROR_NOTIFY, "Mã không được để trắng");
            frame->active_element = 1;
          }
          else if (message == M_MATERIAL_NAME_INVALID) {
            RenderNotify(notify, ERROR_NOTIFY, "Tên không được để trắng");
            frame->active_element = 2;
          }
          else if (message == M_MATERIAL_UNIT_INVALID) {
            RenderNotify(notify, ERROR_NOTIFY, "ĐVT không được để trắng");
            frame->active_element = 3;
          }
          else {
            RenderNotify(notify, ERROR_NOTIFY, "Thông tin cung cấp không hợp lệ");
          }
        }
      }
      else if (keycode == KEY_RIGHT)
        frame->active_element = 6;
      else if (keycode == KEY_UP)
        frame->active_element = 4;
      else if (keycode == KEY_DOWN)
        frame->active_element = 7;
    } else if (frame->active_element == 6) {
      // Delete
      keycode = ActiveButton(delete_button);
      if (keycode == ENTER) {
        message = DeleteMaterialInArchive(_material->code);
        if (message != OK)
          RenderNotify(notify, ERROR_NOTIFY, "Lỗi không xác định");
        else frame->active_element = 0;
      }
      else if (keycode == KEY_UP)
        frame->active_element = 4;
      else if (keycode == KEY_LEFT)
        frame->active_element = 5;
      else if (keycode == KEY_DOWN)
        frame->active_element = 7;
    } else if (frame->active_element == 7) {
      // Close
      keycode = ActiveButton(close_button);
      if (keycode == ENTER) {
        DestroyMaterial(material);
        frame->active_element = 0;
      }
      else if (keycode == KEY_UP)
        frame->active_element = 5;
      else if (keycode == KEY_LEFT)
        frame->active_element = 5;
      else if (keycode == KEY_RIGHT)
        frame->active_element = 6;
    }
  }

  // Release
  DestroyEditStr(edit_name);
  DestroyEditStr(edit_unit);
  DestroyEditInt(edit_quantity);
  DestroyButton(save_button);
  DestroyButton(delete_button);
  DestroyButton(close_button);
  DestroyNotify(notify);

  MUPRecovery(frame);
}

#ifdef __cplusplus
}
#endif

#endif
