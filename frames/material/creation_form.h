#ifndef __FRAMES_MATERIAL_CREATION_FORM__
#define __FRAMES_MATERIAL_CREATION_FORM__

#ifdef __cplusplus
extern "C" {
#endif

void MCPRecovery(Frame frame) {
  DrawRecShape(
    frame->width, frame->height, ' ', frame->position_x, frame->position_y,
    CURRENT_FOREGROUND, PROGRAM_THEME_BACKGROUND_LV1
  );
}

void ActiveMaterialCreationFrame(Frame frame) {
  // Init form
  DrawRecShape(
    frame->width, frame->height, ' ', frame->position_x, frame->position_y,
    CURRENT_FOREGROUND, PROGRAM_THEME_BACKGROUND
  );

  WriteStr("Mã", frame->position_x + 2, frame->position_y + 2);
  WriteStr("Tên", frame->position_x + 2, frame->position_y + 6);
  WriteStr("ĐVT", frame->position_x + 2, frame->position_y + 10);
  WriteStr("Số lượng", frame->position_x + 2, frame->position_y + 14);

  // Init material
  Material material = NewMaterial();

  // Init templates
  EditStr edit_code = NewEditStr(
    material->code,
    10, 1,
    36, 3,
    frame->position_x + 12, frame->position_y + 1,
    EDIT_STR_FOREGROUND, EDIT_STR_BACKGROUND,
    EDIT_STR_ACTIVE_FOREGROUND, EDIT_STR_ACTIVE_BACKGROUND,
    CODE_FORMAT_CHAR_SET
  );

  EditStr edit_name = NewEditStr(
    material->name,
    32, 1,
    36, 3,
    frame->position_x + 12, frame->position_y + 5,
    EDIT_STR_FOREGROUND, EDIT_STR_BACKGROUND,
    EDIT_STR_ACTIVE_FOREGROUND, EDIT_STR_ACTIVE_BACKGROUND,
    STANDARD_CHAR_SET
  );

  EditStr edit_unit = NewEditStr(
    material->unit,
    10, 1,
    36, 3,
    frame->position_x + 12, frame->position_y + 9,
    EDIT_STR_FOREGROUND, EDIT_STR_BACKGROUND,
    EDIT_STR_ACTIVE_FOREGROUND, EDIT_STR_ACTIVE_BACKGROUND,
    STANDARD_CHAR_SET
  );

  EditInt edit_quantity = NewEditInt(
    &(material->quantity),
    MATERIAL_QUANTITY_MAX_VALUE, 0,
    36, 3,
    frame->position_x + 12, frame->position_y + 13,
    EDIT_INT_FOREGROUND, EDIT_INT_BACKGROUND,
    EDIT_INT_ACTIVE_FOREGROUND, EDIT_INT_ACTIVE_BACKGROUND
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

  RenderEditStr(edit_code);
  RenderEditStr(edit_name);
  RenderEditStr(edit_unit);
  RenderEditInt(edit_quantity);
  RenderButton(save_button);
  RenderButton(close_button);

  // Active
  message_tp message;
  keycode_tp keycode;
  while (frame->active_element != 0) {
    if (frame->active_element == 1) {
      // Code
      keycode = ActiveEditStr(edit_code);
      if (keycode == ENTER) {
        if (IsBlankString(edit_code->str))
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
      keycode = ActiveEditStr(edit_name);
      if (keycode == ENTER) {
        if (IsBlankString(edit_name->str))
          RenderNotify(notify, WARNING_NOTIFY, "Tên không được để trắng");
        else frame->active_element = 3;
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
        message = SaveMaterialToArchive(material);
        if (message == OK) {
          RenderNotify(notify, SUCCESS_NOTIFY, "Lưu thành công");
          material = NewMaterial();
          edit_code->str = material->code;
          edit_name->str = material->name;
          edit_unit->str = material->unit;
          edit_quantity->num = &(material->quantity);
          RenderEditStr(edit_code);
          RenderEditStr(edit_name);
          RenderEditStr(edit_unit);
          RenderEditInt(edit_quantity);
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
    } else if (frame->active_element == 6) {
      // Close
      keycode = ActiveButton(close_button);
      if (keycode == ENTER) {
        DestroyMaterial(material);
        frame->active_element = 0;
      }
      else if (keycode == KEY_UP)
        frame->active_element = 4;
      else if (keycode == KEY_LEFT)
        frame->active_element = 5;
    }
  }

  // Release
  DestroyEditStr(edit_code);
  DestroyEditStr(edit_name);
  DestroyEditStr(edit_unit);
  DestroyEditInt(edit_quantity);
  DestroyButton(save_button);
  DestroyButton(close_button);
  DestroyNotify(notify);

  MCPRecovery(frame);
}

#ifdef __cplusplus
}
#endif

#endif
