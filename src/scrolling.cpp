#include "../headers/scrolling.h"
#include <algorithm>

scrolling::scrolling(sf::FloatRect bounds, float rowHeight, sf::Font& font, unsigned int fontSize)
	: bounds(bounds), rowHeight(rowHeight), font(font), fontSize(fontSize), scrollOffset(0.0f)
{
	columns = {
		{ "UFID",      0,   90,  BY_GPA },
		{ "Age",       95,  40,  BY_AGE },
		{ "Gender",    140, 70,  BY_GPA },
		{ "Major",     215, 160, BY_GPA },
		{ "GPA",       380, 50,  BY_GPA },
		{ "Sleep",     435, 55,  BY_SLEEP_DURATION },
		{ "Study",     495, 55,  BY_STUDY_HOURS },
		{ "Social",    555, 60,  BY_SOCIAL_MEDIA },
		{ "Phys",      620, 45,  BY_PHYSICAL_ACTIVITY },
		{ "Stress",    670, 55,  BY_STRESS },
		{ "Depressed", 730, 80,  BY_GPA },
	};
	headerBg.setSize({ bounds.size.x, rowHeight });
	headerBg.setPosition(bounds.position);
	headerBg.setFillColor(sf::Color(60, 60, 60));
}

void scrolling::clamp()
{
	float maxScroll = 0.0f;
	if (data)
		maxScroll = std::max(0.0f, (float)data->size() * rowHeight - (bounds.size.y - rowHeight));
	scrollOffset = std::clamp(scrollOffset, 0.0f, maxScroll);
}

sf::Text scrolling::makeText(std::string& str, float x, float y)
{
	sf::Text text(font);
	text.setString(str);
	text.setCharacterSize(fontSize);
	text.setFillColor(sf::Color::Black);
	text.setPosition({ x, y + 3.f });
	return text;
}

void scrolling::drawHeaderText(sf::RenderWindow& window)
{
	float baseX = bounds.position.x;
	float baseY = bounds.position.y;

	for (auto& col : columns) {
		bool sortable = (col.title != "UFID" && col.title != "Gender" &&
			col.title != "Major" && col.title != "Depressed");
		bool selected = selectedCriterion.has_value() && selectedCriterion.value() == col.criterion && sortable;

		if (sortable) {
			sf::RectangleShape highlight({ col.width, rowHeight });
			highlight.setPosition({ baseX + col.xCoord, baseY });
			highlight.setFillColor(selected ? sf::Color(100, 140, 220) : sf::Color(90, 90, 90));
			window.draw(highlight);
		}

		sf::Text text(font);
		text.setString(col.title);
		text.setCharacterSize(fontSize);
		text.setFillColor(sf::Color::White);
		text.setStyle(sf::Text::Bold);
		text.setPosition({ baseX + col.xCoord, baseY + 3.0f });
		window.draw(text);
	}
}

void scrolling::drawRow(sf::RenderWindow& window, student& s, float rowY)
{
	std::vector<std::string> cells = {
		std::to_string(s.Student_ID) + "0000",
		std::to_string(s.Age),
		s.Gender,
		s.Department.size() > 18 ? s.Department.substr(0, 18) : s.Department,
		std::to_string(s.GPA).substr(0, 4),
		std::to_string(s.Sleep_Duration).substr(0, 3),
		std::to_string(s.Study_Hours).substr(0, 3),
		std::to_string(s.Social_Media_Hours).substr(0, 3),
		std::to_string(s.Physical_Activity),
		std::to_string(s.Stress_Level),
		s.Depression ? "Yes" : "No",
	};

	for (size_t c = 0; c < columns.size() && c < cells.size(); ++c) {
		sf::Text t = makeText(cells[c], columns[c].xCoord, rowY);
		if (c == 10 && s.Depression)
			t.setFillColor(sf::Color(180, 0, 0));
		window.draw(t);
	}
}

