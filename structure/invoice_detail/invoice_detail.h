/* Invoice detail */

#ifndef __STRUCTURE_INVOICE_DETAIL__
#define __STRUCTURE_INVOICE_DETAIL__

#include <stdlib.h>
#include <string.h>

#include "../../support/message/message.h"
#include "../material/material.h"

/* Limits */

#define INVOICE_DETAIL_LIST_MAX_ITEMS 20

#define INVOICE_DETAIL_MATERIAL_CODE_DEFAULT_VALUE "\0"
#define INVOICE_DETAIL_AMOUNT_DEFAULT_VALUE 0
#define INVOICE_DETAIL_PRICE_DEFAULT_VALUE 0.0f
#define INVOICE_DETAIL_VAT_DEFAULT_VALUE 0.0f

#define INVOICE_DETAIL_SHOW_FORMAT_DEFAULT "%-12s %-12d %-12f %-12f\n"
#define INVOICE_DETAIL_LIST_SHOW_FORMAT_DEFAULT "%-12s %-12d %-12f %-12f\n"

#ifdef __cplusplus
extern "C" {
#endif

/* -----------------------------------------------------------------------------
Struct
----------------------------------------------------------------------------- */

typedef struct InvoiceDetailT {
  char material_code[MATERIAL_CODE_MAX_LEN];
  int amount;
  float price;
  float vat;
} InvoiceDetailT, * InvoiceDetail;

typedef struct InvoiceDetailListT {
  int count;
  InvoiceDetailT * invoice_details[INVOICE_DETAIL_LIST_MAX_ITEMS];
} InvoiceDetailListT, * InvoiceDetailList;

/* -----------------------------------------------------------------------------
Object
----------------------------------------------------------------------------- */
InvoiceDetail NewInvoiceDetail(const char *, int, float, float);
void DestroyInvoiceDetail(InvoiceDetail &);
void RevokeInvoiceDetail(InvoiceDetail &);

void TranferInvoiceDetail(InvoiceDetail, InvoiceDetail);
void CopyInvoiceDetail(InvoiceDetail, InvoiceDetail);
InvoiceDetail DuplicateInvoiceDetail(InvoiceDetail);

/* -----------------------------------------------------------------------------
List
----------------------------------------------------------------------------- */
InvoiceDetailList NewInvoiceDetailList();
void DestroyInvoiceDetailList(InvoiceDetailList &);

bool IsInvoiceDetailListEmpty(InvoiceDetailList);
bool IsInvoiceDetailListFull(InvoiceDetailList);
bool IsMaterialCodeInDetailList(InvoiceDetailList, const char *);

message_tp AddItemToInvoiceDetailList(InvoiceDetailList &, InvoiceDetail);
message_tp InsertItemToBeginningOfInvoiceDetailList(InvoiceDetailList &, InvoiceDetail);
message_tp InsertItemToEndOfInvoiceDetailList(InvoiceDetailList &, InvoiceDetail);
message_tp InsertItemToInvoiceDetailListByIndex(InvoiceDetailList &, InvoiceDetail, int);

InvoiceDetail GetFirstItemInInvoiceDetailList(InvoiceDetailList);
InvoiceDetail GetLastItemInInvoiceDetailList(InvoiceDetailList);
InvoiceDetail GetInvoiceDetailInListByIndex(InvoiceDetailList, int);

message_tp DeleteFirstItemInInvoiceDetailList(InvoiceDetailList &);
message_tp DeleteLastItemInInvoiceDetailList(InvoiceDetailList &);
message_tp DeleteItemInInvoiceDetailListByIndex(InvoiceDetailList &, int);

/* -----------------------------------------------------------------------------
Test
----------------------------------------------------------------------------- */
void ShowInvoiceDetail(InvoiceDetail, const char *);
void ShowInvoiceDetailList(InvoiceDetailList, const char *);

#include "invoice_detail.cpp"

#ifdef __cplusplus
}
#endif

#endif
