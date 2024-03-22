#include "Function.h"

int main() {
	SchoolYear *SyList;
	int numSY;
	loadSchoolYearList(SyList, numSY);
	delete[] SyList;
	return 0;
}