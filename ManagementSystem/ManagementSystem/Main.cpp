#include "Function.h"
#include "Menu.h"

using namespace std;

#define Login 0
#define ForgotPass 1
#define HomePage 2

int main() {
	SchoolYear *SyList;
	Node<User> *StaffHead = nullptr;
	bool isStaff; //true: Staff; false: Student
	int numSY;
	Node<Student> *pStudent = nullptr;
	Node<User> *pUser = nullptr;
	loadStaffFromFile(StaffHead);
	SchoolYear *currentSchoolYear = loadSchoolYearList(SyList, numSY);
	//if (checkLogin(isStaff, pUser, pStudent, username, password, currentSchoolYear, StaffHead)) {
	//	cout << "SUCCESS" << endl;
	//}
	//else cout << "FAIl" << endl;
	// 
	//if (isStaff) {
	//	cout << pUser->data.Fullname;
	//}
	//else {
	//	cout << pStudent->data.FirstName;
	//}
	/*outputStaffList(StaffHead);*/
	
	cout << currentSchoolYear->ClassesList[0].Name << endl;
	outputStudentList(currentSchoolYear->ClassesList[0].stHead);
	

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
								currentPage = HomePage;
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
			case HomePage:
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