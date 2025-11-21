#include <iostream>
#include <deque>
using namespace std;

int main() {

    deque<int> dq;

    // Insert elements
    dq.push_back(10);   // back -> 10
    dq.push_back(20);   // back -> 10 20
    dq.push_front(5);   // front -> 5 10 20
    dq.push_front(2);   // front -> 2 5 10 20

    cout << "Deque elements: ";
    for (int x : dq) {
        cout << x << " ";
    }
    cout << endl;

    // Access front and back
    cout << "Front element: " << dq.front() << endl;
    cout << "Back element : " << dq.back() << endl;

    // Remove from both ends
    dq.pop_front();     // removes 2 -> 5 10 20
    dq.pop_back();      // removes 20 -> 5 10

    cout << "After popping: ";
    for (int x : dq) {
        cout << x << " ";
    }
    cout << endl;

    // Insert at specific position
    dq.insert(dq.begin() + 1, 99);  // 5 99 10

    cout << "After inserting 99: ";
    for (int x : dq) {
        cout << x << " ";
    }
    cout << endl;

    // Erase element at index 1
    dq.erase(dq.begin() + 1); // 5 10

    cout << "After erasing index 1: ";
    for (int x : dq) {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
