/* Supplies */

#ifndef __SUPPLIES
#define __SUPPLIES

#include <stdlib.h>
#include <string.h>

#include "../support/message/message.h"

/* Limits */

#define SUPPLIES_CODE_MAX_LEN 10
#define SUPPLIES_NAME_MAX_LEN 50
#define SUPPLIES_UNIT_MAX_LEN 5

#ifdef __cplusplus
extern "C" {
#endif

/* structure */

typedef struct SuppliesT {
  char code[SUPPLIES_CODE_MAX_LEN];
  char name[SUPPLIES_NAME_MAX_LEN];
  char unit[SUPPLIES_UNIT_MAX_LEN];
  int quantity;
} SuppliesT, * Supplies;

typedef struct SuppliesNodeT {
  SuppliesT * supplies;
  SuppliesNodeT * left_node;
  SuppliesNodeT * right_node;
} SuppliesNodeT, * SuppliesNode, * SuppliesList;

/* object methods */

Supplies NewSupplies(const char *, const char *, const char *, int);
void DestroySupplies(Supplies &);

/* node methods */
SuppliesNode NewSuppliesNode(Supplies);
void DestroySuppliesNode(SuppliesNode &);

/* list methods */
SuppliesList NewSuppliesList();
void DestroySuppliesList(SuppliesList &);

// Logic
bool IsSuppliesListEmpty(SuppliesList);
bool IsSuppliesCodeValid(SuppliesList, char * code);

// Count
int SuppliesListCount(SuppliesList);

// Add
message_tp AddItemToSuppliesList(SuppliesList &, Supplies);

// Get
Supplies GetItemInSuppliesListByCode(SuppliesList, const char *);

// Remove
message_tp RemoveItemInSuppliesListByCode(SuppliesList &, const char *);

// test
#include "supplies.cpp"

#ifdef __cplusplus
}
#endif

#endif
