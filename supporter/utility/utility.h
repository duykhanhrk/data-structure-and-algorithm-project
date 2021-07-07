/* Utilities */

#ifndef __SUPPORT_UTILITY__
#define __SUPPORT_UTILITY__

#include <string.h>
#include <math.h>

// Type
#define str_tp char *
#define position_tp int
#define color_tp int
#define size_tp int
#define status_tp int
#define align_tp char
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

// templates
#define ALIGN_LEFT 'L'
#define ALIGN_RIGHT 'R'
#define ALIGN_CENTER 'C'

#define NORMAL_TEMPLATE 1
#define ACTIVE_TEMPLATE 2

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
#define IsSpecialChar(c) (('!' <= c && c <= '/') || (':' <= c && c <= '@') || ('[' <= c && c <= '`') || ('{' <= c && c <= '~'))
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
#define NumViolatesMinValue(num, c, min) ((min - num > min - min/10) || (min - num == min - min/10 && 48 - c < min%10))
#define IsLeapYear(year) (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))

#ifdef __cplusplus
extern "C" {
#endif

/* String */

// Char
char UpcaseChar(char c) {
  if ('a' <= c && c <= 'z') return c - 32;

  return c;
}

char DowncaseChar(char c) {
  if ('A' <= c && c <= 'Z') return c + 32;

  return c;
}

bool IsBlankString(const char * str) {
  for (const char * c = str; *c != '\0'; c ++)
    if (*c != ' ') return false;

  return true;
}

bool IsUNString(const char * str) {
  if (*str == '\0') return false;
  for (const char * c = str; *c != '\0'; c ++)
    if (!IsUpcaseCharacter(*c) && !IsNumericCharacter(*c))
      return false;

  return true;
}

bool IsUNUString(const char * str) {
  if (*str == '\0') return false;
  for (const char * c = str; *c != '\0'; c ++)
    if (!IsUpcaseCharacter(*c) && !IsNumericCharacter(*c) && !IsUnderscore(*c))
      return false;

  return true;
}

bool IsNumericString(const char * str) {
  if (*str == '\0') return false;
  for (const char * c = str; *c != '\0'; c ++)
    if (!IsNumericCharacter(*c))
      return false;

  return true;
}

bool IsASString(const char * str) {
  if (*str == '\0') return false;
  for (const char * c = str; *c != '\0'; c ++)
    if (!IsAlphabeticCharacter(*c) && *c != ' ') {
      return false;
    }
  return true;
}

bool IsCrestOfStringTypeA(const char * str, const char * _str) {
  const char * c = str;
  const char * _c = _str;
  while (*c != '\0') {
    if (DowncaseChar(*c) != DowncaseChar(*_c) || *_c == '\0') return false;
    c ++;
    _c ++;
  }

  return true;
}

bool IsCharInString(char _c, const char * str) {
  for (const char * c = str; *c != '\0'; c ++)
    if (_c == *c) return true;
  return false;
}

index_tp IndexOfCharInString(char _c, const char * str) {
  int index = 0;
  for (const char * c = str; *c != '\0'; c ++) {
    if (_c == *c) return index;
    index ++;
  }
  return -1;
}

int DigitsOfInt(int num) {
  if (num == 0) return 1;

  int count = 0;
  while (num != 0) {
    num /= 10;
    count ++;
  }

  return count;
}

int DigitsOfLong(long long int num) {
  if (num == 0) return 1;

  int count = 0;
  while (num != 0) {
    num /= 10;
    count ++;
  }

  return count;
}

int DigitOfIntExceptTrailingZeros(int num) {
  int count = 0;
  bool latch = false;
  while (num != 0) {
    if (num % 10 != 0) latch = true;
    if (latch) count ++;
    num /= 10;
  }

  return count;
}

long long int DoubleToLong(double _num) {
  double integral;
  double fractional = modf(_num, &integral);

  return (long long int) integral;
}

// OPTIMIZE: Need a review
int DigitsOfDoubleAfterDot(double _num, int round_to_digit) {
  long long int pot = pow(10, round_to_digit);
  long long int num = DoubleToLong(_num * pot);
  int delta = 0;
  if (num % pot != 0) delta = round_to_digit - DigitsOfLong(num % pot);
  return DigitOfIntExceptTrailingZeros(num % pot) + delta;
}

// Double
int DigitsOfDoubleIncludeDot(double _num, int round_to_digit) {
  long long int pot = pow(10, round_to_digit);
  long long int num = DoubleToLong(_num * pot);
  if (num == 0) return 1;

  int count = 0;
  while (num != 0) {
    num /= 10;
    count ++;
  }

  if (DigitsOfDoubleAfterDot(_num, round_to_digit) != 0)
    count ++;

  return count;
}

long long int RemoveTrailingZerosOfLong(long long int num, int limit = -1) {
  if (num == 0) return  0;
  while (num % 10 == 0 && limit != 0) {
    num /= 10;
    limit --;
  }

  return num;
}

// String char

char EndOfString(const char * str) {
  return str[strlen(str) - 1];
}

char IntToChar(int num) {
  char x = (char) num;
  return (48 + x);
}


// String to Int
int StringToInt(const char * str) {
  bool sign = false;
  if (*str == '-') sign = true;

  int num = 0;
  for (const char * c = str; *c != '\0'; c ++) {
    if (!IsNumericChar(*c)) return 0;
    num = num * 10 + CharToInt(*c);
  }

  return num;
}

// String to double
double StringToDouble(const char * str) {
  bool sign = (*str == '-');
  double num = 0.0f;
  const char * c = str;
  while ( *c != '\0' && *c != '.') {
    if (!IsNumericChar(*c)) return 0;
    num = num * 10 + CharToInt(*c);
    c ++;
  }

  if (*c == '\0') return num;
  c ++;
  double div = 10.0f;
  while (*c != '\0') {
    num += CharToInt(*c) / div;
    div *= 10;
    c ++;
  }

  return num;
}

#ifdef __cplusplus
}
#endif

#endif
