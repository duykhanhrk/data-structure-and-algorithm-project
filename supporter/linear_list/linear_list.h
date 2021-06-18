#ifndef __SUPPORT_LINEAR_LIST__
#define __SUPPORT_LINEAR_LIST__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct LinearListT {
  void ** data;
  int count;
  int max_items;
} LinearListT, * LinearList;

LinearList NewLinearList(int);
void DestroyLinearList(LinearList &);

message_tp AddItemToLinearList(LinearList, void *);
message_tp DeteleItemInLinearListByIndex(LinearList, int);
void * GetItemInLinearListByIndex(LinearList, int);

/* includes */

#include "linear_list.cpp"

#ifdef __cplusplus
}
#endif

#endif
