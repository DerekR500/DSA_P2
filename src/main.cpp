#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>
#include <string>
#include "../headers/student.h"
#include "../headers/Sorters.h"
#include "../headers/scrolling.h"

static int pickRandomIndex(int size, std::mt19937& rng)
{
	std::uniform_int_distribution<int> dist(0, size - 1);
	return dist(rng);
}

static std::string formatTime(long long microseconds)
{
	if (microseconds < 1000)
		return std::to_string(microseconds) + " us";
	if (microseconds < 1000000)
		return std::to_string(microseconds / 1000) + " ms";
	return std::to_string(microseconds / 1000000) + " s";
}

static std::string criterionLabel(SortCriterion c)
{
	switch (c) {
	case BY_GPA:              return "GPA";
	case BY_STRESS:           return "Stress";
	case BY_STUDY_HOURS:      return "Study Hrs";
	case BY_SLEEP_DURATION:   return "Sleep";
	case BY_SOCIAL_MEDIA:     return "Social";
	case BY_PHYSICAL_ACTIVITY:return "Phys Act";
	case BY_AGE:              return "Age";
	default:                  return "";
	}
}

int main()
{
	std::vector<student> students;

	std::ifstream file;
	file.open("../../../../src/student_lifestyle_100k.csv");
	std::string line = "";
	if (!file.is_open())
		std::cerr << "Unable to open file" << std::endl;

	getline(file, line);
	while (getline(file, line)) {
		std::string id, age, gender, department, gpa, sleep, study, social, physical, stress;
		int location = 0;

		location = line.find(',');
		id = line.substr(0, location);
		line = line.substr(location + 1, line.length());

		location = line.find(',');
		age = line.substr(0, location);
		line = line.substr(location + 1, line.length());

		location = line.find(',');
		gender = line.substr(0, location);
		line = line.substr(location + 1, line.length());

		location = line.find(',');
		department = line.substr(0, location);
		line = line.substr(location + 1, line.length());

		location = line.find(',');
		gpa = line.substr(0, location);
		line = line.substr(location + 1, line.length());

		location = line.find(',');
		sleep = line.substr(0, location);
		line = line.substr(location + 1, line.length());

		location = line.find(',');
		study = line.substr(0, location);
		line = line.substr(location + 1, line.length());

		location = line.find(',');
		social = line.substr(0, location);
		line = line.substr(location + 1, line.length());

		location = line.find(',');
		physical = line.substr(0, location);
		line = line.substr(location + 1, line.length());

		location = line.find(',');
		stress = line.substr(0, location);
		line = line.substr(location + 1, line.length());

		student s(std::stoi(id), std::stoi(age), gender, department, std::stof(gpa),
			std::stof(sleep), std::stof(study), std::stof(social),
			std::stoi(physical), std::stoi(stress), line == "True");
		students.push_back(s);
	}
	file.close();

	std::mt19937 rng(std::random_device{}());

	int featuredIndex = pickRandomIndex((int)students.size(), rng);
	student featuredStudent = students[featuredIndex];
	students.erase(students.begin() + featuredIndex);

	std::vector<student> displayStudents = students;

	sf::RenderWindow window(sf::VideoMode({ 1200, 800 }), "Depression Analysts");
	window.setFramerateLimit(60);

	sf::Font font;
	if (!font.openFromFile("../../../../Resources/Google_Sans/sans.ttf"))
		std::cerr << "Unable to open font" << std::endl;

	sf::FloatRect tableBounds({ 410.f, 120.f }, { 780.f, 660.f });
	scrolling table(tableBounds, 24.f, font, 13);
	table.setData(&displayStudents);

	int correctCount = 0;
	int wrongCount = 0;
	std::string sortTimeStr = "";

	auto buildStudentInfoString = [](const student& s) {
		return
			"ID: " + std::to_string(s.Student_ID) + "0000\n"
			"Age: " + std::to_string(s.Age) + "\n"
			"Gender: " + s.Gender + "\n"
			"Major: " + s.Department + "\n"
			"GPA: " + std::to_string(s.GPA).substr(0, 4) + "\n"
			"Stress Level: " + std::to_string(s.Stress_Level) + "\n"
			"Physical Activity: " + std::to_string(s.Physical_Activity) + "\n"
			"Study Hours: " + std::to_string(s.Study_Hours).substr(0, 3) + "\n"
			"Sleep Duration: " + std::to_string(s.Sleep_Duration).substr(0, 3) + "\n"
			"Social Media: " + std::to_string(s.Social_Media_Hours).substr(0, 3);
		};

	sf::Text ufid(font);
	ufid.setCharacterSize(36);
	ufid.setStyle(sf::Text::Bold);
	ufid.setFillColor(sf::Color::Black);
	ufid.setPosition({ 20.0f, 10.0f });

	sf::Text studentInfo(font);
	studentInfo.setPosition({ 20.0f, 55.0f });
	studentInfo.setFillColor(sf::Color::Black);
	studentInfo.setCharacterSize(16);

	sf::Text question(font);
	question.setString("Does this student have depression?");
	question.setPosition({ 20.0f, 430.0f });
	question.setCharacterSize(17);
	question.setFillColor(sf::Color::Black);

	auto updateFeatured = [&]() {
		ufid.setString(std::to_string(featuredStudent.Student_ID) + "0000");
		studentInfo.setString(buildStudentInfoString(featuredStudent));
		};
	updateFeatured();

	sf::RectangleShape yesButton({ 160, 50 });
	yesButton.setPosition({ 20.0f, 460.0f });
	yesButton.setFillColor(sf::Color(50, 180, 50));

	sf::Text yesText(font);
	yesText.setCharacterSize(20);
	yesText.setString("Yes");
	yesText.setFillColor(sf::Color::White);
	yesText.setPosition({ 80.0f, 472.0f });

	sf::RectangleShape noButton({ 160, 50 });
	noButton.setPosition({ 200.0f, 460.0f });
	noButton.setFillColor(sf::Color(200, 50, 50));

	sf::Text noText(font);
	noText.setCharacterSize(20);
	noText.setString("No");
	noText.setFillColor(sf::Color::White);
	noText.setPosition({ 265.0f, 472.0f });

	sf::Text scoreText(font);
	scoreText.setCharacterSize(16);
	scoreText.setFillColor(sf::Color::Black);
	scoreText.setPosition({ 20.0f, 530.0f });

	sf::Text feedbackText(font);
	feedbackText.setCharacterSize(17);
	feedbackText.setPosition({ 20.0f, 580.0f });
	feedbackText.setFillColor(sf::Color::Black);

	sf::RectangleShape mergeSortBtn({ 170, 45 });
	mergeSortBtn.setPosition({ 410.f, 65.f });
	mergeSortBtn.setFillColor(sf::Color(70, 70, 160));

	sf::Text mergeSortText(font);
	mergeSortText.setString("Merge Sort");
	mergeSortText.setCharacterSize(16);
	mergeSortText.setFillColor(sf::Color::White);
	mergeSortText.setPosition({ 450.f, 79.f });

	sf::RectangleShape quickSortBtn({ 170, 45 });
	quickSortBtn.setPosition({ 595.f, 65.f });
	quickSortBtn.setFillColor(sf::Color(70, 70, 160));

	sf::Text quickSortText(font);
	quickSortText.setString("Quick Sort");
	quickSortText.setCharacterSize(16);
	quickSortText.setFillColor(sf::Color::White);
	quickSortText.setPosition({ 635.f, 79.f });

	sf::Text sortTimeText(font);
	sortTimeText.setCharacterSize(15);
	sortTimeText.setFillColor(sf::Color(50, 50, 50));
	sortTimeText.setPosition({ 785.f, 79.f });

	auto runSort = [&](bool useMerge) {
		auto crit = table.getSelectedCriterion();
		if (!crit.has_value()) return;

		std::vector<student*> ptrs;
		ptrs.reserve(displayStudents.size());
		for (auto& s : displayStudents)
			ptrs.push_back(&s);

		auto start = std::chrono::high_resolution_clock::now();
		if (useMerge)
			mergeSort(ptrs, 0, (int)ptrs.size() - 1, crit.value());
		else
			quickSort(ptrs, 0, (int)ptrs.size() - 1, crit.value());
		auto end = std::chrono::high_resolution_clock::now();

		long long elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

		std::vector<student> sorted;
		sorted.reserve(ptrs.size());
		for (auto* p : ptrs)
			sorted.push_back(*p);
		displayStudents = sorted;
		table.setData(&displayStudents);

		std::string algo = useMerge ? "Merge" : "Quick";
		sortTimeStr = algo + " Sort (" + criterionLabel(crit.value()) + "): " + formatTime(elapsed);
		sortTimeText.setString(sortTimeStr);
		table.clearSelection();
		};

	auto selectNewStudent = [&]() {
		int idx = pickRandomIndex((int)displayStudents.size(), rng);
		featuredStudent = displayStudents[idx];
		displayStudents.erase(displayStudents.begin() + idx);
		table.setData(&displayStudents);
		updateFeatured();
		feedbackText.setString("");
		};

	auto handleGuess = [&](bool guessedYes) {
		bool correct = (guessedYes == featuredStudent.Depression);
		if (correct) {
			correctCount++;
			feedbackText.setString("Correct!");
			feedbackText.setFillColor(sf::Color(0, 150, 0));
		}
		else {
			wrongCount++;
			feedbackText.setString("Wrong! Answer was: " +
				std::string(featuredStudent.Depression ? "Yes" : "No"));
			feedbackText.setFillColor(sf::Color(180, 0, 0));
		}
		scoreText.setString("Correct: " + std::to_string(correctCount) +
			"   Wrong: " + std::to_string(wrongCount));
		selectNewStudent();
		};

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();

			table.handleEvent(*event, window);

			if (auto* click = event->getIf<sf::Event::MouseButtonPressed>())
			{
				if (click->button == sf::Mouse::Button::Left)
				{
					sf::Vector2f mouse = window.mapPixelToCoords({ click->position.x, click->position.y });

					if (yesButton.getGlobalBounds().contains(mouse))
						handleGuess(true);
					else if (noButton.getGlobalBounds().contains(mouse))
						handleGuess(false);
					else if (mergeSortBtn.getGlobalBounds().contains(mouse))
						runSort(true);
					else if (quickSortBtn.getGlobalBounds().contains(mouse))
						runSort(false);
				}
			}
		}

		window.clear(sf::Color::White);

		window.draw(ufid);
		window.draw(studentInfo);
		window.draw(question);

		window.draw(yesButton);
		window.draw(yesText);
		window.draw(noButton);
		window.draw(noText);

		window.draw(scoreText);
		window.draw(feedbackText);

		window.draw(mergeSortBtn);
		window.draw(mergeSortText);
		window.draw(quickSortBtn);
		window.draw(quickSortText);
		window.draw(sortTimeText);

		table.draw(window);

		window.display();
	}

	return 0;
}