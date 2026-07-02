#pragma once 
#include <vector>
#include <limits>
#include <set> 
#include <map> 
#include "grafi.hpp"
#include "algoritmi.hpp"

//trova il percorso tra u e v
bool findpath(const unidirected_graph& T, int u, int v, std::set<int>& nodi_visitati, std::vector<int>& percorso) {
    nodi_visitati.insert(u);
    percorso.push_back(u);
    if (u == v) { 
        return true;
    }
    for (int n : T.neighbours(u)) {
        if (!nodi_visitati.count(n) && findpath(T, n, v, nodi_visitati, percorso)) { 
            return true;
        }
    }  
    percorso.pop_back();
    return false;
}

//calcolo i cicli fondamentali con DFS
std::vector<std::vector<int>> cicli_dfs(const unidirected_graph& G) {
    std::set<int> nodi = G.all_nodes();
    if (nodi.empty()) {
        return{};
    }

    unidirected_graph T = recursive_dfs(G, *nodi.begin());
    unidirected_graph C = G - T;

    std::vector <std::vector<int>> cicli;
    for (const auto& arco : C.all_edges()) {
        std::set<int> nodi_visitati;
        std::vector<int> percorso;
        if (findpath(T, arco.from(), arco.to(), nodi_visitati, percorso)) {
            cicli.push_back(percorso);
        }
    }
    return cicli;
}

//calcolo i cicli minimi con De Pina

//calcolo il prodotto scalare
int prodotto_scalare(const std::vector<bool>& S, const std::vector<bool>& P) {
    int prodotto = 0;
    for (size_t i = 0; i < S.size(); i++) {
        auto contributo = S[i] && P[i];
        prodotto ^= contributo;
    }
    return prodotto;
}

//calcolo la differenza simmetrica
std::vector<bool> differenza_simmetrica(const std::vector<bool>& S, const std::vector<bool>& P) {
    std::vector<bool> differenza(S.size(), false);
    for (size_t i = 0; i < S.size(); i++) {
        differenza[i] = S[i] ^ P[i];
    }
    return differenza;
}

//Creo un grafo ausiliario per trovare il ciclo minimo

//duplico i vertici del grafo: costruisco v+ e v- in modo da non sovrapporre nodi originali e copie
int v_piu(int v) {
    return v;
}
int v_meno(int v, int N) {
    return v + N;
}


//trovo cicli minimi
std::vector<std::vector<int>> trova_cicli_minimi(const unidirected_graph& G) {
    std::set<int> nodi = G.all_nodes();
    if (nodi.empty()) {
        return {};
    }
    unidirected_graph T = recursive_dfs(G, *nodi.begin());
    unidirected_graph C =  G - T;
    auto archi = G.all_edges();
    int numero_archi = G.all_edges().size();

    //mappa per i vettori di incidenza
    std::map<unidirected_edge, int> archi_incidenza;
    int indice = 0;
    for (const auto& e : archi) {
        archi_incidenza[e] = indice++;
    }

    auto lista_archi_C = C.all_edges();
    std::vector<unidirected_edge> archi_C(lista_archi_C.begin(), lista_archi_C.end());
    size_t numero_cicli_fond = archi_C.size();
    
    std::vector<std::vector<bool>> S(numero_cicli_fond, std::vector<bool>(numero_archi, false));
    for (size_t i = 0; i < numero_cicli_fond; i++) {
        S[i][archi_incidenza[archi_C[i]]] = true;
    }
    int N = *nodi.rbegin() + 1;

    std::vector<std::vector<int>> cicli;
    for (size_t i = 0; i < numero_cicli_fond; i++) {
        unidirected_graph G_primo;
        auto it_archi = archi.begin();
        //aggiungo archi
        for (int k = 0; k < numero_archi; k++, it_archi++) {
            int u = (*it_archi).from(); 
            int v = (*it_archi).to();
            if (S[i][k]) {
                G_primo.add_edge(unidirected_edge(v_piu(u), v_meno(v,N)));
                G_primo.add_edge(unidirected_edge(v_piu(v), v_meno(u,N)));
            }
            else {
                G_primo.add_edge(unidirected_edge(v_piu(u), v_piu(v)));   
                G_primo.add_edge(unidirected_edge(v_meno(u,N), v_meno(v,N)));
            }

        }
        //calcolo cammino minimo
        std::vector<bool> ciclo_minimo;
        int lunghezza_ciclo_migliore = std::numeric_limits<int>::max();
        for (int v : nodi) {
            unidirected_graph T_primo = dijkstra(G_primo, v_meno(v,N));
            std::set<int> visitati;
            std::vector<int> percorso;
            if (!findpath(T_primo, v_meno(v,N), v_piu(v), visitati, percorso)) {
                continue;
            }
            //trasformo il cammino trovato nel grafo G_primo in un ciclo del grafo G
            std::vector<bool> candidato(numero_archi, false);
            for (size_t p = 0; p + 1 < percorso.size(); p++) {
                int p1 = percorso[p]; 
                int p2 = percorso[p+1];
                if (p1 >= N) {
                    p1 = p1 - N;
                }
                if (p2 >= N) {
                    p2 = p2 - N; 
                }
                unidirected_edge arco(p1, p2);
                if (archi_incidenza.count(arco)) {
                    int ind = archi_incidenza[arco];
                    candidato[ind] = candidato[ind]^true;
                }  
            }
            int lunghezza_ciclo = 0;
            for (bool presente : candidato) {
                if (presente) {
                    lunghezza_ciclo++;
                }
            }
            //conservo il ciclo con il più piccolo numero di elementi 1
            if (prodotto_scalare(candidato, S[i]) == 1 && lunghezza_ciclo < lunghezza_ciclo_migliore) {
                lunghezza_ciclo_migliore = lunghezza_ciclo;
                ciclo_minimo = candidato;
            }
        }

        if (ciclo_minimo.empty()) {
            return {};
        }

        //converto un vettore di incidenza nella sequenza di nodi che percorre il ciclo
        std::map<int, std::vector<int>> adiacenza;
        auto iteratore = archi.begin();
        for (size_t e = 0; e < ciclo_minimo.size(); e++, iteratore++) {
            if (ciclo_minimo[e]) {
                int u = (*iteratore).from();
                int v = (*iteratore).to();
                adiacenza[u].push_back(v);
                adiacenza[v].push_back(u);
            }
        }
        if (adiacenza.empty()) {
            return {};
        }

        int partenza = (*adiacenza.begin()).first; 
        std::vector<int> ciclo;
        int corrente = partenza;
        int precedente = -1;

        ciclo.push_back(partenza);
        while (true) {
            int prossimo = -1;
            for (int vicino : adiacenza[corrente]) {
                if (vicino != precedente) {
                    prossimo = vicino;
                    break;
                }
            }
            if (prossimo == -1) {
                return {};
            }
            precedente = corrente;
            corrente = prossimo;

            if (corrente == partenza) {
                break;
            }
            ciclo.push_back(corrente);
        }

        cicli.push_back(ciclo);

        // S[j] = S[j] XOR miglior ciclo per tutti j > i con prodotto scalare = 1
        for (size_t j = i + 1; j < numero_cicli_fond; j++) {
            if (prodotto_scalare(ciclo_minimo, S[j]) == 1) {
                S[j] = differenza_simmetrica(S[j], ciclo_minimo);
            }
        }
    }
    return cicli;
}