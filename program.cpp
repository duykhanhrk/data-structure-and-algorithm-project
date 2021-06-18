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
