#include "archivist.h"

/* Init and Destroy */

void InitArchive() {
  archive = (Archive) malloc(sizeof(ArchiveT));
  archive->material_list = NewMaterialList();
  archive->staff_list = NewStaffList();
  archive->depot = NULL;
}

void DestroyArchive() {
  DestroyMaterialList(archive->material_list);
  DestroyStaffList(archive->staff_list);
  free(archive);
}

// OPTIMIZE: depot
void SendToDepot(void * item) {
  archive->depot = item;
}

void * TakeFromDepot() {
  return archive->depot;
  archive->depot = NULL;
}

/* Save support */

void WriteMaterialToFile(Material material, FILE * file) {
  if (material == NULL) return;
  fwrite(material, sizeof(MaterialT), 1, file);
}

void WriteMaterialListToFile(MaterialList material_list, FILE * file) {
  if (material_list == NULL) return;

  // write material to file
  WriteMaterialToFile(material_list->material, file);

  WriteMaterialListToFile(material_list->left_node, file);
  WriteMaterialListToFile(material_list->right_node, file);
}

// Invoice Detail

void WriteInvoiceDetailToFile(InvoiceDetail invoice_detail, FILE * file) {
  if (invoice_detail == NULL) return;
  fwrite(invoice_detail, sizeof(InvoiceDetailT), 1, file);
}

void WriteInvoiceDetailListToFile(InvoiceDetailList invoice_detail_list, FILE * file) {
  if (invoice_detail_list == NULL) return;

  for (int interact = 0; interact < invoice_detail_list->count; interact ++)
    WriteInvoiceDetailToFile(invoice_detail_list->invoice_details[interact], file);
}

// Invoice

void WriteInvoiceToFile(Invoice invoice, FILE * file) {
  if (invoice == NULL) return;

  // Write base info
  fwrite(invoice->number, sizeof(char) * INVOICE_NUMBER_MAX_LEN, 1, file);
  fwrite(&(invoice->created_at), sizeof(time_t), 1, file);
  fwrite(&(invoice->type), sizeof(char), 1, file);

  // Write invoice detail count
  int invoice_detail_list_count = invoice->invoice_detail_list->count;
  fwrite(&invoice_detail_list_count, sizeof(int), 1, file);

  // Write invoice detail list
  WriteInvoiceDetailListToFile(invoice->invoice_detail_list, file);
}

void WriteInvoiceListToFile(InvoiceList invoice_list, FILE * file) {
  if (invoice_list == NULL) return;

  InvoiceNode invoice_node = invoice_list;
  while (invoice_node != NULL) {
    WriteInvoiceToFile(invoice_node->invoice, file);
    invoice_node = invoice_node->next_node;
  }
}

// Staff

void WriteStaffToFile(Staff staff, FILE * file) {
  if (staff == NULL) return;

  // Write base info
  fwrite(staff->code, sizeof(char) * STAFF_CODE_MAX_LEN, 1, file);
  fwrite(staff->first_name, sizeof(char) * STAFF_FIRST_NAME_MAX_LEN, 1, file);
  fwrite(staff->last_name, sizeof(char) * STAFF_LAST_NAME_MAX_LEN, 1, file);
  fwrite(&(staff->sex), sizeof(char), 1, file);

  // Write invoice detail count
  int invoice_list_count = InvoiceListCount(staff->invoice_list);
  fwrite(&invoice_list_count, sizeof(int), 1, file);

  // Write invoice list
  WriteInvoiceListToFile(staff->invoice_list, file);
}

void WriteStaffListToFile(StaffList staff_list, FILE * file) {
  if (staff_list == NULL) return;

  for (int interact = 0; interact < staff_list->count; interact ++)
    WriteStaffToFile(staff_list->staffs[interact], file);
}

/* Save */

message_tp SaveMaterialListFromArchiveToStorage() {
  // Open file
  FILE * file = fopen(MATERIALS_FILE_PATH, "wb");

  // Handle errors
  if (!file) return M_COULD_NOT_OPEN_FILE;

  // Write header
  fwrite("DSAA", 4, 1, file);

  // Write material count
  int material_count = MaterialListCount(archive->material_list);
  fwrite(&material_count, sizeof(int), 1, file);

  // Write content
  WriteMaterialListToFile(archive->material_list, file);

  // Close file
  fclose(file);

  return OK;
}

