#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "sorts.hpp"
#include "randfiller.h"
#include "timecounter.h"

//misuro il tempo medio di un algoritmo su vettori che hanno la stessa dimensione
int main() {
	randfiller rf;
	const int N_VETTORI = 100; // realizzo 100 vettori
	
	for (int size = 4; size <= 8192; size *= 2) {
		std::cout << "\nMisurazione con il vettore di dimensione: " << size << "\n";
		// Creo e riempio 100 vettori con dimensione 'size'
		std::vector<std::vector<int>> vec(N_VETTORI, std::vector<int>(size));
        for (int i = 0; i < N_VETTORI; ++i) {
            rf.fill(vec[i], -1000, 1000); 
        }
		
		
		//per ogni algoritmo creo copie per ordinarle in modo separato
		std::vector<std::vector<int>> vec_bubble = vec;
		std::vector<std::vector<int>> vec_insertion = vec;
		std::vector<std::vector<int>> vec_selection = vec;
		std::vector<std::vector<int>> vec_std = vec;
		std::vector<std::vector<int>> vec_merge = vec;
		std::vector<std::vector<int>> vec_quick = vec;
		std::vector<std::vector<int>> vec_quick_ott = vec;
		
		timecounter tc;
		//misura il tempo con Bubble Sort
		tc.tic(); //inizio
		for (int i = 0; i < N_VETTORI; ++i) {
			bubble_sort(vec_bubble[i]);
		}
		double tempo_bubble = tc.toc()/N_VETTORI; //fine
		std::cout << "Tempo di Bubble Sort: " << tempo_bubble << " secondi \n";
		
		//misura il tempo con Insertion Sort
		tc.tic(); //inizio
		for (int i = 0; i < N_VETTORI; ++i) {
			insertion_sort(vec_insertion[i]);
		}
		double tempo_insertion = tc.toc()/N_VETTORI; //fine
		std::cout << "Tempo di Insertion Sort: " << tempo_insertion << " secondi \n";
		
		//misura il tempo con Selection Sort
		tc.tic(); //inizio
		for (int i = 0; i < N_VETTORI; ++i) {
			selection_sort(vec_selection[i]);
		}
		double tempo_selection = tc.toc()/N_VETTORI; //fine
		std::cout << "Tempo di Selection Sort: " << tempo_selection << " secondi \n";
		
		//misura il tempo con std::sort
		tc.tic(); //inizio
		for (int i = 0; i < N_VETTORI; ++i) {
			std::sort(vec_std[i].begin(), vec_std[i].end());
		}
		double tempo_sort = tc.toc()/N_VETTORI; //fine
		std::cout << "Tempo di std::sort: " << tempo_sort << " secondi \n";
		
		//misura il tempo con Merge Sort
		tc.tic(); //inizio
		for (int i = 0; i < N_VETTORI; ++i) {
			merge_sort(vec_merge[i], 0, (int)vec_merge[i].size() - 1);
		}
		double tempo_merge = tc.toc()/N_VETTORI; //fine
		std::cout << "Tempo di Merge Sort: " << tempo_merge << " secondi \n";
		
		//misura il tempo con Quick Sort
		tc.tic(); //inizio
		for (int i = 0; i < N_VETTORI; ++i) {
			quick_sort(vec_quick[i], 0, (int)vec_quick[i].size() - 1);
		}
		double tempo_quick = tc.toc()/N_VETTORI; //fine
		std::cout << "Tempo di Quick Sort: " << tempo_quick << " secondi \n";
		
		//misura il tempo con Quick Sort ottimale
		tc.tic();
		for (int i = 0; i < N_VETTORI; ++i) {
			quick_sort_ottimale(vec_quick_ott[i], 0, (int)vec_quick_ott[i].size() - 1);
		}
		double tempo_quick_ott = tc.toc()/N_VETTORI; //fine
		std::cout << "Tempo di Quick Sort ottimale: " << tempo_quick_ott << " secondi \n";
	}
	
	return EXIT_SUCCESS;
}