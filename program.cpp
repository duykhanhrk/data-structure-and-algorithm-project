/* Program */

/* Debug */
#include <iostream>
#define show(x) std::cout << x << std::endl;

/* Makers */
#include "support/supporter.h"
#include "structure/structure.h"
#include "archivist/archivist.h"

extern Archive archive;

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

  for (char chr = 'a'; chr <= 'z'; chr ++) {
    code[0] = chr;
    first_name[0] = chr;
    last_name[0] = chr;

    staff = NewStaff(code, first_name, last_name, sex);
    SaveStaffToArchive(staff);
  }
}

int main() {
  InitArchive();
  SeedMaterial();

  Material material = NewMaterial("1256BC", "material name", "unit", 0);
  message_tp message = SaveMaterialToArchive(material);
  if (message != OK) {
    show(message);
    DestroyMaterial(material);
  }
  DestroyArchive();

  InitArchive();

  LoadMaterialListFromStorageToArchive();
  ShowMaterialListInArchive();

  DestroyArchive();
  getchar();
  return 0;
}
