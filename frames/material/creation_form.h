#ifndef __FRAMES_MATERIAL_CREATION_FORM__
#define __FRAMES_MATERIAL_CREATION_FORM__

#ifdef __cplusplus
extern "C" {
#endif

void MCPRecovery(Frame frame) {
  DrawRecShape(
    50, 17, ' ', frame->position_x, frame->position_y,
    CURRENT_FOREGROUND, PROGRAM_THEME_BACKGROUND_LV1
  );
}

void ActiveMaterialCreationFrame(Frame frame) {
  DrawRecShape(
    frame->width, frame->height, ' ', frame->position_x, frame->position_y,
    CURRENT_FOREGROUND, PROGRAM_THEME_BACKGROUND
  );

  WriteStr("Mã", frame->position_x + 2, frame->position_y + 2);
  WriteStr("Tên", frame->position_x + 2, frame->position_y + 6);
  WriteStr("ĐVT", frame->position_x + 2, frame->position_y + 10);
  WriteStr("Số lượng", frame->position_x + 2, frame->position_y + 14);

  // Input
  Material material = NewMaterial();

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

  RenderEditStr(edit_code);
  RenderEditStr(edit_name);
  RenderEditStr(edit_unit);

  keycode_tp keycode;
  while (frame->active_element != 0) {
    if (frame->active_element == 1) {
      keycode = ActiveEditStr(edit_code);
      if (keycode == ENTER || keycode == KEY_DOWN)
        frame->active_element = 2;
      else if (keycode == KEY_UP)
        frame->active_element = 0;
    } else if (frame->active_element == 2) {
      keycode = ActiveEditStr(edit_name);
      if (keycode == ENTER || keycode == KEY_DOWN)
        frame->active_element = 3;
      else if (keycode == KEY_UP)
        frame->active_element = 1;
    } else if (frame->active_element == 3) {
      keycode = ActiveEditStr(edit_unit);
      if (keycode == ENTER || keycode == KEY_DOWN)
        frame->active_element = 1;
      else if (keycode == KEY_UP)
        frame->active_element = 2;
    }
  }

  SaveMaterialToArchive(material);

  // Release
  DestroyEditStr(edit_code);
  DestroyEditStr(edit_name);
  DestroyEditStr(edit_unit);

  MCPRecovery(frame);
}

#ifdef __cplusplus
}
#endif

#endif
