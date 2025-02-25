#include <iostream>
using namespace std;

class Subforwardlist {
private:
    struct Node {
        int data;
        Node* next;
        Node(int d, Node* n = nullptr) : data(d), next(n) {}
    };
    Node* head;

public:
    Subforwardlist() : head(nullptr) {}

    ~Subforwardlist() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    bool push_back(int d) {
        if (!head) {
            head = new Node(d);
            return true;
        }
        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new Node(d);
        return true;
    }

    int pop_back() {
        if (!head) return 0;
        if (!head->next) {
            int val = head->data;
            delete head;
            head = nullptr;
            return val;
        }
        Node* temp = head;
        while (temp->next->next) {
            temp = temp->next;
        }
        int val = temp->next->data;
        delete temp->next;
        temp->next = nullptr;
        return val;
    }

    bool push_forward(int d) {
        head = new Node(d, head);
        return true;
    }

    int pop_forward() {
        if (!head) return 0;
        Node* temp = head;
        int val = temp->data;
        head = head->next;
        delete temp;
        return val;
    }

    bool push_where(unsigned int where, int d) {
        if (where == 0) return push_forward(d);
        Node* temp = head;
        for (unsigned int i = 0; i < where - 1; ++i) {
            if (!temp) return false;
            temp = temp->next;
        }
        if (!temp) return false;
        temp->next = new Node(d, temp->next);
        return true;
    }

    int erase_where(unsigned int where) {
        if (!head) return 0;
        if (where == 0) return pop_forward();
        Node* temp = head;
        for (unsigned int i = 0; i < where - 1; ++i) {
            if (!temp->next) return 0;
            temp = temp->next;
        }
        if (!temp->next) return 0;
        Node* to_delete = temp->next;
        int val = to_delete->data;
        temp->next = to_delete->next;
        delete to_delete;
        return val;
    }

    void clear() {
        while (head) {
            pop_forward();
        }
    }

    unsigned int size() const {
        unsigned int count = 0;
        Node* temp = head;
        while (temp) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void print() const {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    Subforwardlist list;

    list.push_back(10);
    list.push_back(20);
    list.push_forward(5);

    cout << "Size: " << list.size() << endl;
    cout << "List: ";
    list.print();

    cout << "Pop forward: " << list.pop_forward() << endl;
    cout << "Pop back: " << list.pop_back() << endl;

    list.push_where(1, 15);
    cout << "List after push_where: ";
    list.print();

    cout << "Erase where (index 1): " << list.erase_where(1) << endl;
    cout << "List after erase_where: ";
    list.print();

    list.clear();
    cout << "Size after clear: " << list.size() << endl;

    list.~Subforwardlist();
    return 0;
}
