/* message */

#ifndef __STRUCTURE_SUPPORT_MESSAGE__
#define __STRUCTURE_SUPPORT_MESSAGE__

/* Type */
#define message_tp int

/* Message code table
0: OK             | 0:                               | 0: Void
1:                | 1: Empty | Full | Out | NULL     | 1:
2: Void           | 2: No save                       | 2:
3: File           | 3: Not found | exists | comflict | 3:
4: Program        | 4: Program error                 | 4:
5: Material       | 5: Validates                     | 5:
6: Staff          | 6: Custom                        | 6:
7: Invoice        | 7: Couldn't open | Not support   | 7:
8: Invoice Detail | 8:                               | 8:
9:                | 9:                               | 9:
*/

/* Quickly - No prefix */

#define OK 0
#define BAD 1

/* Prefix 'M' */

#define M_OK 0
#define M_BAD 1
#define M_NOT_FOUND 231
#define M_EXISTS 232
#define M_LIST_IS_EMPTY 211
#define M_LIST_IS_FULL 212
#define M_OUT_OF_RANGE 213
#define M_NULL 214
#define M_INVALID 250
#define M_CONFLICT 233

// Program
#define M_PROGRAM_ERROR 441

// File
#define M_COULD_NOT_OPEN_FILE 371
#define M_UNSUPPORTED_FILE 372

// Staff
#define M_STAFF_NOT_FOUND 631
#define M_STAFF_CODE_INVALID 651
#define M_STAFF_FIRST_NAME_INVALID 652
#define M_STAFF_LAST_NAME_INVALID 653
#define M_STAFF_SEX_INVALID 654

// Invoice
#define M_INVOICE_NOT_FOUND 731
#define M_INVOICE_NUMBER_INVALID 751
#define M_INVOICE_CREATED_AT_INVALID 752
#define M_INVOICE_TYPE_INVALID 753
#define M_INVOICE_INVOICE_DETAILS_INVALID 754
#define M_INVOICE_INVOICE_DETAILS_TOTAL_MATERIALS_INVALID 755

// Invoice Detail
#define M_INVOICE_DETAIL_MATERIAL_CODE_INVALID 851
#define M_INVOICE_DETAIL_AMOUNT_INVALID 852
#define M_INVOICE_DETAIL_PRICE_INVALID 853
#define M_INVOICE_DETAIL_VAT_INVALID 854
#define M_INVOICE_DETAIL_MATERIAL_IS_NOT_AVAILABLE 855

// Material
#define M_MATERIAL_CODE_INVALID 551
#define M_MATERIAL_NAME_INVALID 552
#define M_MATERIAL_UNIT_INVALID 553
#define M_MATERIAL_QUANTITY_INVALID 554

/* Prefix 'MESSAGE' */

#define MESSAGE_OK 0
#define MESSAGE_BAD 1
#define MESSAGE_LIST_IS_EMPTY 211
#define MESSAGE_LIST_IS_FULL 212
#define MESSAGE_OUT_OF_RANGE 213
#define MESSAGE_NULL 214
#define MESSAGE_OBJECT_NOT_FOUND 231
#define MESSAGE_OBJECT_EXISTS 232
#define MESSAGE_CODE_IS_NOT_AVAILABLE 251

#endif
