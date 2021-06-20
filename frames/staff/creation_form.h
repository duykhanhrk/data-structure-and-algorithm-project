#ifndef __FRAMES_STAFF_CREATION_FORM__
#define __FRAMES_STAFF_CREATION_FORM__

#define STP_INPUT_WIDTH 36
#define STP_INPUT_HEIGHT 3

#ifdef __cplusplus
extern "C" {
#endif

void SCPRecovery(Frame frame) {
  DrawRecShape(
    frame->width, frame->height, ' ', frame->position_x, frame->position_y,
    CURRENT_FOREGROUND, PROGRAM_THEME_BACKGROUND_LV1
  );
}

void ActiveStaffCreationFrame(Frame frame) {
  // Init form
  DrawRecShape(
    frame->width, frame->height, ' ', frame->position_x, frame->position_y,
    CURRENT_FOREGROUND, PROGRAM_THEME_BACKGROUND
  );

  WriteStr("Mã", frame->position_x + 2, frame->position_y + 2);
  WriteStr("Họ", frame->position_x + 2, frame->position_y + 6);
  WriteStr("Tên", frame->position_x + 2, frame->position_y + 10);
  WriteStr("Giới tính", frame->position_x + 2, frame->position_y + 14);

  // Init staff
  Staff staff = NewStaff();

  // Init templates
  EditStr edit_code = NewEditStr(
    staff->code,
    STAFF_CODE_MAX_LEN, 1,
    STP_INPUT_WIDTH, STP_INPUT_HEIGHT,
    frame->position_x + 12, frame->position_y + 1,
    EDIT_STR_FOREGROUND, EDIT_STR_BACKGROUND,
    EDIT_STR_ACTIVE_FOREGROUND, EDIT_STR_ACTIVE_BACKGROUND,
    CODE_FORMAT_CHAR_SET
  );

  EditStr edit_last_name = NewEditStr(
    staff->last_name,
    STAFF_FIRST_NAME_MAX_LEN, 1,
    STP_INPUT_WIDTH, STP_INPUT_HEIGHT,
    frame->position_x + 12, frame->position_y + 5,
    EDIT_STR_FOREGROUND, EDIT_STR_BACKGROUND,
    EDIT_STR_ACTIVE_FOREGROUND, EDIT_STR_ACTIVE_BACKGROUND,
    HUMAN_NAME_FORMAT_CHAR_SET
  );

  EditStr edit_first_name = NewEditStr(
    staff->first_name,
    STAFF_LAST_NAME_MAX_LEN, 1,
    STP_INPUT_WIDTH, STP_INPUT_HEIGHT,
    frame->position_x + 12, frame->position_y + 9,
    EDIT_STR_FOREGROUND, EDIT_STR_BACKGROUND,
    EDIT_STR_ACTIVE_FOREGROUND, EDIT_STR_ACTIVE_BACKGROUND,
    HUMAN_NAME_FORMAT_CHAR_SET
  );

  Button sex_button = NewButton(
    "Nữ", ALIGN_LEFT,
    STP_INPUT_WIDTH, STP_INPUT_HEIGHT, 0,
    frame->position_x + 12, frame->position_y + 13,
    PROGRAM_FOREGROUND_REVERSE, PROGRAM_THEME_BACKGROUND_LV1,
    PROGRAM_THEME_FOREGROUND_LV1, PROGRAM_BACKGROUND,
    STANDARD_CONSOLE
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
  RenderEditStr(edit_last_name);
  RenderEditStr(edit_first_name);
  RenderButton(sex_button);
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
      keycode = ActiveEditStr(edit_last_name);
      if (keycode == ENTER) {
        if (IsBlankString(edit_last_name->str))
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
      keycode = ActiveEditStr(edit_first_name);
      if (keycode == ENTER) {
        if (IsBlankString(edit_first_name->str))
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
      // Sex
      keycode = ActiveButton(sex_button);
      if (keycode == ENTER) {
        if (staff->sex == FEMALE_STAFF) {
          staff->sex = MALE_STAFF;
          SetButtonText(sex_button, "Nam");
        } else if (staff->sex == MALE_STAFF) {
          staff->sex = FEMALE_STAFF;
          SetButtonText(sex_button, "Nữ");
        }
      } else if (keycode == KEY_DOWN)
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
        message = SaveStaffToArchive(staff);
        if (message == OK) {
          RenderNotify(notify, SUCCESS_NOTIFY, "Lưu thành công");
          staff = NewStaff();
          edit_code->str = staff->code;
          edit_last_name->str = staff->last_name;
          edit_first_name->str = staff->first_name;
          SetButtonText(sex_button, "Nữ");
          RenderEditStr(edit_code);
          RenderEditStr(edit_last_name);
          RenderEditStr(edit_first_name);
          RenderButton(sex_button);
        } else {
          if (message == M_CONFLICT) {
            RenderNotify(notify, ERROR_NOTIFY, "Mã đã được sử dụng");
            frame->active_element = 1;
          }
          else if (message == M_STAFF_CODE_INVALID) {
            RenderNotify(notify, ERROR_NOTIFY, "Mã không được để trắng");
            frame->active_element = 1;
          }
          else if (message == M_STAFF_LAST_NAME_INVALID) {
            RenderNotify(notify, ERROR_NOTIFY, "Tên không được để trắng");
            frame->active_element = 2;
          }
          else if (message == M_STAFF_FIRST_NAME_INVALID) {
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
        DestroyStaff(staff);
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
  DestroyEditStr(edit_last_name);
  DestroyEditStr(edit_first_name);
  DestroyButton(sex_button);
  DestroyButton(save_button);
  DestroyButton(close_button);
  DestroyNotify(notify);

  SCPRecovery(frame);
}

#ifdef __cplusplus
}
#endif

#endif
