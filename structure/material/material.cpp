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
  while (material_list != NULL) {
    if (strcmp(code, material_list->material->code) < 0) {
      material_list = material_list->left_node;
      continue;
    }

    if (strcmp(code, material_list->material->code) > 0){
      material_list = material_list->right_node;
      continue;
    }

    return true;
  }

  return false;
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
  return M_CONFLICT;
}

/* Get */

Material GetItemInMaterialListByCode(MaterialList material_list, const char * code) {
  while (material_list != NULL) {
    if (strcmp(code, material_list->material->code) < 0) {
      material_list = material_list->left_node;
      continue;
    }

    if (strcmp(code, material_list->material->code) > 0){
      material_list = material_list->right_node;
      continue;
    }

    return material_list->material;
  }

  return NULL;
}

void TakeItemsInMaterialList(MaterialList material_list, LinearList linear_list, int &offset, int &limit) {
  if (material_list == NULL || limit == 0) return;

  GetItemsInMaterialList(material_list->left_node, linear_list, offset, limit);

  if (offset > 0) {
    offset --;
  } else if (limit > 0) {
    AddItemToLinearList(linear_list, material_list->material);
    limit --;
  }

  GetItemsInMaterialList(material_list->right_node, linear_list, offset, limit);
}

/* Delete */

message_tp DeleteItemInMaterialListByCode(MaterialList &material_list, const char * code) {
  if (material_list == NULL)
    return M_NOT_FOUND;

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

void MaterialListEach(MaterialList material_list, void (* _do) (Material)) {
  if (material_list == NULL) return;
  MaterialListEach(material_list->left_node, _do);
  MaterialListEach(material_list->right_node, _do);
  _do(material_list->material);
}

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
