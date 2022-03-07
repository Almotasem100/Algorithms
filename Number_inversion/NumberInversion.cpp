/*#include<iostream>
#include<vector>
#define Matrix vector<vector<int>>
using namespace std;



int main()
{
    size_t n{};
    cin>>n;
    int numbers[n]{};
    for(size_t i=0; i<n; i++)
    {
        cin>>numbers[i];
    }

    return 0;
}*/
// C++ program for Merge Sort
#include <iostream>
using namespace std;

int merge(int arr[], int low, int mid, int high)
{
    int n1 = mid - low + 1;
    int n2 = high - mid;
    int L[n1], R[n2];   // two subarrays to hold data

    for (int i = 0; i < n1; i++)
        L[i] = arr[low + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i{}, j{}, k=low;
    int inver_count = 0;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
            inver_count += n1 -i;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }


    return inver_count;
}

int mergeSort(int arr[],int low,int high){
    if(low >= high){
        return 0;
    }
    int global_inv_counter = 0; 
    int mid = low + (high - low) / 2;
    global_inv_counter +=  mergeSort(arr, low, mid);
    global_inv_counter +=  mergeSort(arr, mid+1, high);
    global_inv_counter +=  merge(arr, low, mid, high);

    return global_inv_counter;
}

int main()
{
    int n{};
    cin>>n;
    int arr[n]{};
    for(size_t i=0; i<n; i++)
    {
        cin>>arr[i];
    }
    int inver_number = mergeSort(arr, 0, n-1);
    cout<< "The inversion count is: "<<inver_number<<endl;
    return 0;
}

