#pragma once
#include <string>
#include <iostream>

class student
{
public:
	int Student_ID;
	int Age;
	std::string Gender;
	std::string Department;
	float GPA;
	float Sleep_Duration;
	float Study_Hours;
	float Social_Media_Hours;
	int Physical_Activity;
	int Stress_Level;
	bool Depression;

	student(int id, int age, std::string gender, std::string department,
		float GPA, float sleep, float study, float social, int physical, int stress, bool depression);

	void display();
 };