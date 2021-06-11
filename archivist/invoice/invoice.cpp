/* Invoice & Invoice Detail */

/* Rapid - ivp */

#define ivp_invoice_validation message_tp mess = IsInvoiceValid(invoice, true); \
                               if (mess != OK) return mess

#define ivp_invoice_validation_for_update message_tp mess = IsInvoiceValid(invoice, false); \
                                          if (mess != OK) return mess

#define ivp_staff_must_be_in_archive if (!IsInStaffList(archive->staff_list, staff)) \
                                       return M_STAFF_NOT_FOUND

/* Logic */

message_tp IsInvoiceNumberValid(Invoice invoice) {
  if (invoice->number == NULL || strcpy(invoice->number, "") == 0 || strlen(invoice->number) > INVOICE_NUMBER_MAX_LEN)
    return BAD;

  for (int interact = 0; interact < archive->staff_list->count; interact ++) {
    if (IsNumberInInvoiceList(archive->staff_list->staffs[interact]->invoices, invoice->number))
      return BAD;
  }

  return OK;
}

message_tp IsInvoiceValid(Invoice invoice, bool strict = true) {
  if (invoice == NULL) return M_NULL;

  if (strict == true && IsInvoiceNumberValid(invoice) != OK)
    return M_INVOICE_NUMBER_INVALID;

  if (invoice->created_at > TimeNow())
    return M_INVOICE_CREATED_AT_INVALID;

  if (invoice->type != INVOICE_TYPE_IMPORT && invoice->type != INVOICE_TYPE_EXPORT)
    return M_INVOICE_TYPE_INVALID;

  if (invoice->invoice_details == NULL || invoice->invoice_details->count == 0)
    return M_INVOICE_INVOICE_DETAILS_INVALID;

  return OK;
}

/* Standard */
message_tp SaveInvoiceToArchive(Staff staff, Invoice invoice) {
  ivp_invoice_validation;
  ivp_staff_must_be_in_archive;

  return AddItemToInvoiceList(staff->invoices, invoice);
}

// Unstable
//
message_tp UpdateInvoiceInArchive(Staff staff, Invoice _invoice, Invoice invoice) {
  ivp_invoice_validation_for_update;
  ivp_staff_must_be_in_archive;

  if (!IsInInvoiceList(staff->invoices, invoice)) return M_NOT_FOUND;
  TranferInvoice(_invoice, invoice);

  return OK;
}

message_tp DeleteInvoiceInArchive(Staff staff, Invoice invoice) {
  ivp_staff_must_be_in_archive;

  return DeleteItemInInvoiceList(staff->invoices, invoice);
}

/* Extend */

Invoice GetInvoiceInArchiveByNumber(Staff staff, const char * number) {
  if (!IsInStaffList(archive->staff_list, staff)) return NULL;

  return GetItemInInvoiceListByNumber(staff->invoices, number);
}

message_tp UpdateInvoiceInArchiveByCode(Staff staff, const char * number, Invoice invoice) {
  ivp_invoice_validation_for_update;
  ivp_staff_must_be_in_archive;

  Invoice _invoice = GetItemInInvoiceListByNumber(staff->invoices, number);
  if (_invoice == NULL) return M_NOT_FOUND;

  TranferInvoice(_invoice, invoice);

  return OK;
}

message_tp DeleteInvoiceInArchiveByCode(Staff staff, const char * code) {
  ivp_staff_must_be_in_archive;

  return DeleteItemInInvoiceListByCode(staff->invoices, code);
}

/* Not safe */

message_tp UpdateInvoiceInArchiveNS(Invoice invoice, Invoice _invoice) {
  ivp_invoice_validation;

  TranferInvoice(invoice, _invoice);

  return OK;
}

/* Debug */

void ShowInvoiceListInArchiveByStaff(Staff staff) {
  printf("%s\n-----------------------\n", staff->code);
  ShowInvoiceList(staff->invoices);
  printf("-----------------------\n");
}

void ShowInvoiceListInArchive() {
  StaffListEach(archive->staff_list, ShowInvoiceListInArchiveByStaff);
}
