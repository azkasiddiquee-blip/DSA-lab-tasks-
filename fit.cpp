#include <iostream>
#include <string>
using namespace std;
struct Node {
    int studentID;
    string name;
    int semester;
    float gpa;
    Node* prev;
    Node* next;
};
class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() {
        head = tail = NULL;
    }
    Node* createNode() {
        Node* newNode = new Node();
        cout << "Enter Student ID: ";
        cin >> newNode->studentID;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, newNode->name);
        cout << "Enter Semester: ";
        cin >> newNode->semester;
        cout << "Enter GPA: ";
        cin >> newNode->gpa;
        newNode->prev = newNode->next = NULL;
        return newNode;
    }
    void insertAtBeginning() {
        Node* newNode = createNode();
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        cout << "Inserted at beginning.\n";
    }
    void insertAtEnd() {
        Node* newNode = createNode();
        if (!tail) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        cout << "Inserted at end.\n";
    }

    // Insert at specific position (1-based index)
    void insertAtPosition(int pos) {
        if (pos <= 1) {
            insertAtBeginning();
            return;
        }

        Node* temp = head;
        for (int i = 1; i < pos - 1 && temp; i++)
            temp = temp->next;

        if (!temp || !temp->next) {
            insertAtEnd();
            return;
        }

        Node* newNode = createNode();
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next->prev = newNode;
        temp->next = newNode;

        cout << "Inserted at position " << pos << ".\n";
    }
    void deleteFromBeginning() {
        if (!head) {
            cout << "List is empty.\n";
            return;
        }
        Node* temp = head;
        head = head->next;
        if (head)
            head->prev = NULL;
        else
            tail = NULL;
        delete temp;
        cout << "Deleted from beginning.\n";
    }
    void deleteFromEnd() {
        if (!tail) {
            cout << "List is empty.\n";
            return;
        }
        Node* temp = tail;
        tail = tail->prev;
        if (tail)
            tail->next = NULL;
        else
            head = NULL;
        delete temp;
        cout << "Deleted from end.\n";
    }
    void deleteFromPosition(int pos) {
        if (!head) {
            cout << "List is empty.\n";
            return;
        }

        if (pos <= 1) {
            deleteFromBeginning();
            return;
        }

        Node* temp = head;
        for (int i = 1; i < pos && temp; i++)
            temp = temp->next;

        if (!temp) {
            cout << "Invalid position.\n";
            return;
        }

        if (temp == tail) {
            deleteFromEnd();
            return;
        }

        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        delete temp;

        cout << "Deleted from position " << pos << ".\n";
    }
    void displayForward() {
        if (!head) {
            cout << "List is empty.\n";
            return;
        }
        Node* temp = head;
        cout << "\n--- Student Records (Start to End) ---\n";
        while (temp) {
            cout << "ID: " << temp->studentID
                 << ", Name: " << temp->name
                 << ", Semester: " << temp->semester
                 << ", GPA: " << temp->gpa << endl;
            temp = temp->next;
        }
    }
    void displayBackward() {
        if (!tail) {
            cout << "List is empty.\n";
            return;
        }
        Node* temp = tail;
        cout << "\n--- Student Records (End to Start) ---\n";
        while (temp) {
            cout << "ID: " << temp->studentID
                 << ", Name: " << temp->name
                 << ", Semester: " << temp->semester
                 << ", GPA: " << temp->gpa << endl;
            temp = temp->prev;
        }
    }
    ~DoublyLinkedList() {
        while (head)
            deleteFromBeginning();
    }
};
int main() {
    DoublyLinkedList list;
    int choice, position;

    do {
        cout << "\n===== Student Enrollment System =====\n";
        cout << "1. Insert at Beginning\n";
        cout << "2. Insert at End\n";
        cout << "3. Insert at Specific Position\n";
        cout << "4. Delete from Beginning\n";
        cout << "5. Delete from End\n";
        cout << "6. Delete from Specific Position\n";
        cout << "7. Display Forward\n";
        cout << "8. Display Backward\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            list.insertAtBeginning();
            break;
        case 2:
            list.insertAtEnd();
            break;
        case 3:
            cout << "Enter position: ";
            cin >> position;
            list.insertAtPosition(position);
            break;
        case 4:
            list.deleteFromBeginning();
            break;
        case 5:
            list.deleteFromEnd();
            break;
        case 6:
            cout << "Enter position: ";
            cin >> position;
            list.deleteFromPosition(position);
            break;
        case 7:
            list.displayForward();
            break;
        case 8:
            list.displayBackward();
            break;
        case 0:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}