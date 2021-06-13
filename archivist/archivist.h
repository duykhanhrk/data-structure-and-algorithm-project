/* archivist */

#ifndef __ARCHIVIST__
#define __ARCHIVIST__

#define MATERIALS_FILE_PATH "storage/materials.dat"
#define STAFFS_FILE_PATH "storage/staffs.dat"

#include "../structure/structure.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct ArchiveT {
  MaterialList material_list;
  StaffList staff_list;
} ArchiveT, * Archive;

Archive archive;

void InitArchive();
void DestroyArchive();

message_tp LoadMaterialListFromStorageToArchive();
message_tp SaveMaterialListFromArchiveToStorage();
message_tp SaveStaffListFromArchiveToStorage();
message_tp LoadStaffListFromStorageToArchive();

#include "material/material.h"
#include "staff/staff.h"
#include "invoice/invoice.h"

#include "archivist.cpp"
#ifdef __cplusplus
}
#endif

#endif
