#include "invoice.h"

/* object methods */

Invoice NewInvoice(
    const char * number = "\0",
    time_t created_at = 0,
    char type = 'N'
) {
  Invoice invoice = (Invoice) malloc(sizeof(InvoiceT));

  strcpy(invoice->number, number);
  invoice->created_at = created_at;
  invoice->type = type;
  invoice->invoice_details = NewInvoiceDetailList();

  return invoice;
}

void DesroyInvoice(Invoice &invoice) {
  free(invoice);
  invoice = NULL;
}

/* node methods */

InvoiceNode NewInvoiceNode(Invoice invoice) {
  InvoiceNode invoice_node = (InvoiceNode) malloc(sizeof(InvoiceNodeT));
  invoice_node->invoice = invoice;
  invoice_node->next_node = NULL;

  return invoice_node;
}

void DestroyInvoiceNode(InvoiceNode &invoice_node) {
  free(invoice_node);
  invoice_node = NULL;
}

/* list methods */

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

bool IsInvoiceNumberAvailable(InvoiceList invoice_list, const char * number) {
  InvoiceNode interact = invoice_list;
  while (interact != NULL && strcmp(interact->invoice->number, number) != 0)
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

Invoice GetInvoiceInListByNumber(InvoiceList invoice_list, const char * number) {
  InvoiceNode interact = invoice_list;
  while (interact != NULL && strcmp(interact->invoice->number, number) != 0)
    interact = interact->next_node;

  if (interact == NULL) return NULL;

  return interact->invoice;
}

Invoice GetInvoiceInListByIndex(InvoiceList invoice_list, int index) {
  InvoiceNode interact = invoice_list;
  while (interact != NULL && index --)
    interact = interact->next_node;

  if (interact == NULL) return NULL;

  return interact->invoice;
}

/* Delete */
message_tp RemoveFirstItemInInvoiceList(InvoiceList &invoice_list) {
  if (invoice_list == NULL) return BAD;

  InvoiceNode _invoice_node = invoice_list->next_node;
  DestroyInvoiceNode(invoice_list);
  invoice_list = _invoice_node;

  return OK;
}

message_tp RemoveLastItemInInvoiceList(InvoiceList &invoice_list) {
  if (invoice_list == NULL) return BAD;

  InvoiceNode _invoice_node = invoice_list->next_node;
  DestroyInvoiceNode(invoice_list);
  invoice_list = _invoice_node;

  return OK;
}

message_tp RemoveItemInInvoiceListByCode(InvoiceList &invoice_list, const char * number) {
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

message_tp RemoveItemInInvoiceListByIndex(InvoiceList &invoice_list, int index) {
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

message_tp RemoveItemInInvoiceList(InvoiceList &invoice_list, Invoice invoice) {
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
