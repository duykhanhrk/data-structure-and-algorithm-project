/* Invoice detail */

#ifndef __INVOICE_DETAIL
#define __INVOICE_DETAIL

#include <stdlib.h>
#include <string.h>
#include "../supplies/supplies.h"

/* Limits */

#define INVOICE_DETAIL_LIST_MAX_ITEMS 20

/* Errors */

#ifndef error_tp
#define error_tp int
#endif

#ifndef NO_ERRORS
#define NO_ERRORS 0
#endif

#ifndef OK
#define OK 0
#endif

#define INVOICE_DETAIL_NO_ERRORS 80
#define INVOICE_DETAIL_LIST_IS_EMPTY 810
#define INVOICE_DETAIL_LIST_IS_FULL 811
#define INVOICE_DETAIL_NOT_FOUND 83

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
  InvoiceDetail items[INVOICE_DETAIL_LIST_MAX_ITEMS];
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
error_tp AddItemToInvoiceDetailList(InvoiceDetailList &, InvoiceDetail);
error_tp InsertItemToBeginningOfInvoiceDetailList(InvoiceDetailList &, InvoiceDetail);
error_tp InsertItemToEndOfInvoiceDetailList(InvoiceDetailList &, InvoiceDetail);
error_tp InsertItemToInvoiceDetailListByIndex(InvoiceDetailList &, InvoiceDetail, int);


/* Get */
InvoiceDetail GetFirstItemInInvoiceDetailList(InvoiceDetailList);
InvoiceDetail GetLastItemInInvoiceDetailList(InvoiceDetailList);
InvoiceDetail GetInvoiceDetailInListByIndex(InvoiceDetailList, int);

/* Delete */
error_tp RemoveFirstItemInInvoiceDetailList(InvoiceDetailList &);
error_tp RemoveLastItemInInvoiceDetailList(InvoiceDetailList &);
error_tp RemoveItemInInvoiceDetailListByIndex(InvoiceDetailList &, int);
error_tp RemoveItemInInvoice(InvoiceDetailList &, InvoiceDetail);

#include "invoice_detail.cpp"

#ifdef __cplusplus
}
#endif

#endif
