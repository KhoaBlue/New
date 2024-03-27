#include "Function.h"

int main() {
	SchoolYear *SyList;
	Node<User> *StaffHead = nullptr;
	//Node<Student> *StudentHead = nullptr;
	int numSY;
	loadStaffFromFile(StaffHead);
	SchoolYear *currentSchoolYear = loadSchoolYearList(SyList, numSY);
	/*outputStaffList(StaffHead);*/
	deleteStaffList(StaffHead);
	deleteSchoolYearList(SyList, numSY);
	//delete[] SyList;
	
	return 0;
}