#ifndef __FRAMES_STAFF_SELECTION_LIST__
#define __FRAMES_STAFF_SELECTION_LIST__

/* Private key - SLP */

#define SLP_STAFF_LIST_ITEMS 22
#define SLP_STAFF_LIST_WIDTH 96
#define SLP_STAFF_LIST_HEIGHT 24
#define SLP_STAFF_LIST_ITEM_WIDTH 96
#define SLP_STAFF_LIST_ITEM_HEIGHT 1

#define SLP_ADD_BUTTON_WIDTH 48
#define SLP_ADD_BUTTON_HEIGHT 3

#define SLP_CREATION_FORM_WIDTH 50
#define SLP_CREATION_FORM_HEIGHT 25

#define SLP_UPDATED_FORM_WIDTH 50
#define SLP_UPDATED_FORM_HEIGHT 25

#ifdef __cplusplus
extern "C" {
#endif

Staff ActiveStaffSelectionListFrame(Frame);

#include "staff_selection_list.cpp"

#ifdef __cplusplus
}
#endif

#endif
