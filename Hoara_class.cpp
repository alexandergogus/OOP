#include <iostream>
using namespace std;

class HoareSort {
public:
    HoareSort(int* arr, int size) : arr(arr), size(size) {}
    void sort() {
        hoareSort(0, size - 1);
    }
    void printArray() {
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

private:
    int* arr; 
    int size; 
    void hoareSort(int low, int high) {
        if (low < high) {
            int p = partition(low, high);
            hoareSort(low, p);
            hoareSort(p + 1, high);
        }
    }
    int partition(int low, int high) {
        int pivot = arr[(low + high) / 2]; 
        int i = low - 1; 
        int j = high + 1;

        while (true) {
            do {
                i++;
            } while (arr[i] < pivot);
            do {
                j--;
            } while (arr[j] > pivot);
            if (i >= j) {
                return j;
            }
            swap(arr[i], arr[j]);
        }
    }
};

int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    HoareSort hs(arr, size);

    cout << "Original array: ";
    hs.printArray();

    hs.sort();

    cout << "Sorted array: ";
    hs.printArray();

    return 0;
}
