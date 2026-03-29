//Sorter cpp file for quicksort and mergesort algorithms
#include <vector>
#include <algorithm>
#include "../headers/student.h"

void merge(std::vector<student*>& arr, int left, int mid, int right) {
	int i = left;
	int j = mid + 1;
	std::vector<student*> temp;
	while (i <= mid && j <= right) {
		if (arr[i]->Stress_Level < arr[j]->Stress_Level) {
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

int partition(std::vector<student*>& arr, int low, int high) {
	student* pivot = arr[high];
	int i = low - 1;
	for (int j = low; j < high; j++) {
		if (arr[j]->Stress_Level < pivot->Stress_Level) {
			i++;
			std::swap(arr[i], arr[j]);
		}
	}
	std::swap(arr[i + 1], arr[high]);
	return i + 1;
}

void quickSort(std::vector<student*>& arr, int low, int high) {
	if (low < high) {
		int pi = partition(arr, low, high);
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}