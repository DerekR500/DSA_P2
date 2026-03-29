#pragma once
#include <vector>
#include "../headers/student.h"

enum SortCriterion {
	BY_GPA,
	BY_STRESS,
	BY_STUDY_HOURS,
	BY_SLEEP_DURATION,
	BY_SOCIAL_MEDIA,
	BY_PHYSICAL_ACTIVITY,
	BY_AGE
};

float getValue(student* s, SortCriterion criterion);
void mergeSort(std::vector<student*>& arr, int left, int right, SortCriterion criterion = BY_GPA);
void quickSort(std::vector<student*>& arr, int low, int high, SortCriterion criterion = BY_GPA);