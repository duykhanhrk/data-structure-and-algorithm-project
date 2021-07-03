#include "invoice.h"

/* Rapid - ivp */

#define ivp_invoice_validation_with_strict message_tp mess = InvoiceValidation(invoice); \
                                           if (mess != OK) return mess

#define ivp_invoice_validation_without_strict message_tp mess = InvoiceValidation(invoice, false); \
                                              if (mess != OK) return mess

/* Logic */

bool IsInvoiceNumberValid(Invoice invoice) {
  if (IsNull(invoice->number) || !IsNumericString(invoice->number) || strlen(invoice->number) > INVOICE_NUMBER_MAX_LEN)
    return false;
  for (int interact = 0; interact < archive->staff_list->count; interact ++) {
    if (IsNumberInInvoiceList(archive->staff_list->staffs[interact]->invoice_list, invoice->number))
      return false;
  }

  return true;
}

/* Validation */

message_tp InvoiceDetailListValidation(InvoiceDetailList invoice_detail_list, bool strict = true, char invoice_type = IMPORT_INVOICE) {
  if (IsNull(invoice_detail_list) || IsZero(invoice_detail_list->count))
    return M_INVOICE_INVOICE_DETAILS_INVALID;

  if (TotalMaterialsInInvoiceDetailList(invoice_detail_list) > INVOICE_DETAIL_MAX_TOTAL_MATERIALS)
    return M_INVOICE_INVOICE_DETAILS_INVALID;

  for (int interact = 0; interact < invoice_detail_list->count; interact ++) {
    message_tp mess = InvoiceDetailValidation(invoice_detail_list->invoice_details[interact], strict, invoice_type);
    if (mess != OK) return mess;
  }

  return OK;
}

message_tp InvoiceValidation(Invoice invoice, bool strict = true) {
  if (IsNull(invoice)) return M_NULL;

  if (strict == true)
  if (!IsInvoiceNumberValid(invoice))
    return M_INVOICE_NUMBER_INVALID;

  if (invoice->created_at > TimeNow())
    return M_INVOICE_CREATED_AT_INVALID;

  if (invoice->type != IMPORT_INVOICE && invoice->type != EXPORT_INVOICE)
    return M_INVOICE_TYPE_INVALID;

  if (strict == true) {
    message_tp mess = InvoiceDetailListValidation(invoice->invoice_detail_list, true, invoice->type);
    if (mess != OK) return mess;
  }

  return OK;
}

/* Standard */

double CalculateTotalPriceOfInvoice(Invoice invoice) {
  double total_price = 0.0;
  InvoiceDetail invoice_detail;
  for (int interact = 0; interact < invoice->invoice_detail_list->count; interact ++) {
    invoice_detail = GetItemInInvoiceDetailListByIndex(invoice->invoice_detail_list, interact);
    total_price += invoice_detail->amount * invoice_detail->price
                   + (invoice_detail->amount * invoice_detail->price * invoice_detail->vat);
  }

  return total_price;
}

Staff GetCreatedInvoiceStaff(const char * invoice_number) {
  for (int interact = 0; interact < archive->staff_list->count; interact ++) {
    if (IsNumberInInvoiceList(archive->staff_list->staffs[interact]->invoice_list, invoice_number))
      return archive->staff_list->staffs[interact];
  }

  return NULL;
}

Invoice GetInvoiceInArchive(const char * staff_code, const char * number) {
  Staff staff = GetItemInStaffListByCode(archive->staff_list, staff_code);
  if (IsNull(staff)) return NULL;

  return GetItemInInvoiceListByNumber(staff->invoice_list, number);
}

// TODO: (1) filter by created_at
int CountInvoicesInArchive(void * data, void * filter) {
  int count = 0;
  InvoiceList invoice_list;

  for (int interact = 0; interact < archive->staff_list->count; interact ++) {
    invoice_list = archive->staff_list->staffs[interact]->invoice_list;
    count += InvoiceListCount(invoice_list);
  }

  return count;
}

// TODO: (2) filter by created_at
void TakeInvoicesInArchive(void * data, void * filter, LinearList linear_list, int offset, int limit) {
  for (int interact = 0; interact < linear_list->count; interact ++)
    DestroyLinearList((LinearList) (linear_list->data[interact]));
  EmptyLinearList(linear_list);

  InvoiceNode invoice_node;
  LinearList container;
  for (int interact = 0; interact < archive->staff_list->count; interact ++) {
    invoice_node = archive->staff_list->staffs[interact]->invoice_list;
    while (invoice_node != NULL && limit > 0) {
      if (offset > 0) offset --;
      else {
        container = NewLinearList(2);
        AddItemToLinearList(container, invoice_node->invoice);
        AddItemToLinearList(container, archive->staff_list->staffs[interact]);
        AddItemToLinearList(linear_list, container);
        limit --;
      }
      invoice_node = invoice_node->next_node;
    }
  }
}

