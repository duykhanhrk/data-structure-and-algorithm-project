/* Invoice detail */

#ifndef __INVOICE_DETAIL
#define __INVOICE_DETAIL

#include <stdlib.h>
#include <string.h>

#include "../support/message/message.h"
#include "../supplies/supplies.h"

/* Limits */

#define INVOICE_DETAIL_LIST_MAX_ITEMS 20

#ifdef __cplusplus
extern "C" {
#endif

typedef struct InvoiceDetailT {
  char supplies_code[SUPPLIES_CODE_MAX_LEN];
  int amount;
  float price;
  float vat;
} InvoiceDetailT, * InvoiceDetail;

typedef struct InvoiceDetailListT {
  int count;
  InvoiceDetailT * items[INVOICE_DETAIL_LIST_MAX_ITEMS];
} InvoiceDetailListT, InvoiceDetailList;

/* Object methods */
InvoiceDetail NewInvoiceDetail(const char *, int, float, float);
void DestroyInvoiceDetail(InvoiceDetail &invoice_detail);

/* List methods */

// New and Destroy
InvoiceDetailList NewInvoiceDetailList();
void DestroyInvoiceDetailList(InvoiceDetailList &);

// Logic
bool IsInvoiceDetailListEmpty(InvoiceDetailList);
bool IsInvoiceDetailListFull(InvoiceDetailList);

// Insert
message_tp AddItemToInvoiceDetailList(InvoiceDetailList &, InvoiceDetail);
message_tp InsertItemToBeginningOfInvoiceDetailList(InvoiceDetailList &, InvoiceDetail);
message_tp InsertItemToEndOfInvoiceDetailList(InvoiceDetailList &, InvoiceDetail);
message_tp InsertItemToInvoiceDetailListByIndex(InvoiceDetailList &, InvoiceDetail, int);

/* Get */
InvoiceDetail GetFirstItemInInvoiceDetailList(InvoiceDetailList);
InvoiceDetail GetLastItemInInvoiceDetailList(InvoiceDetailList);
InvoiceDetail GetInvoiceDetailInListByIndex(InvoiceDetailList, int);

/* Delete */
message_tp RemoveFirstItemInInvoiceDetailList(InvoiceDetailList &);
message_tp RemoveLastItemInInvoiceDetailList(InvoiceDetailList &);
message_tp RemoveItemInInvoiceDetailListByIndex(InvoiceDetailList &, int);
message_tp RemoveItemInInvoiceDetailList(InvoiceDetailList &, InvoiceDetail);

#include "invoice_detail.cpp"

#ifdef __cplusplus
}
#endif

#endif
