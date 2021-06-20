#ifndef __FRAMES_STAFF__
#define __FRAMES_STAFF__

/* Private key - STP */

#define STP_STAFF_LIST_ITEMS 22
#define STP_STAFF_LIST_WIDTH 96
#define STP_STAFF_LIST_HEIGHT 24
#define STP_STAFF_LIST_ITEM_WIDTH 96
#define STP_STAFF_LIST_ITEM_HEIGHT 1

#define STP_ADD_BUTTON_WIDTH 48
#define STP_ADD_BUTTON_HEIGHT 3

#define STP_CREATION_FORM_WIDTH 50
#define STP_CREATION_FORM_HEIGHT 25

#define STP_UPDATED_FORM_WIDTH 50
#define STP_UPDATED_FORM_HEIGHT 25

#include "creation_form.h"
#include "updated_form.h"

#ifdef __cplusplus
extern "C" {
#endif

void ActiveMaterialFrame(Frame);

// Private
bool MTPAddButtonConsole(keycode_tp);
void MTPRecovery(Frame);

#include "staff.cpp"

#ifdef __cplusplus
}
#endif

#endif
