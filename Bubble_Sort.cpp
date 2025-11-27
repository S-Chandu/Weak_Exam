#include<iostream>

using namespace std;

// Function to implement bubble sort
void Bubble_Sort(int arr[], int n){
    for(int i = 0; i < n-1; i++){
        for(int j = 0; j< n-1; j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j], arr[j+1]);
            }
        }
    }
}
void SWAP(int a, int b){
    int temp =a;
    a=b;
    b=temp;
}

void PrintArray(int arr[], int n){
    for(int i = 0; i<n; i++){
        cout<<arr[i]<<"  ";
    }
}

int main(){
    int arr[] = {25,22,12,64,11};
    int n = size(arr);
    cout<<n<<"\n";
    cout<<"Unsorted Array: ";
    PrintArray(arr,n);
    cout<<"\n";
    Bubble_Sort(arr,n);
    cout<<"Sorted Array: ";
    PrintArray(arr,n);
    return 0;
}