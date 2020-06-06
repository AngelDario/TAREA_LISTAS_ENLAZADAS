#include <iostream>

using namespace std;

template <class T>
class NODE {
public:
    T val;
    NODE* next;

    NODE(T _val, NODE* n = NULL) : val(_val) {
        next = n;
    }
};

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


template <class T, class O>
struct LIST {
    NODE<T>* head;
    NODE<T>* end;
    O order;

    LIST() {
        end = NULL;
        head = NULL;
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

    void endf() {
        NODE<T>* p;
        p = head;
        while (p->next != head) {
            p = p->next;
        }
        end = p;
    }

    bool find(T val, NODE<T>**& p) {
		p = &head;
		while (*p && order((*p)->val, val)) {
            if ((*p)->val == val) {
                return 1;
            }
			p = &((*p)->next);
            if (*p == head) {
                return 0;
            }
		}
		return (*p) && (*p)->val == val;
	}

    bool add(T val) {
        NODE<T>** p;
        if (!find(val, p)) {
            if (!(*p)) {
                *p = new NODE<T>(val, head);
                (*p)->next = head;
                end = head;
                return 1;
            }else if(*p == head && order(head->val,val)){
                *p = new NODE<T>(val, *p);
                end = *p;
            }else if(order(val, (*p)->val)){
                *p = new NODE<T>(val, *p);
                end->next = head;
            }
            else {
                *p = new NODE<T>(val, *p);
            }
            return 1;
        }
        return 0;
    }

    bool del(T val) {
        NODE<T>** p;
        if (find(val, p)) {
            if (*p == head) {
                NODE<T>* temp = *p;
                end->next = (*p)->next;
                *p = (*p)->next;
                delete temp;
                return 1;
            }if (*p == end) {
                NODE<T>* temp = *p;
                *p = (*p)->next;
                delete temp;
                endf();
                return 1;
            }
            NODE<T>* temp = *p;
            *p = (*p)->next;
            delete temp;
            return 1;
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

int main()
{

    menu();
}