/* Program */

/* Debug */
#include <iostream>
#define show(x) std::cout << x << std::endl;

/* Makers */
#include "supporter/supporter.h"
#include "structure/structure.h"
#include "archivist/archivist.h"
#include "templates/templates.h"
#include "frames/frames.h"

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

void SeedStaff() {
  Staff staff;
  char code[10] = " \0";
  char first_name[32] = "  first name\0";
  char last_name[64] = "  last name\0";
  char sex = FEMALE_STAFF;

  for (char chr = 'A'; chr <= 'Z'; chr ++) {
    code[0] = chr;
    first_name[0] = chr;
    last_name[0] = chr;

    staff = NewStaff(code, first_name, last_name, sex);
    SaveStaffToArchive(staff);
  }
}

int main() {
  // Config console
  CursorVisible(false);
  SetConsoleOutputCP(65001);
  SetConsoleTitle("Quan li vat tu");
  SetWindowSize(120, 30);
  SetScreenBufferSize(120, 30);
  DisableResizeWindow();
  DisableCtrButton(true, true, true);
  DisableSelection();

  // Init Archive
  InitArchive();

  // Load data from storage
  LoadMaterialListFromStorageToArchive();
  LoadStaffListFromStorageToArchive();

  // Init main frame
  Frame main_frame = NewFrame(WINDOW_COLUMNS, WINDOW_ROWS);

  // Acrive main frame
  ActiveMainFrame(main_frame);

  // Release memmory
  DestroyFrame(main_frame);
  DestroyArchive();

  // Exit
  return 0;
}
