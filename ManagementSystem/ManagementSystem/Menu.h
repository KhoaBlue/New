#pragma once

#include <SFML/Graphics.hpp>
#include "Objects.h"
#include "Function.h"
#include <stack>

struct LoginMenu;
struct ForgotPassMenu;
struct StudentMainMenu;
void setTextMiddle(sf::Text *txt, float x, float y, float width, float height);

struct LoginMenu {
	Object oBackGround;
	Object oLoginSpace;
	Object oUsername;
	Object oPassword;
	Object oLoginFailed;
	TextBox tbUsername;
	TextBox tbPassword;
	Button butClarifyPW;
	Button butLogIn;
	Button butForgotPW;

	LoginMenu() {
		oBackGround.loadTexture("../ManagementSystem/Texture/LoginMenu/Background.png", 0.0f, 0.0f);
		oLoginSpace.loadTexture("../ManagementSystem/Texture/LoginMenu/LoginSpace.png", 106.0f, 55.0f);
		oUsername.loadTexture("../ManagementSystem/Texture/LoginMenu/Username.png", 198.0f, 314.0f);
		oPassword.loadTexture("../ManagementSystem/Texture/LoginMenu/Password.png", 198.0f, 442.0f);
		oLoginFailed.loadTexture("../ManagementSystem/Texture/LoginMenu/Incorrect Username or Password.png", 233.0f, 615.0f);
		oLoginFailed.hide();
		tbUsername.loadTexture("../ManagementSystem/Texture/LoginMenu/UsernameTextbox.png", false, 176.0f, 290.0f, 24);
		tbPassword.loadTexture("../ManagementSystem/Texture/LoginMenu/PasswordTextbox.png", false, 176.0f, 420.0f, 24);
		tbPassword.hide();
		butClarifyPW.loadTexture("../ManagementSystem/Texture/LoginMenu/ClarifyPassword.png", 499.0f, 441.0f);
		butLogIn.loadTexture("../ManagementSystem/Texture/LoginMenu/SignInButton.png", 176.0f, 541.0f);
		butForgotPW.loadTexture("../ManagementSystem/Texture/LoginMenu/Forgot Password.png", 176.0f, 508.0f);
	}
	void drawTo(sf::RenderWindow &window);
	void handleClicking(sf::RenderWindow &window);
	void handleTyping(sf::RenderWindow &window, sf::Event ev);

	void EventHandling(sf::RenderWindow &window, sf::Event &ev, StudentMainMenu *studentMainMenu, bool &isStaff, Node<User> *pUser, Node<Student> *pStudent, SchoolYear *currentSchoolYear, Node<User> *StaffHead, int &currentPage);
};

struct ForgotPassMenu {
	Object oBackGround;
	Object oLoginSpace;
	Object oUsername;
	Object oEmail;
	Object oNewPass;
	TextBox tbUsername;
	TextBox tbEmail;
	TextBox tbNewPass;
	Button butClarifyNewPW;
	Button butBack;
	Button butConfirm;

	ForgotPassMenu() {
		oBackGround.loadTexture("../ManagementSystem/Texture/LoginMenu/Background.png", 0.0f, 0.0f);
		oLoginSpace.loadTexture("../ManagementSystem/Texture/LoginMenu/ForgotPass/LoginSpace.png", 106.0f, 55.0f);
		oUsername.loadTexture("../ManagementSystem/Texture/LoginMenu/ForgotPass/Username.png", 198.0f, 293.0f);
		oEmail.loadTexture("../ManagementSystem/Texture/LoginMenu/ForgotPass/Email.png", 198.0f, 391.0f);
		oNewPass.loadTexture("../ManagementSystem/Texture/LoginMenu/ForgotPass/New password.png", 200.0f, 494.0f);	
		tbUsername.loadTexture("../ManagementSystem/Texture/LoginMenu/ForgotPass/UsernameTextbox.png", false, 176.0f, 270.0f, 24);
		tbEmail.loadTexture("../ManagementSystem/Texture/LoginMenu/ForgotPass/EmailTextbox.png", false, 176.0f, 368.0f, 24);
		tbNewPass.loadTexture("../ManagementSystem/Texture/LoginMenu/ForgotPass/NewPassTextbox.png", false, 176.0f, 472.0f, 24);
		tbNewPass.hide();
		butClarifyNewPW.loadTexture("../ManagementSystem/Texture/LoginMenu/ForgotPass/ClarifyPassword.png", 503.0f, 493.0f);
		butBack.loadTexture("../ManagementSystem/Texture/LoginMenu/ForgotPass/Back button.png", 176.0f, 563.0f);
		butConfirm.loadTexture("../ManagementSystem/Texture/LoginMenu/ForgotPass/Confirm button.png", 314.0f, 564.0f);
	}
	void drawTo(sf::RenderWindow &window);
	void handleClicking(sf::RenderWindow &window);
	void handleTyping(sf::RenderWindow &window, sf::Event ev);
};

