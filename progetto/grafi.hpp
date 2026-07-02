#pragma once
#include <iostream>
#include <set>
#include <map>
#include <unordered_map>
#include <stdexcept>
#include <list>
#include <algorithm>
#include <vector>

//implemento la classe arco in un grafo non orientato
class unidirected_edge {
private:
	int n_from;
	int n_to;
	
public:
	//è sempre garantito che from è minore di to
	unidirected_edge(int n1, int n2) {
		n_from = std::min(n1, n2);
		n_to = std::max(n1, n2);
	}
	
	//per restituire i due nodi dell'arco
	int from() const {
		return n_from;
	}
	
	int to() const {
		return n_to;
	}
	
	//operatore < in modo da rendere ordinabili gli archi
	bool operator<(const unidirected_edge& other) const {
		if (n_from != other.n_from) {
			return n_from < other.n_from;
		}
		return n_to < other.n_to;
	}
	
	//operatore == in per avere l'uguaglianza
	bool operator==(const unidirected_edge& other) const {
		return n_from == other.n_from && n_to == other.n_to;
	}
};

//operatore << 
std::ostream& operator<<(std::ostream& os, const unidirected_edge& edge) {
	os<<"(" <<edge.from() <<", " << edge.to() << ")";
	return os;
}

//implemento un grafo non orientato
class unidirected_graph{
	private:
	//lista di adiacenza
	std::unordered_map<int, std::set<int>> adiacenza;
	//archi di ordine di inserimento
	std::vector<unidirected_edge> edges_per_indice;
	//mappa arco-> indice
	std::map<unidirected_edge, int> edge_indice;
	
	
	public:
	//costruttore di default
	unidirected_graph() = default;
			
	//costruttore di copia
	unidirected_graph(const unidirected_graph&) = default;
		
		
	//metodo neighbours() che restituisce i nodi vicini di un nodo
	std::set<int> neighbours(int nodo) const {
		auto iteratore = adiacenza.find(nodo);
		if (iteratore == adiacenza.end()) {
			return {};
		}
		return (*iteratore).second;
	}
	
	//metodo add_edge() che permette di aggiungere un arco al grafo
	void add_edge(const unidirected_edge& edge) {
		if (edge_indice.find(edge) != edge_indice.end()) {   // se l'arco esiste già, non lo aggiungo
			return;
		}
		//calcolo il nuovo indice per l'arco che devo inserire
		size_t indice = edges_per_indice.size();
		//aggiungo l'arco alla fine
		edges_per_indice.push_back(edge);
		edge_indice[edge] = indice;
		
		adiacenza[edge.from()].insert(edge.to());
		adiacenza[edge.to()].insert(edge.from());
	}
	
	//metodo all_edges() che restituisce tutti gli archi
	std::list<unidirected_edge> all_edges() const {
		return std::list<unidirected_edge>(edges_per_indice.begin(), edges_per_indice.end());
	}
	
	//metodo all_nodes() che restituisce tutti i nodi
	std::set<int> all_nodes() const {
		std::set<int> nodi;
		
		for (const auto& coppia : adiacenza){
			nodi.insert(coppia.first);
		}
		return nodi;
	}
	
	//operator-() permette di calcolare la differenza tra due grafi
	unidirected_graph operator-(const unidirected_graph& other) const {
		unidirected_graph result; //si crea un grafo vuoto dove si mette la differenza
		for (const auto& edge : edges_per_indice) {
			if (other.edge_indice.find(edge) == other.edge_indice.end()) { //se non ho trovato  l'arco, aggiungilo alla differenza
				result.add_edge(edge);
			}
		}
		return result;
	}
};
	
	
	

		