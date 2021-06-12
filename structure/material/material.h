/* Material */

#ifndef __STRUCTURE_MATERIAL__
#define __STRUCTURE_MATERIAL__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../support/message/message.h"

#define MATERIAL_CODE_MAX_LEN 10
#define MATERIAL_NAME_MAX_LEN 50
#define MATERIAL_UNIT_MAX_LEN 10

#define MATERIAL_CODE_DEFAULT_VALUE "\0"
#define MATERIAL_NAME_DEFAULT_VALUE "\0"
#define MATERIAL_UNIT_DEFAULT_VALUE "\0"
#define MATERIAL_QUANTITY_DEFAULT_VALUE 0

#define MATERIAL_SHOW_FORMAT_DEFAULT "%-12s %-24s %-10s %d"
#define MATERIAL_LIST_SHOW_FORMAT_DEFAULT "%-12s %-24s %-10s %d\n"

#ifdef __cplusplus
extern "C" {
#endif

/* -----------------------------------------------------------------------------
Struct
----------------------------------------------------------------------------- */

typedef struct MaterialT {
  char code[MATERIAL_CODE_MAX_LEN];
  char name[MATERIAL_NAME_MAX_LEN];
  char unit[MATERIAL_UNIT_MAX_LEN];
  int quantity;
} MaterialT, * Material;

typedef struct MaterialNodeT {
  MaterialT * material;
  MaterialNodeT * left_node;
  MaterialNodeT * right_node;
} MaterialNodeT, * MaterialNode, * MaterialList;

/* -----------------------------------------------------------------------------
Object
----------------------------------------------------------------------------- */
Material NewMaterial(const char *, const char *, const char *, int);
void DestroyMaterial(Material &);
void RevokeMaterial(Material &material);

void TranferMaterial(Material, Material &);
void CopyMaterial(Material, Material);
Material DuplicateMaterial(Material);

/* -----------------------------------------------------------------------------
Node
----------------------------------------------------------------------------- */
MaterialNode NewMaterialNode(Material);
void DestroyMaterialNode(MaterialNode &);

/* -----------------------------------------------------------------------------
List
----------------------------------------------------------------------------- */
MaterialList NewMaterialList();
void DestroyMaterialList(MaterialList &);

bool IsMaterialListEmpty(MaterialList);
bool IsCodeInMaterialList(MaterialList, const char * code);
int MaterialListCount(MaterialList);
message_tp AddItemToMaterialList(MaterialList &, Material);
Material GetItemInMaterialListByCode(MaterialList, const char *);
message_tp DeleteItemInMaterialListByCode(MaterialList &, const char *);

/* -----------------------------------------------------------------------------
Test
----------------------------------------------------------------------------- */
void MaterialListEach(MaterialList, void (* _do) (Material));
void ShowMaterialList(MaterialList, const char *);
void ShowMaterial(Material, const char *);

#include "material.cpp"

#ifdef __cplusplus
}
#endif

#endif
