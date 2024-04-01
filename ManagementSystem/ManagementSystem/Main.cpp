#include "Function.h"
#include "Menu.h"

using namespace std;

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
	//if (isStaff) {
	//	cout << pUser->data.Fullname;
	//}
	//else {
	//	cout << pStudent->data.FirstName;
	//}
	/*outputStaffList(StaffHead);*/
	
	cout << currentSchoolYear->ClassesList[0].Name << endl;
	outputStudentList(currentSchoolYear->ClassesList[0].stHead);
	deleteStaffList(StaffHead);
	deleteSchoolYearList(SyList, numSY);
	//delete[] SyList;

	sf::RenderWindow window(sf::VideoMode(1200, 800), "Student Management System");
	window.setFramerateLimit(60);

	while (window.isOpen()) {
		sf::Event ev;
		while (window.pollEvent(ev)) {
			if (ev.type == sf::Event::Closed) {
				window.close();
			}
			window.clear(sf::Color::White);
			window.display();
		}
	}

	return 0;
}