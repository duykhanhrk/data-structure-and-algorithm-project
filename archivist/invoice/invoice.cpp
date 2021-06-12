/* Invoice & Invoice Detail */

/* Rapid - ivp */

#define ivp_invoice_validation_with_strict message_tp mess = IsInvoiceValid(invoice); \
                                           if (mess != OK) return mess

#define ivp_invoice_validation_without_strict message_tp mess = IsInvoiceValid(invoice, false); \
                                              if (mess != OK) return mess

#define ivp_staff_must_be_in_archive if (!IsInStaffList(archive->staff_list, staff)) \
                                        return M_STAFF_NOT_FOUND

/* Logic */

message_tp IsInvoiceNumberValid(Invoice invoice) {
  if (IsNull(invoice->number) || IsBlankString(invoice->number) || strlen(invoice->number) > INVOICE_NUMBER_MAX_LEN)
    return BAD;

  for (int interact = 0; interact < archive->staff_list->count; interact ++) {
    if (IsNumberInInvoiceList(archive->staff_list->staffs[interact]->invoices, invoice->number))
      return BAD;
  }

  return OK;
}

bool IsInvoiceDetailsValid(InvoiceDetailList invoice_detail_list) {
  if (IsNull(invoice_detail_list) || IsZero(invoice_detail_list->count))
    return false;

  for (int interact = 0; interact < invoice_detail_list->count; interact ++) {
    if (IsInvoiceDetailValid(invoice_detail_list->invoice_details[interact]) != OK)
      return false;
  }
  return true;
}

message_tp IsInvoiceValid(Invoice invoice, bool strict = true) {
  if (IsNull(invoice)) return M_NULL;

  if (strict == true)
  if (IsInvoiceNumberValid(invoice) != OK)
    return M_INVOICE_NUMBER_INVALID;

  if (invoice->created_at > TimeNow())
    return M_INVOICE_CREATED_AT_INVALID;

  if (invoice->type != IMPORT_INVOICE && invoice->type != EXPORT_INVOICE)
    return M_INVOICE_TYPE_INVALID;

  if (strict == true)
  if (!IsInvoiceDetailsValid(invoice->invoice_details))
    return M_INVOICE_INVOICE_DETAILS_INVALID;

  return OK;
}

/* Standard */
message_tp SaveInvoiceToArchive(Staff staff, Invoice invoice) {
  ivp_invoice_validation_with_strict;
  ivp_staff_must_be_in_archive;

  return AddItemToInvoiceList(staff->invoices, invoice);
}

message_tp UpdateInvoiceInArchive(Staff staff, Invoice _invoice, Invoice invoice) {
  ivp_invoice_validation_without_strict;
  ivp_staff_must_be_in_archive;

  // invoice must be in archive
  if (!IsInInvoiceList(staff->invoices, invoice)) return M_NOT_FOUND;

  // staff must be same number with invoice
  strcpy(invoice->number, _invoice->number);

  // invoice invoice_details must be same _invoice invoice_details
  invoice->invoice_details = _invoice->invoice_details;

  // tranfer data
  TranferInvoice(_invoice, invoice);

  return OK;
}

message_tp DeleteInvoiceInArchive(Staff staff, Invoice _invoice) {
  ivp_staff_must_be_in_archive;

  return DeleteItemInInvoiceList(staff->invoices, _invoice);
}

/* Extend */

Invoice GetInvoiceInArchiveByNumber(Staff staff, const char * number) {
  if (!IsInStaffList(archive->staff_list, staff)) return NULL;

  return GetItemInInvoiceListByNumber(staff->invoices, number);
}

message_tp UpdateInvoiceInArchiveByCode(Staff staff, const char * number, Invoice invoice) {
  ivp_invoice_validation_without_strict;
  ivp_staff_must_be_in_archive;

  // get invoice
  Invoice _invoice = GetItemInInvoiceListByNumber(staff->invoices, number);
  if (_invoice == NULL) return M_NOT_FOUND;

  // invoice number must be same _invoice number
  strcpy(invoice->number, _invoice->number);

  // invoice invoice_details must be same _invoice invoice_details
  invoice->invoice_details = _invoice->invoice_details;

  // tranfer data
  TranferInvoice(_invoice, invoice);

  return OK;
}

message_tp DeleteInvoiceInArchiveByCode(Staff staff, const char * code) {
  ivp_staff_must_be_in_archive;

  return DeleteItemInInvoiceListByCode(staff->invoices, code);
}

/* Not safe */

message_tp UpdateInvoiceInArchiveNS(Invoice invoice, Invoice _invoice) {
  ivp_invoice_validation_without_strict;

  // invoice number must be same _invoice number
  strcpy(invoice->number, _invoice->number);

  // invoice invoice_details must be same _invoice invoice_details
  invoice->invoice_details = _invoice->invoice_details;

  // tranfer data
  TranferInvoice(invoice, _invoice);

  return OK;
}

/* Lazy */
Invoice GetInvoiceInArchiveByNumberLZ(const char * number) {
  Invoice invoice;
  for (int interact = 0; interact < archive->staff_list->count; interact ++) {
    invoice = GetItemInInvoiceListByNumber(archive->staff_list->staffs[interact]->invoices, number);
    if (invoice != NULL) return invoice;
  }

  return NULL;
}

/* Debug */

void ShowInvoiceInArchive(const char * number) {
  Invoice invoice = GetInvoiceInArchiveByNumberLZ(number);
  if (IsNull(invoice)) return;
  ShowInvoice(invoice);
  for(int interact = 0; interact < invoice->invoice_details->count; interact ++) {
    ShowInvoiceDetail(invoice->invoice_details->invoice_details[interact]);
  }
}

void ShowInvoiceListInArchiveByStaff(Staff staff) {
  printf("%s\n-----------------------\n", staff->code);
  ShowInvoiceList(staff->invoices);
  printf("-----------------------\n");
}

void ShowInvoiceListInArchive() {
  StaffListEach(archive->staff_list, ShowInvoiceListInArchiveByStaff);
}
