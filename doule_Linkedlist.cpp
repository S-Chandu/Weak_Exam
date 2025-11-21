#include <iostream>
using namespace std;

// Node for Doubly Linked List
struct Node {
    int data;
    Node* prev;
    Node* next;

    Node(int value) {
        data = value;
        prev = nullptr;
        next = nullptr;
    }
};

// Doubly Linked List class
class DoublyLinkedList {
private:
    Node* head;

public:
    DoublyLinkedList() {
        head = nullptr;
    }

    // Insert at beginning
    void insertAtBeginning(int value) {
        Node* newNode = new Node(value);

        if (head != nullptr) {
            head->prev = newNode;
            newNode->next = head;
        }

        head = newNode;
    }

    // Insert at end
    void insertAtEnd(int value) {
        Node* newNode = new Node(value);

        if (head == nullptr) { 
            head = newNode;
            return;
        }

        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }

        temp->next = newNode;
        newNode->prev = temp;
    }

    // Delete a value
    void deleteValue(int value) {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }

        Node* temp = head;

        // Searching for the node
        while (temp != nullptr && temp->data != value) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Value not found in list.\n";
            return;
        }

        // Case 1: Deleting head
        if (temp->prev == nullptr) {
            head = temp->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
        }
        // Case 2: Middle or End node
        else {
            temp->prev->next = temp->next;

            if (temp->next != nullptr) {
                temp->next->prev = temp->prev;
            }
        }

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

        cout << "Value " << value << " not found in list.\n";
    }

    // Display list forward
    void displayForward() {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }

        Node* temp = head;
        cout << "List (Forward): ";
        while (temp != nullptr) {
            cout << temp->data << " <-> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }

    // Display list backward
    void displayBackward() {
        if (head == nullptr) {
            cout << "List is empty.\n";
            return;
        }

        // Go to the last node
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }

        cout << "List (Backward): ";
        while (temp != nullptr) {
            cout << temp->data << " <-> ";
            temp = temp->prev;
        }
        cout << "NULL\n";
    }
};

// Main function
int main() {
    DoublyLinkedList list;
    int choice, value;

    while (true) {
        cout << "\n--- Doubly Linked List Menu ---\n";
        cout << "1. Insert at Beginning\n";
        cout << "2. Insert at End\n";
        cout << "3. Delete a Value\n";
        cout << "4. Search a Value\n";
        cout << "5. Display Forward\n";
        cout << "6. Display Backward\n";
        cout << "7. Exit\n";
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
                list.displayForward();
                break;

            case 6:
                list.displayBackward();
                break;

            case 7:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}
