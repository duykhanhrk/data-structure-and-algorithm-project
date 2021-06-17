/* Utilities */

#ifndef __SUPPORT_UTILITY__
#define __SUPPORT_UTILITY__

#include <string.h>

// Type
#define str_tp char *
#define position_tp int
#define color_tp int
#define size_tp int
#define status_tp int
#define keycode_tp char
#define index_tp int
#define visible_tp bool
#define void_tp void *
#define uh_tp unsigned short int
#define ui_tp unsigned int
#define ul_tp unsigned long long int
#define h_tp short int
#define i_tp int
#define l_tp long long int

// Pointer
#define IsNull(x) x == NULL

// Number
#define IsZero(x) x == 0
#define IsOne(x) x == 1
#define IsPositive(x) x > 0
#define IsNegative(x) x < 0

// String
#define IsEmptyString(str) strcmp(str, "\0") == 0

// Char
#define IsAlphabeticCharacter(chr) (('A' <= chr && chr <= 'Z') || ('a' <= chr && chr <= 'z'))
#define IsUpcaseCharacter(chr) ('A' <= chr && chr <= 'Z')
#define IsDowncaseCharacter(chr) ('a' <= chr && chr <= 'z')
#define IsNumericCharacter(chr) ('0' <= chr && chr <= '9')

// Common
#define IsNumericChar(c) (c >= 48 && c <= 57)
#define IsLowercaseChar(c) (c >= 97 && c<= 122)
#define IsUppercaseChar(c) (c >= 65 && c <= 90)
#define IsAlphabeticChar(c) (IsLowercaseChar(c) || IsUppercaseChar(c))
#define IsSpace(c) (c == 32)
#define IsUnderscore(c) (c == 95)
#define CharToInt(c) (c - 48)
#define VoidTypeToUShort(obj) (*((uh_tp *) obj))
#define VoidTypeToUInt(obj) (*((ui_tp *) obj))
#define VoidTypeToULong(obj) (*((ul_tp *) obj))
#define VoidTypeToShort(obj) (*((h_tp *) obj))
#define VoidTypeToInt(obj) (*((i_tp *) obj))
#define VoidTypeToLong(obj) (*((l_tp *) obj))
#define VoidTypeToDateTime(obj) (*((time_t *) obj))
#define NumViolatesMaxValue(num, c, max) ((max - num < max - max/10) || (max - num == max - max/10 && CharToInt(c) > max%10))
#define NumViolatesMinValue(num, c, min) ((min - obj > min - min/10) || (min - obj == min - min/10 && 48 - c < min%10))

#ifdef __cplusplus
extern "C" {
#endif

/* String */

bool IsBlankString(str_tp str) {
  for (char * c = str; *c != '\0'; c ++)
    if (*c != ' ') return false;

  return true;
}

bool IsUNString(str_tp str) {
  for (char * c = str; *c != '\0'; c ++)
    if (!IsUpcaseCharacter(*c) && !IsNumericCharacter(*c))
      return false;

  return true;
}

bool IsNumericString(str_tp str) {
  for (char * c = str; *c != '\0'; c ++)
    if (!IsNumericCharacter(*c))
      return false;

  return true;
}

bool IsASString(str_tp str) {
  for (char * c = str; *c != '\0'; c ++)
    if (!IsAlphabeticCharacter(*c) && *c != ' ') {
      return false;
    }
  return true;
}

#ifdef __cplusplus
}
#endif

#endif
