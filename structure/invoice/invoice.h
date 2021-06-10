/* Invoice detail */

#ifndef __INVOICE
#define __INVOICE

#include <stdlib.h>
#include <string.h>

#include "../../support/message/message.h"
#include "../invoice_detail/invoice_detail.h"

/* Limits */

#define INVOICE_NUMBER_MAX_LEN 20

// Invoice type
#define INVOICE_TYPE_IMPORT 'N'
#define INVOICE_TYPE_EXPORT 'X'

#define INVOICE_NUMBER_DEFAULT_VALUE "\0"
#define INVOICE_CREATED_AT_DEFAULT_VALUE 0
#define INVOICE_TYPE_DEFAULT_VALUE INVOICE_TYPE_IMPORT
#define INVOICE_INVOICE_DETAILS_DEFAULT_VALUE NewInvoiceDetailList()

#define INVOICE_SHOW_FORMAT_DEFAULT "%-12s %-24lld %-5c\n"
#define INVOICE_LIST_SHOW_FORMAT_DEFAULT "%-12s %-24lld %-5c\n"

#ifdef __cplusplus
extern "C" {
#endif

/* -----------------------------------------------------------------------------
Struct
----------------------------------------------------------------------------- */

typedef struct InvoiceT {
  char number[INVOICE_NUMBER_MAX_LEN];
  time_t created_at;
  char type;
  InvoiceDetailList invoice_details;
} InvoiceT, * Invoice;

typedef struct InvoiceNodeT {
  InvoiceT * invoice;
  InvoiceNodeT * next_node;
} InvoiceNodeT, * InvoiceNode, * InvoiceList;

/* -----------------------------------------------------------------------------
Object
----------------------------------------------------------------------------- */
Invoice NewInvoice(const char *, time_t, char, InvoiceDetailList);
void DestroyInvoice(Invoice &);
void RevokeInvoice(Invoice &);

void ReplaceInvoice(Invoice &, Invoice);
void TranferInvoice(Invoice, Invoice);
void CopyInvoice(Invoice, Invoice);
Invoice DuplicateInvoice(Invoice);

/* -----------------------------------------------------------------------------
Node
----------------------------------------------------------------------------- */
InvoiceNode NewInvoiceNode(Invoice invoice);
void DestroyInvoiceNode(InvoiceNode &invoice_node);

/* -----------------------------------------------------------------------------
List
----------------------------------------------------------------------------- */
InvoiceList NewInvoiceList();
void DestroyInvoiceList(InvoiceList &);
bool IsInvoiceListEmpty(InvoiceList);
bool IsNumberInInvoiceList(InvoiceList, const char *);
bool IsInInvoiceList(InvoiceList, Invoice);
int InvoiceListCount(InvoiceList);
message_tp AddItemToInvoiceList(InvoiceList &, Invoice);
message_tp InsertItemToBeginningOfInvoiceList(InvoiceList &, Invoice);
message_tp InsertItemToEndOfInvoiceList(InvoiceList &, Invoice);
message_tp InsertItemToInvoiceListByIndex(InvoiceList &, Invoice, int);
Invoice GetFirstItemInInvoiceList(InvoiceList);
Invoice GetLastItemInInvoiceList(InvoiceList);
Invoice GetItemInInvoiceListByNumber(InvoiceList, const char *);
Invoice GetItemInInvoiceListByIndex(InvoiceList, int);

message_tp DeleteFirstItemInInvoiceList(InvoiceList &);
message_tp DeleteLastItemInInvoiceList(InvoiceList &);
message_tp DeleteItemInInvoiceListByCode(InvoiceList &, const char *);
message_tp DeleteItemInInvoiceList(InvoiceList &, Invoice);
message_tp DeleteItemInInvoiceListByIndex(InvoiceList &, int);

/* -----------------------------------------------------------------------------
List
----------------------------------------------------------------------------- */
void ShowInvoice(Invoice, const char *);
void ShowInvoiceList(InvoiceList, const char *);

#include "invoice.cpp"

#ifdef __cplusplus
}
#endif

#endif
