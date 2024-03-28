#include "Function.h"

int main() {
	SchoolYear *SyList;
	Node<User> *StaffHead = nullptr;
	//Node<Student> *StudentHead = nullptr;
	int numSY;
	loadStaffFromFile(StaffHead);
	SchoolYear *currentSchoolYear = loadSchoolYearList(SyList, numSY);
	/*outputStaffList(StaffHead);*/
	
	cout << currentSchoolYear->ClassesList[0].Name << endl;
	outputStudentList(currentSchoolYear->ClassesList[0].stHead);
	deleteStaffList(StaffHead);
	deleteSchoolYearList(SyList, numSY);
	//delete[] SyList;
	
	return 0;
}