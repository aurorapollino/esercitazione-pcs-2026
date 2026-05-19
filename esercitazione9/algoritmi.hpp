#pragma once
#include "grafi.hpp"
#include "contenitori.hpp"
#include <set>
#include <map>
#include <queue>
#include <cmath>
#include <functional>


// dfs e bfs
template<typename Contenitore>
unidirected_graph graph_visit(const unidirected_graph& G, int nodo_sorgente, Contenitore& c) {
	unidirected_graph grafo;
	std::set<int> visitato; //tiene traccia dei nodi che ho già incontrato
	c.put(nodo_sorgente); //inserisco il nodo di partenza
	visitato.insert(nodo_sorgente); 
	
	while (!c.empty()) { //fino a che il contenitore non è vuoto, estraggo l'elemento
		int u = c.get();
		for (int vicino : G.neighbours(u)) { // for vicino in vicini di u
			if (!visitato.count(vicino)) {
				visitato.insert(vicino);
				c.put(vicino);
				grafo.add_edge(unidirected_edge(u, vicino)); //aggiungo l'arco al grafo
			}
		}
	}
	return grafo;
}


//dfs ricorsiva
unidirected_graph recursive_dfs(const unidirected_graph& G, int nodo_sorgente) {
	unidirected_graph grafo;
	std::set<int> visitato;
	std::function<void(int)> dfs = [&G, &visitato, &grafo, &dfs] (int u) {
		visitato.insert(u);
		for (int vicino : G.neighbours(u)) {
			if (!visitato.count(vicino)) {
				grafo.add_edge(unidirected_edge(u, vicino));
				dfs(vicino); //chiamata ricorsiva
			}
		}
	};
	dfs(nodo_sorgente);
	return grafo;
}

//Dijkstra
struct DistanzaNodo {
	int distanza;
	int posizione_nodo;
	bool operator<(const DistanzaNodo& altro) const {
		return distanza > altro.distanza;
	}
};
	

unidirected_graph dijkstra(const unidirected_graph& G, int nodo_sorgente) {
	std::map<int, int> dist; //array delle distanze
	std::map<int, int> pred; //array dei predecessori
	std::set<int> nodi = G.all_nodes();
	
	for (int i : nodi) {
		pred[i] = -1;   //inizializza a -1
		dist[i] = (int)INFINITY;  //inizializza a +Inf
	}
	pred[nodo_sorgente] = 0;
	dist[nodo_sorgente] = 0;
	
	//coda con priorità usando DistanzaNodo
	std::priority_queue<DistanzaNodo> PQ;
	//enqueue iniziale di tutti i nodi
	for (int i : nodi) {
		PQ.push({dist[i], i});
	}
	
	while (!PQ.empty()) {
		//dequeue : estraggo il nodo con la distanza minore
		int d = PQ.top().distanza;
		int n = PQ.top().posizione_nodo;
		PQ.pop();
		
		//se la distanza è stata gia vista o è maggiore di quella salvata, ignoro
		if (d > dist[n]) continue;
		
		for (int w : G.neighbours(n)) {
			int peso = 1; // il grafo non è pesato, assumo che peso = 1
			
			if (dist[w] > dist[n] + peso) {
				dist[w] = dist[n] + peso;
				pred[w] = n;
				
				PQ.push({dist[w], w});
			}
		}
	}
	
	//costruzione del grafo
	unidirected_graph grafo;
	for (int i : nodi) {
		//se il nodo ha un nodo precedente valido e non è la sorgente
		if (pred[i] != -1 && pred[i] != i) {
			grafo.add_edge(unidirected_edge(pred[i], i));
		}
	}
	return grafo;
}