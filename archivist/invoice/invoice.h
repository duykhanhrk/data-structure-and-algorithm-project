/* Invoice */

#ifndef __ARCHIVIST_INVOICE__
#define __ARCHIVIST_INVOICE__

#include <stdlib.h>
#include <string.h>

#include "../../support/message/message.h"
#include "../../structure/invoice/invoice.h"
#include "../invoice_detail/invoice_detail.h"

extern Archive archive;

#ifdef __cplusplus
extern "C" {
#endif

/* Validation */
message_tp InvoiceValid(Invoice, bool);

/* Standard */
Invoice GetInvoiceInArchiveByCode(const char *, const char *);
message_tp SaveInvoiceToArchive(const char *, Invoice);
message_tp UpdateInvoiceInArchive(const char *, const char *, Invoice);
message_tp DeleteInvoiceInArchive(const char *, const char *);
Invoice GetInvoiceInArchiveByNumber(const char *);
message_tp DeleteInvoiceInArchiveByNumber(const char *);

/* Not safe */
message_tp UpdateInvoiceInArchiveNS(Invoice, Invoice);

/* Debug */
void ShowInvoiceInArchive(const char *);
void ShowInvoiceListInArchiveByStaff(Staff);
void ShowInvoiceListInArchive();

#include "invoice.cpp"

#ifdef __cplusplus
}
#endif

#endif
