#include <iostream>
#include <cmath>
#include <algorithm>


int main()
{
	static const int N = 10; 
	double arr[N] = {4.3, 7.8, 2.1, 11.8, 9.3, 15.5, 3.6, 4.8, 17.2, 13.4};
	
	double min = arr[0];
	double max = arr[0];
	double somma = 0.0;
	double somma_scarti_quadrati = 0.0;
	
	//Calcolo il minimo, il massimo e la somma
	for (int i = 0; i < N; i++) {
		min = std::min(min,arr[i]);
		max = std::max(max, arr[i]);
		somma = somma + arr[i];
	}
		
	//Calcolo la media
	double media = somma / N;
	
	//Calcolo la deviazione standard
	for (int i = 0; i < N; i++) {
		double differenza = arr[i] - media;
		somma_scarti_quadrati = somma_scarti_quadrati + (differenza*differenza);
	}
	
	double varianza = somma_scarti_quadrati / N;
	double deviazione_standard = std::sqrt(varianza);
	
	//Stampo i risultati
	std::cout << "Minimo: " << min << "\n";
	std::cout << "Massimo: " << max << "\n";
	std::cout << "Media: " << media << "\n";
	std::cout << "Deviazione standard: " << deviazione_standard << "\n";
	
	return 0;
	
}
	