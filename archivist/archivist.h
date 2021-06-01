/* archivist */

#ifndef __ARCHIVIST__
#define __ARCHIVIST__

#include "../structure/structure.h"

typedef struct ArchiveT {
  MaterialList material_list;
  StaffList staff_list;
} ArchiveT, * Archive;

Archive archive;

void InitArchive() {
  archive = (Archive) malloc(sizeof(ArchiveT));
  archive->material_list = NewMaterialList();
  archive->staff_list = NewStaffList();
}

void DestroyArchive() {
  DestroyMaterialList  (archive->material_list);
  DestroyStaffList(archive->staff_list);
  free(archive);
}

#include "material/material.h"

#endif
