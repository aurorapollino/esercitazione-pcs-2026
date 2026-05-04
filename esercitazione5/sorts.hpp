#pragma once
#include <vector>
#include <algorithm>

//Serve per verificare se il vettore è ordinato
template<typename T>
int is_sorted(const std::vector<T>& vec) {
	int n = (int)vec.size();
	if (n <= 1) 
		return 1; 
	for (int i = 1; i < n; ++i) {
		if (vec[i-1] > vec[i]) {
			return 0;
		}
	}
	return 1;
}

//Bubble Sort
template<typename T>
void bubble_sort(std::vector<T>& A) {
	int n = (int)A.size();
	if (n <= 1) {
		return;
	}
	for (int i = 0; i < n - 1; ++i) {
		for (int j = n - 1; j > i; --j) {
			if (A[j] < A[j-1]) {
				std::swap(A[j], A[j-1]);
			}
		}
	}
}

//Insertion Sort
template<typename T>
void insertion_sort(std::vector<T>& A) {
	int n  = (int)A.size();
	if (n <= 1) {
		return;
	}
	for (int j = 1; j < n; ++j) {
		T key = A[j];
		int i = j - 1;
		while (i >= 0 && A[i] > key)  {
			A[i+1] = A[i];
			i = i - 1;
		}
		A[i + 1] = key;
	}
}

//Selection Sort
template<typename T> 
void selection_sort(std::vector<T>& A) {
	int n = (int)A.size();
	if (n <= 1) {
		return;
	}
	for (int i = 0; i < n - 1; ++i) {
		int min = i;
		for (int j = i + 1; j < n; ++j) {
			if (A[j] < A[min]) {
				min = j;
			}
		}
		std::swap(A[i], A[min]);
	}
}

//Merge
template<typename T> 
void merge(std::vector<T>& A, int p, int q, int r) {
	int n1 = q - p + 1;
	int n2 = r - q;
	
	std::vector<T> L(n1);
	std::vector<T> R(n2);
	
	for (int i = 0; i < n1; ++i) {
		L[i] = A[p + i];
	}
	for (int j = 0; j < n2; ++j) {
		R[j] = A[q + j + 1];
	}
	
	int i = 0;
	int j = 0;
	int k = p;
	// L[n1] = +Inf, R[n2] = +Inf
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			A[k] = L[i];
			i++;
		} else {
			A[k] = R[j];
			j++;
		}
		k++;
	}
	
	// Se avanzano elementi in L, vengono copiati alla fine di A
	while (i < n1) {
		A[k] = L[i];
		i++;
		k++;
	}
	// Se avanzano elementi in R, vengono copiati alla fine di A
	while (j < n2) {
		A[k] = R[j];
		j++;
		k++;
	}
}
	
// Merge Sort
template<typename T> 
void merge_sort(std::vector<T>& A, int p, int r) {
	if (p < r) {
		int q = (p + r)/2;
		merge_sort(A, p, q);
		merge_sort(A, q + 1, r);
		merge(A,p,q,r);	
	}
}

//Partition
template<typename T> 
int partition(std::vector<T>& A, int p, int r) {
	T x = A[r];
	int i = p - 1;
	for (int j = p; j < r; ++j) {
		if (A[j] <= x) {
			i++;
			std::swap(A[i], A[j]);
		}
	}
	std::swap(A[i + 1], A[r]);
	return i + 1;
}

//Quick Sort
template<typename T> 
void quick_sort(std::vector<T>& A, int p, int r) {
	if (p < r) {
		int q = partition(A, p, r);
		quick_sort(A, p, q - 1);
		quick_sort(A, q + 1, r);
	}
}
	
	
//Modifico Quick Sort che utilizza l'algoritmo quadratico più veloce 
//Insertion Sort modificato:
template<typename T>
void insertion_sort_new(std::vector<T>& A, int p, int r) {
	if (p >= r)
		return;
	for (int j = p + 1; j <= r; ++j) {
		T key = A[j];
		int i = j - 1;
		while (i >= p && A[i] > key)  {
			A[i+1] = A[i];
			i = i - 1;
		}
		A[i + 1] = key;
	}
}
	
//Quick Sort ottimale
template<typename T>
void quick_sort_ottimale(std::vector<T>& A, int p, int r) {
	const int SOGLIA = 64;
	if ((r - p + 1) < SOGLIA) { // (r - p +1) : quanti elementi ci sono tra p e radi
		insertion_sort_new(A, p, r); // sotto la soglia agisce Insertion Sort
	} else if (p < r) {
	int q = partition(A, p, r);
	quick_sort_ottimale(A, p, q - 1);
	quick_sort_ottimale(A, q + 1, r);
	}
}