/* Program */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* Debug */
#include <iostream>
#define show(x) std::cout << x << std::endl;

#include "structure/structure.h"
#include "archivist/archivist.h"

extern Archive archive;

int main() {
  InitArchive();

  // Create new Invoice
  Staff staff;
  Invoice invoice;

  staff = NewStaff("code", "first_name", "last_name", STAFF_SEX_FEMALE);
  if (SaveStaffToArchive(staff) != OK) show("Khong luu duoc");

  invoice = NewInvoice("number", time(NULL), INVOICE_TYPE_IMPORT);
  if (SaveInvoiceToArchive(staff, invoice) != OK) show("Khong luu duoc");

  invoice = NewInvoice("number 1", time(NULL), INVOICE_TYPE_IMPORT);
  if (SaveInvoiceToArchive(staff, invoice) != OK) show("Khong luu duoc");

  staff = NewStaff("code 1", "first_name", "last_name", STAFF_SEX_FEMALE);
  if (SaveStaffToArchive(staff) != OK) show("Khong luu duoc");

  invoice = NewInvoice("number 2", time(NULL), INVOICE_TYPE_IMPORT);
  if (SaveInvoiceToArchive(staff, invoice) != OK) show("Khong luu duoc");

  invoice = NewInvoice("number 3", time(NULL), INVOICE_TYPE_IMPORT);
  if (SaveInvoiceToArchive(staff, invoice) != OK) show("Khong luu duoc");

  ShowInvoiceListInArchive();

  // line
  show("---------------------------------------------------------------------");

  // Update
  Invoice _invoice = DuplicateInvoice(invoice);
  _invoice->type = INVOICE_TYPE_EXPORT;
  message_tp t = UpdateInvoiceInArchive(staff, invoice, _invoice);
  if (t != OK) show("Khong cap nhat duoc");
  show(t);

  ShowInvoiceListInArchive();
  // line
  show("---------------------------------------------------------------------");

  // Delete


  ShowStaffListInArchive();

  DestroyArchive();
  system("PAUSE");
  return 0;
}
