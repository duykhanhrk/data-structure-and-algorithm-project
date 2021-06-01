#include "invoice_detail.h"

/* -----------------------------------------------------------------------------
Object
----------------------------------------------------------------------------- */

InvoiceDetail NewInvoiceDetail(
  const char * material_code = INVOICE_DETAIL_MATERIAL_CODE_DEFAULT_VALUE,
  int amount = INVOICE_DETAIL_AMOUNT_DEFAULT_VALUE,
  float price = INVOICE_DETAIL_PRICE_DEFAULT_VALUE,
  float vat = INVOICE_DETAIL_VAT_DEFAULT_VALUE
) {
  InvoiceDetail invoice_detail = (InvoiceDetail) malloc(sizeof(struct InvoiceDetailT));
  strcpy(invoice_detail->material_code, material_code);
  invoice_detail->amount = amount;
  invoice_detail->price = price;
  invoice_detail->vat = vat;

  return invoice_detail;
}

void DestroyInvoiceDetail(InvoiceDetail &invoice_detail) {
  free(invoice_detail);
  invoice_detail = NULL;
}

void RevokeInvoiceDetail(InvoiceDetail &invoice_detail) {
  free(invoice_detail);
  invoice_detail = NULL;
}

void ReplaceInvoiceDetail(InvoiceDetail &invoice_detail, InvoiceDetail _invoice_detail) {
  RevokeInvoiceDetail(_invoice_detail);
  invoice_detail = _invoice_detail;
}

void TranferInvoiceDetail(InvoiceDetail invoice_detail, InvoiceDetail _invoice_detail) {
  strcpy(invoice_detail->material_code, invoice_detail->material_code);
  invoice_detail->amount = _invoice_detail->amount;
  invoice_detail->price = _invoice_detail->price;
  invoice_detail->vat = _invoice_detail->vat;

  RevokeInvoiceDetail(_invoice_detail);
}

void CopyInvoiceDetail(InvoiceDetail invoice_detail, InvoiceDetail _invoice_detail) {
  strcpy(invoice_detail->material_code, invoice_detail->material_code);
  invoice_detail->amount = _invoice_detail->amount;
  invoice_detail->price = _invoice_detail->price;
  invoice_detail->vat = _invoice_detail->vat;
}

InvoiceDetail DuplicateInvoiceDetail(InvoiceDetail invoice_detail) {
  return NewInvoiceDetail(
    invoice_detail->material_code,
    invoice_detail->amount,
    invoice_detail->price,
    invoice_detail->vat
  );
}

/* -----------------------------------------------------------------------------
List
----------------------------------------------------------------------------- */

InvoiceDetailList NewInvoiceDetailList() {
  InvoiceDetailList invoice_detail_list = (InvoiceDetailList) malloc(sizeof(InvoiceDetailListT));
  invoice_detail_list->count = 0;

  return invoice_detail_list;
}

void DestroyInvoiceDetailList(InvoiceDetailList &invoice_detail_list) {
  while (invoice_detail_list->count) {
    invoice_detail_list->count --;
    DestroyInvoiceDetail(invoice_detail_list->invoice_details[invoice_detail_list->count]);
  }

  free(invoice_detail_list);
  invoice_detail_list = NULL;
}

bool IsInvoiceDetailListEmpty(InvoiceDetailList invoice_detail_list) {
  return (invoice_detail_list->count == 0);
}

bool IsInvoiceDetailListFull(InvoiceDetailList invoice_detail_list) {
  return (invoice_detail_list->count == INVOICE_DETAIL_LIST_MAX_ITEMS);
}

message_tp AddItemToInvoiceDetailList(
    InvoiceDetailList &invoice_detail_list,
    InvoiceDetail invoice_detail
) {
  if (invoice_detail_list->count == INVOICE_DETAIL_LIST_MAX_ITEMS)
    return MESSAGE_LIST_IS_FULL;

  invoice_detail_list->invoice_details[invoice_detail_list->count] = NewInvoiceDetail(
      invoice_detail->material_code,
      invoice_detail->amount,
      invoice_detail->price,
      invoice_detail->vat
  );

  invoice_detail_list->count ++;

  return OK;
}

message_tp InsertItemToBeginningOfInvoiceDetailList(
    InvoiceDetailList &invoice_detail_list,
    InvoiceDetail invoice_detail
) {
  if (invoice_detail_list->count == INVOICE_DETAIL_LIST_MAX_ITEMS)
    return MESSAGE_LIST_IS_FULL;

  for (int interact = invoice_detail_list->count; interact > 0; interact --)
    invoice_detail_list->invoice_details[interact] = invoice_detail_list->invoice_details[interact - 1];

  invoice_detail_list->invoice_details[0] = NewInvoiceDetail(
      invoice_detail->material_code,
      invoice_detail->amount,
      invoice_detail->price,
      invoice_detail->vat
  );

  invoice_detail_list->count ++;

  return OK;
}

