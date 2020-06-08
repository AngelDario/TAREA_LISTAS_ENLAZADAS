#include <iostream>
#include <stdlib.h>

using namespace std;

struct Cgreater {
	inline bool operator() (int a, int b) {
		return a <= b;
	}
};

struct Cless {
	inline bool operator() (int a, int b) {
		return a >= b;
	}
};

template <class T>
class NODE {
public:
	T val;
	NODE* next;

	NODE(T _val, NODE* x = NULL) : val(_val) {
		next = x;
	}
};

template <class T, class O>
struct LIST{
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
			b = a->next;
			delete a;
			a = b;
		}
		cout << "Lista eliminada." << endl;
	}

	bool find(T val, NODE<T>*& p) {
		NODE<T>* temp = head;
		p = temp;
		while (temp && order(temp ->val, val)) {
			if (temp->val == val) {	
				return 1;
			}
			p = temp;
			temp = temp->next;
		}
		return 0;
	}

	bool add(T val) {
		NODE<T>* p = NULL;
		if (!find(val, p)) {
			if (!p || order(val, p->val)) {
				head = new NODE<T>(val, head);
			}
			else {
				p -> next = new NODE<T>(val, p->next);
			}
			return 1;
		}
		return 0;
	}

	bool del(T val) {
		NODE<T>* p = NULL;
		if (find(val, p)) {
			if (p->val == val) {
				NODE<T>* aux = p;
				head = p->next;
				delete aux;
				return 1;
			}
			else if (p->next->next == NULL) {
				p->next = NULL;
				return 1;
			}
			NODE<T>* aux = p ->next;
			p->next = p->next->next;
			delete aux;
			return 1;
		}
		return 0;
	}

	void print() {
		NODE<T>* p = head;
		while (p) {
			cout << p->val<< " -> ";
			p = p->next;
		}
		cout <<"NULL"<< endl;
	}
};

bool menu() {
	char x;
	int accion;
	LIST<char, Cgreater> l;

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
