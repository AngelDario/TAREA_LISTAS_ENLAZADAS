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
struct LIST {
	NODE<T>* head, *end;
	O order;

	LIST() {
		head = NULL;
		end = NULL;
	}

	~LIST() {
		NODE<T>* a;
		NODE<T>* b;
		a = head;
		while (a != end) {
			b = a->next;
			delete a;
			a = b;
		}
		cout << "Lista eliminada." << endl;
	}

	bool find(T val, NODE<T>*& p) {
		NODE<T>* temp = head;
		p = temp;
		while (temp && order(temp->val, val)) {
			if (temp->val == val) {
				return 1;
			}
			p = temp;
			temp = temp->next;
			if (temp == head) {
				return 0;
			}
		}
		return 0;
	}

	bool add(T val) {
		NODE<T>* p = NULL;
		if (!find(val, p)) {
			if (!p) {
				head = new NODE<T>(val, head);
				end = head;
				head->next = head;
			}
			else if (order(val, p->val) && p == head) {
				head = new NODE<T>(val, head);
				end->next = head;
			}
			else {
				p->next = new NODE<T>(val, p->next);
				if (p->next->next == head) {
					end = p->next;
				}
			}
			return 1;
		}
		return 0;
	}

	bool del(T val) {
		NODE<T>* p = NULL;
		if (find(val, p)) {
			if (p == head && p->val == val) {
				head = head->next;
				end->next = head;
				delete p;
			}
			else if (p == head && order(p->val, val)) {
				NODE<T>* temp = p->next;
				p->next = p->next->next;
				delete temp;
			}else if (p->next == end) {
				NODE<T>* temp = p->next;
				end = p;
				p->next = head;
				delete temp;
			}
			else {
				NODE<T>* temp = p->next;
				p->next = p->next->next;
				delete temp;
			}
		}
		return 0;
	}

	void print() {
		NODE<T>* p = head;
		while (p) {
			cout << p->val << " -> ";
			p = p->next;
			if (p == head) {
				break;
			}
		}
		cout << endl;
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
