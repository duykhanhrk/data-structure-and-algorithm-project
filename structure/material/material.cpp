#include "material.h"

/* -----------------------------------------------------------------------------
Object
----------------------------------------------------------------------------- */

Material NewMaterial(
    const char * code = MATERIAL_CODE_DEFAULT_VALUE,
    const char * name = MATERIAL_NAME_DEFAULT_VALUE,
    const char * unit = MATERIAL_UNIT_DEFAULT_VALUE,
    int quantity = MATERIAL_QUANTITY_DEFAULT_VALUE
) {
  Material material = (Material) malloc(sizeof(MaterialT));
  strcpy(material->code, code);
  strcpy(material->name, name);
  strcpy(material->unit, unit);
  material->quantity = quantity;

  return material;
}

void DestroyMaterial(Material &material) {
  free(material);
  material = NULL;
}

void RevokeMaterial(Material &material) {
  free(material);
  material = NULL;
}

void ReplaceMaterial(Material &material, Material _material) {
  RevokeMaterial(material);
  material = _material;
}

void TranferMaterial(Material material, Material &_material) {
  strcpy(material->code, _material->code);
  strcpy(material->name, _material->name);
  strcpy(material->unit, _material->unit);
  material->quantity = _material->quantity;

  RevokeMaterial(_material);
}

void CopyMaterial(Material material, Material _material) {
  strcpy(material->code, _material->code);
  strcpy(material->name, _material->name);
  strcpy(material->unit, _material->unit);
  material->quantity = _material->quantity;
}

Material DuplicateMaterial(Material material) {
  return NewMaterial(
    material->code,
    material->name,
    material->unit,
    material->quantity
  );
}

/* -----------------------------------------------------------------------------
Node
----------------------------------------------------------------------------- */

MaterialNode NewMaterialNode(Material material) {
  MaterialNode material_node = (MaterialNode) malloc(sizeof(MaterialNodeT));
  material_node->material = material;
  material_node->left_node = NULL;
  material_node->right_node = NULL;

  return material_node;
}

void DestroyMaterialNode(MaterialNode &material_node) {
  free(material_node);
  material_node = NULL;
}

/* -----------------------------------------------------------------------------
List
----------------------------------------------------------------------------- */

MaterialList NewMaterialList() {
  return NULL;
}

void DestroyMaterialList(MaterialList &material_list) {
  if (material_list == NULL) return;
  DestroyMaterialList(material_list->left_node);
  DestroyMaterialList(material_list->right_node);
  DestroyMaterialNode(material_list);
  material_list = NULL;
}

/* Logic */

bool IsMaterialListEmpty(MaterialList material_list) {
  return (material_list == NULL);
}

bool IsCodeInMaterialList(MaterialList material_list, const char * code) {
  if (material_list == NULL) return false;

  if (strcmp(code, material_list->material->code) < 0)
    return IsCodeInMaterialList(material_list->left_node, code);

  if (strcmp(code, material_list->material->code) > 0)
    return IsCodeInMaterialList(material_list->right_node, code);

  return true;
}

bool IsInMaterialList(MaterialList material_list, Material material) {
  if (material_list == NULL) return false;

  if (strcmp(material_list->material->code, material->code) > 0)
    return IsInMaterialList(material_list->left_node, material);

  if (strcmp(material_list->material->code, material->code) < 0)
    return IsInMaterialList(material_list->right_node, material);

  return true;
}

/* count */

int MaterialListCount(MaterialList material_list) {
  if (material_list != NULL)
    return (1 + MaterialListCount(material_list->left_node) + MaterialListCount(material_list->right_node));

  return 0;
}

/* Add */

message_tp AddItemToMaterialList(MaterialList &material_list, Material material) {
  if (material_list == NULL) {
    material_list = NewMaterialNode(material);
    return OK;
  }

  if (strcmp(material->code, material_list->material->code) < 0)
    return AddItemToMaterialList(material_list->left_node, material);

  if (strcmp(material->code, material_list->material->code) > 0)
    return AddItemToMaterialList(material_list->right_node, material);

  // Code is not available
  return BAD;
}

/* Update */

message_tp UpdateItemInMaterialList(MaterialList material_list, Material material) {
  if (material_list == NULL)
    return MESSAGE_OBJECT_NOT_FOUND;

  if (strcmp(material_list->material->code, material->code) > 0)
    return UpdateItemInMaterialList(material_list->left_node, material);

  if (strcmp(material_list->material->code, material->code) < 0)
    return UpdateItemInMaterialList(material_list->right_node, material);

  DestroyMaterial(material_list->material);
  material_list->material = material;

  return OK;
}

Material GetItemInMaterialListByCode(MaterialList material_list, const char * code) {
  if (material_list == NULL)
    return NULL;

  if (strcmp(material_list->material->code, code) > 0)
    return GetItemInMaterialListByCode(material_list->left_node, code);

  if (strcmp(material_list->material->code, code) < 0)
    return GetItemInMaterialListByCode(material_list->right_node, code);

  return material_list->material;
}

message_tp DeleteItemInMaterialList(MaterialList &material_list, Material material) {
  if (material_list == NULL)
    return MESSAGE_OBJECT_NOT_FOUND;

  if (strcmp(material_list->material->code, material->code) > 0)
    return DeleteItemInMaterialListByCode(material_list->left_node, material->code);

  if (strcmp(material_list->material->code, material->code) < 0)
    return DeleteItemInMaterialListByCode(material_list->right_node, material->code);

  MaterialList _material_list = material_list;
  if (_material_list->right_node == NULL) material_list = _material_list->left_node;
  else if (_material_list->left_node == NULL) material_list = _material_list->right_node;
  else {
    MaterialList __material_list = _material_list->right_node;
    for (; __material_list->left_node != NULL; __material_list = material_list->left_node);
    material_list->material = __material_list->material;
    _material_list = __material_list;
    __material_list = _material_list->right_node;
  }

  DestroyMaterialNode(_material_list);

  return OK;
}

message_tp DeleteItemInMaterialListByCode(MaterialList &material_list, const char * code) {
  if (material_list == NULL)
    return MESSAGE_OBJECT_NOT_FOUND;

  if (strcmp(material_list->material->code, code) > 0)
    return DeleteItemInMaterialListByCode(material_list->left_node, code);

  if (strcmp(material_list->material->code, code) < 0)
    return DeleteItemInMaterialListByCode(material_list->right_node, code);

  MaterialList _material_list = material_list;
  if (_material_list->right_node == NULL) material_list = _material_list->left_node;
  else if (_material_list->left_node == NULL) material_list = _material_list->right_node;
  else {
    MaterialList __material_list = _material_list->right_node;
    for (; __material_list->left_node != NULL; __material_list = material_list->left_node);
    material_list->material = __material_list->material;
    _material_list = __material_list;
    __material_list = _material_list->right_node;
  }

  DestroyMaterialNode(_material_list);

  return OK;
}

/* -----------------------------------------------------------------------------
Test
----------------------------------------------------------------------------- */

void ShowMaterial(Material material, const char * format = MATERIAL_SHOW_FORMAT_DEFAULT) {
  printf(
      format,
      material->code,
      material->name,
      material->unit,
      material->quantity
  );
}

void ShowMaterialList(MaterialList material_list, const char * format = MATERIAL_LIST_SHOW_FORMAT_DEFAULT) {
  if (material_list == NULL) return;
  ShowMaterialList(material_list->left_node);
  ShowMaterial(material_list->material, format);
  ShowMaterialList(material_list->right_node);
}
