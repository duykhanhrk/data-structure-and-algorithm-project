#ifndef __ARCHIVIST_MATERIAL__
#define __ARCHIVIST_MATERIAL__

#include <stdlib.h>
#include <string.h>

#include "../../supporter/supporter.h"
#include "../../structure/material/material.h"

extern Archive archive;

#ifdef __cplusplus
extern "C" {
#endif

/* Validation */
message_tp MaterialValidation(Material, bool);

/* Logic */
bool IsMaterialAvailable(const char * code, int amount);

/* Standard */
Material GetMaterialInArchive(const char * code);
void TakeMaterialsInArchive(LinearList, int, int);
message_tp SaveMaterialToArchive(Material);
message_tp UpdateMaterialInArchive(const char * code, Material material);
message_tp DeleteMaterialInArchive(const char * code);

/* Not safe */
message_tp UpdateMaterialInArchiveNS(Material, Material);

/* Debug */
void ShowMaterialListInArchive();

#include "material.cpp"

#ifdef __cplusplus
}
#endif

#endif
