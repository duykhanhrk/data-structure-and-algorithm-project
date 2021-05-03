#include "staff.h"

/* Object methods */

Staff NewStaff(
  const char * code = "\0",
  const char * first_name = "\0",
  const char * last_name = "\0",
  char sex = 'F'
) {
  Staff staff = (Staff) malloc(sizeof(struct StaffT));
  strcpy(staff->code, code);
  strcpy(staff->first_name, first_name);
  strcpy(staff->last_name, last_name);
  staff->sex = sex;

  return staff;
}

void DestroyStaff(Staff &staff) {
  free(staff);
  staff = NULL;
}

/* List methods */

// New and Destroy
StaffList NewStaffList() {
  StaffList staff_list;
  staff_list->count = 0;

  return staff_list;
}

void DestroyStaffList(StaffList &staff_list) {
  while (staff_list->count --)
    DestroyStaff(staff_list->staffs[staff_list->count]);
}

// Logic
bool IsStaffListEmpty(StaffList staff_list) {
  return (staff_list->count == 0);
}

bool IsStaffListFull(StaffList staff_list) {
  return (staff_list->count == STAFF_LIST_MAX_ITEMS);
}

bool IsStaffCodeAvailable(StaffList staff_list, const char * code) {
  for (int interact = 0; interact < staff_list->count; interact ++)
    if (strcmp(staff_list->staffs[interact]->code, code) == 0) return false;

  return true;
}

// Insert
message_tp AddItemToStaffList(StaffList &staff_list, Staff staff) {
  if (staff_list->count == STAFF_LIST_MAX_ITEMS)
    return MESSAGE_LIST_IS_FULL;

  staff_list->staffs[staff_list->count] = staff;

  staff_list->count ++;

  return MESSAGE_OK;
}

message_tp InsertItemToBeginningOfStaffList(StaffList &staff_list, Staff staff) {
  if (staff_list->count == STAFF_LIST_MAX_ITEMS)
    return MESSAGE_LIST_IS_FULL;

  for (int interact = staff_list->count; interact > 0; interact --)
    staff_list->staffs[interact] = staff_list->staffs[interact - 1];

  staff_list->staffs[0] = staff;

  staff_list->count ++;

  return MESSAGE_OK;
}

message_tp InsertItemToEndOfStaffList(StaffList &staff_list, Staff staff) {
  if (staff_list->count == STAFF_LIST_MAX_ITEMS)
    return MESSAGE_LIST_IS_FULL;

  staff_list->staffs[staff_list->count];

  staff_list->count ++;

  return MESSAGE_OK;
}

message_tp InsertItemToStaffListByIndex(StaffList &staff_list, Staff staff, int index) {
  if (staff_list->count == STAFF_LIST_MAX_ITEMS)
    return MESSAGE_LIST_IS_FULL;

  for (int interact = staff_list->count; interact > index; interact --)
    staff_list->staffs[interact] = staff_list->staffs[interact - 1];

  staff_list->staffs[index] = staff;

  staff_list->count ++;

  return MESSAGE_OK;
}

// Get
Staff GetFirstItemStaffList(StaffList staff_list) {
  if (staff_list->count == 0) return NULL;

  return staff_list->staffs[0];
}

Staff GetLastItemInStaffList(StaffList staff_list) {
  if (staff_list->count == 0) return NULL;

  return staff_list->staffs[staff_list->count - 1];
}

Staff GetItemInStaffListByIndex(StaffList staff_list, int index) {
  if (staff_list->count == 0 || index < 0 || index > staff_list->count - 1)
    return NULL;

  return staff_list->staffs[index];
}

Staff GetItemInStaffListByCode(StaffList staff_list, const char * code) {
  for (int interact = 0; interact < staff_list->count; interact ++)
    if (strcmp(staff_list->staffs[interact]->code, code) == 0)
      return staff_list->staffs[interact];

  return NULL;
}

// Delete

message_tp RemoveFirstItemInStaffList(StaffList &staff_list) {
  if (staff_list->count == 0) return MESSAGE_OBJECT_NOT_FOUND;

  DestroyStaff(staff_list->staffs[0]);

  for (int interact = 0; interact < staff_list->count - 2; interact ++)
    staff_list->staffs[interact] = staff_list->staffs[interact + 1];

  staff_list->count --;

  return MESSAGE_OK;
}

message_tp RemoveLastItemInStaffList(StaffList &staff_list) {
  if (staff_list->count == 0) return MESSAGE_OBJECT_NOT_FOUND;

  DestroyStaff(staff_list->staffs[staff_list->count - 1]);

  return MESSAGE_OK;
}

message_tp RemoveItemInStaffListByIndex(StaffList &staff_list, int index) {
  if (staff_list->count == 0 || index < 0 || index > staff_list->count - 1)
    return MESSAGE_OBJECT_NOT_FOUND;

  DestroyStaff(staff_list->staffs[index]);

  for (int interact = index; interact < staff_list->count - 2; interact ++)
    staff_list->staffs[interact] = staff_list->staffs[interact + 1];

  staff_list->count --;

  return MESSAGE_OK;
}

message_tp RemoveItemInStaffListByCode(StaffList &staff_list, const char * code) {
  for (int interact = 0; interact < staff_list->count; interact ++)
    if (strcmp(staff_list->staffs[interact]->code, code) == 0)
      return RemoveItemInStaffListByIndex(staff_list, interact);

  return MESSAGE_OBJECT_NOT_FOUND;
}

message_tp RemoveItemInStaffList(StaffList &staff_list, Staff staff) {
  for (int interact = 0; interact < staff_list->count; interact ++)
    if (staff_list->staffs[interact] == staff)
      return RemoveItemInStaffListByIndex(staff_list, interact);

  return MESSAGE_OBJECT_NOT_FOUND;
}
