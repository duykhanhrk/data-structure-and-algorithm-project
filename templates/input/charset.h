/* Character set */
#define NUMERIC_CHAR_SET NumericCharSet
#define ALPHABETIC_CHAR_SET AlphabeticCharSet

#define CharactorSetPrototype(chs_name) char (*chs_name)(char)
#define CharactorSetInit(chs_name) char chs_name(char c)
#define CharactorSetCall(chs_name) chs_name(c)
#define CharactorSetHandle(chs_name) \
        CharactorSetCall(chs_name)

// Numberic character set
CharactorSetInit(NumericCharSet) {
  if (IsNumericChar(c)) return c;

  return '\0';
}

// Alphabetic character set
CharactorSetInit(AlphabeticCharSet) {
  if (IsAlphabeticChar(c)) return c;

  return '\0';
}
