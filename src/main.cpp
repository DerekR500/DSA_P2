#include <SFML/Graphics.hpp>
#include <fstream>
#include <vector>
#include "../headers/student.h"

void merge(std::vector<student*>& arr, int left, int mid, int right) {
	int i = left;
	int j = mid + 1;
	std::vector<student*> temp;
	while (i <= mid && j <= right) {
		if (arr[i]->GPA < arr[j]->GPA) {
			temp.push_back(arr[i]);
			i++;
		}
		else {
			temp.push_back(arr[j]);
			j++;
		}
	}
	while (i <= mid) {
		temp.push_back(arr[i]);
		i++;
	}
	while (j <= right) {
		temp.push_back(arr[j]);
		j++;
	}
	for (int k = left; k <= right; k++) {
		arr[k] = temp[k - left];
	}
}

void mergeSort(std::vector<student*>& arr, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;
		mergeSort(arr, left, mid);
		mergeSort(arr, mid + 1, right);
		merge(arr, left, mid, right);
	}
}




int main()
{
	std::vector<student*> students;

	std::ifstream file;
	file.open("../../../../src/student_lifestyle_100k.csv");
	std::string line = "";
	if (!file.is_open())
	{
		std::cerr << "Error opening file!" << std::endl;
		return 1;

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

	std::vector<student*> testVec;

	for (int i = 1; i < 10; i++) {
		testVec.push_back(students[i]);
	}

	printf("Before sorting:\n");
	for (auto s : testVec) {
		if (s) s->display();
	}
	if (!testVec.empty()) {
		mergeSort(testVec, 0, static_cast<int>(testVec.size()) - 1);
	}
	std::cout << "After sorting:\n";
	for (auto s : testVec) {
		if (s) s->display();
	}

	
	//sf::RenderWindow window( sf::VideoMode( { 1200, 800 } ), "Main" );
	//sf::CircleShape shape( 100.f );
	//shape.setFillColor( sf::Color::Green );
	//

	//while ( window.isOpen() )
	//{
	//	while ( const std::optional event = window.pollEvent() )
	//	{
	//		if ( event->is<sf::Event::Closed>() )
	//			window.close();
	//	}

	//	window.clear(sf::Color::White);
	//	window.draw( shape );
	//	window.display();
	//}
	file.close();
}
