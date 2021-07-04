#ifndef __FRAMES_INVOICE_DETAIL__
#define __FRAMES_INVOICE_DETAIL__

/* Private key - IDP */

#define IDP_INVOICE_DETAIL_LIST_ITEMS 22
#define IDP_INVOICE_DETAIL_LIST_WIDTH 96
#define IDP_INVOICE_DETAIL_LIST_HEIGHT 24
#define IDP_INVOICE_DETAIL_LIST_ITEM_WIDTH 96
#define IDP_INVOICE_DETAIL_LIST_ITEM_HEIGHT 1

#define IDP_ADD_BUTTON_WIDTH 48
#define IDP_ADD_BUTTON_HEIGHT 3

#define IDP_CREATION_FORM_WIDTH 50
#define IDP_CREATION_FORM_HEIGHT 25

#define IDP_UPDATED_FORM_WIDTH 50
#define IDP_UPDATED_FORM_HEIGHT 25

#include "creation_form.h"
#include "updated_form.h"

#ifdef __cplusplus
extern "C" {
#endif

void ActiveMaterialFrame(Frame);

// Private
bool MTPAddButtonConsole(keycode_tp);
void MTPRecovery(Frame);

#include "invoice_detail.cpp"

#ifdef __cplusplus
}
#endif

#endif
