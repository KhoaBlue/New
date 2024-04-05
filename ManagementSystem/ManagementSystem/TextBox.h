

#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>;

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

struct TextBox {
	//Attributes
	sf::Text textbox;
	std::ostringstream text;
	sf::Sprite sprite;
	sf::Texture texture;
	bool isSelected = false;
	bool hasLimit = false;
	int limit;
	
	//Constructors
	TextBox(std::string filename, bool sel, float x, float y, int charSize) {
		if (!texture.loadFromFile(filename)) {
			std::cout << "Cannot load " + filename << std::endl;
		}
		sprite.setTexture(texture);
		sprite.setPosition({x, y});

		sf::Font font;
		font.loadFromFile("../ManagementSystem/Poppins/Poppins-SemiBold.ttf");
		textbox.setFont(font);
		textbox.setCharacterSize(charSize);
		textbox.setFillColor(sf::Color::White);
		textbox.setPosition(x + 10.0f, y + sprite.getGlobalBounds().height / 2);
		
		isSelected = sel;
		if (sel) {
			textbox.setString("|");
		}
		else textbox.setString("");
		hasLimit = true;
		limit = 32;
	}

	//Functions
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
			else if (charTyped == ENTER_KEY) {
				setSelected(true);
			}
			else if (charTyped == ESCAPE_KEY) {
				setSelected(false);
			}
		}
	}

	bool isMouseOver(sf::RenderWindow &window) {
		int MouseX = sf::Mouse::getPosition(window).x;
		int MouseY = sf::Mouse::getPosition(window).y;

		int PosX = textbox.getPosition().x;
		int PosY = textbox.getPosition().y;

		if (MouseX < PosX || MouseX > PosX + textbox.getGlobalBounds().width)
			return false;
		if (MouseY < PosY || MouseY > PosY + textbox.getGlobalBounds().height)
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