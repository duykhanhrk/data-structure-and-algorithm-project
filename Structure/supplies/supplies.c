#include "supplies.h"

/* object methods */

Supplies NewSupplies(
    const char * code = "\0",
    const char * name = "\0",
    const char * unit = "\0",
    int quantity = 0
) {
  Supplies supplies = (Supplies) malloc(sizeof(SuppliesT));
  strcpy(supplies->code, code);
  strcpy(supplies->name, name);
  strcpy(supplies->unit, unit);
  supplies->quantity = quantity;

  return supplies;
}

void DestroySupplies(Supplies &supplies) {
  free(supplies);
  supplies = NULL;
}

/* node methods */

SuppliesNode NewSuppliesNode(Supplies supplies) {
  SuppliesNode supplies_node = (SuppliesNode) malloc(sizeof(SuppliesNodeT));
  strcpy(supplies_node->supplies.code, supplies->code);
  strcpy(supplies_node->supplies.name, supplies->name);
  supplies_node->supplies.quantity = supplies->quantity;
  strcpy(supplies_node->supplies.unit, supplies->unit);
  supplies_node->left_node = NULL;
  supplies_node->right_node = NULL;

  return supplies_node;
}

void DestroySuppliesNode(SuppliesNode &supplies_node) {
  free(supplies_node);
  supplies_node = NULL;
}

/* list methods */

SuppliesList NewSuppliesList() {
  return NULL;
}

void DestroySeppliesList(SuppliesList &supplies_list) {
  if (supplies_list == NULL) return;
  DestroySeppliesList(supplies_list->left_node);
  DestroySeppliesList(supplies_list->right_node);
  DestroySuppliesNode(supplies_list);
  supplies_list = NULL;
}

/* Logic */

bool IsSuppliesListEmpty(SuppliesList supplies_list) {
  return (supplies_list == NULL);
}

bool IsSuppliesCodeValid(SuppliesList supplies_list, char * code) {
  if (supplies_list == NULL) return true;

  if (strcmp(code, supplies_list->supplies.code) < 0)
    return IsSuppliesCodeValid(supplies_list->left_node, code);

  if (strcmp(code, supplies_list->supplies.code) > 0)
    return IsSuppliesCodeValid(supplies_list->right_node, code);

  return false;
}

/* count */

int SuppliesListCount(SuppliesList supplies_list) {
  if (supplies_list != NULL)
    return (1 + SuppliesListCount(supplies_list->left_node) + SuppliesListCount(supplies_list->right_node));

  return 0;
}

/* Add */

error_tp AddItemToSuppliesList(SuppliesList &supplies_list, Supplies supplies) {
  if (supplies_list == NULL) {
    supplies_list = NewSuppliesNode(supplies);
    return OK;
  }

  if (strcmp(supplies->code, supplies_list->supplies.code) < 0)
    return AddItemToSuppliesList(supplies_list->left_node, supplies);

  if (strcmp(supplies->code, supplies_list->supplies.code) > 0)
    return AddItemToSuppliesList(supplies_list->right_node, supplies);

  return SUPPLIES_INVALID_CODE;
}

/* Get from list */

Supplies GetSuppliesInListByCode(SuppliesList supplies_list, const char * code) {
  if (supplies_list == NULL)
    return NULL;

  if (strcmp(supplies_list->supplies.code, code) > 0)
    return GetSuppliesInListByCode(supplies_list->left_node, code);

  if (strcmp(supplies_list->supplies.code, code) < 0)
    return GetSuppliesInListByCode(supplies_list->right_node, code);

  return &(supplies_list->supplies);
}

/* Delete node from list */
error_tp RemoveItemInSuppliesListByCode(SuppliesList &supplies_list, const char * code) {
  if (supplies_list == NULL)
    return SUPPLIES_NOT_FOUND;

  if (strcmp(supplies_list->supplies.code, code) > 0)
    return RemoveItemInSuppliesListByCode(supplies_list->left_node, code);

  if (strcmp(supplies_list->supplies.code, code) < 0)
    return RemoveItemInSuppliesListByCode(supplies_list->right_node, code);

  SuppliesList _supplies_list = supplies_list;
  if (_supplies_list->right_node == NULL) supplies_list = _supplies_list->left_node;
  else if (_supplies_list->left_node == NULL) supplies_list = _supplies_list->right_node;
  else {
    SuppliesList __supplies_list = _supplies_list->right_node;
    for (; __supplies_list->left_node != NULL; __supplies_list = supplies_list->left_node);
    supplies_list->supplies = __supplies_list->supplies;
    _supplies_list = __supplies_list;
    __supplies_list = _supplies_list->right_node;
  }

  DestroySuppliesNode(_supplies_list);

  return OK;
}
