#include "material.h"

/* rapid - mtp */

#define mtp_material_validation_with_strict message_tp mess = MaterialValidation(material); \
                                            if (mess != OK) return mess

#define mtp_material_validation_without_strict message_tp mess = MaterialValidation(material, false); \
                                               if (mess != OK) return mess

/* validation */

message_tp MaterialValidation(Material material, bool strict = true) {
  if (IsNull(material)) return M_NULL;

  if (strict == true)
  if (IsNull(material->code) || !IsUNUString(material->code) || strlen(material->code) > MATERIAL_CODE_MAX_LEN)
    return M_MATERIAL_CODE_INVALID;

  if (IsNull(material->name) || IsBlankString(material->name) || strlen(material->name) > MATERIAL_NAME_MAX_LEN)
    return M_MATERIAL_NAME_INVALID;

  if (IsNull(material->unit) || IsBlankString(material->unit) || strlen(material->unit) > MATERIAL_UNIT_MAX_LEN)
    return M_MATERIAL_UNIT_INVALID;

  if (IsNegative(material->quantity) || material->quantity > MATERIAL_QUANTITY_MAX_VALUE)
    return M_MATERIAL_QUANTITY_INVALID;

  return OK;
}

/* logic */

bool IsMaterialAvailable(const char * code, int amount) {
  Material material = GetItemInMaterialListByCode(archive->material_list, code);
  if (IsNull(material)) return false;
  if (amount <= 0 || amount > material->quantity) return false;
  return true;
}

/* Standard */

MaterialList MaterialListInArchive() {
  return archive->material_list;
}

int CountMaterialsInArchive() {
  return MaterialListCount(archive->material_list);
}

message_tp UpdateMaterialQuantityInArchive(const char * code, int quantity) {
  Material material = GetItemInMaterialListByCode(archive->material_list, code);
  if (material == NULL) return M_NOT_FOUND;
  if (material->quantity + quantity < 0) return M_MATERIAL_QUANTITY_INVALID;
  material->quantity += quantity;
  return OK;
}

Material GetMaterialInArchive(const char * code) {
  return GetItemInMaterialListByCode(archive->material_list, code);
}

message_tp SaveMaterialToArchive(Material material) {
  mtp_material_validation_with_strict;

  message_tp message = AddItemToMaterialList(archive->material_list, material);
  if (message != OK) return message;

  SaveMaterialListFromArchiveToStorage();
  return OK;
}

message_tp UpdateMaterialInArchive(const char * code, Material material) {
  // validation without strict
  mtp_material_validation_without_strict;

  // get material by code
  Material _material = GetItemInMaterialListByCode(archive->material_list, code);
  if (_material == NULL) return M_NOT_FOUND;

  // _material must be same code with material
  strcpy(material->code, _material->code);

  // tranfer data
  CopyMaterial(_material, material);

  // Save to storage
  SaveMaterialListFromArchiveToStorage();
  return OK;
}

message_tp DeleteMaterialInArchive(const char * code) {
  message_tp message = DeleteItemInMaterialListByCode(archive->material_list, code);
  if (message != OK) return message;

  SaveMaterialListFromArchiveToStorage();
  return OK;
}

/* Not safe */

message_tp UpdateMaterialInArchiveNS(Material _material, Material material) {
  // validation without strict
  mtp_material_validation_without_strict;

  // _material must be same code with material
  strcpy(material->code, _material->code);

  // tranfer data
  CopyMaterial(_material, material);

  return OK;
}

// OPTIMIZE: code grouping
// Sort by name
void ExportMaterialListToLinearList(MaterialNode material_node, LinearList linear_list) {
  if (material_node == NULL) return;
  ExportMaterialListToLinearList(material_node->left_node, linear_list);
  AddItemToLinearList(linear_list, material_node->material);
  ExportMaterialListToLinearList(material_node->right_node, linear_list);
}

void SwapLinearListItems(void * &item, void * &_item) {
  void * t = item;
  item = _item;
  _item = t;
}

void SortMaterialsInLinearListByName(void ** list, int left, int right) {
  int i = left;
  int j = right;
  Material material = (Material) list[(left + right) / 2];
  do
  {
    while (strcmp(((Material) list[i])->name, material->name) < 0) i ++;
    while (strcmp(((Material) list[j])->name, material->name) > 0) j --;
    if (i <= j) {
      SwapLinearListItems(list[i], list[j]);
	    i ++;
	    j --;
   }
  } while (i <= j);
  if (left < j) SortMaterialsInLinearListByName(list, left, j);
  if (i < right) SortMaterialsInLinearListByName(list, i, right);
}

void TakeAllMaterialsInArchiveSortByName(LinearList linear_list) {
  EmptyLinearList(linear_list);
  ExportMaterialListToLinearList(archive->material_list, linear_list);
  if (linear_list->count == 0) return;
  SortMaterialsInLinearListByName(linear_list->data, 0, linear_list->count - 1);
}

// OPTIMIZE: remove redundant code
// OPTIMIZE: suspended
// For list view - suspended
int CountMaterials(void * material_list, void * filter) {
  return MaterialListCount((MaterialList) material_list);
}

void TakeMaterials(void * material_list, void * filter, LinearList linear_list, int offset, int limit) {
  EmptyLinearList(linear_list);
  TakeItemsInMaterialList((MaterialList) material_list, linear_list, offset, limit);
}

// Test - No longer in use
void TakeMaterialsInArchiveTypeV(MaterialNode material_node, LinearList linear_list, int &limit) {
  if (material_node == NULL || limit == 0) return;
  TakeMaterialsInArchiveTypeV(material_node->right_node, linear_list, limit);
  if (limit > 0) {
    AddItemToLinearList(linear_list, material_node->material);
    limit --;
  }
  TakeMaterialsInArchiveTypeV(material_node->left_node, linear_list, limit);
}

/* Top materials in archive */
void TopMaterialInArchive(LinearList linear_list, int limit) {
  EmptyLinearList(linear_list);
  TakeMaterialsInArchiveTypeV(archive->material_list, linear_list, limit);
}

/* Debug */

void ShowMaterialListInArchive() {
  ShowMaterialList(archive->material_list);
}
