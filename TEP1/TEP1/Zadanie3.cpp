bool b_dealloc_table_2_dim(int** piTable, int iSizeX, int iSizeY) {
	if (iSizeX < 1 || iSizeY < 1 || piTable == nullptr) {
		return false;
	}

	for (int i = 0; i < iSizeX; i++) {
		delete[] piTable[i];
	}
	delete[] piTable;

	return true;
}