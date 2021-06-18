/* Express */
#define USHORT_STANDARD_EXPRESS UShortStandardExpress
#define UINT_STANDARD_EXPRESS UIntStandardExpress
#define ULONG_STANDARD_EXPRESS ULongStandardExpress
#define SHORT_STANDARD_EXPRESS ShortStandardExpress
#define INT_STANDARD_EXPRESS IntStandardExpress
#define LONG_STANDARD_EXPRESS LongStandardExpress
#define DATE_STANDARD_EXPRESS DateStandardExpress

#define TWO_DIGITS_USHORT_EXPRESS TwoDigitsUShortExpress

#define ExpressPrototype(express_name) \
        void (*express_name)(char, void_tp, void_tp, void_tp, position_tp, position_tp, color_tp, color_tp)

#define ExpressInit(express_name) \
        void express_name(char c, void_tp obj, void_tp max, void_tp min, position_tp position_x, position_tp position_y, color_tp f_color, color_tp b_color)

#define ExpressCall(express_name) \
        express_name(c, &obj, &max, &min, position_x, position_y, f_color, b_color);

#define ExpressHandle(express_name) \
        ExpressCall(express_name);

/* Standard */

ExpressInit(UShortStandardExpress) {
  printf("%hu", VoidTypeToUShort(obj));
}

ExpressInit(UIntStandardExpress) {
  printf("%u", VoidTypeToUInt(obj));
}

ExpressInit(ULongStandardExpress) {
  printf("%llu", VoidTypeToULong(obj));
}

ExpressInit(ShortStandardExpress) {
  printf("%hi", VoidTypeToShort(obj));
}

ExpressInit(IntStandardExpress) {
  printf("%d", VoidTypeToInt(obj));
}

ExpressInit(LongStandardExpress) {
  printf("%lld", VoidTypeToLong(obj));
}

ExpressInit(DateStandardExpress) {
  time_t t = VoidTypeToDateTime(obj);
  WriteDate(t);
}

/* Using for DateTime Input */
ExpressInit(TwoDigitsUShortExpress) {
  if (VoidTypeToUShort(obj) < 10) printf("0%hu\n", VoidTypeToUShort(obj));
  else printf("%hu\n", VoidTypeToUShort(obj));
}