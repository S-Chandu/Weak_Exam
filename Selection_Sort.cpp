#include <iostream>                                                                  
using namespace std;                                                                  
// Function to implement selection sort                                                                  
void selectionSort(int arr[], int n) {                                                                  
    // Outer loop to traverse the array                                                                  
    for (int i = 0; i < n - 1; i++) {                                                                  
        int minIndex = i; // Assume the current index as the minimum                                                                  
        // Inner loop to find the minimum element in the unsorted part                                                                  
        for (int j = i + 1; j < n; j++) {                                                                  
            if (arr[j] < arr[minIndex]) {                                                                  
                minIndex = j; // Update minIndex if a smaller element is found                                                                  
            }                                                                  
        }                                                                  
        // Swap the found minimum element with the first element of the unsorted part                                                                  
        if (minIndex != i) {                                                                  
            swap(arr[i], arr[minIndex]);                                                                  
        }                                                                  
    }                                                                  
}                                                                  
// Function to print the array                                                                  
void printArray(int arr[], int n) {                                                                  
    for (int i = 0; i < n; i++) {                                                                  
        cout << arr[i] << " ";                                                                  
    }                                                                  
    cout << endl;                                                                  
}                                                                  
int main() {                                                                  
    int arr[] = {25, 22, 12, 64, 11};  // Array to be sorted                                                                  
    int n = sizeof(arr) / sizeof(arr[0]); // Calculate number of elements in array                                                                  
    // Calling the selectionSort function                                                                  
    selectionSort(arr, n);                                                                  
    // Print the sorted array                                                                  
    cout << "Sorted array: ";                                                                  
    printArray(arr, n);
    return 0;
}