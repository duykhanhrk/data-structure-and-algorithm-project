/* Staff */

#ifndef __ARCHIVIST_INVOICE__
#define __ARCHIVIST_INVOICE__

#include <stdlib.h>
#include <string.h>

#include "../../support/message/message.h"
#include "../../structure/invoice/invoice.h"

extern Archive archive;

#ifdef __cplusplus
extern "C" {
#endif

message_tp SaveInvoiceToArchive(Staff, Invoice);
message_tp UpdateInvoiceInArchive(Invoice, Invoice);
message_tp DeleteInvoiceInArchive(Invoice);
void ShowInvoiceListInArchive(const char *);

#include "invoice.cpp"

#ifdef __cplusplus
}
#endif

#endif
