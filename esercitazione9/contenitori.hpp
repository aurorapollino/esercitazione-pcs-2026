#pragma once
#include <queue>
#include <stack>

//FIFO
class fifo{
private:
	std::queue<int> q; 
public:
	fifo() = default;
	//put
	void put(int valore) { 
		q.push(valore); 
	}   //inserisce un elemento in fondo alla coda
		
	//estrae l'elemento in testa alla coda
	//get
	int get() {
		int valore = q.front(); //ricorda il primo elemento
		q.pop(); // lo elimina
		return valore;
	}
		
	bool empty() const {
		return q.empty();
	}
};

//LIFO
class lifo{
private:
	std::stack<int> s; 
public:
	lifo() = default;
	//put
	void put(int valore) { 
		s.push(valore); 
	}   //inserisce un elemento in cima allo stack
		
	//estrae l'elemento sulla cima dello stack
	//get
	int get() {
		int valore = s.top(); //ricorda l'ultimo elemento aggiunto
		s.pop(); // lo elimina
		return valore;
	}
		
	bool empty() const {
		return s.empty();
	}
};
			