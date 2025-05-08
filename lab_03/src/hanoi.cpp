#include <iostream>
#include <string>

using namespace std;

struct ListNode {
    string move;
    ListNode* prev;
    ListNode* next;
    ListNode(const string& m) : move(m), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
public:
    ListNode* head;
    ListNode* tail;

    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void append(const string& move) {
        ListNode* newNode = new ListNode(move);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void print() const {
        ListNode* current = head;
        while (current) {
            cout << current->move << endl;
            current = current->next;
        }
    }

    ~DoublyLinkedList() {
        ListNode* current = head;
        while (current) {
            ListNode* next = current->next;
            delete current;
            current = next;
        }
    }
};

void hanoi(int n, char from, char to, char aux, DoublyLinkedList& list) {
    if (n == 1) {
        list.append("Move disk 1 from " + string(1, from) + " to " + string(1, to));
        return;
    }
    hanoi(n - 1, from, aux, to, list);
    list.append("Move disk " + to_string(n) + " from " + string(1, from) + " to " + string(1, to));
    hanoi(n - 1, aux, to, from, list);
}

int main() {
    const int disks = 8;
    DoublyLinkedList list;
    hanoi(disks, 'A', 'C', 'B', list);
    list.print();
    return 0;
}