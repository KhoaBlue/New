#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <string>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

struct Object {
	sf::Sprite sprite;
	sf::Texture texture;
	bool isHiden = false;

	//Object(std::string filename, float x, float y) {
	//	texture.loadFromFile(filename);
	//	sprite.setTexture(texture);
	//	sprite.setPosition(x, y);
	//}

	void loadTexture(std::string filename, float x, float y) {
		texture.loadFromFile(filename);
		sprite.setTexture(texture);
		sprite.setPosition(x, y);
	}
	
	void drawTo(sf::RenderWindow &window) {
		if(!isHiden)
			window.draw(sprite);
	}

	void hide() {
		isHiden = true;
	}

	void reveal() {
		isHiden = false;
	}
};

struct Button : Object {
	//Attributes
	sf::Text text;
	sf::Font font;

	//Button(std::string filename, float x, float y) : Object(filename, x, y) {
	//	text.setString("");
	//	font.loadFromFile("../ManagementSystem/Poppins/Poppins-SemiBold.ttf");
	//}
	//Functions

	void loadTexture(std::string filename, float x, float y) {
		text.setString("");
		font.loadFromFile("../ManagementSystem/Poppins/Poppins-SemiBold.ttf");
		setFont(font);
		texture.loadFromFile(filename);
		sprite.setTexture(texture);
		sprite.setPosition(x, y);
	}
	void setFont(sf::Font &font) {
		text.setFont(font);
	}

	void setPos(sf::Vector2f pos) {
		sprite.setPosition(pos);
		float txtPosX = (float) (pos.x + sprite.getGlobalBounds().width / 4) - (text.getGlobalBounds().width / 2);
		float txtPosY = (float)	(pos.y + sprite.getGlobalBounds().height / 4) - (text.getGlobalBounds().height / 2);
		text.setPosition(txtPosX, txtPosY);
	}

	void setTextColor(sf::Color color) {
		text.setFillColor(color);
	}

	void drawTo(sf::RenderWindow &window) {
		if (!isHiden) {
			window.draw(sprite);
			window.draw(text);
		}
	}

	bool isMouseOver(sf::RenderWindow &window) {
		int mouseX = sf::Mouse::getPosition(window).x;
		int mouseY = sf::Mouse::getPosition(window).y;

		float buttonX = sprite.getPosition().x;
		float buttonY = sprite.getPosition().y;

		return (mouseX >= buttonX && mouseX <= buttonX + sprite.getGlobalBounds().width) && (mouseY >= buttonY && mouseY <= buttonY + sprite.getGlobalBounds().height);
	}
};

struct TextBox : Object {
	//Attributes
	sf::Text textbox;
	std::ostringstream text;
	sf::Font font;
	int limit = 21;
	bool isSelected = false;
	bool hasLimit = true;
	

	//Constructors
	//TextBox(std::string filename, bool sel, float x, float y, int charSize) : Object(filename, x, y) {
	//	font.loadFromFile("../ManagementSystem/Poppins/Poppins-SemiBold.ttf");
	//	textbox.setFont(font);
	//	textbox.setCharacterSize(charSize);
	//	textbox.setFillColor(sf::Color::Black);
	//	textbox.setPosition(x + 20.0f, y + sprite.getGlobalBounds().height / 4);
	//	text << "";
	//	isSelected = sel;
	//	if (sel) {
	//		textbox.setString("|");
	//	}
	//	else textbox.setString("");
	//	hasLimit = true;
	//	limit = 32;
	//}

	//Functions
	
	void loadTexture(std::string filename, bool sel, float x, float y, int charSize) {
		texture.loadFromFile(filename);
		sprite.setTexture(texture);
		sprite.setPosition(x, y);
		font.loadFromFile("../ManagementSystem/Poppins/Poppins-SemiBold.ttf");
		textbox.setFont(font);
		textbox.setCharacterSize(charSize);
		textbox.setFillColor(sf::Color::Black);
		textbox.setPosition(x + 20.0f, y + sprite.getGlobalBounds().height / 4);
		text << "";
		isSelected = sel;
		if (sel) {
			textbox.setString("|");
		}
		else textbox.setString("");
	}

	void clearText() {
		text.str() = "";
		textbox.setString(text.str());
		setSelected(false);
	}
	void setFont(sf::Font &font) {
		textbox.setFont(font);
	}

	void setPos(sf::Vector2f pos) {
		textbox.setPosition(pos);
	}

	void setLimit(bool hasL) {
		hasLimit = hasL;
	}

	void setLimit(bool hasL, int lim) {
		hasLimit = hasL;
		if (hasL)
			limit = lim;
	}

	void setSelected(bool isSel) {
		isSelected = isSel;
		if (!isSel) {
			std::string curT = text.str();
			std::string newT = "";
			int curLength = curT.length();
			for (int i = 0; i < curLength; ++i) {
				newT += curT[i];
			}
			textbox.setString(newT);
		}
		else {
			textbox.setString(text.str() + "|");
		}
	}

	void drawTo(sf::RenderWindow &window) {
		window.draw(sprite);
		if (isHiden) {
			int len = text.str().length();
			if (isSelected) {
				textbox.setString(std::string(len, '*') + "|");
			}
			else {
				textbox.setString(std::string(len, '*'));
			}
		}
		window.draw(textbox);
	}

	void typedOn(sf::Event input) {
		if (isSelected) {
			int charTyped = input.text.unicode;
			if (charTyped < 128) {
				if (hasLimit) {
					if (text.str().length() < limit) {
						inputLogic(charTyped);
					}
					else if (charTyped == DELETE_KEY) {
						deleteBack();
					}
				}
				else {
					inputLogic(charTyped);
				}
			}
		}
	}

	bool isMouseOver(sf::RenderWindow &window) {
		int MouseX = sf::Mouse::getPosition(window).x;
		int MouseY = sf::Mouse::getPosition(window).y;
		float PosX = sprite.getPosition().x;
		float PosY = sprite.getPosition().y;       
		if (MouseX < PosX || MouseX > PosX + sprite.getGlobalBounds().width)
			return false;
		if (MouseY < PosY || MouseY > PosY + sprite.getGlobalBounds().height)
			return false;
		return true;
	}

	bool getState() {
		return isSelected;
	}
	//void moveCursor();

	void inputLogic(int charTyped) {
		if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
			text << static_cast<char>(charTyped);
		}
		else if (charTyped == DELETE_KEY) {
			if (text.str().length() > 0)
				deleteMiddle(text.str().length() - 1);
		}
		textbox.setString(text.str() + "|");
	}

	void deleteBack() {
		std::string curT = text.str();
		std::string newT = "";
		int curLength = curT.length();
		for (int i = 0; i < curLength - 1; ++i) {
			newT += curT[i];
		}

		text.str("");
		text << newT;
		textbox.setString(text.str());
	}

	void deleteMiddle(int idx) {
		std::string curT = text.str();
		std::string newT = "";
		int curLength = curT.length();
		for (int i = 0; i < idx; ++i) {
			newT += curT[i];
		}

		for (int i = idx + 1; i < curLength; ++i) {
			newT += curT[i];
		}
		text.str("");
		text << newT;
		textbox.setString(text.str());
	}
};