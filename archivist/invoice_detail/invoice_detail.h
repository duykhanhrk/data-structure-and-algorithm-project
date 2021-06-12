/* Invoice */

#ifndef __ARCHIVIST_INVOICE_DETAIL__
#define __ARCHIVIST_INVOICE_DETAIL__

#include <stdlib.h>
#include <string.h>

#include "../../support/message/message.h"
#include "../../structure/invoice_detail/invoice_detail.h"

extern Archive archive;

#ifdef __cplusplus
extern "C" {
#endif

/* Logic */
message_tp InvoiceDetailValidation(InvoiceDetail, bool);

#include "invoice_detail.cpp"

#ifdef __cplusplus
}
#endif

#endif
