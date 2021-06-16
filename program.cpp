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

int main() {
  // Hiden cursor
  CursorVisible(false);

  // Unicode
  system("chcp 65001");

  // Main Frame
  Frame main_frame = NewFrame(WINDOW_COLUMNS, WINDOW_ROWS, 0, 0, 1);
  ActiveMainFrame(main_frame);

  // Release
  DestroyFrame(main_frame);

  return 0;
}
