#include "supplies.h"

/* methods for Supplies */

Supplies * NewSupplies(
    const char * code = SUPPLIES_CODE_DEFAULT_VALUE,
    const char * name = SUPPLIES_NAME_DEFAULT_VALUE,
    const char * unit = SUPPLIES_UNIT_DEFAULT_VALUE,
    int quantity = SUPPLIES_QUANTITY_DEFAULT_VALUE
) {
  Supplies * supplies = (Supplies *) malloc(sizeof(Supplies));
  strcpy(supplies->code, code);
  strcpy(supplies->name, name);
  strcpy(supplies->unit, unit);
  supplies->quantity = quantity;

  return supplies;
}

void DestroySupplies(Supplies * &supplies) {
  free(supplies);
  supplies = NULL;
}

/* methods for SuppliesNode */

SuppliesNode * NewSuppliesNode(Supplies * supplies) {
  SuppliesNode * supplies_node = (SuppliesNode *) malloc(sizeof(SuppliesNode));
  strcpy(supplies_node->data.code, supplies->code);
  strcpy(supplies_node->data.name, supplies->name);
  strcpy(supplies_node->data.unit, supplies->unit);
  supplies_node->data.quantity = supplies->quantity;
  supplies_node->left_node = NULL;
  supplies_node->right_node = NULL;

  return supplies_node;
}

void DestroySuppliesNode(SuppliesNode * &supplies_node) {
  free(supplies_node);
  supplies_node = NULL;
}

/* methods for SuppliesList */

SuppliesList NewSuppliesList() {
  return NULL;
}

/* yes or no */

bool IsSuppliesListEmpty(SuppliesList supplies_list) {
  return (supplies_list == NULL);
}

bool IsSuppliesCodeValid(SuppliesList supplies_list, char * code) {
  if (supplies_list == NULL) return true;

  if (strcmp(supplies->code, supplies_list->data.code) < 0)
    return IsSuppliesCodeValid(supplies_list->left_node);

  if (strcmp(supplies->code, supplies_list->data.code) > 0)
    return IsSuppliesCodeValid(supplies_list->right_node, supplies);

  return false;
}

/* count */

int SuppliesListCount(SuppliesList supplies_list) {
  if (supplies_list != NULL)
    return (1 + SuppliesListCount(supplies_list->left_node) + SuppliesListCount(supplies_list->right_node));

  return 0;
}

/* Add to list */

int AddSuppliesToList(SuppliesList &supplies_list, Supplies * supplies) {
  if (supplies_list == NULL) {
    supplies_list = NewSuppliesNode(supplies);
    return OK;
  }

  if (strcmp(supplies->code, supplies_list->data.code) < 0)
    return AddSuppliesToList(supplies_list->left_node, supplies);

  if (strcmp(supplies->code, supplies_list->data.code) > 0)
    return AddSuppliesToList(supplies_list->right_node, supplies);

  return SUPPLIES_INVALID_CODE;
}

/* Get from list */

Supplies * GetSuppliesFromListByCode(SuppliesList supplies_list, const char * code) {
  if (supplies_list == NULL)
    return NULL;

  if (strcmp(supplies_list->data.code, code) > 0)
    return GetSuppliesFromListByCode(supplies_list->left_node, code);

  if (strcmp(supplies_list->data.code, code) < 0)
    return GetSuppliesFromListByCode(supplies_list->right_node, code);

  return &(supplies_list->data);
}

/* Delete node from list */

int DeleteSuppliesFromListByCode(SuppliesList &supplies_list, const char * code) {
  if (supplies_list == NULL)
    return SUPPLIES_NOT_FOUND;

  if (strcmp(supplies_list->data.code, code) > 0)
    return DeleteSuppliesFromListByCode(supplies_list->left_node, code);

  if (strcmp(supplies_list->data.code, code) < 0)
    return DeleteSuppliesFromListByCode(supplies_list->right_node, code);

  SuppliesList _supplies_list = supplies_list;
  if (_supplies_list->right_node == NULL) supplies_list = _supplies_list->left_node;
  else if (_supplies_list->left_node == NULL) supplies_list = _supplies_list->right_node;
  else {
    SuppliesList __supplies_list = _supplies_list->right_node;
    for (; __supplies_list->left_node != NULL; __supplies_list = supplies_list->left_node);
    supplies_list->data = __supplies_list->data;
    _supplies_list = __supplies_list;
    __supplies_list = _supplies_list->right_node;
  }

  DestroySuppliesNode(_supplies_list);

  return OK;
}

void EmptySeppliesList(SuppliesList &supplies_list) {
  if (supplies_list == NULL) return;
  EmptySeppliesList(supplies_list->left_node);
  EmptySeppliesList(supplies_list->right_node);
  DestroySuppliesNode(supplies_list);
  supplies_list = NULL;
}
