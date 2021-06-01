/* Program */

#include <stdlib.h>
#include <stdio.h>

// Debug
#include <iostream>
#define show(x) std::cout << x << std::endl;

#include "archivist/archivist.h"

extern Archive archive;

int main() {
  InitArchive();

  Material material;

  material = NewMaterial("abc", "abc", "abc", 9);
  if (SaveMaterialToArchive(material) != OK) show("Khong luu duoc!");

  material = NewMaterial("def", "abc", "abc", 9);
  if (SaveMaterialToArchive(material) != OK) show("Khong luu duoc!");

  material = NewMaterial("ghi", "abc", "abc", 9);
  if (SaveMaterialToArchive(material) != OK) show("Khong luu duoc!");

  material = NewMaterial("jkm", "abc", "abc", 9);
  if (SaveMaterialToArchive(material) != OK) show("Khong luu duoc!");

  ShowMaterialListInArchive();
  show("---------------------------------------------------------------------");

  Material _material = DuplicateMaterial(material);
  _material->quantity = 10;

  if (UpdateMaterialInArchive(material, _material) != OK) show(":(");

  ShowMaterialListInArchive();

  DestroyArchive();

  system("PAUSE");
  return 0;
}
