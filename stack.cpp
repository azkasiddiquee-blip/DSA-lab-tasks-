#include <iostream>
#include <string>
using namespace std;

#define MAX 100  

class BookStack {
private:
    string books[MAX]; // Array to store books
    int top;           // Top of stack

public:
    BookStack() {
        top = -1; // Stack is empty initially
    }
    void push(string bookName) {
        if (top == MAX - 1) {
            cout << "Stack Overflow! Cannot add more books.\n";
            return;
        }
        top++;
        books[top] = bookName;
        cout << "Book added successfully: " << bookName << endl;
    }
    void pop() {
        if (isEmpty()) {
            cout << "Stack Underflow! No books to remove.\n";
            return;
        }
        cout << "Removed Book: " << books[top] << endl;
        top--;
    }
    void peek() {
        if (isEmpty()) {
            cout << "No books in the stack.\n";
            return;
        }
        cout << "Top Book: " << books[top] << endl;
    }
    void display() {
        if (isEmpty()) {
            cout << "No books to display.\n";
            return;
        }
        cout << "\nBooks in Stack (Top to Bottom):\n";
        for (int i = top; i >= 0; i--) {
            cout << "- " << books[i] << endl;
        }
    }
    bool isEmpty() {
        return (top == -1);
    }
};
int main() {
    BookStack stack;
    int choice;
    string bookName;

    do {
        cout << "\n===== Book Management System =====\n";
        cout << "1. Add Book (Push)\n";
        cout << "2. Remove Book (Pop)\n";
        cout << "3. View Top Book (Peek)\n";
        cout << "4. Display All Books\n";
        cout << "5. Check if Stack is Empty\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch (choice) {
        case 1:
            cout << "Enter book name: ";
            getline(cin, bookName);
            stack.push(bookName);
            break;

        case 2:
            stack.pop();
            break;

        case 3:
            stack.peek();
            break;

        case 4:
            stack.display();
            break;

        case 5:
            if (stack.isEmpty())
                cout << "Stack is empty.\n";
            else
                cout << "Stack is not empty.\n";
            break;

        case 6:
            cout << "Exiting program...\n";
            break;

        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 6);

    return 0;
}