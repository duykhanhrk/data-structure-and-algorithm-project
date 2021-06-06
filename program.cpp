/* Program */

#include <stdlib.h>
#include <stdio.h>

/* Debug */
#include <iostream>
#define show(x) std::cout << x << std::endl;

#include "structure/structure.h"
#include "archivist/archivist.h"

extern Archive archive;

int main() {
  InitArchive();

  Staff staff;

  // Create new
  staff = NewStaff("code", "first_name", "last_name", STAFF_SEX_FEMALE);
  if (SaveStaffToArchive(staff) != OK) show("Khong luu duoc");

  staff = NewStaff("code 1", "first_name", "last_name", STAFF_SEX_FEMALE);
  if (SaveStaffToArchive(staff) != OK) show("Khong luu duoc");

  ShowStaffListInArchive();

  // line
  show("---------------------------------------------------------------------");

  // Update staff
  staff = GetStaffInArchiveByCode("code");
  Staff _staff = DuplicateStaff(staff);
  strcpy(_staff->first_name, "Hello world");
  if (UpdateStaffInArchive(staff, _staff) != OK) show("Khong cap nhat duoc");
  ShowStaffListInArchive();

  // line
  show("---------------------------------------------------------------------");

  // Delete staff
  staff = GetStaffInArchiveByCode("code");
  if (DeleteStaffInArchive(staff) != OK) show("Khong xoa duoc");

  ShowStaffListInArchive();

  DestroyArchive();
  system("PAUSE");
  return 0;
}
