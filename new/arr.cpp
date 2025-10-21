#include <iostream>
void reverseArray(int arr[], int size) {
   int start = 0;
   int end = size - 1;

   while (start < end) {
      int temp = arr[start];
      arr[start] = arr[end];
      arr[end] = temp;
      start++;
      end--;
   }
}

int main() {
   int arr[5];
   int size = sizeof(arr) / sizeof(arr[0]);
   for (int i = 0; i < size; i++) {
      arr[i] = 0;
   }

   std::cout << "原始数组：" << std::endl;
   for (int i = 0; i < size; i++) {
      std::cout << "arr[" << i << "]=";
      std::cin >> arr[i];
   }

   reverseArray(arr, size);

   std::cout << "\n逆序数组：" << std::endl;
   for (int i = 0; i < size; i++) {
      std::cout << "arr[" << i << "]=";
      std::cout << arr[i] << std::endl;
   }
   return 0;
}