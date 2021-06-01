/* material */

/* logic */

bool IsMaterialValid(Material material) {
  if (material == NULL) return false;

  if (material->code == NULL || material->code == "" || strlen(material->code) > MATERIAL_CODE_MAX_LEN)
    return false;

  if (material->name == NULL || material->name == "" || strlen(material->name) > MATERIAL_NAME_MAX_LEN)
    return false;

  if (material->unit == NULL || material->unit == "" || strlen(material->unit) > MATERIAL_UNIT_MAX_LEN)
    return false;

  if (material->quantity < 0)
    return false;

  return true;
}

/* Standard */

message_tp SaveMaterialToArchive(Material material) {
  if (!IsMaterialValid(material)) return M_INVALID;

  return AddItemToMaterialList(archive->material_list, material);
}

message_tp UpdateMaterialInArchive(Material material, Material _material) {
  if (!IsMaterialValid(_material)) return M_INVALID;
  if (!IsInMaterialList(archive->material_list, material)) return M_NOT_FOUND;
  TranferMaterial(material, _material);

  return OK;
}

message_tp DeleteMaterialInArchive(Material material) {
  if (material == NULL) return M_NOT_FOUND;
  return DeleteItemInMaterialList(archive->material_list, material);
}

/* Extend */

Material GetMaterialInArchiveByCode(const char * code) {
  return GetItemInMaterialListByCode(archive->material_list, code);
}

message_tp UpdateMaterialInArchiveByCode(const char * code, Material material) {
  if (!IsMaterialValid(material)) return M_INVALID;

  Material _material = GetItemInMaterialListByCode(archive->material_list, code);
  if (_material == NULL) return M_NOT_FOUND;

  ReplaceMaterial(_material, material);

  return OK;
}

message_tp DeleteMaterialInArchiveByCode(const char * code) {
  return DeleteItemInMaterialListByCode(archive->material_list, code);
}

/* Not safe */

message_tp UpdateMaterialInArchiveNS(Material material, Material _material) {
  if (!IsMaterialValid(_material)) return M_INVALID;
  ReplaceMaterial(material, _material);

  return OK;
}

/* Debug */

void ShowMaterialListInArchive() {
  ShowMaterialList(archive->material_list);
}
