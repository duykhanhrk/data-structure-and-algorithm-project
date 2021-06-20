#include "staff.h"

/* Object methods */

Staff NewStaff(
  const char * code = STAFF_CODE_DEFAULT_VALUE,
  const char * first_name = STAFF_FIRST_NAME_DEFUALT_VALUE,
  const char * last_name = STAFF_LAST_NAME_DEFAULT_VALUE,
  char sex = STAFF_SEX_DEFAULT_VALUE,
  InvoiceList invoice_list = STAFF_INVOICES_DEFAULT_VALUE
) {
  Staff staff = (Staff) malloc(sizeof(struct StaffT));
  strcpy(staff->code, code);
  strcpy(staff->first_name, first_name);
  strcpy(staff->last_name, last_name);
  staff->sex = sex;
  staff->invoice_list = invoice_list;

  return staff;
}

void DestroyStaff(Staff &staff) {
  DestroyInvoiceList(staff->invoice_list);
  free(staff);
  staff = NULL;
}

void RevokeStaff(Staff &staff) {
  free(staff);
  staff = NULL;
}

void TranferStaff(Staff staff, Staff &_staff) {
  strcpy(staff->code, _staff->code);
  strcpy(staff->first_name, _staff->first_name);
  strcpy(staff->last_name, _staff->last_name);
  staff->sex = _staff->sex;
  staff->invoice_list = _staff->invoice_list;

  RevokeStaff(_staff);
}

void CopyStaff(Staff staff, Staff _staff) {
  strcpy(staff->code, _staff->code);
  strcpy(staff->first_name, _staff->first_name);
  strcpy(staff->last_name, _staff->last_name);
  staff->sex = _staff->sex;
  staff->invoice_list = _staff->invoice_list;
}

Staff DuplicateStaff(Staff staff) {
  return NewStaff(
    staff->code,
    staff->first_name,
    staff->last_name,
    staff->sex,
    staff->invoice_list
  );
}

/* List methods */

// New and Destroy
StaffList NewStaffList() {
  StaffList staff_list = (StaffList) malloc(sizeof(StaffListT));
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

bool IsCodeInStaffList(StaffList staff_list, const char * code) {
  for (int interact = 0; interact < staff_list->count; interact ++)
    if (strcmp(staff_list->staffs[interact]->code, code) == 0) return true;

  return false;
}

// Count
int StaffListCount(StaffList staff_list) {
  return staff_list->count;
}

// Insert
message_tp AddItemToStaffList(StaffList &staff_list, Staff staff) {
  if (staff_list->count == STAFF_LIST_MAX_ITEMS)
    return M_LIST_IS_FULL;

  if (IsCodeInStaffList(staff_list, staff->code))
    return M_CONFLICT;

  staff_list->staffs[staff_list->count] = staff;
  staff_list->count ++;

  return OK;
}

message_tp InsertItemToBeginningOfStaffList(StaffList &staff_list, Staff staff) {
  if (staff_list->count == STAFF_LIST_MAX_ITEMS)
    return M_LIST_IS_FULL;

  for (int interact = staff_list->count; interact > 0; interact --)
    staff_list->staffs[interact] = staff_list->staffs[interact - 1];

  staff_list->staffs[0] = staff;

  staff_list->count ++;

  return OK;
}

message_tp InsertItemToEndOfStaffList(StaffList &staff_list, Staff staff) {
  if (staff_list->count == STAFF_LIST_MAX_ITEMS)
    return M_LIST_IS_FULL;

  staff_list->staffs[staff_list->count];

  staff_list->count ++;

  return OK;
}

message_tp InsertItemToStaffListByIndex(StaffList &staff_list, Staff staff, int index) {
  if (staff_list->count == STAFF_LIST_MAX_ITEMS)
    return M_LIST_IS_FULL;

  for (int interact = staff_list->count; interact > index; interact --)
    staff_list->staffs[interact] = staff_list->staffs[interact - 1];

  staff_list->staffs[index] = staff;

  staff_list->count ++;

  return OK;
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

void TakeItemsInStaffList(StaffList staff_list, LinearList linear_list, int &offset, int &limit) {
  if (offset >= staff_list->count) return;
  for (int interact = offset; interact < staff_list->count && limit > 0; interact ++, limit --)
    AddItemToLinearList(linear_list, staff_list->staffs[interact]);
}

// Delete

message_tp DeleteFirstItemInStaffList(StaffList &staff_list) {
  if (staff_list->count == 0) return M_NOT_FOUND;

  DestroyStaff(staff_list->staffs[0]);

  for (int interact = 0; interact < staff_list->count - 2; interact ++)
    staff_list->staffs[interact] = staff_list->staffs[interact + 1];

  staff_list->count --;

  return OK;
}

message_tp DeleteLastItemInStaffList(StaffList &staff_list) {
  if (staff_list->count == 0) return M_NOT_FOUND;

  DestroyStaff(staff_list->staffs[staff_list->count - 1]);

  return OK;
}

message_tp DeleteItemInStaffListByIndex(StaffList &staff_list, int index) {
  if (staff_list->count == 0 || index < 0 || index > staff_list->count - 1)
    return M_NOT_FOUND;

  DestroyStaff(staff_list->staffs[index]);

  for (int interact = index; interact < staff_list->count - 1; interact ++)
    staff_list->staffs[interact] = staff_list->staffs[interact + 1];

  staff_list->count --;

  return OK;
}

message_tp DeleteItemInStaffListByCode(StaffList &staff_list, const char * code) {
  for (int interact = 0; interact < staff_list->count; interact ++)
    if (strcmp(staff_list->staffs[interact]->code, code) == 0)
      return DeleteItemInStaffListByIndex(staff_list, interact);

  return M_NOT_FOUND;
}

/* Test */

void StaffListEach(StaffList staff_list, void (* perform) (Staff)) {
  for (int interact = 0; interact < staff_list->count; interact ++)
    perform(staff_list->staffs[interact]);
}

void ShowStaff(Staff staff, const char * format = STAFF_SHOW_FORMAT_DEFAULT) {
  printf(
      format,
      staff->code,
      staff->first_name,
      staff->last_name,
      staff->sex
  );
}

void ShowStaffList(StaffList staff_list, const char * format = STAFF_LIST_SHOW_FORMAT_DEFAULT) {
  for (int interact = 0; interact < staff_list->count; interact ++)
    ShowStaff(staff_list->staffs[interact], format);
}
