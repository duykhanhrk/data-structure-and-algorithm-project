void SaveMaterialToArchiveFile(Material material) {
  fwrite(material, sizeof(MaterialT), 1, archive->file);
}

message_tp SaveMaterialsFromArchiveToStorage() {
  // Open file
  archive->file = fopen(MATERIALS_FILE_PATH, "wb");

  // Handle errors
  if (!archive->file) return M_COULD_NOT_OPEN_FILE;

  // Write header
  fwrite("DSAA", 4, 1, archive->file);

  // Write material count
  int material_count = MaterialListCount(archive->material_list);
  fwrite(&material_count, sizeof(int), 1, archive->file);

  // Write content
  MaterialListEach(archive->material_list, SaveMaterialToArchiveFile);

  // Close file
  fclose(archive->file);

  return OK;
}

message_tp SaveStaffsFromArchiveToStorage();
message_tp SaveDateFromArchiveToStorage();

message_tp LoadMaterialsFromStorageToArchive() {
  // Open file
  archive->file = fopen(MATERIALS_FILE_PATH,"rb");

  // Handle errors
  if (!archive->file) return M_COULD_NOT_OPEN_FILE;

  // Read header
  char buffer[5];
  buffer[4] = '\0';
  fread(&buffer, 4, 1, archive->file);
  if (strcmp(buffer, "DSAA\0") != 0) return M_UNSUPPORTED_FILE;

  // Read material count
  int material_count = 0;
  fread(&material_count, sizeof(int), 1, archive->file);

  // Read materials
  Material material;
  while (material_count --) {
    material = NewMaterial();
    fread(material, sizeof(MaterialT), 1, archive->file);
    SaveMaterialToArchive(material);
  }

  // Close file
  fclose(archive->file);

  return OK;
}

message_tp LoadStaffsFromStorageToArchive();
message_tp LoadDataFromStorageToArchive();
