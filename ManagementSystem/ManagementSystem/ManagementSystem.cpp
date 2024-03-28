#include "Function.h"

int main() {
	SchoolYear *SyList;
	Node<User> *StaffHead = nullptr;
	//Node<Student> *StudentHead = nullptr;
	bool isStaff; //tru
	int numSY;
	Node<Student> *pStudent = nullptr;
	Node<User> *pUser = nullptr;
	loadStaffFromFile(StaffHead);
	SchoolYear *currentSchoolYear = loadSchoolYearList(SyList, numSY);
	string username, password;
	getline(cin, username);
	getline(cin, password);
	if (checkLogin(isStaff, pUser, pStudent, username, password, currentSchoolYear, StaffHead)) {
		cout << "SUCCESS" << endl;
	}
	else cout << "FAIl" << endl;
	if (isStaff) {
		cout << pUser->data.Fullname;
	}
	else {
		cout << pStudent->data.FirstName;
	}
	/*outputStaffList(StaffHead);*/
	deleteStaffList(StaffHead);
	deleteSchoolYearList(SyList, numSY);
	//delete[] SyList;

	return 0;
}