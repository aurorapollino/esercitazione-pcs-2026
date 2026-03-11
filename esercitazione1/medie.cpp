#include <iostream>
#include <fstream>

using namespace std;


int main(int argc, const char *argv[]) {
	if (argc < 2) {
		cerr << "Errore: parametro non specificato.\n";
		return 1;
	}
	
	string filename = argv[1];
	ifstream ifs(filename);
	
	if (!ifs.is_open()) {
		cerr << "Errore: impossibile aprire il file " << filename << "\n";
		return 1;
		
	}
	while (!ifs.eof()) {
		string location;
		double t1, t2, t3, t4;
		ifs >> location >> t1 >> t2 >> t3 >> t4;
		if (ifs.fail()) {
			break;
		}
		double media = (t1 + t2 + t3 + t4)/4.0;
		cout << location << " " << media << "\n";
	}
	
	return 0;
}
	
	