#include "linear_list.h"

LinearList NewLinearList(int max_items) {
  LinearList linear_list = (LinearList) malloc(sizeof(LinearListT));
  linear_list->data = (void **) malloc(sizeof(void *) * max_items);
  linear_list->max_items = max_items;
  linear_list->count = 0;

  return linear_list;
}

void DestroyLinearList(LinearList &linear_list) {
  free(linear_list->data);
  free(linear_list);
  linear_list = NULL;
}

message_tp AddItemToLinearList(LinearList linear_list, void * item) {
  if (linear_list->count == linear_list->max_items) return M_LIST_IS_FULL;
  linear_list->data[linear_list->count] = item;
  linear_list->count ++;

  return OK;
}

message_tp DeteleItemInLinearListByIndex(LinearList linear_list, int index) {
  if (index < 0 || index > linear_list->count) return M_OUT_OF_RANGE;

  for (int interact = index; interact < linear_list->count - 1; interact ++)
    linear_list->data[interact] = linear_list->data[interact + 1];

  linear_list->count --;

  return OK;
}

void * GetItemInLinearListByIndex(LinearList linear_list, int index) {
  if (index < 0 || index > linear_list->count) return NULL;

  return linear_list->data[index];
}
