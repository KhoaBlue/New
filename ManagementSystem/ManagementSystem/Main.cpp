#include "Function.h"
#include "Menu.h"
#include <stack>

using namespace std;
#define Login 0
#define ForgotPass 1



//Student section: define from 10 - 19
#define StudentMain 10
#define StudentCourse 11
#define StudentResult 12
#define StudentProfile 13
#define StudentChangePass 14


#define StaffMainMenu 3		
#define StaffProfile 5
//Create new School year: 20-29
//Create new Semester: 30 - 39
//Academic infor : 40 - 49
//Result: 50 - 59



int main() {
	SchoolYear *SyList;
	Node<User> *StaffHead = nullptr;
	bool isStaff = false; //true: Staff; false: Student
	int numSY;
	Node<Student> *pStudent = nullptr;
	Node<User> *pUser = nullptr;
	loadStaffFromFile(StaffHead);
	SchoolYear *currentSchoolYear = loadSchoolYearList(SyList, numSY);

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Student Management System", sf::Style::Close);
	window.setFramerateLimit(60);
	int currentPage = Login;	
	stack<int> pageStack;
	LoginMenu *loginMenu = new LoginMenu;
	ForgotPassMenu *forgotPassMenu = new ForgotPassMenu;
	StudentMainMenu *studentMainMenu = new StudentMainMenu;
	while (window.isOpen()) {
		sf::Event ev;
		window.clear(sf::Color::White);
		switch (currentPage) {
			case Login:
				loginMenu->EventHandling(window, ev, studentMainMenu, isStaff, pUser, pStudent, currentSchoolYear, StaffHead, currentPage);
				loginMenu->drawTo(window);
				break;
			case ForgotPass:
				while (window.pollEvent(ev)) {
					if (ev.type == sf::Event::Closed) {
						window.close();
					}
					if (ev.type == sf::Event::MouseButtonPressed) {
						if (forgotPassMenu->butBack.isMouseOver(window)) {
							forgotPassMenu->tbUsername.clearText();
							forgotPassMenu->tbEmail.clearText();
							forgotPassMenu->tbNewPass.clearText();
							currentPage = Login;
						}
						if (forgotPassMenu->butConfirm.isMouseOver(window)) {
							//Check and change Password.
						}
						forgotPassMenu->handleClicking(window);
					}
					if (ev.type == sf::Event::TextEntered) {
						forgotPassMenu->handleTyping(window, ev);
					}
				}
				forgotPassMenu->drawTo(window);
				break;	
			case StudentMain:
				studentMainMenu->EventHandling(window, ev, currentPage, pageStack);
				studentMainMenu->drawTo(window);
				break;
			case StudentCourse:
				while (window.pollEvent(ev)) {
					if (ev.type == sf::Event::Closed) {
						window.close();
					}
				}
				break;
			case StudentResult:
				while (window.pollEvent(ev)) {
					if (ev.type == sf::Event::Closed) {
						window.close();
					}
				}
				break;
			case StudentProfile:
				while (window.pollEvent(ev)) {
					if (ev.type == sf::Event::Closed) {
						window.close();
					}
				}
				break;
			case StudentChangePass:
				while (window.pollEvent(ev)) {
					if (ev.type == sf::Event::Closed) {
						window.close();
					}
				}
				break;
		}
		window.display();		
	}
	 
	updateSchoolYearList(SyList, numSY);
	updateStaffToFile(StaffHead);
	deleteStaffList(StaffHead);
	deleteSchoolYearList(SyList, numSY);
	//delete loginMenu;
	//delete studentMainMenu;
	//delete forgotPassMenu;
	return 0;
}