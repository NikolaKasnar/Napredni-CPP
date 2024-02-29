#include "array.h"
#include <iostream>


int main(){
  /*// testiranje obicnih konstruktora
  Array<int, 10> myIntArray(42);

  std::cout << "myIntArray: " << myIntArray << std::endl;

  
  Array<char, 4> myCharArray{'a', 'b', 'c', 'd'};

  std::cout << "myCharArray: " << myCharArray << std::endl;

  */

  /*//testiranje copy konstruktora i copy join konstruktora
  
  Array<int, 5> arr1{1, 2, 3, 4, 5};
  Array<int, 5> arr2{10, 20, 30, 40, 50};

  Array<int, 5> arr3 = arr1; // Copy constructor
  arr2=arr1;

  std::cout << "arr3: " << arr3 << std::endl;
  std::cout << "arr2: " << arr2 << std::endl;

  */

  /*//testiranje operatora idneksiranja
  Array<int, 5> arr{1, 2, 3, 4, 5};

  std::cout << "arr: " << arr << std::endl;

  int element = arr[2]; // Dohvaća drugi element
  arr[3] = 42; // Mpromijeni element na cetvrtom mjestu

  std::cout << "arr: " << arr << std::endl;

  std::cout << element;//ispis elementa

  */

  /*//testiranje iteratora(test je pronaden na internetu)
  Array<int, 5> arr{1, 2, 3, 4, 5};

    // Using a non-const range-based for loop
    for (int element : arr) {
        std::cout << element << ' ';
    }
    std::cout << std::endl;

    // Using a const range-based for loop
    const Array<int, 5> constArr{10, 20, 30, 40, 50};
    for (const int element : constArr) {
        std::cout << element << ' ';
    }
    std::cout << std::endl;

    */

  /*//testiranje operatora ==
  Array<int, 5> arr1{1, 2, 3, 4, 5};
  Array<double, 5> arr2{1.0, 2.0, 3.2, 4.0, 5.0};

  if (arr1 == arr2) {
    std::cout << "Polja su jednaka" << std::endl;
  } else {
    std::cout << "Polja nisu jednaka" << std::endl;
  }

  */
  

    
  return 0;

  
}
