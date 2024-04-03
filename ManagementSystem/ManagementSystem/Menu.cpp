#include "Menu.h"
#include "Function.h"


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
