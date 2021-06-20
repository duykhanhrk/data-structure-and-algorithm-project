#include "staff.h"

/* rapid - stp */
#define stp_staff_validation_with_strict message_tp mess = StaffValidation(staff); \
                                         if (mess != OK) return mess;

#define stp_staff_validation_without_strict message_tp mess = StaffValidation(staff, false); \
                                            if (mess != OK) return mess;

/* Validation */

message_tp StaffValidation(Staff staff, bool strict = true) {
  if (IsNull(staff)) return M_NULL;

  if (strict == true)
  if (IsNull(staff->code) || !IsUNString(staff->code) || strlen(staff->code) > STAFF_CODE_MAX_LEN)
    return M_STAFF_CODE_INVALID;

  if (IsNull(staff->first_name) || !IsASString(staff->first_name) || strlen(staff->first_name) > STAFF_FIRST_NAME_MAX_LEN)
    return M_STAFF_FIRST_NAME_INVALID;

  if (IsNull(staff->last_name) || !IsASString(staff->last_name) || strlen(staff->last_name) > STAFF_LAST_NAME_MAX_LEN)
    return M_STAFF_LAST_NAME_INVALID;

  if (staff->sex != FEMALE_STAFF && staff->sex != MALE_STAFF)
    return M_STAFF_SEX_INVALID;

  return OK;
}

/* Standard */
int CountStaffsInArchive() {
  return StaffListCount(archive->staff_list);
}

Staff GetStaffInArchive(const char * code) {
  return GetItemInStaffListByCode(archive->staff_list, code);
}

void TakeStaffsInArchive(LinearList linear_list, int offset, int limit) {
  EmptyLinearList(linear_list);
  TakeItemsInStaffList(archive->staff_list, linear_list, offset, limit);
}

message_tp SaveStaffToArchive(Staff staff) {
  stp_staff_validation_with_strict;

  // must be empty list
  staff->invoice_list = NULL;

  message_tp message = AddItemToStaffList(archive->staff_list, staff);
  if (message != OK) return message;

  SaveStaffListFromArchiveToStorage();
  return OK;
}

message_tp UpdateStaffInArchive(const char * code, Staff staff) {
  // validation
  stp_staff_validation_without_strict;

  // get staff in archive
  Staff _staff = GetItemInStaffListByCode(archive->staff_list, code);
  if (_staff == NULL) return M_NOT_FOUND;

  // staff code must be same _staff
  strcpy(staff->code, _staff->code);

  // staff invoice list must be invoice list _staff
  staff->invoice_list = _staff->invoice_list;

  // tranfer data
  CopyStaff(_staff, staff);

  // Save staff to storage
  SaveStaffListFromArchiveToStorage();
  return OK;
}

message_tp DeleteStaffInArchive(const char * code) {
  message_tp message = DeleteItemInStaffListByCode(archive->staff_list, code);
  if (message != OK) return message;

  SaveStaffListFromArchiveToStorage();
  return OK;
}

/* Debug */

void ShowStaffListInArchive() {
  ShowStaffList(archive->staff_list);
}
