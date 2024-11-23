#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
    int value; // значение узла
    Node* next;// указатель на следующий узел
    Node* prev;// указатель на предыдущий узел
};

int top_value(Node* stack) {
    if (stack != nullptr) {
        return stack->value;
    }
    throw "empty";
}

void stack_insert(Node** stack, int value) {
    Node *node = new Node{value, *stack};
    *stack = node;
}

void pop(Node** stack, int value) {
    if (stack == nullptr) {
        throw "empty";
    }

    Node* top_node = *stack;

    *stack = top_node->next;

    delete top_node;
}

// 1. реализовать очередь на базе двусвязного списка с функциями:
/*
 * вставка в конец очереди
 * получение первого элемента
 * удаление элемента из начала
*/

// 2. подумать какие из рассмотренных алгоритмов можно применить для связных списков

#include <stack> // push, pop, get
#include <queue> // push, pop, get (но с другого конца)
#include <deque> // push_front, pop_front, pop_back, push_back (на самом деле не список)
#include <list>  // вставка в конец/начало/середину удалить элементы ото всюду

void list_remove(Node *p) {
    Node* prev = p->prev;
    Node* next = p->next;
    prev->next = next;
    next->prev = prev;

    // + обработка удаления из начала и из конца

    delete p;

}

int main() {
    Node *p = new Node{1, nullptr};

    Node *pp = new Node{123, nullptr};
    p->next = pp;

    Node *ppp = new Node{55, p};

    Node *pppp = new Node{44, p};
    ppp->next = pppp;
    Node *stack(p);
}
