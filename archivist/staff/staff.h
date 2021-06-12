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

/* Logic */
message_tp IsStaffValid(Staff, bool);

/* Standard */
message_tp SaveStaffToArchive(Staff);
message_tp UpdateStaffInArchive(Staff, Staff);
message_tp DeleteStaffInArchive(Staff);

/* Extend */
Staff GetStaffInArchiveByCode(const char * code);
message_tp UpdateStaffInArchiveByCode(const char * code, Staff staff);
message_tp DeleteStaffInArchiveByCode(const char * code);

/* Not safe */
message_tp UpdateStaffInArchiveNS(Staff, Staff);

/* Debug */
void ShowStaffListInArchive();

#include "staff.cpp"

#ifdef __cplusplus
}
#endif

#endif
