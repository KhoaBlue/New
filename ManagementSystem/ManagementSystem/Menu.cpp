#include "Menu.h"

#define Login 0
#define ForgotPass 1
#define StudentMain 10
#define StudentCourse 11
#define StudentResult 12
#define StudentProfile 13
#define StudentChangePass 14


void setTextMiddle(sf::Text *txt, float x, float y, float width, float height)
{
	float posX = (2 * x + width) / 2.0f - txt->getGlobalBounds().width / 2.0f;
	float posY = (2 * y + height) / 2.0f - txt->getGlobalBounds().height / 2.0f - 3.0f;
	txt->setPosition(posX, posY);
}

void LoginMenu::drawTo(sf::RenderWindow &window)
{
	oBackGround.drawTo(window);
	oLoginSpace.drawTo(window);
	tbUsername.drawTo(window);
	tbPassword.drawTo(window);
	oUsername.drawTo(window);
	oPassword.drawTo(window);
	butClarifyPW.drawTo(window);
	butLogIn.drawTo(window);
	butForgotPW.drawTo(window);
	oLoginFailed.drawTo(window);

}

void LoginMenu::handleClicking(sf::RenderWindow &window)
{
	if (tbUsername.isMouseOver(window)) {
		tbUsername.setSelected(true);
		oUsername.hide();
	}
	else {
		tbUsername.setSelected(false);
		if (tbUsername.text.str() == "") {
			oUsername.reveal();
		}
	}

	if (tbPassword.isMouseOver(window)) {
		tbPassword.setSelected(true);
		oPassword.hide();
	}
	else {
		tbPassword.setSelected(false);
		if (tbPassword.text.str() == "")
			oPassword.reveal();
	}

	if (butClarifyPW.isMouseOver(window)) {
		tbPassword.isHiden = !tbPassword.isHiden;
	}
}

void LoginMenu::handleTyping(sf::RenderWindow &window, sf::Event ev)
{
	tbUsername.typedOn(ev);
	tbPassword.typedOn(ev);
}

void LoginMenu::EventHandling(sf::RenderWindow &window, sf::Event &ev, bool &isStaff, Node<User> *pUser, Node<Student> *&pStudent, SchoolYear *currentSchoolYear, Node<User> *StaffHead, int &currentPage)
{
	while (window.pollEvent(ev)) {
		if (ev.type == sf::Event::Closed) {
			window.close();
		}
		if (ev.type == sf::Event::MouseButtonPressed) {
			if (butLogIn.isMouseOver(window)) {
				string username = tbUsername.text.str();
				string password = tbPassword.text.str();
				if (checkLogin(isStaff, pUser, pStudent, username, password, currentSchoolYear, StaffHead)) {
					if (!isStaff) {
						currentPage = StudentMain;
					}
					tbUsername.clearText();
					tbPassword.clearText();
					cout << "Login succeeded" << endl;
				}
				else {
					oLoginFailed.reveal();
					cout << "Login Failed" << endl;
				}
				cout << currentPage << endl;
				cout << (pStudent == nullptr) << endl;
			}
			if (butForgotPW.isMouseOver(window)) {
				tbUsername.clearText();
				tbPassword.clearText();
				string username = tbUsername.text.str();
				string password = tbPassword.text.str();
				cout << username << " " << password << endl;
				currentPage = ForgotPass;
			}
			handleClicking(window);
		}
		if (ev.type == sf::Event::TextEntered) {
			handleTyping(window, ev);
		}
	}
}

void ForgotPassMenu::drawTo(sf::RenderWindow &window)
{
	oBackGround.drawTo(window);
	oLoginSpace.drawTo(window);
	tbUsername.drawTo(window);
	tbEmail.drawTo(window);
	tbNewPass.drawTo(window);
	oUsername.drawTo(window);
	oEmail.drawTo(window);
	oNewPass.drawTo(window);
	butClarifyNewPW.drawTo(window);
	butBack.drawTo(window);
	butConfirm.drawTo(window);
}

void ForgotPassMenu::handleClicking(sf::RenderWindow &window)
{
	if (tbUsername.isMouseOver(window)) {
		tbUsername.setSelected(true);
		oUsername.hide();
	}
	else {
		tbUsername.setSelected(false);
		if (tbUsername.text.str() == "") {
			oUsername.reveal();
		}
	}

	if (tbEmail.isMouseOver(window)) {
		tbEmail.setSelected(true);
		oEmail.hide();
	}
	else {
		tbEmail.setSelected(false);
		if (tbEmail.text.str() == "")
			oEmail.reveal();
	}

	if (tbNewPass.isMouseOver(window)) {
		tbNewPass.setSelected(true);
		oNewPass.hide();
	}
	else {
		tbNewPass.setSelected(false);
		if (tbNewPass.text.str() == "") {
			oNewPass.reveal();
		}
	}
	if (butClarifyNewPW.isMouseOver(window)) {
		tbNewPass.isHiden = !tbNewPass.isHiden;
	}
}

void ForgotPassMenu::handleTyping(sf::RenderWindow &window, sf::Event ev)
{
	tbUsername.typedOn(ev);
	tbEmail.typedOn(ev);
	tbNewPass.typedOn(ev);
}

