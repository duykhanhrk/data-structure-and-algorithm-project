/* message */

#ifndef __STRUCTURE_SUPPORT_MESSAGE__
#define __STRUCTURE_SUPPORT_MESSAGE__

/* Type */
#define message_tp int

/* Message code table
0: OK             | 0:                               | 0: Void
1:                | 1: Empty | Full | Out | NULL     | 1:
2: Void           | 2: No save                       | 2:
3:                | 3: Not found | exists | comflict | 3:
4:                | 4:                               | 4:
5: Material       | 5: Validates                     | 5:
6: Staff          | 6:                               | 6:
7: Invoice        | 7:                               | 7:
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
#define M_LIST_FULL_FULL 212
#define M_NULL 214
#define M_INVALID 250
#define M_CONFLICT 233

// Staff
#define M_STAFF_NOT_FOUND 631

// Invoice
#define M_INVOICE_NOT_FOUND 731
#define M_INVOICE_NUMBER_INVALID 751
#define M_INVOICE_TYPE_INVALID 753

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
