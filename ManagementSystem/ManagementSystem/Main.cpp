#include "Function.h"
#include "Menu.h"

using namespace std;
#define Login 0
#define ForgotPass 1



//Student section: define from 10 - 19
#define StudentMainMenu 10
#define StudentProfile 11



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
	
	updateSchoolYearList(SyList, numSY);
	updateStaffToFile(StaffHead);

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Student Management System", sf::Style::Close);
	window.setFramerateLimit(60);
	int currentPage = Login;	
	LoginMenu loginMenu;
	ForgotPassMenu forgotPassMenu;
	while (window.isOpen()) {
		sf::Event ev;
		window.clear(sf::Color::White);
		switch (currentPage) {
			case Login:
				while (window.pollEvent(ev)) {
					if (ev.type == sf::Event::Closed) {
						window.close();
					}
					if (ev.type == sf::Event::MouseButtonPressed) {
						if (loginMenu.butLogIn.isMouseOver(window)) {
							string username = loginMenu.tbUsername.text.str();
							string password = loginMenu.tbPassword.text.str();
							if (checkLogin(isStaff, pUser, pStudent, username, password, currentSchoolYear, StaffHead)) {
								currentPage = StudentMainMenu;
								cout << "Login succeeded" << endl;
							}
							else {
								cout << "Login Failed" << endl;
							}
							cout << currentPage << endl;
						}
						if (loginMenu.butForgotPW.isMouseOver(window)) {
							loginMenu.tbUsername.clearText();
							loginMenu.tbPassword.clearText();
							string username = loginMenu.tbUsername.text.str();
							string password = loginMenu.tbPassword.text.str();
							cout << username << " " << password << endl;
							currentPage = ForgotPass;	
						}
						loginMenu.handleClicking(window);
					}
					if (ev.type == sf::Event::TextEntered) {
						loginMenu.handleTyping(window, ev);
					}
				}
				loginMenu.drawTo(window);
				break;
			case ForgotPass:
				while (window.pollEvent(ev)) {
					if (ev.type == sf::Event::Closed) {
						window.close();
					}
					if (ev.type == sf::Event::MouseButtonPressed) {
						if (forgotPassMenu.butBack.isMouseOver(window)) {
							forgotPassMenu.tbUsername.clearText();
							forgotPassMenu.tbEmail.clearText();
							forgotPassMenu.tbNewPass.clearText();
							currentPage = Login;
						}
						if (forgotPassMenu.butConfirm.isMouseOver(window)) {
							//Check and change Password.
						}
						forgotPassMenu.handleClicking(window);
					}
					if (ev.type == sf::Event::TextEntered) {
						forgotPassMenu.handleTyping(window, ev);
					}
				}
				forgotPassMenu.drawTo(window);
				break;	
			case StudentMainMenu:
				while(window.pollEvent(ev)) {
					if (ev.type == sf::Event::Closed) {
						window.close();
					}
				}
				break;
		}
		window.display();		
	}
	deleteStaffList(StaffHead);
	deleteSchoolYearList(SyList, numSY);
	return 0;
}