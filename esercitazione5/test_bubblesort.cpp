#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <random>
#include "sorts.hpp"
#include "randfiller.h"

int main() {
	randfiller rf;
	
	//Creo dimensioni casuali per 100 vettori (da 0 a 1000 elementi)
	std::random_device rd;
	std::mt19937 gen(rd()); //serve per creare un generatore di numeri casuali
	std::uniform_int_distribution<int> dist(0, 1000); //distribuzione uniforme tra 0 e 1000
	
	for (int i = 0; i < 100; ++i) {
		int size = dist(gen); //si estrae una dimensione a caso tra 0 e 1000
		std::vector<int> vec(size); //crea un vettore di dimensione size
		rf.fill(vec,-1000,1000); //il vettore viene riempito con valori casuali tra -1000 e 1000
		
		bubble_sort(vec);
		if (!is_sorted(vec)) {
			std::cerr << "Errore: il vettore non è ordinato \n";
			return EXIT_FAILURE;
		}
	}
	
	//creo un vettore e lo riempio con delle stringhe
	std::vector<std::string> stringa = {"lavagna", "letto", "casa", "gelato", "nonna", "gatto", "telefono", "albero", "spugna", "incendio"};
	bubble_sort(stringa);
	
	if (!is_sorted(stringa)) {
		std::cerr <<"Errore: il vettore di stringhe non è ordinato \n";
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
	