#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "grafi.hpp"
#include "algoritmi.hpp"
#include "controllo_netlist.hpp"
#include "dfs_depina.hpp"
#include "risolutore_sistema.hpp"

int main() {
    std::cout << "Inserisci i dati nel formato: <netlist> <dfs/depina>\n";
    
    std::string file_netlist;
    std::string metodo;

    if (!(std::cin >> file_netlist >> metodo)) {
        std::cerr << "Errore di lettura.\n";
        return EXIT_FAILURE;
    }

    if (metodo != "dfs" && metodo != "depina") {
        std::cerr << "Metodo non riconosciuto" << "\n";
        return EXIT_FAILURE;
    }
    
    Vettori vettori;
    if (!leggi_circuito(file_netlist,vettori)) {
        return EXIT_FAILURE;
    }
    
    //calcolo dei cicli fondamentali
    std::vector<std::vector<int>> cicli;
    if (metodo == "depina") {
        cicli = trova_cicli_minimi(vettori.grafo);
    }
    else {
        cicli = cicli_dfs(vettori.grafo);
    }

    if (cicli.empty()) {
        std::cerr << "Il circuito è aperto. Impossibile risolvere il sistema.\n";
        return EXIT_FAILURE;
    }

    Risultati res = risolvi_circuito(vettori, cicli);
    if (res.tensioni.size() == 0) {
        return EXIT_FAILURE;
    }

    //output
    for (size_t i = 0; i < res.nomi.size(); i++) {
        std::cout << res.nomi[i]
                  << ": V = " << res.tensioni(i)
                  << " volts, I = " << res.correnti(i) << " amps.\n";
    }

    return EXIT_SUCCESS;
}