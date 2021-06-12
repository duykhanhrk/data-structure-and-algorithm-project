/* Material */

#ifndef __SUPPORT_UTILITY__
#define __SUPPORT_UTILITY__

#include <string.h>

// Type
#define str_tp char *

// Pointer
#define IsNull(x) x == NULL

// Number
#define IsZero(x) x == 0
#define IsOne(x) x == 1
#define IsPositive(x) x > 0
#define IsNegative(x) x < 0

// String
#define IsEmptyString(str) strcmp(str, "\0") == 0

#ifdef __cplusplus
extern "C" {
#endif

/* String */

bool IsBlankString(str_tp str) {
  for (char * c = str; *c != '\0'; c ++)
    if (*c != ' ') return false;

  return true;
}

#ifdef __cplusplus
}
#endif

#endif
