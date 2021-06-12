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

/* Logic */
message_tp IsInvoiceValid(Invoice, bool);

/* Standard */
message_tp SaveInvoiceToArchive(Staff, Invoice);
message_tp UpdateInvoiceInArchive(Staff, Invoice, Invoice);
message_tp DeleteInvoiceInArchive(Staff, Invoice);

/* Extend */
Invoice GetInvoiceInArchiveByCode(Staff, const char * code);
message_tp UpdateInvoiceInArchiveByCode(Staff, const char * code, Invoice);
message_tp DeleteInvoiceInArchiveByCode(Staff, const char * code);

/* Not safe */
message_tp UpdateInvoiceInArchiveNS(Invoice, Invoice);

/* Lazy */
Invoice GetInvoiceInArchiveByNumberLZ(const char *);

/* Debug */
void ShowInvoiceInArchive(const char *);
void ShowInvoiceListInArchiveByStaff(Staff);
void ShowInvoiceListInArchive();


#include "invoice.cpp"

#ifdef __cplusplus
}
#endif

#endif
