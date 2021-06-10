#include "invoice.h"

/* -----------------------------------------------------------------------------
Object
----------------------------------------------------------------------------- */

Invoice NewInvoice(
    const char * number = INVOICE_NUMBER_DEFAULT_VALUE,
    time_t created_at = INVOICE_CREATED_AT_DEFAULT_VALUE,
    char type = INVOICE_TYPE_DEFAULT_VALUE,
    InvoiceDetailList invoice_details = INVOICE_INVOICE_DETAILS_DEFAULT_VALUE
) {
  Invoice invoice = (Invoice) malloc(sizeof(InvoiceT));

  strcpy(invoice->number, number);
  invoice->created_at = created_at;
  invoice->type = type;
  invoice->invoice_details = invoice_details;

  return invoice;
}

void DestroyInvoice(Invoice &invoice) {
  DestroyInvoiceDetailList(invoice->invoice_details);
  free(invoice);
  invoice = NULL;
}

void RevokeInvoice(Invoice &invoice) {
  free(invoice);
  invoice = NULL;
}

void ReplaceInvoice(Invoice &invoice, Invoice _invoice) {
  RevokeInvoice(_invoice);
  invoice = _invoice;
}

void TranferInvoice(Invoice invoice, Invoice _invoice) {
  strcpy(invoice->number, _invoice->number);
  invoice->created_at = _invoice->created_at;
  invoice->type = _invoice->type;
  invoice->invoice_details = _invoice->invoice_details;

  RevokeInvoice(_invoice);
}

void CopyInvoice(Invoice invoice, Invoice _invoice) {
  strcpy(invoice->number, _invoice->number);
  invoice->created_at = _invoice->created_at;
  invoice->type = _invoice->type;
  invoice->invoice_details = _invoice->invoice_details;
}

Invoice DuplicateInvoice(Invoice invoice) {
  return NewInvoice(
    invoice->number,
    invoice->created_at,
    invoice->type,
    invoice->invoice_details
  );
}

/* -----------------------------------------------------------------------------
Node
----------------------------------------------------------------------------- */

InvoiceNode NewInvoiceNode(Invoice invoice) {
  InvoiceNode invoice_node = (InvoiceNode) malloc(sizeof(InvoiceNodeT));
  invoice_node->invoice = invoice;
  invoice_node->next_node = NULL;

  return invoice_node;
}

void DestroyInvoiceNode(InvoiceNode &invoice_node) {
  DestroyInvoice(invoice_node->invoice);
  free(invoice_node);
  invoice_node = NULL;
}

/* -----------------------------------------------------------------------------
List
----------------------------------------------------------------------------- */

InvoiceList NewInvoiceList() {
  return NULL;
}

void DestroyInvoiceList(InvoiceList &invoice_list) {
  InvoiceNode interact = invoice_list;
  InvoiceNode _interact = NULL;

  while (interact != NULL) {
    _interact = interact->next_node;
    DestroyInvoiceNode(interact);
    interact = _interact;
  }
}

// Logic

bool IsInvoiceListEmpty(InvoiceList invoice_list) {
  return (invoice_list == NULL);
}

bool IsNumberInInvoiceList(InvoiceList invoice_list, const char * number) {
  InvoiceNode interact = invoice_list;
  while (interact != NULL && strcmp(interact->invoice->number, number) != 0)
    interact = interact->next_node;

  return (interact != NULL);
}

bool IsInInvoiceList(InvoiceList invoice_list, Invoice invoice) {
  InvoiceNode interact = invoice_list;
  while (interact != NULL && interact->invoice == invoice)
    interact = interact->next_node;

  return (interact == NULL);
}

// count

int InvoiceListCount(InvoiceList invoice_list) {
  int count = 0;

  InvoiceNode interact = invoice_list;
  while (interact != NULL) {
    interact = interact->next_node;
    count ++;
  }

  return count;
}

// Insert

message_tp AddItemToInvoiceList(InvoiceList &invoice_list, Invoice invoice) {
  if (invoice_list == NULL) {
    invoice_list = NewInvoiceNode(invoice);
    return OK;
  }

  InvoiceNode interact = invoice_list;
  while (interact->next_node != NULL) interact = interact->next_node;

  interact->next_node = NewInvoiceNode(invoice);

  return OK;
}

message_tp InsertItemToBeginningOfInvoiceList(InvoiceList &invoice_list, Invoice invoice) {
  InvoiceNode _invoice_node = invoice_list;
  invoice_list = NewInvoiceNode(invoice);
  invoice_list->next_node = _invoice_node;

  return OK;
}

message_tp InsertItemToEndOfInvoiceList(InvoiceList &invoice_list, Invoice invoice) {
  if (invoice_list == NULL) {
    invoice_list = NewInvoiceNode(invoice);
    return OK;
  }

  InvoiceNode interact = invoice_list;
  while (interact->next_node != NULL) interact = interact->next_node;

  interact->next_node = NewInvoiceNode(invoice);;

  return OK;
}

