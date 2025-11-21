#include <iostream>
using namespace std;

// Node structure for singly linked list
struct Node {
    int data;
    Node* next;

    Node(int value) {
        data = value;                                                                        
        next = nullptr;                                                                        
    }                                              
};                                              
                                              
// Linked List class                                              
class SinglyLinkedList {                                              
private:                                              
    Node* head;                                              
                                              
public:                                              
    SinglyLinkedList() {                                              
        head = nullptr;                                              
    }                                              
                                              
    // Insert at beginning                                                                        
    void insertAtBeginning(int value) {                                                                        
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    // Insert at Particular position
    void insertAtPosition(int value, int position) {
        if (position < 1) {
            cout << "Position should be >= 1.\n";
            return;
        }

        Node* newNode = new Node(value);

        if (position == 1) {
            newNode->next = head;
            head = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 1; i < position - 1 && temp != nullptr; i++) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Position is out of bounds. Inserting at the end.\n";
            insertAtEnd(value);
            return;
        }

        newNode->next = temp->next;
        temp->next = newNode;
    }

    // Insert at end
    void insertAtEnd(int value) {
        Node* newNode = new Node(value);

        if (head == nullptr) { // If list is empty
            head = newNode;
            return;
        }

        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    // Delete a node by value
    void deleteValue(int value) {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }

        // If the head node contains the value
        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            cout << "Deleted " << value << " from list.\n";
 
 
 
            return;
        }

        Node* temp = head;
        Node* prev = nullptr;

        while (temp != nullptr && temp->data != value) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Value not found in list.\n";
            return;
        }

        prev->next = temp->next;
        delete temp;
        cout << "Deleted " << value << " from list.\n";
    }

    // Search for a value
    void search(int value) {
        Node* temp = head;
        int position = 1;

        while (temp != nullptr) {
            if (temp->data == value) {
                cout << "Value " << value << " found at position " << position << ".\n";
                return;
            }
            temp = temp->next;
            position++;
        }

        cout << "Value " << value << " not found in the list.\n";
    }

    // Display the list
    void display() {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }

        Node* temp = head;
        cout << "Linked List: ";
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
};

// Main function
int main() {
    SinglyLinkedList list;
    int choice, value;

    while (true) {
        cout << "\n--- Singly Linked List Menu ---\n";
        cout << "1. Insert at Beginning\n";
        cout << "2. Insert at End\n";
        cout << "3. Delete a Value\n";
        cout << "4. Search a Value\n";
        cout << "5. Display List\n";
        cout << "7. Insert at Position\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> value;
                list.insertAtBeginning(value);
                break;

            case 2:
                cout << "Enter value: ";
                cin >> value;
                list.insertAtEnd(value);
                break;

            case 3:
                cout << "Enter value to delete: ";
                cin >> value;
                list.deleteValue(value);
                break;

            case 4:
                cout << "Enter value to search: ";
                cin >> value;
                list.search(value);
                break;

            case 5:
                list.display();
                break;

            case 6:
                cout << "Exiting...\n";
                return 0;
            case 7:
                cout << "Enter value: ";
                cin >> value;
                int position;
                cout << "Enter position: ";
                cin >> position;
                list.insertAtPosition(value, position);
                break;


            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}