message_tp InsertItemToEndOfInvoiceDetailList(
    InvoiceDetailList &invoice_detail_list,
    InvoiceDetail invoice_detail
) {
  if (invoice_detail_list->count == INVOICE_DETAIL_LIST_MAX_ITEMS)
    return MESSAGE_LIST_IS_FULL;

  invoice_detail_list->invoice_details[invoice_detail_list->count] = NewInvoiceDetail(
      invoice_detail->material_code,
      invoice_detail->amount,
      invoice_detail->price,
      invoice_detail->vat
  );

  invoice_detail_list->count ++;

  return OK;
}

message_tp InsertItemToInvoiceDetailListByIndex(
    InvoiceDetailList &invoice_detail_list,
    InvoiceDetail invoice_detail,
    int index
) {
  if (invoice_detail_list->count == INVOICE_DETAIL_LIST_MAX_ITEMS)
    return MESSAGE_LIST_IS_FULL;

  for (int interact = invoice_detail_list->count; interact > index; interact --)
    invoice_detail_list->invoice_details[interact] = invoice_detail_list->invoice_details[interact - 1];

  invoice_detail_list->invoice_details[index] = NewInvoiceDetail(
      invoice_detail->material_code,
      invoice_detail->amount,
      invoice_detail->price,
      invoice_detail->vat
  );

  invoice_detail_list->count ++;

  return OK;
}

// Get
InvoiceDetail GetFirstItemInInvoiceDetailList(InvoiceDetailList invoice_detail_list) {
  if (invoice_detail_list->count == 0) return NULL;

  return invoice_detail_list->invoice_details[0];
}

InvoiceDetail GetLastItemInInvoiceDetailList(InvoiceDetailList invoice_detail_list) {
  if (invoice_detail_list->count == 0) return NULL;

  return invoice_detail_list->invoice_details[invoice_detail_list->count - 1];
}

InvoiceDetail GetInvoiceDetailInListByIndex(InvoiceDetailList invoice_detail_list, int index) {
  if (invoice_detail_list->count == 0 || index < 0 || index > invoice_detail_list->count - 1)
    return NULL;

  return invoice_detail_list->invoice_details[index];
}

// Delete

message_tp RemoveFirstItemInInvoiceDetailList(InvoiceDetailList &invoice_detail_list) {
  if (invoice_detail_list->count == 0) return MESSAGE_OBJECT_NOT_FOUND;

  DestroyInvoiceDetail(invoice_detail_list->invoice_details[0]);

  for (int interact = 0; interact < invoice_detail_list->count - 2; interact ++)
    invoice_detail_list->invoice_details[interact] = invoice_detail_list->invoice_details[interact + 1];

  invoice_detail_list->count --;

  return OK;
}

message_tp RemoveLastItemInInvoiceDetailList(InvoiceDetailList &invoice_detail_list) {
  if (invoice_detail_list->count == 0) return MESSAGE_OBJECT_NOT_FOUND;

  DestroyInvoiceDetail(invoice_detail_list->invoice_details[invoice_detail_list->count - 1]);

  return OK;
}

message_tp RemoveItemInInvoiceDetailListByIndex(InvoiceDetailList &invoice_detail_list, int index) {
  if (invoice_detail_list->count == 0 || index < 0 || index > invoice_detail_list->count - 1)
    return MESSAGE_OBJECT_NOT_FOUND;

  DestroyInvoiceDetail(invoice_detail_list->invoice_details[index]);

  for (int interact = index; interact < invoice_detail_list->count - 2; interact ++)
    invoice_detail_list->invoice_details[interact] = invoice_detail_list->invoice_details[interact + 1];

  invoice_detail_list->count --;

  return OK;
}

message_tp RemoveItemInInvoiceDetailList(InvoiceDetailList & invoice_detail_list, InvoiceDetail invoice_detail) {
  for (int interact = 0; interact < invoice_detail_list->count; interact ++)
    if (invoice_detail_list->invoice_details[interact] == invoice_detail)
      return RemoveItemInInvoiceDetailListByIndex(invoice_detail_list, interact);

  return MESSAGE_OBJECT_NOT_FOUND;
}

/* -----------------------------------------------------------------------------
Test
----------------------------------------------------------------------------- */
void ShowInvoiceDetail(
    InvoiceDetail invoice_detail,
    const char * format = INVOICE_DETAIL_SHOW_FORMAT_DEFAULT
) {
  printf(
      format,
      invoice_detail->material_code,
      invoice_detail->amount,
      invoice_detail->price,
      invoice_detail->vat
  );
}

void ShowInvoiceDetailList(
    InvoiceDetailList invoice_detail_list,
    const char * format = INVOICE_DETAIL_LIST_SHOW_FORMAT_DEFAULT
) {
  for (int interact = 0; interact < invoice_detail_list->count; interact ++)
    ShowInvoiceDetail(invoice_detail_list->invoice_details[interact], format);
}
