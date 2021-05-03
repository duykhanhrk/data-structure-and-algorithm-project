/* staff */

#ifndef __STRUCTURE_STAFF__
#define __STRUCTURE_STAFF__

#include <stdlib.h>
#include <string.h>

#include "../support/message/message.h"
#include "../invoice/invoice.h"

/* Limits */

#define STAFF_CODE_MAX_LEN 10
#define STAFF_FIRST_NAME_MAX_LEN 32
#define STAFF_LAST_NAME_MAX_LEN 64
#define STAFF_LIST_MAX_ITEMS 500
#define STAFF_SEX_FEMALE 'F'
#define STAFF_SEX_MALE 'M'

#ifdef __cplusplus
extern "C" {
#endif

typedef struct StaffT {
  char code[STAFF_CODE_MAX_LEN];
  char first_name[STAFF_LAST_NAME_MAX_LEN];
  char last_name[STAFF_FIRST_NAME_MAX_LEN];
  char sex;
} StaffT, * Staff;

typedef struct StaffListT {
  int count;
  StaffT * staffs[STAFF_LIST_MAX_ITEMS];
} StaffListT, * StaffList;

/* Object methods */
Staff NewStaff(const char *, const char *, const char *, char);
void DestroyStaff(Staff &staff);

/* List methods */

// New and Destroy
StaffList NewStaffList();
void DestroyStaffList(StaffList &);

// Logic
bool IsStaffListEmpty(StaffList);
bool IsStaffListListFull(StaffList);
bool IsStaffCodeAvailable(StaffList, const char *);

// Insert
message_tp AddItemToStaffList(StaffList &, Staff);
message_tp InsertItemToBeginningOfStaffList(StaffList &, Staff);
message_tp InsertItemToEndOfStaffList(StaffList &, Staff);
message_tp InsertItemToStaffListByIndex(StaffList &, Staff, int);

/* Get */
Staff GetFirstItemInStaffList(StaffList);
Staff GetLastItemInStaffList(StaffList);
Staff GetStaffInListByIndex(StaffList, int);
Staff GetStaffInListByCode(StaffList, const char *);

/* Delete */
message_tp RemoveFirstItemInStaffList(StaffList &);
message_tp RemoveLastItemInStaffList(StaffList &);
message_tp RemoveItemInStaffListByIndex(StaffList &, int);
message_tp RemoveItemInStaffListByCode(StaffList &, const char *);
message_tp RemoveItemInStaffList(StaffList &, Staff);

#include "staff.cpp"

#ifdef __cplusplus
}
#endif

#endif
