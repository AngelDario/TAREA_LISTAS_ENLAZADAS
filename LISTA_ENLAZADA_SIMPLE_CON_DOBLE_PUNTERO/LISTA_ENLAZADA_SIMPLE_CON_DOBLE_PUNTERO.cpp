#include <iostream>

using namespace std;

struct Cgreater {
	inline bool operator() (int a, int b) {
		return a < b;
	}
};

struct Cless {
	inline bool operator() (int a, int b) {
		return a > b;
	}
};

template<class T>
class NODE {
	public:
		int val;
		NODE<T>* next;

		NODE<T>(T _val, NODE* n = NULL ) : val(_val) {
			next = n;
		}
};

template<class T, class O>
struct LIST {
	NODE<T>* head;
	O order;

	LIST() {
		head = NULL;
	}

	~LIST() {
		NODE<T>* a;
		NODE<T>* b;
		a = head;
		while (a) {
			b = a ->next;
			delete a;
			a = b;
		}
		cout << "Lista eliminada." << endl;
	}

	bool find(T val, NODE<T>**& p) {
		p = &head;
		while (*p && order((*p)->val, val)) {
			p = &((*p)->next);
		}
		return (*p) && (*p)->val == val;
	}

	bool add(T val){
		NODE<T>** p;
		if (!find(val, p)) {
			*p = new NODE<T>(val, *p);
			return 1;
		}
		return 0;
	}
		
	bool del(T val) {
		NODE<T>** p;
		if (find(val, p)) {
			NODE<T>* temp = *p;
			*p = (*p)->next;
			delete temp;
			return 1;
		}
		return 0;
	}

	void print() {
		NODE<T>** p = &head;
		while (*p) {
			cout << (*p)->val << " -> ";
			p = &((*p)->next);
		}
		cout << "NULL" << endl;
	}
	
};

bool menu() {
	int x;
	int accion;
	LIST<int, Cless> l;

	while (1) {
		system("cls");
		cout << "LISTA: \n";
		l.print();
		cout << endl;
		cout << "Elegir accion: \n";
		cout << "1. Add \n";
		cout << "2. Del \n";
		cout << "3. Salir del programa \n";
		cout << "Ingrese numero de la accion: ";
		cin >> accion;
		cout << endl;
		

		switch (accion)
		{
		case 1:
			cout << "Ingrese numero para la lista: ";
			cin >> x;
			l.add(x);
			continue;
		case 2:
			cout << "Ingrese numero para la lista: ";
			cin >> x;
			l.del(x);
			continue;
		case 3:
			l.~LIST();
			exit(0);
		default:
			cout << "Valor incorrecto.";
		}

	}
}



int main() {

	menu();

	return 0;
}
