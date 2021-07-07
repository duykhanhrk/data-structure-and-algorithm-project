#ifndef __FRAMES_MATERIAL_SELECTION_LIST__
#define __FRAMES_MATERIAL_SELECTION_LIST__

/* Private key - MLP */

#define MLP_MATERIAL_LIST_ITEMS 22
#define MLP_MATERIAL_LIST_WIDTH 96
#define MLP_MATERIAL_LIST_HEIGHT 28
#define MLP_MATERIAL_LIST_ITEM_WIDTH 96
#define MLP_MATERIAL_LIST_ITEM_HEIGHT 1

#define MLP_ADD_BUTTON_WIDTH 48
#define MLP_ADD_BUTTON_HEIGHT 3

#define MLP_CREATION_FORM_WIDTH 50
#define MLP_CREATION_FORM_HEIGHT 25

#define MLP_UPDATED_FORM_WIDTH 50
#define MLP_UPDATED_FORM_HEIGHT 25

#ifdef __cplusplus
extern "C" {
#endif

Material ActiveMaterialSelectionListFrame(Frame);

#include "material_selection_list.cpp"

#ifdef __cplusplus
}
#endif

#endif
