#include "grafi.hpp"
#include <iostream>
#include <set>
#include <list>
#include "contenitori.hpp"
#include "algoritmi.hpp"
#include <fstream>

//per GraphViz
	
	static void to_graphviz(const unidirected_graph& G, const std::string& filename, const std::string& title = "G")
{
    std::ofstream f(filename);
    f << "grafo " << title << " {\n";
    f << "  node [shape=circle];\n";
	//elenco tutti gli archi
    for (const auto& arco : G.all_edges())
        f << "  " << arco.from() << " -- " << arco.to() << ";\n";
    f << "}\n";
    std::cout << "  -> " << filename << " salvato\n";
}


int main() {
	//Test from to
	std::cout << "\n";
	std::cout << "TEST FROM_TO" << "\n";
	std::cout << "\n";
	
	unidirected_edge e1(5,9);
	std::cout << "Arco: " << e1 << "\n";
	std::cout << "\n";
	
	if (e1.from() == 5) {
		std::cout << "Test from_to passato per from " << "\n";
	} else {
		std::cout << "Test from_to nom passato per from "<< "\n";
	}
	
	if (e1.to() == 9) {
		std::cout << "Test from_to passato per to " << "\n";
	} else {
		std::cout << "Test from_to non passato per to " << "\n";
	}
	
	
	//Test operator<
	unidirected_edge e2(1,6);
	unidirected_edge e3(6,1);
	unidirected_edge e4(3,7);
	
	std::cout << "\n";
	std::cout << "TEST OPERATOR<" << "\n";
	std::cout << "\n";
	std::cout << "Archi: " << e2 << "," << e3 << "," << e4 << "\n";
	std::cout << "\n";
	
	if (e2 < e4) {
		std::cout << "Test operator< " << e2 << " < " << e4 << " passato"<< "\n";
	}
	else {
		std::cout << "Test operator< " << e2 << " < " << e4 << " non passato"<< "\n";
	}
	
	
	//Test operator==
	std::cout << "\n";
	std::cout << "TEST OPERATOR==" << "\n";
	std::cout << "\n";
	std::cout << "Archi: " << e2 << "," << e3 << "," << e4 << "\n";
	std::cout << "\n";
	
	if (e2 == e3) {
		std::cout <<"Test operator " << e2 << " = " << e3 << " passato" << "\n";
	}
	else {
		std::cout << "Test operator " << e2 << " = " << e3 << " non passato"  << "\n";
	}
	
	if (e2 == e4) {
		std::cout <<"Test operator " << e2 << " = " << e4 << " passato" << "\n";
	}
	else {
		std::cout << "Test operator " << e2 << " = " << e4 << " non passato" << "\n";
	}
		
	
	//Costruttore di copia
	std::cout << "\n";
	std::cout << "TEST COSTRUTTORE DI COPIA" << "\n";
	std::cout << "\n";
	
	unidirected_graph g_originale;
	
	unidirected_edge e17(0,1);
	unidirected_edge e18(1,2);
    g_originale.add_edge(e17);
    g_originale.add_edge(e18);
	
	std::cout << "Archi: " << e17 << "," << e18 << "\n";
	std::cout << "\n";

    unidirected_graph g_copia(g_originale);

    if (g_copia.all_edges().size() == g_originale.all_edges().size()) {
        std::cout << "Test copia passato: la copia ha lo stesso numero di archi dell'originale" << "\n";
    } 
	else {
        std::cout << "Test copia non passato: la copia deve avere lo stesso numero di archi dell'originale" << "\n";
    }

    g_copia.add_edge(unidirected_edge(1, 3));
    if (g_originale.all_edges().size() == 2) {
        std::cout << "Test copia passato: modificando la copia l'originale non cambia" << "\n";
	}
	else {
        std::cout << "Test copia non passato: se si modifica la copia, l'originale non deve caambiare" << "\n";
    }
	
	
	//Test neighbours()
	std::cout << "\n";
	std::cout << "TEST NEIGHBOURS" << "\n";
	std::cout << "\n";
	
	unidirected_graph g_neib;
	
	unidirected_edge e11(0,1);
	unidirected_edge e12(0,2);
	unidirected_edge e13(1,3);
    g_neib.add_edge(e11);
    g_neib.add_edge(e12);
    g_neib.add_edge(e13);
	
	std::cout << "Archi: " << e11 << "," << e12 << "," << e13 << "\n";
	std::cout << "\n";

    auto vicino_0 = g_neib.neighbours(0);
    if (vicino_0.size() == 2) {
        std::cout << "Test neighbours passato: il nodo 0 ha 2 vicini" << "\n";
    } 
	else {
        std::cout << "Test neighbours non passato: il nodo 0 deve avere 2 vicini" << "\n";
    }
    if (vicino_0.count(1) == 0 || vicino_0.count(2) == 0) { // se 1 cèe 0 volte o 2 c'e 0 volte
        std::cout << "Test neighbours non passato: i vicini di 0 devono essere 1 e 2" << "\n";
    } 
	else {
        std::cout << "Test neighbours passato: i vicini di 0 sono 1 e 2" << "\n";
    }
	
	auto vicino_5 = g_neib.neighbours(5);
    if (vicino_5.empty()) {
        std::cout << "Test neighbours passato: il nodo inesistente restituisce l'insieme vuoto" << "\n";
    } 
	else {
        std::cout << "Test neighbours non passato: un nodo che non esiste deve restituire l'insieme vuoto" << "\n";
    }
	
	
	//Test add_edge, all_edges, all_nodes
	std::cout << "\n";
	std::cout << "TEST ADD_EDGES, ALL_EDGES, ALL_NODES" << "\n";
	std::cout << "\n";
	
	unidirected_graph g;
	
	unidirected_edge e5(0,1);
	unidirected_edge e6(1,2);
	unidirected_edge e7(0,2);
	
	g.add_edge(e5);
	g.add_edge(e6);
	g.add_edge(e7);
	
	std::cout << "Archi: " << e5 << "," << e6 << "," << e7 << "\n";
	std::cout << "\n";
	auto nodi = g.all_nodes();
	if (nodi.size() == 3) {
		std::cout << "Test all_nodes passato: il grafo ha 3 nodi" << "\n";
	} 
	else {
		std::cout << "Test all_nodes non passato: il grafo deve avere 3 nodi" << "\n";
	}
	if (nodi.count(0) == 0 || nodi.count(1) == 0 || nodi.count(2) == 0) {
		std::cout << "Test all_nodes non passato: i nodi 0,1,2 devono essere presenti" << "\n";
	}
	else {
		std::cout << "Test all_nodes passato: i nodi 0,1,2 sono presenti" << "\n";
	}
	
	auto archi = g.all_edges();
	if (archi.size() == 3) {
		std::cout << "Test all_edges passato: il grafo ha 3 archi" << "\n";
	} 
	else {
		std::cout << "Test all_edges non passato: il grafo deve avere 3 archi" << "\n";
	}
	
	
	//Test archi duplicati
	std::cout << "\n";
	std::cout << "TEST ARCHI DUPLICATI" << "\n";
	std::cout << "\n";
	
	unidirected_graph g_edges;
	
	unidirected_edge e8(1,2);
	unidirected_edge e9(1,2);
	unidirected_edge e10(2,1);//inverso
	
	g_edges.add_edge(e8);
	g_edges.add_edge(e9);
	g_edges.add_edge(e10);  
	
	std::cout << "Archi: " << e8 << "," << e9 << "," << e10 << "\n";
	std::cout << "\n";
	
	if (g_edges.all_edges().size() == 1) {
		std::cout << "Test sugli archi duplicati passato: l'arco duplicato è stato ignorato" << "\n";
	}
	else {
		std::cout << "Test sugli archi duplicati non passato: ci deve essere solo 1 arco anche se ci sono stati 3 inserimenti" << "\n";
	}
	
	
	
	//Test edge_number() e edge_at()
	std::cout << "\n";
	std::cout << "TEST EDGE_NUMBER E EDGE_AT" << "\n";
	std::cout << "\n";
	
	unidirected_graph g_num;
	
	unidirected_edge e14(0,1);
	unidirected_edge e15(0,2);
	unidirected_edge e16(1,3);
	g_num.add_edge(e14);
	g_num.add_edge(e15);
	g_num.add_edge(e16);
	
	std::cout << "Archi: " << e14 << "," << e15 << "," << e16 << "\n";
	std::cout << "\n";

	unidirected_edge cercato(0, 2);
    int indice = -1;
    bool trovato = g_num.edge_number(cercato, indice);  //restituisce true se l'arco esiste e scrive il suo indice

    if (trovato) {
        std::cout << "Test edge_number passato: trovato l'arco all'indice " << indice << "\n";
    } 
	else {
        std::cout << "Test edge_number non passato: edge_number deve trovare l'arco (1,2)" << "\n";
    }


	//prendo l'indice e mi dice quale arco corrisponde a quell'indice
	unidirected_edge ritrovato(0,0);
    bool found = g_num.edge_at(indice, ritrovato); //cerco l'arco all'indice e lo scrivo in ritrovato, se è true lo trovo
    if (found) {
        std::cout << "Test edge_at passato: edge_at ha trovato l'arco " << ritrovato << "\n";
    } 
	else {
        std::cout << "Test edge_at non passato: edge_at deve trovare l'arco all'indice " << indice << "\n";
    }
	
	//l'arco trovato con edge_at è lo stesso di quello trovato in edge_number
    if ((ritrovato == cercato)) {
        std::cout << "Test passato: l'arco ritrovato in edge_at coincide con quello cercato in edge_number" << "\n";
    } 
	else {
        std::cout << "Test non passato: edge_at deve restituire lo stesso arco cercato in edge_number" << "\n";
    }
	
	int indice_2 = -1;
    if (g_num.edge_number(unidirected_edge(3, 4), indice_2)) {
        std::cout << "Test edge_number non passato: edge_number non deve trovare un arco che non esiste" << "\n";
    } 
	else {
        std::cout << "Test edge_number passato: edge_number non trova un arco che non esiste" << "\n";
    }

    unidirected_edge arco_2(0, 0);
    if (g_num.edge_at(5, arco_2)) {
        std::cout << "Test edge_at non passato: edge_at non deve trovare nulla che abbia indice fuori dal range" << "\n";
    } 
	else {
        std::cout << "Test edge_at passato: edge_at non trova nulla che abbia indice fuori dal range" << "\n";
    }
	
	
	//Test operator-()
	std::cout << "\n";
	std::cout << "TEST OPERATOR-" << "\n";
	std::cout << "\n";
	
	unidirected_graph g1, g2;
	
	unidirected_edge e19(0,1);
	unidirected_edge e20(1,3);
	unidirected_edge e21(2,3);
	unidirected_edge e22(1,3);
	
    g1.add_edge(e19);
    g1.add_edge(e20);
    g1.add_edge(e21);
    g2.add_edge(e22);
	
	std::cout << "Archi: " << e19 << "," << e20 << "," << e21 << "," << e22 << "\n";
	std::cout << "\n";

    unidirected_graph diff = g1 - g2;
    auto diff_archi = diff.all_edges();

    if (diff_archi.size() == 2) {
        std::cout << "Test operator- passato : (G1 - G2) ha 2 archi" << "\n";
    } 
	else {
        std::cout << "Test operator- non passato: (G1 - G2) deve avere 2 archi" << "\n";
    }
	
	bool arco_cancellato = false;
    for (auto& e : diff_archi) {
        if (e == unidirected_edge(1, 3)){
            arco_cancellato = true;
		}
	}
    if (arco_cancellato) {
        std::cout << "Test operator- non passato: l'arco (1,3) non deve essere presente nella differenza (G1 - G2)" << "\n";
    } 
	else {
        std::cout << "Test operator- passato: l'arco (1,3) non è presente nella differenza (G1 - G2)" << "\n";
    }
	std::cout << "\n";
	
	
	
	//Costruisco il grafo
	unidirected_graph G;
    
    
    // Nodi collegati a 1
    G.add_edge(unidirected_edge(1, 2));
    G.add_edge(unidirected_edge(1, 3));
    G.add_edge(unidirected_edge(1, 4));
    G.add_edge(unidirected_edge(1, 6));
    
    // Nodi collegati a 2 (escluso l'1 già messo)
    G.add_edge(unidirected_edge(2, 4));
    G.add_edge(unidirected_edge(2, 5));
    G.add_edge(unidirected_edge(2, 7));
    
    // Nodi collegati a 3
    G.add_edge(unidirected_edge(3, 6));
    
    // Nodi collegati a 4
    G.add_edge(unidirected_edge(4, 6));
    G.add_edge(unidirected_edge(4, 7));
    
    // Nodi collegati a 5
    G.add_edge(unidirected_edge(5, 7));
    
    // Nodi collegati a 6
    G.add_edge(unidirected_edge(6, 7));
    G.add_edge(unidirected_edge(6, 8));
    
    // Nodi collegati a 7
    G.add_edge(unidirected_edge(7, 9));
    
    // Nodi collegati a 8
    G.add_edge(unidirected_edge(8, 9));
	
	//Effettua una visita in ampiezza di G, restituendo il risultato in bfsG
	fifo q;
	auto bfsG = graph_visit(G, 1, q);
	to_graphviz(bfsG, "bfs.dot", "BFS_grafo");
	std::cout << "File bfs.dot creato" << "\n";
	std::cout << "\n";
	
	//Effettua una visita in profondità di G, restituendo il risultato in dfsG 
	lifo s;
	auto dfsG = graph_visit(G, 1, s);
	to_graphviz(dfsG, "dfs.dot", "DFS_grafo");
	std::cout << "File dfs.dot creato" << "\n";
	
	return 0;
	
}

	



