#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include <algorithm>
#include "../headers/student.h"
#include "../headers/Sorters.h"



int main()
{
	std::vector<student*> students;

	std::ifstream file;
	file.open("../../../../src/student_lifestyle_100k.csv");
	std::string line = "";
	if (!file.is_open())
#include "../headers/scrolling.h"

int main()
{
	//std::vector<student*> students;
	//std::ifstream file;
	//file.open("../../../../student_lifestyle_100k.csv");
	//std::string line = "";
	//if (!file.is_open()) 
	//{
	//	std::cerr << "Error opening file!" << std::endl;
	//	return 1;
	//}
	//getline(file, line);
	//getline(file, line);
	//
	//std::string id = "", age = "", gender = "", department = "", gpa = "", sleep = "", study = "", social = "", physical = "", stress = "";
	//int location = 0;
	//	
	//location = line.find(',');
	//id = line.substr(0, location); //remember to add '0000'
	//line = line.substr(location + 1, line.length());

	//location = line.find(',');
	//age = line.substr(0, location); 
	//line = line.substr(location + 1, line.length());

	//location = line.find(',');
	//gender = line.substr(0, location);
	//line = line.substr(location + 1, line.length());

	//location = line.find(',');
	//department = line.substr(0, location);
	//line = line.substr(location + 1, line.length());

	//location = line.find(',');
	//gpa = line.substr(0, location);
	//line = line.substr(location + 1, line.length());

	//location = line.find(',');
	//sleep = line.substr(0, location);
	//line = line.substr(location + 1, line.length());

	//location = line.find(',');
	//study = line.substr(0, location);
	//line = line.substr(location + 1, line.length());

	//location = line.find(',');
	//social = line.substr(0, location);
	//line = line.substr(location + 1, line.length());

	//location = line.find(',');
	//physical = line.substr(0, location);
	//line = line.substr(location + 1, line.length());

	//location = line.find(',');
	//stress = line.substr(0, location);
	//line = line.substr(location + 1, line.length());



	//student* s = new student(std::stoi(id), std::stoi(age), gender, department, std::stof(gpa), std::stof(sleep), std::stof(study), std::stof(social), std::stoi(physical), std::stoi(stress), line == "True");
	//

	sf::RenderWindow window(sf::VideoMode({ 1200, 800 }), "SFML works!");

	sf::Font font;
#include <filesystem>
	std::cout << std::filesystem::current_path() << std::endl;
	if (!font.openFromFile("../../../../Resources/Google_Sans/sans.ttf"))
	{
		std::cerr << "Unable to open font" << std::endl;
	}

	sf::Text ufid(font);
	ufid.setString("40542887");
	ufid.setCharacterSize(72);
	ufid.setStyle(sf::Text::Bold);
	ufid.setFillColor(sf::Color::Black);
	ufid.setPosition({ 50.0f, 50.0f });

	sf::Text studentInfo(font);
	studentInfo.setString(
		"Age: 20\n"
		"Gender: Male\n"
		"Major : Computer Science\n"
		"GPA : 3.78\n"
		"Stress Level : 2\n"
		"Physical Activity : 2\n"
		"Study Hours : 3\n"
		"Sleep Duration : 9\n"
		"Social Media Screen - Time : 3"
	);
	studentInfo.setPosition({ 50.0f, 140.0f });
	studentInfo.setFillColor(sf::Color::Black);
	studentInfo.setCharacterSize(25);

	sf::Text question(font);
	question.setString("Could this student have");
	question.setPosition({ 70.0f, 470.0f });
	question.setCharacterSize(28);
	question.setFillColor(sf::Color::Black);

	sf::Text depression(font);
	depression.setString("Depression?");
	depression.setCharacterSize(50);
	depression.setPosition({ 73.0f, 505 });
	depression.setFillColor(sf::Color::Black);

	sf::Text yesText(font);
	yesText.setCharacterSize(24);
	yesText.setString("Yes");
	yesText.setFillColor(sf::Color::Black);

	sf::RectangleShape yesButton({ 150, 90});
	yesButton.setPosition({ 50.0f, 600.0f });
	yesButton.setFillColor(sf::Color::Green);

	sf::FloatRect textBounds = yesText.getLocalBounds();
	sf::FloatRect buttonBounds = yesButton.getGlobalBounds();

	sf::RectangleShape noButton({ 150, 90 });
	noButton.setPosition({ 225.0f, 600.0f });
	noButton.setFillColor(sf::Color::Red);

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				window.close();
		}
		window.clear(sf::Color::White);
		window.draw(ufid);
		window.draw(studentInfo);
		window.draw(question);
		window.draw(depression);
		window.draw(yesButton);
		window.draw(noButton);
		window.display();
	}
	getline(file, line);
	while (getline(file, line)) {

		std::string id = "", age = "", gender = "", department = "", gpa = "", sleep = "", study = "", social = "", physical = "", stress = "";
		int location = 0;

		location = line.find(',');
		id = line.substr(0, location); //remember to add '0000'
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

		student* s = new student(std::stoi(id), std::stoi(age), gender, department, std::stof(gpa), std::stof(sleep), std::stof(study), std::stof(social), std::stoi(physical), std::stoi(stress), line == "True");
		students.push_back(s);

	}


	//Loop for testing sorting algorithms
	std::vector<student*> testVec;

	for (int i = 100; i < 200; i++) {
		testVec.push_back(students[i]);
	}

	printf("Before sorting:\n");
	for (auto s : testVec) {
		if (s) s->display();
	}
	if (!testVec.empty()) {
		quickSort(testVec, 0, static_cast<int>(testVec.size()) - 1);
	}
	std::cout << "After sorting:\n";
	for (auto s : testVec) {
		if (s) s->display();
	}

	
	//sf::RenderWindow window( sf::VideoMode( { 1200, 800 } ), "Main" );
	//sf::CircleShape shape( 100.f );
	//shape.setFillColor( sf::Color::Green );
	//

	//file.close();
	return 0;
}
