#include "invoice_detail.h"

// Invoice detail
InvoiceDetail * NewInvoiceDetail(
  const char * supplies_code = "\0",
  int amount = 0,
  float price = 0.0f,
  float vat = 0.0f
) {
  InvoiceDetail * invoice_detail = (InvoiceDetail *) malloc(sizeof(InvoiceDetail));
  strcpy(invoice_detail->supplies_code, supplies_code);
  invoice_detail->amount = amount;
  invoice_detail->price = price;
  invoice_detail->vat = vat;

  return invoice_detail;
}

void DestroyInvoiceDetail(InvoiceDetail * &invoice_detail) {
  free(invoice_detail);
  invoice_detail = NULL;
}

InvoiceDetailList NewInvoiceDetailList() {
  InvoiceDetailList invoice_detail_list;
  invoice_detail_list.count = 0;

  return invoice_detail_list;
}

bool IsInvoiceDetailListEmpty(InvoiceDetailList invoice_detail_list) {
  return (invoice_detail_list.count == 0);
}

bool IsInvoiceDetailListFull(InvoiceDetailList invoice_detail_list) {
  return (invoice_detail_list.count == INVOICE_DETAIL_LIST_MAX_ITEMS);
}

/* Add invoice detail */
error_tp AddInvoiceDetailToList(InvoiceDetailList &invoice_detail_list, InvoiceDetail * invoice_detail) {
  if (invoice_detail_list.count == INVOICE_DETAIL_LIST_MAX_ITEMS)
    return INVOICE_DETAIL_LIST_IS_FULL;

  invoice_detail_list.items[invoice_detail_list.count] = NewInvoiceDetail(
      invoice_detail->supplies_code,
      invoice_detail->amount,
      invoice_detail->price,
      invoice_detail->vat
  );

  invoice_detail_list.count ++;

  return OK;
}

/* Get */

InvoiceDetail * GetFirstInvoiceDetailFromList(InvoiceDetailList invoice_detail_list) {
  if (invoice_detail_list.count == 0) return NULL;

  return invoice_detail_list.items[0];
}

InvoiceDetail * GetLastInvoiceDetailFromList(InvoiceDetailList invoice_detail_list) {
  if (invoice_detail_list.count == 0) return NULL;

  return invoice_detail_list.items[invoice_detail_list.count - 1];
}

InvoiceDetail * GetInvoiceDetailFromListByIndex(InvoiceDetailList invoice_detail_list, int index) {
  if (invoice_detail_list.count == 0 || index < 0 || index > invoice_detail_list.count - 1)
    return NULL;

  return invoice_detail_list.items[index];
}

/* Delete */
error_tp DeleteFirstInvoiceDetailFromList(InvoiceDetailList &invoice_detail_list) {
  if (invoice_detail_list.count == 0) return INVOICE_DETAIL_NOT_FOUND;

  DestroyInvoiceDetail(invoice_detail_list.items[0]);

  for (int interact = 0; interact < invoice_detail_list.count - 2; interact ++)
    invoice_detail_list.items[interact] = invoice_detail_list.items[interact + 1];

  invoice_detail_list.count --;

  return OK;
}

error_tp DeleteLastInvoiceDetailFromList(InvoiceDetailList &invoice_detail_list) {
  if (invoice_detail_list.count == 0) return INVOICE_DETAIL_NOT_FOUND;

  DestroyInvoiceDetail(invoice_detail_list.items[invoice_detail_list.count - 1]);

  return OK;
}

error_tp DeleteInvoiceDetailFromListByIndex(InvoiceDetailList &invoice_detail_list, int index) {
  if (invoice_detail_list.count == 0 || index < 0 || index > invoice_detail_list.count - 1)
    return INVOICE_DETAIL_NOT_FOUND;

  DestroyInvoiceDetail(invoice_detail_list.items[index]);

  for (int interact = index; interact < invoice_detail_list.count - 2; interact ++)
    invoice_detail_list.items[interact] = invoice_detail_list.items[interact + 1];

  invoice_detail_list.count --;

  return OK;
}

void EmptyInvoiceDetailList(InvoiceDetailList &invoice_detail_list) {
  while (invoice_detail_list.count) {
    invoice_detail_list.count --;
    DestroyInvoiceDetail(invoice_detail_list.items[invoice_detail_list.count]);
  }
}
