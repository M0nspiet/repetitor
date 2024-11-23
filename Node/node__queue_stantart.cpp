#include <iostream>
#include <deque> 

using namespace std;

int main() {
    deque<int> queue;

    queue.push_back(10);
    queue.push_back(20);
    queue.push_back(30);

    cout << "Node is: ";
    for (int val : queue) {
        cout << val << " ";
    }
    cout << endl;

    cout << "1st element of Node is: " << queue.front() << endl;

    queue.pop_front();
    cout << "Deleted 1st element from Node: ";
    for (int val : queue) {
        cout << val << " ";
    }
    cout << endl;

    queue.push_back(40);
    cout << "Add elenemt to end of node:" <<queue.back() << endl;

    return 0;
}
