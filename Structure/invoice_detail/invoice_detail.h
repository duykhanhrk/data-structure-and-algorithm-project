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

typedef struct InvoiceDetail {
  char supplies_code[SUPPLIES_CODE_MAX_LEN];
  int amount;
  float price;
  float vat;
} InvoiceDetail;

typedef struct InvoiceDetailList {
  int count;
  InvoiceDetail * items[INVOICE_DETAIL_LIST_MAX_ITEMS];
} InvoiceDetailList;

InvoiceDetail * NewInvoiceDetail(const char *, int, float, float);
void DestroyInvoiceDetail(InvoiceDetail * &invoice_detail);

InvoiceDetailList NewInvoiceDetailList();

/* yes or no */
bool IsInvoiceDetailListEmpty(InvoiceDetailList);
bool IsInvoiceDetailListFull(InvoiceDetailList);

/* Add invoice detail */
error_tp AddInvoiceDetailToList(InvoiceDetailList &, InvoiceDetail *);

/* Get */
InvoiceDetail * GetFirstInvoiceDetailFromList(InvoiceDetailList);
InvoiceDetail * GetLastInvoiceDetailFromList(InvoiceDetailList);
InvoiceDetail * GetInvoiceDetailFromListByIndex(InvoiceDetailList, int);

/* Delete */
error_tp DeleteFirstInvoiceDetailFromList(InvoiceDetailList &);
error_tp DeleteLastInvoiceDetailFromList(InvoiceDetailList &);
error_tp DeleteInvoiceDetailFromListByIndex(InvoiceDetailList &, int);
void EmptyInvoiceDetailList(InvoiceDetailList &);

#include "invoice_detail.cpp"

#ifdef __cplusplus
}
#endif

#endif
