#pragma once
#include <SFML/Graphics.hpp>

struct Button {
	//Attributes
	sf::RectangleShape button;
	sf::Text text;

	//Constructor
	Button(std::string txt, sf::Vector2f size, int charSize, sf::Color bgColor, sf::Color txtColor) {
		text.setString(txt);
		button.setFillColor(bgColor);
		text.setFillColor(txtColor);
		text.setCharacterSize(charSize);
		button.setSize(size);
	}
	

	//Functions
	void setFont(sf::Font &font) {
		text.setFont(font);
	}

	void setPos(sf::Vector2f pos) {
		button.setPosition(pos);
		float txtPosX = (pos.x + button.getGlobalBounds().width / 4) - (text.getGlobalBounds().width / 2);
		float txtPosY = (pos.y + button.getGlobalBounds().height / 4) - (text.getGlobalBounds().height / 2);
		text.setPosition(txtPosX, txtPosY);
	}

	void setBgColor(sf::Color color) {
		button.setFillColor(color);
	}

	void setTextColor(sf::Color color) {
		text.setFillColor(color);
	}

	void renderTo(sf::RenderWindow &window) {
		window.draw(button);
		window.draw(text);
	}

	bool isMouseOver(sf::RenderWindow &window) {
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;

		float buttonX = button.getPosition().x;
		float buttonY = button.getPosition().y;

		return (mouseX >= buttonX && mouseX <= buttonX + button.getGlobalBounds().width) && (mouseY >= buttonY && mouseY <= buttonY + button.getGlobalBounds().height);
	}
};