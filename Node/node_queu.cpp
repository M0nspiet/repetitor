#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct Node {
    int value;
    Node* next;
    Node* prev;

    Node(int val) : value(val), next(nullptr), prev(nullptr) {}
};

class List{
    Node *Head,*Tail; 
    public:
        List();
        void Add(int value); 
        void Distplay(); 
        void pop_front();
        void push_back(int value);
        int print_head();
};

List::List() : Head(nullptr), Tail(nullptr) {};

void List::Add(int value) {
    Node* temp = new Node(value);
    temp->value = value;
    temp->next = nullptr;
    temp->prev = Tail;

    if (Tail != nullptr) {
        Tail->next = temp;
    }
    Tail = temp;

    if (Head == nullptr) {
        Head = Tail;
    }
}

void List::Distplay(){
    Node *temp = Head; 
    while (temp != NULL)
    {
        cout << temp -> value << " ";
        temp = temp -> next;
    }
    cout << endl;
}

void List::pop_front(){
    if (Head == nullptr) {
        cout << "List is empty!" << endl;
        return;
    }
    Node* temp = Head;
    Head = Head->next;  
    if (Head != nullptr) {
        Head->prev = nullptr; 
    } else {
        Tail = nullptr; 
    }
    delete temp; 
}

int List::print_head(){
    if (Head == nullptr){
        cout << "1st index not found";
    }
    int value = Head -> value;
    cout << value;
    return value;
}

void List::push_back(int value){
    Node* temp = new Node(value);
    if (Tail){
        Tail -> next = temp;
        temp -> prev = Tail;
    }
    Tail = temp;
    if(!Head){
        Head = temp;
    }
}

int main() {
    List queue;

    queue.Add(10);
    queue.Add(20);
    queue.Add(30);

    cout << "Node is:";
    queue.Distplay();
    cout << endl;

    cout<<"1st element of Node is:";
    queue.print_head();
    cout << endl;

    queue.pop_front();
    cout << "Deleted 1st element from Node: ";
    queue.Distplay();
    cout << endl;

    queue.push_back(40);
    cout << "Add element to end of queue:";
    queue.Distplay();
    cout<<endl;

    return 0;
}
