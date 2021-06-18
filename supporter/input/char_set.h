#ifndef __SUPPORTER_INPUT_CHAR_SET__
#define __SUPPORTER_INPUT_CHAR_SET__

#define NUMERIC_CHAR_SET NumericCharSet
#define ALPHABETIC_CHAR_SET AlphabeticCharSet
#define HUMAN_NAME_FORMAT_CHAR_SET HumanNameFormatCharSet
#define CODE_FORMAT_CHAR_SET CodeFormatCharSet
#define STANDARD_CHAR_SET StandardCharSet

#ifdef __cplusplus
extern "C" {
#endif

// Numberic character set
char NumericCharSet(char c, const char * str = "\0") {
  if (IsNumericChar(c)) return c;

  return '\0';
}

// Alphabetic character set
char AlphabeticCharSet(char c, const char * str = "\0") {
  if (IsAlphabeticChar(c)) return c;

  return '\0';
}

char StandardCharSet(char c, const char * str = "\0") {
  if (!IsAlphabeticChar(c) && !IsNumericChar(c) && !IsUnderscore(c) && !IsSpace(c))
    return '\0';

  if (IsEmptyString(str) && IsSpace(c)) return '\0';
  if (IsSpace(EndOfString(str)) && IsSpace(c)) return '\0';

  return c;
}

char CodeFormatCharSet(char c, const char * str = "\0") {
  if (IsAlphabeticChar(c) || IsNumericChar(c) || IsUnderscore(c))
    return UpcaseChar(c);

  return '\0';
}

char HumanNameFormatCharSet(char c, const char * str = "\0") {
  if (!IsAlphabeticChar(c) && !IsSpace(c)) return '\0';

  if (IsEmptyString(str))
    if (IsSpace(c)) return '\0';
    else return UpcaseChar(c);

  if (IsSpace(EndOfString(str)))
    if (IsSpace(c)) return '\0';
    else return UpcaseChar(c);

  return DowncaseChar(c);
}

#ifdef __cplusplus
}
#endif

#endif
