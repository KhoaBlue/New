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

	void EventHandling(sf::RenderWindow &window, sf::Event &ev, bool &isStaff, Node<User> *pUser, Node<Student> *&pStudent, SchoolYear *currentSchoolYear, Node<User> *StaffHead, int &currentPage);
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
	//Header:
	Object oHeader;
	Object oLogo;
	Object oNameRect;
	Button butBackButton;
	//Button butBackButtonClicked;
	Button butHome;
	Button butDrop;
	Button butDrop2;
	Button butMyProfile;
	Button butChangePass;
	Button butLogOut;
	sf::Text tName;
	//Main:
	Object oPromting;
	Object oInfoRect;
	sf::Text tSchoolYearName;
	sf::Text tSemester;
	sf::Text tClass;
	sf::Text tCoursesAttending;
	sf::Font font;
	Button butMyResult;
	Button butMyCourses;

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
		//Header:
		oHeader.loadTexture("../ManagementSystem/Texture/Header/Header Rect.png", 0.0f, 0.0f);
		oLogo.loadTexture("../ManagementSystem/Texture/Header/Fit.png", 530.0f, 6.0f);
		oNameRect.loadTexture("../ManagementSystem/Texture/Header/Name Rect.png", 1024.0f, 18.0f);
		butDrop.loadTexture("../ManagementSystem/Texture/Header/DropButton.png", 1217.0f, 29.0f);
		butDrop2.loadTexture("../ManagementSystem/Texture/Header/DropButton2.png", 1217.0f, 29.0f);
		butDrop2.hide();
		butMyProfile.loadTexture("../ManagementSystem/Texture/Header/My Profile.png", 1024.0f, 100.0f);
		butMyProfile.hide();
		butChangePass.loadTexture("../ManagementSystem/Texture/Header/Change Password.png", 1024.0f, 153.0f);
		butChangePass.hide();
		butLogOut.loadTexture("../ManagementSystem/Texture/Header/Logout.png", 1024.0f, 207.0f);
		butLogOut.hide();
		butBackButton.loadTexture("../ManagementSystem/Texture/Header/Back Button.png", 23.0f, 28.0f);
		//butBackButtonClicked.loadTexture("../ManagementSystem/Texture/Student Main Menu/BackButtonClicked.png", 26.0f, 32.0f);
		//butBackButtonClicked.hide();
		butHome.loadTexture("../ManagementSystem/Texture/Header/Home Button.png", 186.0f, 28.0f);
		//Main:
		oPromting.loadTexture("../ManagementSystem/Texture/Student Main Menu/Prompting.png", 411.0f, 172.0f);
		oInfoRect.loadTexture("../ManagementSystem/Texture/Student Main Menu/InfoRect.png", 22.0f, 128.0f);
		butMyCourses.loadTexture("../ManagementSystem/Texture/Student Main Menu/My Courses.png", 399.0f, 327.0f);
		butMyResult.loadTexture("../ManagementSystem/Texture/Student Main Menu/My Result.png", 399.0f, 454.0f);
	}
	void drawTo(sf::RenderWindow &window);

	void handleClicking(sf::RenderWindow &window, int &currentPage, stack<int> &pageStack);
	
	//void handleMouseOver(sf::RenderWindow &window);

	void EventHandling(sf::RenderWindow &window,  sf::Event &ev, int &currentPage, stack<int> &pageStack);
}; 

