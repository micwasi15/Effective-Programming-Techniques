#pragma once

void vCopyTable(int iBegIdx, int iEndIdx, int** piSrc, int** piDst) {
	while (iBegIdx <= iEndIdx) {
		(*piDst)[iBegIdx] = (*piSrc)[iBegIdx];
		iBegIdx++;
	}
}