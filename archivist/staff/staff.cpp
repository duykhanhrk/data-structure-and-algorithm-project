/* Staff */

message_tp SaveStaffToArchive(Staff staff) {
  return AddItemToStaffList(archive->staff_list, staff);
}

Staff GetStaffInArchive(const char * code) {
  return GetItemInStaffListByCode(archive->staff_list, code);
}

message_tp GetStaffsInArchive(Staff * staffs, int times, int per) {
  // ..
  return OK;
}

message_tp UpdateStaffInArchive(Staff staff) {
  return UpdateItemInStaffList(archive->staff_list, staff);
}

message_tp DeleteStaffInArchive(const char * code) {
  return RemoveItemInStaffListByCode(archive->staff_list, code);
}

void ShowStaffListInArchive() {
  ShowStaffList(archive->staff_list);
}
