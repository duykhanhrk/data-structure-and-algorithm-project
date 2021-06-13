/* material */

/* rapid - mtp */

#define mtp_material_validation_with_strict message_tp mess = MaterialValidation(material); \
                                            if (mess != OK) return mess

#define mtp_material_validation_without_strict message_tp mess = MaterialValidation(material, false); \
                                               if (mess != OK) return mess

/* validation */

message_tp MaterialValidation(Material material, bool strict = true) {
  if (IsNull(material)) return M_NULL;

  if (strict == true)
  if (IsNull(material->code) || !IsUNString(material->code) || strlen(material->code) > MATERIAL_CODE_MAX_LEN)
    return M_MATERIAL_CODE_INVALID;

  if (IsNull(material->name) || IsBlankString(material->name) || strlen(material->name) > MATERIAL_NAME_MAX_LEN)
    return M_MATERIAL_NAME_INVALID;

  if (IsNull(material->unit) || IsBlankString(material->unit) || strlen(material->unit) > MATERIAL_UNIT_MAX_LEN)
    return M_MATERIAL_UNIT_INVALID;

  if (IsNegative(material->quantity))
    return M_MATERIAL_QUANTITY_INVALID;

  return OK;
}

/* logic */

bool IsMaterialAvailable(const char * code, int amount) {
  Material material = GetItemInMaterialListByCode(archive->material_list, code);
  if (IsNull(material)) return false;
  if (amount <= 0 || amount > material->quantity) return false;

  return true;
}

/* Standard */

Material GetMaterialInArchive(const char * code) {
  return GetItemInMaterialListByCode(archive->material_list, code);
}

message_tp SaveMaterialToArchive(Material material) {
  mtp_material_validation_with_strict;

  message_tp message = AddItemToMaterialList(archive->material_list, material);
  if (message != OK) return message;

  SaveMaterialListFromArchiveToStorage();
  return OK;
}

message_tp UpdateMaterialInArchive(const char * code, Material material) {
  // validation without strict
  mtp_material_validation_without_strict;

  // get material by code
  Material _material = GetItemInMaterialListByCode(archive->material_list, code);
  if (_material == NULL) return M_NOT_FOUND;

  // _material must be same code with material
  strcpy(material->code, _material->code);

  // tranfer data
  TranferMaterial(_material, material);

  // Save to storage
  SaveMaterialListFromArchiveToStorage();
  return OK;
}

message_tp DeleteMaterialInArchive(const char * code) {
  message_tp message = DeleteItemInMaterialListByCode(archive->material_list, code);
  if (message != OK) return message;

  SaveMaterialListFromArchiveToStorage();
  return OK;
}

/* Not safe */

message_tp UpdateMaterialInArchiveNS(Material _material, Material material) {
  // validation without strict
  mtp_material_validation_without_strict;

  // _material must be same code with material
  strcpy(material->code, _material->code);

  // tranfer data
  TranferMaterial(_material, material);

  return OK;
}

/* Debug */

void ShowMaterialListInArchive() {
  ShowMaterialList(archive->material_list);
}
