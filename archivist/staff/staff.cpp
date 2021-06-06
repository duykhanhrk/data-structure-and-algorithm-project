/* Staff */

/* logic */

bool IsStaffValid(Staff staff) {
  if (staff == NULL) return false;

  if (staff->code == NULL || staff->code == "" || strlen(staff->code) > STAFF_CODE_MAX_LEN)
    return false;

  if (staff->first_name == NULL || staff->first_name == "" || strlen(staff->first_name) > STAFF_FIRST_NAME_MAX_LEN)
    return false;

  if (staff->last_name == NULL || staff->last_name == "" || strlen(staff->last_name) > STAFF_LAST_NAME_MAX_LEN)
    return false;

  if (staff->sex != STAFF_SEX_FEMALE && staff->sex != STAFF_SEX_MALE)
    return false;

  return true;
}

/* Standard */

message_tp SaveStaffToArchive(Staff staff) {
  if (!IsStaffValid(staff)) return M_INVALID;

  return AddItemToStaffList(archive->staff_list, staff);
}

message_tp UpdateStaffInArchive(Staff staff, Staff _staff) {
  if (!IsStaffValid(_staff)) return M_INVALID;
  if (!IsInStaffList(archive->staff_list, staff)) return M_NOT_FOUND;
  TranferStaff(staff, _staff);

  return OK;
}

message_tp DeleteStaffInArchive(Staff staff) {
  if (staff == NULL) return M_NOT_FOUND;
  return DeleteItemInStaffList(archive->staff_list, staff);
}

/* Extend */

Staff GetStaffInArchiveByCode(const char * code) {
  return GetItemInStaffListByCode(archive->staff_list, code);
}

message_tp UpdateStaffInArchiveByCode(const char * code, Staff staff) {
  if (!IsStaffValid(staff)) return M_INVALID;

  Staff _staff = GetItemInStaffListByCode(archive->staff_list, code);
  if (_staff == NULL) return M_NOT_FOUND;

  ReplaceStaff(_staff, staff);

  return OK;
}

message_tp DeleteStaffInArchiveByCode(const char * code) {
  return DeleteItemInStaffListByCode(archive->staff_list, code);
}

/* Not safe */

message_tp UpdateStaffInArchiveNS(Staff staff, Staff _staff) {
  if (!IsStaffValid(_staff)) return M_INVALID;
  ReplaceStaff(staff, _staff);

  return OK;
}

/* Debug */

void ShowStaffListInArchive() {
  ShowStaffList(archive->staff_list);
}
