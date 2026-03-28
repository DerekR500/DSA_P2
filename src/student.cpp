#include "../headers/student.h"

student::student(int id, int age, std::string gender, std::string department,
	float gpa, float sleep, float study, float social, int physical, int stress, bool depression)
{
	Student_ID = id;
	Age = age;
	Gender = gender;
	Department = department;
	GPA = gpa;
	Sleep_Duration = sleep;
	Study_Hours = study;
	Social_Media_Hours = social;
	Physical_Activity = physical;
	Stress_Level = stress;
	Depression = depression;
}

void student::display()
{
	std::cout << Student_ID << std::endl;
	std::cout << Age << std::endl;
	std::cout << Gender << std::endl;
	std::cout << Department << std::endl;
	std::cout << GPA << std::endl;
	std::cout << Sleep_Duration << std::endl;
	std::cout << Study_Hours << std::endl;
	std::cout << Social_Media_Hours << std::endl;
	std::cout << Physical_Activity << std::endl;
	std::cout << Stress_Level << std::endl;
	std::cout << Depression << std::endl;

}