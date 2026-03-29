#pragma once
#include <SFML/Graphics.hpp>
#include "../headers/student.h"
#include "../headers/Sorters.h"
#include <vector>
#include <optional>

class scrolling
{
	struct column {
		std::string title;
		float xCoord;
		float width;
		SortCriterion criterion;
	};

	sf::FloatRect bounds;
	float rowHeight;
	sf::Font& font;
	unsigned int fontSize;
	float scrollOffset;
	std::vector<student>* data = nullptr;
	std::vector<column> columns;
	sf::RectangleShape headerBg;
	std::optional<SortCriterion> selectedCriterion;

	void clamp();
	sf::Text makeText(std::string& str, float x, float y);
	void drawHeaderText(sf::RenderWindow& window);
	void drawRow(sf::RenderWindow& window, student& s, float rowY);
	void drawScrollbar(sf::RenderWindow& window);

public:
	scrolling(sf::FloatRect bounds, float rowH, sf::Font& font, unsigned int fontS = 16);
	void setData(std::vector<student>* students);
	void handleEvent(const sf::Event& ev, sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
	std::optional<SortCriterion> getSelectedCriterion() const;
	void clearSelection();
};