message_tp InsertItemToInvoiceListByIndex(InvoiceList &invoice_list, Invoice invoice, int index) {
  if (index < 0 || index > InvoiceListCount(invoice_list))
    return MESSAGE_OUT_OF_RANGE;

  InvoiceNode invoice_node = invoice_list;
  while (index --) invoice_node = invoice_node->next_node;

  if (invoice_node == NULL)
    invoice_list = NewInvoiceNode(invoice);
  else if (invoice_node->next_node == NULL)
    invoice_node = NewInvoiceNode(invoice);
  else {
    InvoiceNode _invoice_node = invoice_node->next_node;
    invoice_node = NewInvoiceNode(invoice);
    invoice_node = _invoice_node;
  }

  return OK;
}

/* Get */
Invoice GetFirstItemInInvoiceList(InvoiceList invoice_list) {
  if (invoice_list == NULL) return NULL;

  return invoice_list->invoice;
}

Invoice GetLastItemInInvoiceList(InvoiceList invoice_list) {
  if (invoice_list == NULL) return NULL;

  InvoiceNode interact = invoice_list;
  while (interact->next_node != NULL) interact = interact->next_node;

  return interact->invoice;
}

Invoice GetItemInInvoiceListByNumber(InvoiceList invoice_list, const char * number) {
  InvoiceNode interact = invoice_list;
  while (interact != NULL && strcmp(interact->invoice->number, number) != 0)
    interact = interact->next_node;

  if (interact == NULL) return NULL;

  return interact->invoice;
}

Invoice GetItemInInvoiceListByIndex(InvoiceList invoice_list, int index) {
  InvoiceNode interact = invoice_list;
  while (interact != NULL && index --)
    interact = interact->next_node;

  if (interact == NULL) return NULL;

  return interact->invoice;
}

/* Delete */
message_tp DeleteFirstItemInInvoiceList(InvoiceList &invoice_list) {
  if (invoice_list == NULL) return BAD;

  InvoiceNode _invoice_node = invoice_list->next_node;
  DestroyInvoiceNode(invoice_list);
  invoice_list = _invoice_node;

  return OK;
}

message_tp DeleteLastItemInInvoiceList(InvoiceList &invoice_list) {
  if (invoice_list == NULL) return BAD;

  InvoiceNode _invoice_node = invoice_list->next_node;
  DestroyInvoiceNode(invoice_list);
  invoice_list = _invoice_node;

  return OK;
}

message_tp DeleteItemInInvoiceListByCode(InvoiceList &invoice_list, const char * number) {
  if (invoice_list == NULL) return BAD;

  InvoiceNode interact = invoice_list;
  InvoiceNode _interact = NULL;
  while (interact != NULL && strcmp(interact->invoice->number, number) != 0) {
    _interact = interact;
    interact = interact->next_node;
  }

  if (interact == NULL) return BAD;

  if (_interact == NULL) {
    invoice_list = interact->next_node;
    DestroyInvoiceNode(_interact);
  } else {
    _interact = interact->next_node;
    DestroyInvoiceNode(interact);
  }

  return OK;
}

message_tp DeleteItemInInvoiceListByIndex(InvoiceList &invoice_list, int index) {
  InvoiceNode interact = invoice_list;
  InvoiceNode _interact = NULL;
  while (interact != NULL && index --) {
    _interact == interact;
    interact = interact->next_node;
  }

  if (interact == NULL) return BAD;

  if (_interact == NULL) {
    invoice_list = interact->next_node;
    DestroyInvoiceNode(_interact);
  } else {
    _interact = interact->next_node;
    DestroyInvoiceNode(interact);
  }

  return OK;
}

message_tp DeleteItemInInvoiceList(InvoiceList &invoice_list, Invoice invoice) {
  InvoiceNode interact = invoice_list;
  InvoiceNode _interact = NULL;
  while (interact != NULL && interact->invoice == invoice) {
    _interact == interact;
    interact = interact->next_node;
  }

  if (interact == NULL) return BAD;

  if (_interact == NULL) {
    invoice_list = interact->next_node;
    DestroyInvoiceNode(_interact);
  } else {
    _interact = interact->next_node;
    DestroyInvoiceNode(interact);
  }

  return OK;
}

/* Show */

void ShowInvoice(Invoice invoice, const char * format = INVOICE_SHOW_FORMAT_DEFAULT) {
  printf(
      format,
      invoice->number,
      invoice->created_at,
      invoice->type
  );
}

void ShowInvoiceList(InvoiceList invoice_list, const char * format = INVOICE_LIST_SHOW_FORMAT_DEFAULT) {
  for (InvoiceNode interact = invoice_list; interact != NULL; interact = interact->next_node)
    ShowInvoice(interact->invoice, format);
}
