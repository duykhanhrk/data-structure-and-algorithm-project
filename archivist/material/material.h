/* Material */

#ifndef __ARCHIVIST_MATERIAL__
#define __ARCHIVIST_MATERIAL__

#include <stdlib.h>
#include <string.h>

#include "../../support/message/message.h"
#include "../../structure/material/material.h"

extern Archive archive;

#ifdef __cplusplus
extern "C" {
#endif

/* Logic */
bool IsMaterialValid(Material);

/* Standard */
message_tp SaveMaterialToArchive(Material);
message_tp UpdateMaterialInArchive(Material, Material);
message_tp DeleteMaterialInArchive(Material);

/* Extend */
Material GetMaterialInArchiveByCode(const char * code);
message_tp UpdateMaterialInArchiveByCode(const char * code, Material material);
message_tp DeleteMaterialInArchiveByCode(const char * code);

/* Not safe */
message_tp UpdateMaterialInArchiveNS(Material, Material);

/* Debug */
void ShowMaterialListInArchive();

#include "material.cpp"

#ifdef __cplusplus
}
#endif

#endif
