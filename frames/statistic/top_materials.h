#ifndef __FRAMES_STATISTIC_TOP_MATERIAL__
#define __FRAMES_STATISTIC_TOP_MATERIAL__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct STMFlexT {
  Material material;
  double total_price;
} STMFlexT, * STMFlex;

typedef struct STMFlexListT {
  STMFlex * stm_flexs;
  int count;
  int max_count;
} STMFlexListT, * STMFlexList;

STMFlex NewSTMFlex(Material material = NULL, double total_price = 0) {
  STMFlex stm_flex = (STMFlex) malloc(sizeof(STMFlexT));
  stm_flex->material = material;
  stm_flex->total_price = total_price;
  return stm_flex;
}

void DestroySTMFlex(STMFlex &stm_flex) {
  free(stm_flex);
  stm_flex = NULL;
}

STMFlexList NewSTMFlexList(int max_count) {
  STMFlexList stm_flex_list = (STMFlexList) malloc(sizeof(STMFlexListT));
  stm_flex_list->stm_flexs = (STMFlex *) malloc(sizeof(STMFlex) * max_count);
  stm_flex_list->max_count = max_count;
  stm_flex_list->count = 0;
  return stm_flex_list;
}

void DestroySTMFlexList(STMFlexList &stm_flex_list) {
  for (int interact = 0; interact < stm_flex_list->count; interact ++)
    DestroySTMFlex(stm_flex_list->stm_flexs[interact]);
  free(stm_flex_list->stm_flexs);
  free(stm_flex_list);
  stm_flex_list = NULL;
}

message_tp AddItemToSTMFlexList(STMFlexList stm_flex_list, STMFlex stm_flex) {
  for (int interact = 0; interact < stm_flex_list->count; interact ++)
    if (stm_flex_list->stm_flexs[interact]->material == stm_flex->material) {
      stm_flex_list->stm_flexs[interact]->total_price += stm_flex->total_price;
      DestroySTMFlex(stm_flex);
      return OK;
    }

  if (stm_flex_list->count == stm_flex_list->max_count) return M_LIST_IS_FULL;
  stm_flex_list->stm_flexs[stm_flex_list->count] = stm_flex;
  stm_flex_list->count ++;
  return OK;
}

void SwapSTMFlexs(STMFlex &stm_flex, STMFlex &_stm_flex) {
  STMFlex __stm_flex = stm_flex;
  stm_flex = _stm_flex;
  _stm_flex = __stm_flex;
}

void SortSTMFlexs(STMFlex * list, int left, int right) {
  int i = left;
  int j = right;
  STMFlex stmf = list[(left + right) / 2];
  do
  {
    while (list[i]->total_price < stmf->total_price) i ++;
    while (list[j]->total_price > stmf->total_price) j --;
    if (i <= j) {
      SwapSTMFlexs(list[i], list[j]);
	    i ++;
	    j --;
   }
  } while (i <= j);
  if (left < j) SortSTMFlexs(list, left, j);
  if (i < right) SortSTMFlexs(list, i, right);
}

void SortSTMFlexList(STMFlexList list) {
  SortSTMFlexs(list->stm_flexs, 0, list->count - 1);
}

void STMTakeTopMaterials(time_t from, time_t to, LinearList linear_list, int limit) {
  STMFlexList list = NewSTMFlexList(MaterialListCount(archive->material_list));

  InvoiceNode invoice_node;
  InvoiceDetail invoice_detail;
  Material material;
  STMFlex stm_flex;
  double total_price;
  message_tp message;
  for (int interact = 0; interact < archive->staff_list->count; interact ++) {
    invoice_node = archive->staff_list->staffs[interact]->invoice_list;
    while (invoice_node != NULL) {
      if (invoice_node->invoice->type == EXPORT_INVOICE && from <= invoice_node->invoice->created_at && invoice_node->invoice->created_at <= to) {
        for (int _interact = 0; _interact < invoice_node->invoice->invoice_detail_list->count; _interact ++) {
          invoice_detail = invoice_node->invoice->invoice_detail_list->invoice_details[_interact];
          material = GetMaterialInArchive(invoice_detail->material_code);
          if (IsNull(material)) continue;
          total_price = invoice_detail->price * invoice_detail->amount;
          total_price += total_price * (invoice_detail->vat / 100.0);
          stm_flex = NewSTMFlex(material, total_price);
          message = AddItemToSTMFlexList(list, stm_flex);
          if (message != OK) {
            EchoStr("Program error!", 0, WINDOW_ROWS - 1);
            DestroySTMFlex(stm_flex);
          }
        }
      }
      invoice_node = invoice_node->next_node;
    }
  }

  // Sort
  SortSTMFlexList(list);

  // Render data
  EmptyLinearList(linear_list);
  if (limit > list->count) limit = list->count;
  for (int interact = 0; interact < limit; interact ++)
    AddItemToLinearList(linear_list, list->stm_flexs[interact]->material);

  // Release
  DestroySTMFlexList(list);
}

#ifdef __cplusplus
}
#endif

#endif