struct StudentProfileMenu {
	Student *pStudent = nullptr;
	//Header:
	Object oHeader;
	Object oLogo;
	Object oNameRect;
	Button butBackButton;
	//Button butBackButtonClicked;
	Button butHome;
	Button butDrop;
	Button butDrop2;
	Button butMyProfile;
	Button butChangePass;
	Button butLogOut;
	sf::Text tName;
	//Main:
	Object oBG;
	TextBox tbClassBox;
	TextBox tbFullnameBox;
	TextBox tbDOBBox;
	TextBox tbGenderBox;
	TextBox tbStIDBox;
	TextBox tbSoID;
	sf::Font font;
	void setUp(Student *student) {
		font.loadFromFile("../ManagementSystem/Poppins/Poppins-ExtraBold.ttf");
		pStudent = student;
		tName.setString(student->LastName + " " + student->FirstName);
		tName.setCharacterSize(24);
		tName.setFont(font);
		tName.setFillColor(sf::Color::Black);
		setTextMiddle(&tName, 1043.0f, 18.0f, 186.0f, 54.0f);
		
		tbFullnameBox.textbox.setString(student->LastName + " " + student->FirstName);
		tbFullnameBox.setTextMiddle();
		tbClassBox.textbox.setString(student->Class);
		tbClassBox.setTextMiddle();
		tbDOBBox.textbox.setString(student->DOB);
		tbDOBBox.setTextMiddle();
		tbGenderBox.textbox.setString((student->Gender ? "Male" : "Female"));
		tbGenderBox.setTextMiddle();
		tbStIDBox.textbox.setString(student->StID);
		tbStIDBox.setTextMiddle();
		tbSoID.textbox.setString("0" + student->SocialID);
		tbSoID.setTextMiddle();

	}
	StudentProfileMenu() {
		//Header:
		oHeader.loadTexture("../ManagementSystem/Texture/Header/Header Rect.png", 0.0f, 0.0f);
		oLogo.loadTexture("../ManagementSystem/Texture/Header/Fit.png", 530.0f, 6.0f);
		oNameRect.loadTexture("../ManagementSystem/Texture/Header/Name Rect.png", 1024.0f, 18.0f);
		butDrop.loadTexture("../ManagementSystem/Texture/Header/DropButton.png", 1217.0f, 29.0f);
		butDrop2.loadTexture("../ManagementSystem/Texture/Header/DropButton2.png", 1217.0f, 29.0f);
		butDrop2.hide();
		butMyProfile.loadTexture("../ManagementSystem/Texture/Header/My Profile.png", 1024.0f, 100.0f);
		butMyProfile.hide();
		butChangePass.loadTexture("../ManagementSystem/Texture/Header/Change Password.png", 1024.0f, 153.0f);
		butChangePass.hide();
		butLogOut.loadTexture("../ManagementSystem/Texture/Header/Logout.png", 1024.0f, 207.0f);
		butLogOut.hide();
		butBackButton.loadTexture("../ManagementSystem/Texture/Header/Back Button.png", 23.0f, 28.0f);
		butHome.loadTexture("../ManagementSystem/Texture/Header/Home Button.png", 186.0f, 28.0f);

		//Main:
		oBG.loadTexture("../ManagementSystem/Texture/Student Profile Menu/BG.png", 182.0f, 109.0f);
		tbFullnameBox.loadTexture("../ManagementSystem/Texture/Student Profile Menu/FullnameBox.png", false, 464.0f, 265.0f, 30);
		tbClassBox.loadTexture("../ManagementSystem/Texture/Student Profile Menu/ClassBox.png", false, 819.0f, 483.0f, 30);
		tbDOBBox.loadTexture("../ManagementSystem/Texture/Student Profile Menu/DOBBox.png", false, 464.0f, 483.0f, 30);
		tbGenderBox.loadTexture("../ManagementSystem/Texture/Student Profile Menu/GenderBox.png", false, 819.0f, 371.0f, 30);
		tbStIDBox.loadTexture("../ManagementSystem/Texture/Student Profile Menu/StIDBox.png", false, 464.0f, 371.0f, 30);
		tbSoID.loadTexture("../ManagementSystem/Texture/Student Profile Menu/SoIDBox.png", false, 464.0f, 584.0f, 30);
	}
	void drawTo(sf::RenderWindow &window);

	void EventHandling(sf::RenderWindow &window, sf::Event &ev, int &currentPage, stack<int> &pageStack);

	void handleClicking(sf::RenderWindow &window, int &currentPage, stack<int> &pageStack);
};

