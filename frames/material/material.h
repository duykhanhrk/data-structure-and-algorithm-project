#ifndef __HANDLER_MATERIAL__
#define __HANDLER_MATERIAL__

/* Private key - MTP */

#include "../../archivist/material/material.h"
#include "creation_form.h"
#include "updated_form.h"

#define MTP_MATERIAL_LIST_ITEMS 22
#define MTP_MATERIAL_LIST_WIDTH 96
#define MTP_MATERIAL_LIST_HEIGHT 24
#define MTP_MATERIAL_LIST_ITEM_WIDTH 96
#define MTP_MATERIAL_LIST_ITEM_HEIGHT 1

#define MTP_ADD_BUTTON_WIDTH 48
#define MTP_ADD_BUTTON_HEIGHT 3

#define MTP_CREATION_FORM_WIDTH 50
#define MTP_CREATION_FORM_HEIGHT 25

#define MTP_UPDATED_FORM_WIDTH 50
#define MTP_UPDATED_FORM_HEIGHT 21

#ifdef __cplusplus
extern "C" {
#endif

void ActiveMaterialFrame(Frame);

// Private
bool MTPAddButtonConsole(keycode_tp);
void MTPRecovery(Frame);

#include "material.cpp"

#ifdef __cplusplus
}
#endif

#endif
