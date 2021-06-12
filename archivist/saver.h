/* message */

#ifndef __ARCHIVE_SAVER__
#define __ARCHIVE_SAVER__

#include <stdio.h>

extern Archive archive;

#define MATERIALS_FILE_PATH "storage/materials.dat"
#define STAFFS_FILE_PATH "storage/staffs.dat"

#ifdef __cplusplus
extern "C" {
#endif

message_tp SaveMaterialsFromArchiveToStorage();
message_tp SaveStaffsFromArchiveToStorage();
message_tp SaveDataFromArchiveToStorage();

message_tp LoadMaterialsFromStorageToArchive();
message_tp LoadStaffsFromStorageToArchive();
message_tp LoadDateFromStorageToArchive();

#include "saver.cpp"

#ifdef __cplusplus
}
#endif

#endif
