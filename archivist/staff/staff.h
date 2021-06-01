/* Staff */

#ifndef __ARCHIVIST_STAFF__
#define __ARCHIVIST_STAFF__

#include <stdlib.h>
#include <string.h>

#include "../../support/message/message.h"
#include "../../structure/staff/staff.h"

extern Archive archive;

#ifdef __cplusplus
extern "C" {
#endif

message_tp SaveStaffToArchive(Staff);
Staff GetStaffInArchive(const char *);
message_tp GetStaffsInArchive(Staff *, int, int);
message_tp UpdateStaffInArchive(Staff);
message_tp DeleteStaffInArchive(const char *);
void ShowStaffListInArchive();

#include "staff.cpp"

#ifdef __cplusplus
}
#endif

#endif