message_tp SaveStaffListFromArchiveToStorage() {
  // Open file
  FILE * file = fopen(STAFFS_FILE_PATH, "wb");

  // Handle errors
  if (!file) return M_COULD_NOT_OPEN_FILE;

  // Write header
  fwrite("DSAA", 4, 1, file);

  // Write staff list count
  int staff_list_count = archive->staff_list->count;
  fwrite(&staff_list_count, sizeof(int), 1, file);

  // Write content
  WriteStaffListToFile(archive->staff_list, file);

  // Close file
  fclose(file);

  return OK;
}

/* Loadd support */

// Material
Material ReadMaterialFromFile(FILE * file) {
  Material material = NewMaterial();
  fread(material, sizeof(MaterialT), 1, file);

  return material;
}

// Invocie Detail
InvoiceDetail ReadInvoiceDetailFromFile(FILE * file) {
  InvoiceDetail invoice_detail = NewInvoiceDetail();
  fread(invoice_detail, sizeof(InvoiceDetailT), 1, file);

  return invoice_detail;
}

// Invoice
Invoice ReadInvoiceFromFile(FILE * file) {
  Invoice invoice = NewInvoice();

  // Read base info
  fread(invoice->number, sizeof(char) * INVOICE_NUMBER_MAX_LEN, 1, file);
  fread(&(invoice->created_at), sizeof(time_t), 1, file);
  fread(&(invoice->type), sizeof(char), 1, file);

  // Read invoice detail list cout
  int invoice_detail_list_count;
  fread(&invoice_detail_list_count, sizeof(int), 1, file);

  // Read invoice detail list
  InvoiceDetail invoice_detail;
  while (invoice_detail_list_count --) {
    invoice_detail = ReadInvoiceDetailFromFile(file);
    AddItemToInvoiceDetailList(invoice->invoice_detail_list, invoice_detail);
  }

  return invoice;
}

// Staff

Staff ReadStaffFromFile(FILE * file) {
  Staff staff = NewStaff();

  // Read base info
  char buffer[42];
  fread(staff->code, sizeof(char) * STAFF_CODE_MAX_LEN, 1, file);
  fread(staff->first_name, sizeof(char) * STAFF_FIRST_NAME_MAX_LEN, 1, file);
  fread(staff->last_name, sizeof(char) * STAFF_LAST_NAME_MAX_LEN, 1, file);
  fread(&(staff->sex), sizeof(char), 1, file);

  // Read invoice detail count
  int invoice_list_count;
  fread(&invoice_list_count, sizeof(int), 1, file);

  // Read invoice list
  Invoice invoice;
  while (invoice_list_count --) {
    invoice = ReadInvoiceFromFile(file);
    AddItemToInvoiceList(staff->invoice_list, invoice);
  }

  return staff;
}

/* Load */

message_tp LoadMaterialListFromStorageToArchive() {
  // Open file
  FILE * file = fopen(MATERIALS_FILE_PATH,"rb");

  // Handle errors
  if (!file) return M_COULD_NOT_OPEN_FILE;

  // Read header
  char buffer[5];
  buffer[4] = '\0';
  fread(&buffer, 4, 1, file);
  if (strcmp(buffer, "DSAA\0") != 0) return M_UNSUPPORTED_FILE;

  // Read material count
  int material_count = 0;
  fread(&material_count, sizeof(int), 1, file);

  // Read materials
  Material material;
  while (material_count --) {
    material = ReadMaterialFromFile(file);
    AddItemToMaterialList(archive->material_list, material);
  }

  // Close file
  fclose(file);

  return OK;
}

message_tp LoadStaffListFromStorageToArchive() {
  // Open file
  FILE * file = fopen(STAFFS_FILE_PATH,"rb");

  // Handle errors
  if (!file) return M_COULD_NOT_OPEN_FILE;

  // Read header
  char buffer[5];
  buffer[4] = '\0';
  fread(&buffer, 4, 1, file);
  if (strcmp(buffer, "DSAA\0") != 0) return M_UNSUPPORTED_FILE;

  // Read staff list count
  int staff_list_count;
  fread(&staff_list_count, sizeof(int), 1, file);

  // Read staff list
  Staff staff;
  InvoiceNode invoice_node;
  while (staff_list_count --) {
    staff = ReadStaffFromFile(file);
    AddItemToStaffList(archive->staff_list, staff);
  }

  // Close file
  fclose(file);

  return OK;
}
