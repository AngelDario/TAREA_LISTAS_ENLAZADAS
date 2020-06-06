#include <iostream>
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
    NODE<T>* next;
    NODE<T>* prev;

    NODE(T _val, NODE<T>* n = NULL, NODE<T>* p = NULL) : val(_val) {
        next = n;
        prev = p;
    }
};

template <class T, class O>
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
        }
        return 0;
    }

    bool add(T val) {
        NODE<T>* p = NULL;
        if (!find(val, p)) {
            if (!p) {
                head = new NODE<T>(val, head, NULL);
            }
            else if (p == head && order(val, p->val)) {
                head = new NODE<T>(val, head, NULL);
                p->prev = head;
            }
            else {
                NODE<T>* temp = p->next;
                if (temp) {
                    p->next = new NODE<T>(val, p->next, p);
                    temp->prev = p->next;
                }
                else {
                    p->next = new NODE<T>(val, p->next, p);
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
                head->prev = NULL;
                delete p;
            }
            else {
                p = p->next;
                NODE<T>* temp = p;
                p = p->prev;
                p->next = p->next->next;
                if (p->next != NULL) {
                    p = p->next;
                    p->prev = p->prev->prev;
                }
                delete temp;
            }
            return 1;
        }
        return 0;
    }

    void print() {
        NODE<T>* p = head;
        while (p) {
            cout << p->val << " <-> ";
            p = p->next;
        }
        cout << "NULL" << endl;
    }
};

bool menu() {
    int x;
    int accion;
    LIST<int, Cgreater> l;

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

    return 0;
}