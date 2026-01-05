#include <iostream>
using namespace std;

struct Track {
    int id;
    string title;
    string artist;
    string album;
    float duration;
    Track* next;
    Track* prev;
};

class PremiumPlaylist {
private:
    Track* head;
    Track* current; 

public:
    PremiumPlaylist() {
        head = nullptr;
        current = nullptr;
    }
    void insertAtBeginning(int id, string title, string artist, string album, float duration) {
        Track* newNode = new Track{id, title, artist, album, duration};

        if (!head) {
            newNode->next = newNode->prev = newNode;
            head = current = newNode;
            return;
        }

        Track* tail = head->prev;
        newNode->next = head;
        newNode->prev = tail;
        head->prev = tail->next = newNode;
        head = newNode;
    }
    void insertAtEnd(int id, string title, string artist, string album, float duration) {
        if (!head) {
            insertAtBeginning(id, title, artist, album, duration);
            return;
        }

        Track* tail = head->prev;
        Track* newNode = new Track{id, title, artist, album, duration};

        newNode->next = head;
        newNode->prev = tail;
        tail->next = head->prev = newNode;
    }
    void insertAtPosition(int pos, int id, string title, string artist, string album, float duration) {
        if (pos <= 1 || !head) {
            insertAtBeginning(id, title, artist, album, duration);
            return;
        }

        Track* temp = head;
        for (int i = 1; i < pos - 1 && temp->next != head; i++)
            temp = temp->next;

        Track* newNode = new Track{id, title, artist, album, duration};
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next->prev = newNode;
        temp->next = newNode;
    }
    void deleteFirst() {
        if (!head) return;

        if (head->next == head) {
            delete head;
            head = current = nullptr;
            return;
        }

        Track* tail = head->prev;
        Track* del = head;
        head = head->next;

        tail->next = head;
        head->prev = tail;

        if (current == del)
            current = head;

        delete del;
    }
    void deleteLast() {
        if (!head) return;

        if (head->next == head) {
            delete head;
            head = current = nullptr;
            return;
        }

        Track* tail = head->prev;
        tail->prev->next = head;
        head->prev = tail->prev;

        if (current == tail)
            current = head;

        delete tail;
    }
    void deleteAtPosition(int pos) {
        if (!head) return;

        if (pos == 1) {
            deleteFirst();
            return;
        }

        Track* temp = head;
        for (int i = 1; i < pos && temp->next != head; i++)
            temp = temp->next;

        if (temp == head) return;

        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;

        if (current == temp)
            current = temp->next;

        delete temp;
    }
    void displayForward() {
        if (!head) {
            cout << "Playlist is empty.\n";
            return;
        }

        Track* temp = head;
        cout << "\n--- Playlist (Forward) ---\n";
        do {
            cout << "ID: " << temp->id
                 << ", Title: " << temp->title
                 << ", Artist: " << temp->artist
                 << ", Album: " << temp->album
                 << ", Duration: " << temp->duration << " mins\n";
            temp = temp->next;
        } while (temp != head);
    }
    void displayReverse() {
        if (!head) return;

        Track* temp = head->prev;
        cout << "\n--- Playlist (Reverse) ---\n";
        do {
            cout << "ID: " << temp->id
                 << ", Title: " << temp->title
                 << ", Artist: " << temp->artist
                 << ", Album: " << temp->album
                 << ", Duration: " << temp->duration << " mins\n";
            temp = temp->prev;
        } while (temp != head->prev);
    }
    void playNext() {
        if (!current) return;
        current = current->next;
        showCurrent();
    }
    void playPrevious() {
        if (!current) return;
        current = current->prev;
        showCurrent();
    }
    void showCurrent() {
        if (!current) return;
        cout << "\nNow Playing:\n";
        cout << current->title << " by " << current->artist
             << " (" << current->duration << " mins)\n";
    }
};
int main() {
    PremiumPlaylist playlist;

    playlist.insertAtEnd(1, "Blinding Lights", "The Weeknd", "After Hours", 3.8);
    playlist.insertAtEnd(2, "Believer", "Imagine Dragons", "Evolve", 3.5);
    playlist.insertAtEnd(3, "Perfect", "Ed Sheeran", "Divide", 4.2);

    playlist.displayForward();
    playlist.displayReverse();

    playlist.playNext();
    playlist.playNext();
    playlist.playPrevious();

    playlist.deleteAtPosition(2);
    playlist.displayForward();

    return 0;
}