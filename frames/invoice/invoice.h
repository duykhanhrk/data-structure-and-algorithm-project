#ifndef __HANDLER_INVOICE__
#define __HANDLER_INVOICE__

/* Private key - IVP */

#include "../../archivist/invoice/invoice.h"
#include "creation_form.h"
#include "show.h"
#include "filter.h"

#define IVP_INVOICE_LIST_ITEMS 22
#define IVP_INVOICE_LIST_WIDTH 96
#define IVP_INVOICE_LIST_HEIGHT 20
#define IVP_INVOICE_LIST_ITEM_WIDTH 96
#define IVP_INVOICE_LIST_ITEM_HEIGHT 1

#define IVP_BUTTON_WIDTH 47
#define IVP_BUTTON_HEIGHT 3

#define IVP_CREATION_FORM_WIDTH 50
#define IVP_CREATION_FORM_HEIGHT 30

#define IVP_UPDATED_FORM_WIDTH 50
#define IVP_UPDATED_FORM_HEIGHT 25

#define IVP_FILTER_FORM_WIDTH 50
#define IVP_FILTER_FORM_HEIGHT 17

#ifdef __cplusplus
extern "C" {
#endif

void ActiveInvoiceFrame(Frame);

// Private
bool IVPAddButtonConsole(keycode_tp);
void IVPRecovery(Frame);

#include "invoice.cpp"

#ifdef __cplusplus
}
#endif

#endif