void scrolling::drawScrollbar(sf::RenderWindow& window)
{
	if (!data || data->empty()) return;

	float totalHeight = (float)data->size() * rowHeight;
	float visibleHeight = bounds.size.y - rowHeight;
	if (totalHeight <= visibleHeight) return;

	float trackX = bounds.position.x + bounds.size.x - 10.f;
	float trackY = bounds.position.y + rowHeight;

	sf::RectangleShape track({ 8.f, visibleHeight });
	track.setPosition({ trackX, trackY });
	track.setFillColor(sf::Color(200, 200, 200));
	window.draw(track);

	float thumbHeight = std::max(20.f, visibleHeight * (visibleHeight / totalHeight));
	float thumbY = trackY + (scrollOffset / (totalHeight - visibleHeight)) * (visibleHeight - thumbHeight);

	sf::RectangleShape thumb({ 8.0f, thumbHeight });
	thumb.setPosition({ trackX, thumbY });
	thumb.setFillColor(sf::Color(100, 100, 180));
	window.draw(thumb);
}

void scrolling::setData(std::vector<student>* students)
{
	data = students;
	scrollOffset = 0.0f;
}

void scrolling::handleEvent(const sf::Event& ev, sf::RenderWindow& window)
{
	if (auto* scroll = ev.getIf<sf::Event::MouseWheelScrolled>())
	{
		sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
		if (!bounds.contains(mouse)) return;
		scrollOffset -= scroll->delta * rowHeight * 3.0f;
		clamp();
	}

	if (auto* click = ev.getIf<sf::Event::MouseButtonPressed>())
	{
		if (click->button != sf::Mouse::Button::Left) return;
		sf::Vector2f mouse = window.mapPixelToCoords({ click->position.x, click->position.y });

		float baseX = bounds.position.x;
		float baseY = bounds.position.y;
		sf::FloatRect headerRect({ baseX, baseY }, { bounds.size.x, rowHeight });
		if (!headerRect.contains(mouse)) return;

		for (auto& col : columns) {
			bool sortable = (col.title != "UFID" && col.title != "Gender" &&
				col.title != "Major" && col.title != "Depressed");
			if (!sortable) continue;

			sf::FloatRect colRect({ baseX + col.xCoord, baseY }, { col.width, rowHeight });
			if (colRect.contains(mouse)) {
				if (selectedCriterion.has_value() && selectedCriterion.value() == col.criterion)
					selectedCriterion = std::nullopt;
				else
					selectedCriterion = col.criterion;
				return;
			}
		}
	}
}

void scrolling::draw(sf::RenderWindow& window)
{
	if (!data || data->empty()) return;

	sf::View defaultView = window.getDefaultView();

	window.setView(defaultView);
	window.draw(headerBg);
	drawHeaderText(window);

	sf::Vector2u windowSize = window.getSize();
	float vpLeft = bounds.position.x / windowSize.x;
	float vpTop = (bounds.position.y + rowHeight) / windowSize.y;
	float vpWidth = bounds.size.x / windowSize.x;
	float vpHeight = (bounds.size.y - rowHeight) / windowSize.y;

	sf::View dataView;
	dataView.setViewport(sf::FloatRect({ vpLeft, vpTop }, { vpWidth, vpHeight }));
	dataView.setSize({ bounds.size.x, bounds.size.y - rowHeight });
	dataView.setCenter({ bounds.size.x / 2.f, (bounds.size.y - rowHeight) / 2.f + scrollOffset });
	window.setView(dataView);

	float visibleTop = scrollOffset;
	float visibleBottom = scrollOffset + (bounds.size.y - rowHeight);
	int firstRow = std::max(0, (int)(visibleTop / rowHeight));
	int lastRow = std::min((int)data->size(), (int)(visibleBottom / rowHeight) + 1);

	for (int i = firstRow; i < lastRow; ++i) {
		float rowY = i * rowHeight;

		sf::RectangleShape rowBg({ bounds.size.x, rowHeight - 1.f });
		rowBg.setPosition({ 0.f, rowY });
		rowBg.setFillColor(i % 2 == 0 ? sf::Color(240, 240, 240) : sf::Color(255, 255, 255));
		window.draw(rowBg);

		drawRow(window, (*data)[i], rowY);
	}

	window.setView(defaultView);
	drawScrollbar(window);
}

std::optional<SortCriterion> scrolling::getSelectedCriterion() const
{
	return selectedCriterion;
}

void scrolling::clearSelection()
{
	selectedCriterion = std::nullopt;
}