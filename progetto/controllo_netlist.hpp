
#pragma once 
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
#include "grafi.hpp"

struct Elemento  {   
    std::string componente;  // R1, V1, R2,...
    char tipo;   // o R o V
    double valore; // il valore di R o V
    int nodo1; // + o - per V; nodo1 , nodo2 per R
    int nodo2;

};

struct Vettori {
    std::vector<Elemento> elementi;
    unidirected_graph grafo;
};

//Gestione errori:
bool gestione_errori(const std::string& componente, double valore, int nodo1, int nodo2) {

    //verifico il formato del NetList

    if (componente.size() < 2) {
        std::cerr << "Il formato del componente " << componente << " non è valido" << "\n";
        return false;
    }
    if (componente[0] != 'R' && componente[0] != 'V') {
        std::cerr << "Componente " << componente << " non valido" << "\n";
        return false;
    }
    for (size_t i = 1; i < componente.size(); i++) {
        if (!std::isdigit(componente[i])) {
            std::cerr << "Il componente " << componente << " è scritto in un formato non valido" << "\n";
            return false;
        }
    }
    if (componente[0] == 'R' && valore <= 0.0) {
        std::cerr << "Valore non valido per la resistenza " << componente << "\n";
        return false;
    }
    if (nodo1 == nodo2) {
        std::cerr << "Il componente " << componente << " collega due nodi uguali" << "\n";
        return false;
    }
    return true;

}

//grafo connesso
bool grafo_connesso(const unidirected_graph& G) {
    std::set<int> nodi = G.all_nodes();

    if (nodi.empty()) {
        return false;
    }

    std::set<int> visitati;
    std::vector<int> pila;
    int partenza = *nodi.begin();
    pila.push_back(partenza);
    visitati.insert(partenza);

    while (!pila.empty()) {
        int u = pila.back();
        pila.pop_back();

        for (int vicino : G.neighbours(u)) {
            if (!visitati.count(vicino)) {
                visitati.insert(vicino);
                pila.push_back(vicino);
            }
        }
    }
    if (visitati.size() != nodi.size()) {
        std::cerr << "Il grafo non è connesso" << "\n";
        return false;
    }
    return true;

}

//apertura file
bool leggi_circuito(const std::string& nome_file, Vettori& vettori) {
    std::ifstream ifs(nome_file);
    if (!ifs.is_open()) {
        std::cerr << "Impossibile aprire il file " << nome_file << "\n";
        return false;
    }

    //ordine delle componenti

    std::string riga;
    while (std::getline(ifs, riga)) {
        if (std::all_of(riga.begin(), riga.end(), ::isspace)) {
            continue;
        }

        std::istringstream iss(riga);
        std::string componente;
        double valore;
        int nodo1;
        int nodo2;
        if (!(iss >> componente >> valore >> nodo1 >> nodo2)) {
            std::cerr << "Formato non valido per " << riga << "\n";
            return false;
        }

        std::string parametri_extra;
        if (iss >> parametri_extra) { 
            // Se lo stream riesce a leggere un'altra parola (es. il 99), c'è roba di troppo!
            std::cerr << "Formato non valido: parametri in eccesso nella riga " << riga << "\n";
            return false;
        }

        if (!gestione_errori(componente, valore, nodo1, nodo2)) {
            return false;
        }
        Elemento e{componente, componente[0], valore, nodo1, nodo2};
        vettori.elementi.push_back(e);
        vettori.grafo.add_edge(unidirected_edge(nodo1, nodo2));
        }

    if (vettori.elementi.empty()) {
        std::cerr << "Nessun componente presente nel file" << "\n";
        return false;
    }

    //Almeno un resistore e almeno un generatore
    std::vector<Elemento> resistori, generatori;
    for (const auto& elem : vettori.elementi) {
        if (elem.tipo == 'R') {
            resistori.push_back(elem);
        }
        else {
            generatori.push_back(elem);
        }
    }
    if (resistori.empty()) {
        std::cerr << "Nessun resistore presente nel circuito" << "\n";
        return false;
    }
    if (generatori.empty()) {
        std::cerr << "Nessun generatore presente nel circuito" << "\n";
        return false;
    }

    //No collegamenti in parallelo
    std::map<unidirected_edge, std::string> archi_usati;
    for (const auto& elem : vettori.elementi) {
        unidirected_edge arco(elem.nodo1, elem.nodo2);
        if (archi_usati.contains(arco)) {
            std::cerr << "Il collegamento in parallelo non è ammesso tra " << archi_usati[arco] << " e " << elem.componente << "\n";
            return false;
        }
        archi_usati[arco] = elem.componente;
    }    

    if (!grafo_connesso(vettori.grafo)) {
        return false;
    }

    return true;
}