struct StudentMainMenu {
	Student *pStudent = nullptr;
	SchoolYear *pSchoolYear = nullptr;
	Object oHeader;
	Object oLogo;
	Object oNameRect;
	Object oPromting;
	Object oInfoRect;
	sf::Text tName;
	sf::Text tSchoolYearName;
	sf::Text tSemester;
	sf::Text tClass;
	sf::Text tCoursesAttending;
	sf::Font font;
	Button butBackButton;
	Button butBackButtonClicked;
	Button butNextButton;
	Button butNextButtonClicked;
	Button butDrop;
	Button butDrop2;
	Button butMyProfile;
	Button butChangePass;
	Button butLogOut;
	Button butMyCourses;
	Button butMyResult;
	Button butHome;
	void setUp(Student *student, SchoolYear *schoolyear) {
		font.loadFromFile("../ManagementSystem/Poppins/Poppins-ExtraBold.ttf");
		pStudent = student;
		pSchoolYear = schoolyear;
		tName.setString(student->LastName + " " + student->FirstName);
		tName.setCharacterSize(24);
		tName.setFont(font);
		tName.setFillColor(sf::Color::Black);
		setTextMiddle(&tName, 1043.0f, 18.0f, 186.0f, 54.0f);
		
		tSchoolYearName.setString(schoolyear->Name);
		tSemester.setString(schoolyear->SemestersList[schoolyear->numOfSemesters - 1].name);
		tClass.setString(student->Class);
		cout << student->Class << endl;
		tCoursesAttending.setString(to_string(student->numOfCoursesAttending));
		tSchoolYearName.setFont(font);
		tSemester.setFont(font);
		tClass.setFont(font);
		tCoursesAttending.setFont(font);
		tSchoolYearName.setCharacterSize(15);
		tSemester.setCharacterSize(15);
		tClass.setCharacterSize(15);
		tCoursesAttending.setCharacterSize(15);
		tSchoolYearName.setFillColor(sf::Color(5, 155, 229));
		tSemester.setFillColor(sf::Color(5, 155, 229));
		tClass.setFillColor(sf::Color(5, 155, 229));
		tCoursesAttending.setFillColor(sf::Color(5, 155, 229));
		tSchoolYearName.setPosition({ 221.0f, 144.0f });
		tSemester.setPosition({ 221.0f, 167.0f });
		tClass.setPosition({ 221.0f, 190.0f });
		tCoursesAttending.setPosition({ 221.0f, 213.0f });

	}
	StudentMainMenu() {
		oHeader.loadTexture("../ManagementSystem/Texture/Student Main Menu/Header Rect.png", 0.0f, 0.0f);
		oLogo.loadTexture("../ManagementSystem/Texture/Student Main Menu/Fit.png", 530.0f, 6.0f);
		oNameRect.loadTexture("../ManagementSystem/Texture/Student Main Menu/Name Rect.png", 1024.0f, 18.0f);
		oPromting.loadTexture("../ManagementSystem/Texture/Student Main Menu/Prompting.png", 411.0f, 172.0f);
		oInfoRect.loadTexture("../ManagementSystem/Texture/Student Main Menu/InfoRect.png", 22.0f, 128.0f);
		butBackButton.loadTexture("../ManagementSystem/Texture/Student Main Menu/BackButton.png", 26.0f, 32.0f);
		butBackButtonClicked.loadTexture("../ManagementSystem/Texture/Student Main Menu/BackButtonClicked.png", 26.0f, 32.0f);
		butBackButtonClicked.hide();
		butNextButton.loadTexture("../ManagementSystem/Texture/Student Main Menu/NextButton.png", 70.0f, 32.0f);
		butNextButtonClicked.loadTexture("../ManagementSystem/Texture/Student Main Menu/NextButtonClicked.png", 70.0f, 32.0f);
		butNextButtonClicked.hide();
		butDrop.loadTexture("../ManagementSystem/Texture/Student Main Menu/DropButton.png", 1217.0f, 29.0f);
		butDrop2.loadTexture("../ManagementSystem/Texture/Student Main Menu/DropButton2.png", 1217.0f, 29.0f);
		butDrop2.hide();
		butMyProfile.loadTexture("../ManagementSystem/Texture/Student Main Menu/My Profile.png", 1024.0f, 100.0f);
		butMyProfile.hide();
		butChangePass.loadTexture("../ManagementSystem/Texture/Student Main Menu/Change Password.png", 1024.0f, 153.0f);
		butChangePass.hide();
		butLogOut.loadTexture("../ManagementSystem/Texture/Student Main Menu/Logout.png", 1024.0f, 207.0f);
		butLogOut.hide();
		butMyCourses.loadTexture("../ManagementSystem/Texture/Student Main Menu/My Courses.png", 399.0f, 327.0f);
		butMyResult.loadTexture("../ManagementSystem/Texture/Student Main Menu/My Result.png", 399.0f, 454.0f);
		butHome.loadTexture("../ManagementSystem/Texture/Student Main Menu/Home Button.png", 157.0f, 28.0f);
	}
	void drawTo(sf::RenderWindow &window);

	void handleClicking(sf::RenderWindow &window, int &currentPage, stack<int> &pageStack);
	
	void handleMouseOver(sf::RenderWindow &window);

	void EventHandling(sf::RenderWindow &window, sf::Event &ev, int &currentPage, stack<int> &pageStack);
}; 

