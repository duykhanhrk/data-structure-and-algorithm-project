/* Program */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* Debug */
#include <iostream>
#define show(x) std::cout << x << std::endl;

/* Makers */
#include "support/supporter.h"
#include "structure/structure.h"
#include "archivist/archivist.h"

extern Archive archive;

int main() {
  InitArchive();

//   Material material;

//   material = NewMaterial("code", "name", "unit", 20);
//   if (SaveMaterialToArchive(material) != OK) show("Khong luu duoc");

//   material = NewMaterial("code 1", "name 1", "unit", 40);
//   if (SaveMaterialToArchive(material) != OK) show("Khong luu duoc");

//   material = NewMaterial("code 2", "name 2", "unit", 60);
//   if (SaveMaterialToArchive(material) != OK) show("Khong luu duoc");

//   material = NewMaterial("code 3", "name 3", "unit", 80);
//   if (SaveMaterialToArchive(material) != OK) show("Khong luu duoc");

//   material = NewMaterial("code 4", "name 4", "unit", 100);
//   if (SaveMaterialToArchive(material) != OK) show("Khong luu duoc");

//   ShowMaterialListInArchive();
//   SaveMaterialsFromArchiveToStorage();

  LoadMaterialsFromStorageToArchive();
  ShowMaterialListInArchive();

  DestroyArchive();
  getchar();
  return 0;
}