message_tp SaveInvoiceToArchive(const char * staff_code, Invoice invoice) {
  ivp_invoice_validation_with_strict;

  // Get staff
  Staff staff = GetItemInStaffListByCode(archive->staff_list, staff_code);
  if (IsNull(staff)) return M_STAFF_NOT_FOUND;

  // Add invoice to list
  message_tp message = AddItemToInvoiceList(staff->invoice_list, invoice);
  if (message != OK) return message;

  // Update material list
  if (invoice->type == IMPORT_INVOICE) {
    for (int interact = 0; interact < invoice->invoice_detail_list->count; interact ++) {
      message = UpdateMaterialQuantityInArchive(
        invoice->invoice_detail_list->invoice_details[interact]->material_code,
        invoice->invoice_detail_list->invoice_details[interact]->amount
      );
      if (message != OK) return message;
    }
  } else if (invoice->type == EXPORT_INVOICE) {
    for (int interact = 0; interact < invoice->invoice_detail_list->count; interact ++) {
      message = UpdateMaterialQuantityInArchive(
        invoice->invoice_detail_list->invoice_details[interact]->material_code,
        - invoice->invoice_detail_list->invoice_details[interact]->amount
      );
      if (message != OK) return message;
    }
  }
  else return M_PROGRAM_ERROR;

  SaveMaterialListFromArchiveToStorage();
  SaveStaffListFromArchiveToStorage();

  return OK;
}

message_tp UpdateInvoiceInArchive(const char * staff_code, const char * number, Invoice invoice) {
  ivp_invoice_validation_without_strict;

  // Get staff
  Staff staff = GetItemInStaffListByCode(archive->staff_list, staff_code);
  if (IsNull(staff)) return M_STAFF_NOT_FOUND;

  // get invoice
  Invoice _invoice = GetItemInInvoiceListByNumber(staff->invoice_list, number);
  if (_invoice == NULL) return M_NOT_FOUND;

  // invoice number must be same _invoice number
  strcpy(invoice->number, _invoice->number);

  // invoice invoice_detail_list must be same _invoice invoice_detail_list
  invoice->invoice_detail_list = _invoice->invoice_detail_list;

  // tranfer data
  TranferInvoice(_invoice, invoice);

  SaveStaffListFromArchiveToStorage();

  return OK;
}

message_tp DeleteInvoiceInArchive(const char * staff_code, const char * number) {
  // Get staff
  Staff staff = GetItemInStaffListByCode(archive->staff_list, staff_code);
  if (IsNull(staff)) return M_STAFF_NOT_FOUND;

  message_tp message = DeleteItemInInvoiceListByNumber(staff->invoice_list, number);
  if (message != OK) return message;

  SaveStaffListFromArchiveToStorage();

  return OK;
}

Invoice GetInvoiceInArchiveByNumber(const char * number) {
  Invoice invoice;
  for (int interact = 0; interact < archive->staff_list->count; interact ++) {
    invoice = GetItemInInvoiceListByNumber(archive->staff_list->staffs[interact]->invoice_list, number);
    if (invoice != NULL) return invoice;
  }

  return NULL;
}

message_tp DeleteInvoiceInArchiveByNumber(const char * number) {
  Invoice invoice;
  for (int interact = 0; interact < archive->staff_list->count; interact ++) {
    invoice = GetItemInInvoiceListByNumber(archive->staff_list->staffs[interact]->invoice_list, number);
    if (invoice != NULL)
      return DeleteItemInInvoiceListByNumber(archive->staff_list->staffs[interact]->invoice_list, number);
  }

  return M_NOT_FOUND;
}

/* Not safe */

message_tp UpdateInvoiceInArchiveNS(Invoice invoice, Invoice _invoice) {
  ivp_invoice_validation_without_strict;

  // invoice number must be same _invoice number
  strcpy(invoice->number, _invoice->number);

  // invoice invoice_detail_list must be same _invoice invoice_detail_list
  invoice->invoice_detail_list = _invoice->invoice_detail_list;

  // tranfer data
  TranferInvoice(invoice, _invoice);

  return OK;
}

/* Debug */

void ShowInvoiceInArchive(const char * number) {
  Invoice invoice = GetInvoiceInArchiveByNumber(number);
  if (IsNull(invoice)) return;
  ShowInvoice(invoice);
  for(int interact = 0; interact < invoice->invoice_detail_list->count; interact ++) {
    ShowInvoiceDetail(invoice->invoice_detail_list->invoice_details[interact]);
  }
}

void ShowInvoiceListInArchiveByStaff(Staff staff) {
  printf("%s\n-----------------------\n", staff->code);
  ShowInvoiceList(staff->invoice_list);
  printf("-----------------------\n");
}

void ShowInvoiceListInArchive() {
  StaffListEach(archive->staff_list, ShowInvoiceListInArchiveByStaff);
}
