/* Supplies */

#ifndef __SUPPLIES
#define __SUPPLIES

#include <stdlib.h>
#include <string.h>

/* Limits */

#define SUPPLIES_CODE_MAX_LEN 10
#define SUPPLIES_NAME_MAX_LEN 50
#define SUPPLIES_UNIT_MAX_LEN 5

/* Default values */

#define SUPPLIES_CODE_DEFAULT_VALUE "\0"
#define SUPPLIES_NAME_DEFAULT_VALUE "\0"
#define SUPPLIES_UNIT_DEFAULT_VALUE "\0"
#define SUPPLIES_QUANTITY_DEFAULT_VALUE 0

/* Errors */

#ifndef error_tp
#define error_tp int
#endif

#ifndef NO_ERRORS
#define NO_ERRORS 0
#endif

#ifndef OK
#define OK 0
#endif

#define SUPPLIES_NO_ERRORS 50
#define SUPPLIES_LIST_IS_EMPTY 51
#define SUPPLIES_NOT_FOUND 53
#define SUPPLIES_VALIDATE_NO_ERRORS 550
#define SUPPLIES_INVALID_CODE 551
#define SUPPLIES_INVALID_NAME 552
#define SUPPLIES_INVALID_UNIT 553
#define SUPPLIES_INVALID_QUANTITY 554


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
  SuppliesT supplies;
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

// Yes or no
bool IsSuppliesListEmpty(SuppliesList);
bool IsSuppliesCodeValid(SuppliesList, char * code);

// Count
int SuppliesListCount(SuppliesList);

// Add to list
error_tp AddItemToSuppliesList(SuppliesList &, Supplies);

// Get from list
Supplies * GetItemInSuppliesListByCode(SuppliesList, const char *);

// Remove node from list
error_tp RemoveItemInSuppliesListByCode(SuppliesList &, const char *);

// test
#include "supplies.c"

#ifdef __cplusplus
}
#endif

#endif
