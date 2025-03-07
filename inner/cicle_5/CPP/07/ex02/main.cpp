#include <iostream>
#include "Array.hpp"

int main() {
    std::cout << std::endl << std::endl;
    std::cout << "** Test default constructor" << std::endl;
    Array<int> arr1;
    std::cout << "arr1 size: " << arr1.size() << std::endl;
    std::cout << std::endl;

    std::cout << "** Test constructor with size parameter" << std::endl;
    Array<int> arr2(5);
    std::cout << "arr2 size: " << arr2.size() << std::endl;
    std::cout << "arr2 elements: ";
    for (int i = 0; i < 5; i++) {
        std::cout << arr2[i] << " ";
    }
    std::cout << std::endl << std::endl;

    std::cout << "** Test copy constructor" << std::endl;
    Array<int> arr3 = arr2;
    std::cout << "arr3 size: " << arr3.size() << std::endl;
    std::cout << "arr3 elements: ";
    for (int i = 0; i < 5; i++) {
        std::cout << arr3[i] << " ";
    }
    std::cout << std::endl << std::endl;

    std::cout << "** Test assignment operator" << std::endl;
    Array<int> arr4(5);
    arr4 = arr2;
    std::cout << "arr4 size: " << arr4.size() << std::endl;
    std::cout << "arr4 elements: ";
    for (int i = 0; i < 5; i++) {
        std::cout << arr4[i] << " ";
    }
    std::cout << std::endl << std::endl;
    
    std::cout << "** Test subscript operator" << std::endl;
    arr2[0] = 10;
    arr2[1] = 20;
    std::cout << "arr2[0]: " << arr2[0] << ", arr2[1]: " << arr2[1] << std::endl; // Expected output: 10, 20
    std::cout << std::endl << std::endl;

    std::cout << "** Test deep copy" << std::endl;
    std::cout << "arr3 elements: ";
    for (int i = 0; i < 5; i++) {
        std::cout << arr3[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "arr4 elements: ";
    for (int i = 0; i < 5; i++) {
        std::cout << arr4[i] << " ";
    }
    std::cout << std::endl << std::endl;

    std::cout << "** Test out of range exception" << std::endl;
    try {
        std::cout << arr2[10] << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl; // Expected output: Exception: Index out of range
    }
    std::cout << std::endl << std::endl;

    std::cout << "** Test assignment operator with different size" << std::endl;
    try {
        Array<int> arr5(4);
        arr5 = arr2;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl; // Expected output: Exception: Index out of range
    }
    std::cout << std::endl << std::endl;

    return 0;
}
