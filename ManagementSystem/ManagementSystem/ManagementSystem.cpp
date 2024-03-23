#include "Function.h"

int main() {
	SchoolYear *SyList;
	User *StaffList;
	Student *StudentList;
	int numSY;
	loadSchoolYearList(SyList, numSY);
	for (int i = 0; i < numSY; ++i) {
		cout << SyList[i].Name << endl;
	}
	delete[] StaffList;
	delete[] SyList;
	return 0;
}