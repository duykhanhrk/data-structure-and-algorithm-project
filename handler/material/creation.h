#ifndef __HANDLER_MATERIAL_ADD_FORM__
#define __HANDLER_MATERIAL_ADD_FORM__

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

  WriteStr("Mã", frame->position_x + 2, frame->position_y + 3);
  WriteStr("Tên", frame->position_x + 2, frame->position_y + 6);
  WriteStr("Đơn vị tính", frame->position_x + 2, frame->position_y + 9);
  WriteStr("Số lượng tồn", frame->position_x + 2, frame->position_y + 12);

  // Input

  WriteStr("FHDIEKGHFN", frame->position_x + 20, frame->position_y + 3, CURRENT_FOREGROUND, PROGRAM_THEME_BACKGROUND_LV1);
  WriteStr("Giấy trắng", frame->position_x + 20, frame->position_y + 6, CURRENT_FOREGROUND, PROGRAM_THEME_BACKGROUND_LV1);
  WriteStr("Tờ", frame->position_x + 20, frame->position_y + 9, CURRENT_FOREGROUND, PROGRAM_THEME_BACKGROUND_LV1);
  WriteStr("4000", frame->position_x + 20, frame->position_y + 12, CURRENT_FOREGROUND, PROGRAM_THEME_BACKGROUND_LV1);

  getch();

  MCPRecovery(frame);
}

#ifdef __cplusplus
}
#endif

#endif