void StudentMainMenu::drawTo(sf::RenderWindow &window)
{
	oHeader.drawTo(window);
	butMyProfile.drawTo(window);
	butChangePass.drawTo(window);
	butLogOut.drawTo(window);
	butBackButton.drawTo(window);
	butHome.drawTo(window);
	oNameRect.drawTo(window);
	window.draw(tName);
	butDrop.drawTo(window);
	butDrop2.drawTo(window);

	oInfoRect.drawTo(window);
	oPromting.drawTo(window);
	butMyCourses.drawTo(window);
	butMyResult.drawTo(window);
	//butBackButtonClicked.drawTo(window);
	oLogo.drawTo(window);
	window.draw(tSchoolYearName);
	window.draw(tSemester);
	window.draw(tClass);
	window.draw(tCoursesAttending);
}


//void StudentMainMenu::handleMouseOver(sf::RenderWindow &window)
//{
//	if (butBackButton.isMouseOver(window)) {
//		butBackButtonClicked.reveal();
//	}
//	else {
//		butBackButtonClicked.hide();
//	}
//	if (butNextButton.isMouseOver(window)) {
//		butNextButtonClicked.reveal();
//	}
//	else {
//		butNextButtonClicked.hide();
//	}
//}

void StudentMainMenu::EventHandling(sf::RenderWindow &window, sf::Event &ev, int &currentPage, stack<int> &pageStack)
{
	while (window.pollEvent(ev)) {
		if (ev.type == sf::Event::Closed) {
			window.close();
		}
		//if (ev.type == sf::Event::MouseMoved) {
		//	handleMouseOver(window);
		//}
		if (ev.type == sf::Event::MouseButtonPressed) {
			handleClicking(window, currentPage, pageStack);
		}
	}
}



void StudentMainMenu::handleClicking(sf::RenderWindow &window, int &currentPage, stack<int> &pageStack)
{
	if (!butMyProfile.isHiden && butMyProfile.isMouseOver(window)) {
		pageStack.push(currentPage);
		currentPage = StudentProfile;
		return;
	}
	if (!butChangePass.isHiden && butChangePass.isMouseOver(window)) {
		pageStack.push(currentPage);
		currentPage = StudentChangePass;
		return;
	}
	if (!butLogOut.isHiden && butLogOut.isMouseOver(window)) {
		currentPage = Login;
		return;
	}
	if (!butDrop.isHiden && butDrop.isMouseOver(window)) {
		butMyProfile.reveal();
		butChangePass.reveal();
		butLogOut.reveal();
		butDrop.hide();
		butDrop2.reveal();
		return;
	}
	if (!butDrop2.isHiden && butDrop2.isMouseOver(window)) {
		butMyProfile.hide();
		butChangePass.hide();
		butLogOut.hide();
		butDrop.reveal();
		butDrop2.hide();
		return;
	}
	if (butMyCourses.isMouseOver(window)) {
		pageStack.push(currentPage);
		currentPage = StudentCourse;
	}
	if (butMyResult.isMouseOver(window)) {
		pageStack.push(currentPage);
		currentPage = StudentResult;
	}
	if (butBackButton.isMouseOver(window)) {
		if (pageStack.empty()) return;
		currentPage = pageStack.top();
		pageStack.pop();
	}
}

void StudentProfileMenu::drawTo(sf::RenderWindow &window)
{
	oHeader.drawTo(window);
	oLogo.drawTo(window);
	butBackButton.drawTo(window);
	butHome.drawTo(window);
	oNameRect.drawTo(window);
	window.draw(tName);
	butDrop.drawTo(window);
	butDrop2.drawTo(window);

	oBG.drawTo(window);
	tbFullnameBox.drawTo(window);
	tbClassBox.drawTo(window);
	tbDOBBox.drawTo(window);
	tbSoID.drawTo(window);
	tbGenderBox.drawTo(window);
	tbStIDBox.drawTo(window);
	butMyProfile.drawTo(window);
	butChangePass.drawTo(window);
	butLogOut.drawTo(window);
}

void StudentProfileMenu::EventHandling(sf::RenderWindow &window, sf::Event &ev, int &currentPage, stack<int> &pageStack)
{
	while (window.pollEvent(ev)) {
		if (ev.type == sf::Event::Closed) {
			window.close();
		}
		if (ev.type == sf::Event::MouseButtonPressed) {
			handleClicking(window, currentPage, pageStack);
		}
	}
}

void StudentProfileMenu::handleClicking(sf::RenderWindow &window, int &currentPage, stack<int> &pageStack)
{
	if (!butMyProfile.isHiden && butMyProfile.isMouseOver(window)) {
		pageStack.push(currentPage);
		currentPage = StudentProfile;
		return;
	}
	if (!butChangePass.isHiden && butChangePass.isMouseOver(window)) {
		pageStack.push(currentPage);
		currentPage = StudentChangePass;
		return;
	}
	if (!butLogOut.isHiden && butLogOut.isMouseOver(window)) {
		currentPage = Login;
		return;
	}
	if (!butDrop.isHiden && butDrop.isMouseOver(window)) {
		butMyProfile.reveal();
		butChangePass.reveal();
		butLogOut.reveal();
		butDrop.hide();
		butDrop2.reveal();
		return;
	}
	if (!butDrop2.isHiden && butDrop2.isMouseOver(window)) {
		butMyProfile.hide();
		butChangePass.hide();
		butLogOut.hide();
		butDrop.reveal();
		butDrop2.hide();
		return;
	}
	if (butBackButton.isMouseOver(window)) {
		if (pageStack.empty()) return;
		currentPage = pageStack.top();
		pageStack.pop();
	}
	if (butHome.isMouseOver(window)) {
		pageStack.push(currentPage);
		currentPage = StudentMain;
	}
}
