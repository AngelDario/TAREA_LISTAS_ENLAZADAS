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

template <class T, class O>
struct LIST {
    NODE<T> head;
    O order;

    LIST() {
        head = NULL;
    }

    bool add() {

    }
};


int main()
{
    std::cout << "Hello World!\n";
}