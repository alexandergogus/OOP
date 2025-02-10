#include <iostream>
using namespace std;

class QuickSort {
public:
    QuickSort(int* arr, int size) : arr(arr), size(size) {}
    void sort() {
        quickSort(0, size - 1);
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
    void quickSort(int low, int high) {
        if (low < high) {
            // Partitioning index
            int pi = partition(low, high);
            quickSort(low, pi - 1);
            quickSort(pi + 1, high);
        }
    }
    int partition(int low, int high) {
        int pivot = arr[high];
        int i = (low - 1);

        for (int j = low; j < high; j++) {
            if (arr[j] <= pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return (i + 1);
    }
};

int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int size = sizeof(arr) / sizeof(arr[0]);

    QuickSort qs(arr, size);

    cout << "Original array: ";
    qs.printArray();

    qs.sort();

    cout << "Sorted array: ";
    qs.printArray();

    return 0;
}
