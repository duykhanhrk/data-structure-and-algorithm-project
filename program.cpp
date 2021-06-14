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

  for (char chr = 'A'; chr <= 'Z'; chr ++) {
    code[0] = chr;
    name[0] = chr;
    unit[0] = chr;

    material = NewMaterial(code, name, unit, ((int) chr) - 64);
    SaveMaterialToArchive(material);
  }
}

void SeedStaff() {
  Staff staff;
  char code[10] = " \0";
  char first_name[32] = "  first name\0";
  char last_name[64] = "  last name\0";
  char sex = FEMALE_STAFF;

  for (char chr = 'A'; chr <= 'Z'; chr ++) {
    code[0] = chr;
    first_name[0] = chr;
    last_name[0] = chr;

    staff = NewStaff(code, first_name, last_name, sex);
    SaveStaffToArchive(staff);
  }
}

message_tp CreateInvoice(const char * staff_code, const char * number, char invoice_type) {
  Invoice invoice = NewInvoice(number, TimeNow(), invoice_type);

  InvoiceDetail invoice_detail;
  invoice_detail = NewInvoiceDetail("Z", 30, 200, 0.55);
  AddItemToInvoiceDetailList(invoice->invoice_detail_list, invoice_detail);

  invoice_detail = NewInvoiceDetail("X", 30, 200, 0.55);
  AddItemToInvoiceDetailList(invoice->invoice_detail_list, invoice_detail);

  invoice_detail = NewInvoiceDetail("Y", 30, 200, 0.55);
  AddItemToInvoiceDetailList(invoice->invoice_detail_list, invoice_detail);

  return SaveInvoiceToArchive(staff_code, invoice);
}

int main() {
  InitArchive();
  SeedMaterial();
  SeedStaff();

  CreateInvoice("A", "12568", IMPORT_INVOICE);
    CreateInvoice("A", "12569", EXPORT_INVOICE);
  ShowInvoiceListInArchive();

//   ShowInvoiceListInArchive();
  ShowMaterialListInArchive();

  DestroyArchive();

  InitArchive();

  LoadStaffListFromStorageToArchive();
  ShowStaffListInArchive();

  DestroyArchive();
  getchar();
  return 0;
}
