bool b_alloc_table_2_dim(int*** piTable, int iSizeX, int iSizeY) {
	if (iSizeX < 1 || iSizeY < 1 || piTable == nullptr) {
		return false;
	}
	*piTable = new int* [iSizeX];

	for (int i = 0; i < iSizeX; i++) {
		(*piTable)[i] = new int[iSizeY];
	}

	return true;
}