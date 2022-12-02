#include <iostream>

void insertion_sort(int arr[], std::size_t cap) {
    int i, key, j;

    for (int i{1}; i < cap; ++i) {
        key = arr[i];
        j = i - 1;

        while (j >=0 && arr[j] > key) 
        {
            arr[j+1] = arr[j];
            j = j-1;
        }

        arr[j+1] = key;
        
    }
}

int main() {
    int arr[]{1, 5, 6, 9, 2, 3, 4, 10, 25};

    insertion_sort(arr, 9);
    
    for (int i{0}; i < 9; ++i)
    {
        std::cout << arr[i] << " ";
    }
    
    std::cout << std::endl;

    int a = 7, b = 7;

    std::cout << "a: " << a << " b: " << b;
    
}