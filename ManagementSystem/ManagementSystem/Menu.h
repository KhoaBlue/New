#pragma once

#include <SFML/Graphics.hpp>
#include "Objects.h"

struct LoginMenu {
	Object oBackGround;
	Object oLoginSpace;
	Object oUsername;
	Object oPassword;
	//Object oIncorrectPass;
	Object oUsernameNotExist;
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
		//oIncorrectPass.loadTexture("../ManagementSystem/Texture/LoginMenu/IncorrectPass.png!", 376.0f, 508.0f);
		//oIncorrectPass.hide();
		oUsernameNotExist.loadTexture("../ManagementSystem/Texture/LoginMenu/UsernameNotFound.png", 364.0f, 508.0f);
		oUsernameNotExist.hide();
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