/* Invoice detail */

#ifndef __INVOICE
#define __INVOICE

#include <stdlib.h>
#include <string.h>

#include "../support/message/message.h"
#include "../invoice_detail/invoice_detail.h"

/* Limits */

#define INVOICE_NUMBER_MAX_LEN 20

// Invoice type
#define IMPORT_INVOICE 'N'
#define EXPORT_INVOICE 'X'

#ifdef __cplusplus
extern "C" {
#endif

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

/* Object methods */
Invoice NewInvoice(const char *, time_t, char);
void DestroyInvoice(Invoice &invoice);

/* Node methods */

InvoiceNode NewInvoiceNode(Invoice invoice);
void DestroyInvoiceNode(InvoiceNode &invoice_node);

/* List methods */

// New and Destroy
InvoiceList NewInvoiceList();
void DestroyInvoiceList(InvoiceList &);

// Logic
bool IsInvoiceListEmpty(InvoiceList);
bool IsInvoiceNumberAvailable(InvoiceList, const char *);

// Count
int InvoiceListCount(InvoiceList);

// Insert
message_tp AddItemToInvoiceList(InvoiceList &, Invoice);
message_tp InsertItemToBeginningOfInvoiceList(InvoiceList &, Invoice);
message_tp InsertItemToEndOfInvoiceList(InvoiceList &, Invoice);
message_tp InsertItemToInvoiceListByIndex(InvoiceList &, Invoice, int);

/* Get */
Invoice GetFirstItemInInvoiceList(InvoiceList);
Invoice GetLastItemInInvoiceList(InvoiceList);
Invoice GetInvoiceInListByCode(InvoiceList, const char *);
Invoice GetInvoiceInListByIndex(InvoiceList, int);

/* Delete */
message_tp RemoveFirstItemInInvoiceList(InvoiceList &);
message_tp RemoveLastItemInInvoiceList(InvoiceList &);
message_tp RemoveItemInInvoiceListByCode(InvoiceList &, const char *);
message_tp RemoveItemInInvoiceListByIndex(InvoiceList &, int);
message_tp RemoveItemInInvoiceList(InvoiceList &, Invoice);

#include "invoice.cpp"

#ifdef __cplusplus
}
#endif

#endif
