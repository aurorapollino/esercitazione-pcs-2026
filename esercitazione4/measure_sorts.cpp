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
	for (int size = 4; size <= 8192; size *= 2) {
	std::cout << "\nMisurazione con il vettore di dimensione: " << size << "\n";
		std::vector<int> vec; //creo il vettore da riempire**
		vec.resize(size); //in questo modo il vettore ha dimensione size
		rf.fill(vec, -1000, 1000); //il vettore viene riempito con valori casuali tra -1000 e 1000
		
		//per ogni algoritmo creo copie per ordinarle in modo separato
		std::vector<int> vec_bubble = vec;
		std::vector<int> vec_insertion = vec;
		std::vector<int> vec_selection = vec;
		std::vector<int> vec_std = vec;
		
		timecounter tc;
		//misura il tempo con Bubble Sort
		tc.tic(); //inizio
		bubble_sort(vec_bubble);
		double tempo_bubble = tc.toc(); //fine
		std::cout << "Tempo di Bubble Sort: " << tempo_bubble << " secondi \n";
		
		//misura il tempo con Insertion Sort
		tc.tic(); //inizio
		insertion_sort(vec_insertion);
		double tempo_insertion = tc.toc(); //fine
		std::cout << "Tempo di Insertion Sort: " << tempo_insertion << " secondi \n";
		
		//misura il tempo con Selection Sort
		tc.tic(); //inizio
		selection_sort(vec_selection);
		double tempo_selection = tc.toc(); //fine
		std::cout << "Tempo di Selection Sort: " << tempo_selection << " secondi \n";
		
		//misura il tempo con std::sort
		tc.tic(); //inizio
		std::sort(vec_std.begin(), vec_std.end());
		double tempo_sort = tc.toc(); //fine
		std::cout << "Tempo di std::sort: " << tempo_sort << " secondi \n";
	}
	
	return EXIT_SUCCESS;
}
		
		
		
		
		