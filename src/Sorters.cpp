//Sorter cpp file for quicksort and mergesort algorithms
#include <vector>
#include <algorithm>
#include "../headers/Sorters.h"
#include "../headers/student.h"


float getValue(student* s, SortCriterion criterion) {
	switch (criterion) {
	case BY_GPA:
		return s->GPA;
	case BY_STRESS:
		return static_cast<float>(s->Stress_Level);
	case BY_STUDY_HOURS:
		return s->Study_Hours;
	case BY_SLEEP_DURATION:
		return s->Sleep_Duration;
	case BY_SOCIAL_MEDIA:
		return s->Social_Media_Hours;
	case BY_PHYSICAL_ACTIVITY:
		return static_cast<float>(s->Physical_Activity);
	case BY_AGE:
		return static_cast<float>(s->Age);
	default:
		return 0.0f;
	}
}

void merge(std::vector<student*>& arr, int left, int mid, int right, SortCriterion criterion) {
	int i = left;
	int j = mid + 1;
	std::vector<student*> temp;

	while (i <= mid && j <= right) {
		if (getValue(arr[i], criterion) < getValue(arr[j], criterion)) {
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

void mergeSort(std::vector<student*>& arr, int left, int right, SortCriterion criterion) {
	if (left < right) {
		int mid = left + (right - left) / 2;
		mergeSort(arr, left, mid, criterion);
		mergeSort(arr, mid + 1, right, criterion);
		merge(arr, left, mid, right, criterion);
	}
}

int partition(std::vector<student*>& arr, int low, int high, SortCriterion criterion) {
	student* pivot = arr[high];
	float pivotValue = getValue(pivot, criterion);
	int i = low - 1;

	for (int j = low; j < high; j++) {
		if (getValue(arr[j], criterion) < pivotValue) {
			i++;
			std::swap(arr[i], arr[j]);
		}
	}

	std::swap(arr[i + 1], arr[high]);
	return i + 1;
}

void quickSort(std::vector<student*>& arr, int low, int high, SortCriterion criterion) {
	if (low < high) {
		int pi = partition(arr, low, high, criterion);
		quickSort(arr, low, pi - 1, criterion);
		quickSort(arr, pi + 1, high, criterion);
	}
}
