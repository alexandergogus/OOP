#include <iostream>
using namespace std;

class Subvector {
private:
    int* mas;
    unsigned int top;
    unsigned int capacity;

public:
    Subvector() : mas(nullptr), top(0), capacity(0) {}

    ~Subvector() {
        delete[] mas;
    }

    void push_back(int d) {
        if (top >= capacity) {
            unsigned int new_capacity = (capacity == 0) ? 1 : capacity * 2;
            resize(new_capacity);
        }
        mas[top++] = d;
    }

    int pop_back() {
        if (top == 0) {
            cerr << "Error: Subvector is empty, cannot pop_back." << endl;
            return -1;
        }
        return mas[--top];
    }

    void resize(unsigned int new_capacity) {
        if (new_capacity == 0) {
            delete[] mas;
            mas = nullptr;
            top = 0;
            capacity = 0;
            return;
        }

        int* new_mas = new int[new_capacity];
        for (unsigned int i = 0; i < top && i < new_capacity; ++i) {
            new_mas[i] = mas[i];
        }
        delete[] mas;
        mas = new_mas;
        capacity = new_capacity;
        if (top > new_capacity) {
            top = new_capacity;
        }
    }

    void shrink_to_fit() {
        if (top < capacity) {
            resize(top);
        }
    }

    void clear() {
        top = 0;
    }

    unsigned int size() const {
        return top;
    }

    unsigned int get_capacity() const {
        return capacity;
    }

    int& operator[](unsigned int index) {
        return mas[index];
    }

    const int& operator[](unsigned int index) const {
        return mas[index];
    }
};

int main() {
    Subvector vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);

    cout << "Size: " << vec.size() << ", Capacity: " << vec.get_capacity() << endl;
    cout << "Elements: ";
    for (unsigned int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << " ";
    }
    cout << endl;

    cout << "Popped element: " << vec.pop_back() << endl;
    cout << "After pop_back, Size: " << vec.size() << endl;

    vec.shrink_to_fit();
    cout << "After shrink_to_fit, Capacity: " << vec.get_capacity() << endl;

    vec.clear();
    cout << "After clear, Size: " << vec.size() << endl;

    return 0;
}
