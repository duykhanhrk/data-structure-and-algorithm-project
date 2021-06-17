/* Program */

/* Debug */
#include <iostream>
#define show(x) std::cout << x << std::endl;

/* Makers */
#include "support/supporter.h"
#include "structure/structure.h"
#include "archivist/archivist.h"
#include "template/template.h"
#include "handler/handler.h"

void SeedMaterial() {
  Material material;
  char code[10] = " \0";
  char name[64] = "  name\0";
  char unit[10] = "  unit\0";

  for (char chr = 'A'; chr <= 'Z'; chr ++) {
    code[0] = chr;
    name[0] = chr;
    unit[0] = chr;

    material = NewMaterial(code, name, unit, ((int) chr) - 64);
    SaveMaterialToArchive(material);
  }
}

int main() {
  CursorVisible(false);
  SetConsoleOutputCP(65001);
  SetConsoleTitle("Quản lí vật tư");
  SetWindowSize(120, 30);
  SetScreenBufferSize(120, 30);
  DisableResizeWindow();
  DisableCtrButton(true, true, true);
  DisableSelection();
  ShowScrollbar(false);


  // Init Archive
  InitArchive();
  LoadMaterialListFromStorageToArchive();
  LoadStaffListFromStorageToArchive();

  // Main Frame
  Frame main_frame = NewFrame(WINDOW_COLUMNS, WINDOW_ROWS, 0, 0, 1);
  ActiveMainFrame(main_frame);

  // Release
  DestroyFrame(main_frame);
  DestroyArchive();
  return 0;
}
