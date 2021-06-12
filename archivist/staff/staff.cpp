/* Staff */

/* rapid - stp */
#define stp_staff_validation_with_strict message_tp mess = StaffValidation(staff); \
                                         if (mess != OK) return mess;

#define stp_staff_validation_without_strict message_tp mess = StaffValidation(staff, false); \
                                            if (mess != OK) return mess;

/* Validation */

message_tp StaffValidation(Staff staff, bool strict = true) {
  if (IsNull(staff)) return M_NULL;

  if (strict == true)
  if (IsNull(staff->code) || IsBlankString(staff->code) || strlen(staff->code) > STAFF_CODE_MAX_LEN)
    return M_STAFF_CODE_INVALID;

  if (IsNull(staff->first_name) || IsBlankString(staff->first_name) || strlen(staff->first_name) > STAFF_FIRST_NAME_MAX_LEN)
    return M_STAFF_FIRST_NAME_INVALID;

  if (IsNull(staff->last_name) || IsBlankString(staff->last_name) || strlen(staff->last_name) > STAFF_LAST_NAME_MAX_LEN)
    return M_STAFF_LAST_NAME_INVALID;

  if (staff->sex != FEMALE_STAFF && staff->sex != MALE_STAFF)
    return M_STAFF_SEX_INVALID;

  return OK;
}

/* Standard */

Staff GetStaffInArchive(const char * code) {
  return GetItemInStaffListByCode(archive->staff_list, code);
}

message_tp SaveStaffToArchive(Staff staff) {
  stp_staff_validation_with_strict;

  return AddItemToStaffList(archive->staff_list, staff);
}

message_tp UpdateStaffInArchive(const char * code, Staff staff) {
  // validation
  stp_staff_validation_without_strict;

  // get staff in archive
  Staff _staff = GetItemInStaffListByCode(archive->staff_list, code);
  if (_staff == NULL) return M_NOT_FOUND;

  // staff code must be same _staff
  strcpy(staff->code, _staff->code);

  // tranfer data
  TranferStaff(_staff, staff);

  return OK;
}

message_tp DeleteStaffInArchive(const char * code) {
  return DeleteItemInStaffListByCode(archive->staff_list, code);
}

/* Not safe */

message_tp UpdateStaffInArchiveNS(Staff _staff, Staff staff) {
  // validation
  stp_staff_validation_without_strict;

  // staff code must be same _staff
  strcpy(staff->code, _staff->code);

  // tranfer data
  TranferStaff(_staff, staff);

  return OK;
}

/* Debug */

void ShowStaffListInArchive() {
  ShowStaffList(archive->staff_list);
}
