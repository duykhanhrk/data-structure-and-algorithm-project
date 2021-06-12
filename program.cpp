/* Program */

/* Debug */
#include <iostream>
#define show(x) std::cout << x << std::endl;

/* Makers */
#include "support/supporter.h"
#include "structure/structure.h"
#include "archivist/archivist.h"

extern Archive archive;

void SeedMaterial() {
  Material material;
  char code[10] = " \0";
  char name[64] = "  name\0";
  char unit[10] = "  unit\0";

  for (char chr = 'a'; chr <= 'z'; chr ++) {
    code[0] = chr;
    name[0] = chr;
    unit[0] = chr;

    material = NewMaterial(code, name, unit, ((int) chr) - 97);
    SaveMaterialToArchive(material);
  }
}

void SeedStaff() {
  Staff staff;
  char code[10] = " \0";
  char first_name[64] = "  first name\0";
  char last_name[64] = "  last name\0";
  char sex = FEMALE_STAFF;

  for (char chr = 'a'; chr <= 'z'; chr ++) {
    code[0] = chr;
    first_name[0] = chr;
    last_name[0] = chr;

    staff = NewStaff(code, first_name, last_name, sex);
    SaveStaffToArchive(staff);
  }
}

int main() {
  InitArchive();
  SeedMaterial();
  SeedStaff();

  Staff staff = GetStaffInArchiveByCode("a");
  Invoice invoice = NewInvoice("123456789", TimeNow(), IMPORT_INVOICE);
  InvoiceDetail invoice_detail;
  message_tp mess;

  invoice_detail = NewInvoiceDetail("z", 10, 200, 0.5);
  mess = AddItemToInvoiceDetailList(invoice->invoice_details, invoice_detail);
  if (mess != OK) {
    show("Khong luu duoc");
    DestroyInvoiceDetail(invoice_detail);
  }
  invoice_detail = NewInvoiceDetail("z", 1, 200, 0.5);
  mess = AddItemToInvoiceDetailList(invoice->invoice_details, invoice_detail);
  if (mess != OK) {
    show("Khong luu duoc");
    DestroyInvoiceDetail(invoice_detail);
  }
  invoice_detail = NewInvoiceDetail("b", 1, 200, 0.5);
  mess = AddItemToInvoiceDetailList(invoice->invoice_details, invoice_detail);
  if (mess != OK) {
    show("Khong luu duoc");
    DestroyInvoiceDetail(invoice_detail);
  }

  mess = SaveInvoiceToArchive(staff, invoice);
  if (mess != OK) {
    show("Khong luu duoc");
    DestroyInvoice(invoice);
  }

  ShowInvoiceInArchive("123456789");

  DestroyArchive();
  getchar();
  return 0;
}
