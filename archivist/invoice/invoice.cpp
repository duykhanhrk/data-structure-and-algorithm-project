/* Staff */

message_tp SaveInvoiceToArchive(Staff staff, Invoice invoice) {
  return AddItemToInvoiceList(staff->invoices, invoice);
}

message_tp UpdateInvoiceInArchive(Invoice invoice) {
  Invoice invoice;

  for (int interact = 0; interact < archive->staff_list->count; interact ++) {
    invoice = GetItemInInvoiceListByNumber(archive->staff_list->staffs[interact]->invoices, number)
    if (invoice != NULL)
      return UpdateItemInvoiceList(archive->staff_list->staffs[interact]->invoices, invoice);
  }

  return MESSAGE_OBJECT_NOT_FOUND;
}

message_tp DeleteInvoiceInArchive(Invoice invoice) {
  return OK;
}

void ShowInvoiceListInArchive() {
  ShowInvoiceList(archive->staff_list);
}
