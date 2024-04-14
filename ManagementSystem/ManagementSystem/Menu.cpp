#include "Menu.h"
#include "Function.h"

#define Login 0
#define ForgotPass 1
#define StudentMain 10
#define StudentProfile 11
#define StudentCourse 12
#define StudentResult 13
#define StudentProfile 14
#define StudentChangePass 15


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

void LoginMenu::EventHandling(sf::RenderWindow &window, sf::Event &ev, StudentMainMenu *studentMainMenu, bool &isStaff, Node<User> *pUser, Node<Student> *pStudent, SchoolYear *currentSchoolYear, Node<User> *StaffHead, int &currentPage)
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
					if(!isStaff)
						currentPage = StudentMain;
					studentMainMenu->setUp(&pStudent->data, currentSchoolYear);
					cout << "Login succeeded" << endl;
				}
				else {
					oLoginFailed.reveal();
					cout << "Login Failed" << endl;
				}
				cout << currentPage << endl;
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
	oInfoRect.drawTo(window);
	butMyProfile.drawTo(window);
	butChangePass.drawTo(window);
	butLogOut.drawTo(window);
	oPromting.drawTo(window);
	butMyCourses.drawTo(window);
	butMyResult.drawTo(window);
	oNameRect.drawTo(window);
	butDrop.drawTo(window);
	butDrop2.drawTo(window);
	butHome.drawTo(window);
	butBackButton.drawTo(window);
	butBackButtonClicked.drawTo(window);
	butNextButton.drawTo(window);
	butNextButtonClicked.drawTo(window);
	oLogo.drawTo(window);
	window.draw(tName);
	window.draw(tSchoolYearName);
	window.draw(tSemester);
	window.draw(tClass);
	window.draw(tCoursesAttending);
}


void StudentMainMenu::handleMouseOver(sf::RenderWindow &window)
{
	if (butBackButton.isMouseOver(window)) {
		butBackButtonClicked.reveal();
	}
	else {
		butBackButtonClicked.hide();
	}
	if (butNextButton.isMouseOver(window)) {
		butNextButtonClicked.reveal();
	}
	else {
		butNextButtonClicked.hide();
	}
}

void StudentMainMenu::EventHandling(sf::RenderWindow &window, sf::Event &ev, int &currentPage, stack<int> &pageStack)
{
	while (window.pollEvent(ev)) {
		if (ev.type == sf::Event::Closed) {
			window.close();
		}
		if (ev.type == sf::Event::MouseMoved) {
			handleMouseOver(window);
		}
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
