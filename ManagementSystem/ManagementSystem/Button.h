#pragma once
#include <SFML/Graphics.hpp>

struct Button {
	//Attributes
	sf::Text text;
	sf::Sprite sprite;
	sf::Texture texture;
	//Constructor
	Button(std::string filename, float x, float y) {
		texture.loadFromFile(filename);
		sprite.setTexture(texture);
		sprite.setPosition(x, y);
	}
	

	//Functions
	void setFont(sf::Font &font) {
		text.setFont(font);
	}

	void setPos(sf::Vector2f pos) {
		sprite.setPosition(pos);
		float txtPosX = 1.0 * (pos.x + sprite.getGlobalBounds().width / 4) - (text.getGlobalBounds().width / 2);
		float txtPosY = 1.0 * (pos.y + sprite.getGlobalBounds().height / 4) - (text.getGlobalBounds().height / 2);
		text.setPosition(txtPosX, txtPosY);
	}

	void setTextColor(sf::Color color) {
		text.setFillColor(color);
	}

	void drawTo(sf::RenderWindow &window) {
		window.draw(sprite);
		window.draw(text);
	}

	bool isMouseOver(sf::RenderWindow &window) {
		int mouseX = sf::Mouse::getPosition(window).x;
		int mouseY = sf::Mouse::getPosition(window).y;

		int buttonX = sprite.getPosition().x;
		int buttonY = sprite.getPosition().y;

		return (mouseX >= buttonX && mouseX <= buttonX + sprite.getGlobalBounds().width) && (mouseY >= buttonY && mouseY <= buttonY + sprite.getGlobalBounds().height);
	}
};