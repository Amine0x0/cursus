#include <iostream>
#include "Array.hpp"

int main()
{
    std::cout << "-default constructor:" << std::endl;
    Array<int> empty;
    std::cout << "Empty array size: " << empty.size() << std::endl;

    std::cout << "\n-parameterized constructor and assignment:" << std::endl;
    Array<int> numbers(5);
    std::cout << "array size: " << numbers.size() << std::endl;
    for (unsigned int i = 0; i < numbers.size(); i++)
    {
        numbers[i] = i * 10;
        std::cout << "numbers[" << i << "] = " << numbers[i] << std::endl;
    }

    std::cout << "\n-copy constructor (deep copy validation):" << std::endl;
    Array<int> copy(numbers);
    copy[0] = 99;
    std::cout << "After modifying copy[0] to 99:" << std::endl;
    std::cout << "copy[0] = " << copy[0] << std::endl;
    std::cout << "numbers[0] = " << numbers[0] << std::endl;

    std::cout << "\n-assignment operator:" << std::endl;
    Array<int> assigned;
    assigned = numbers;
    assigned[1] = 88;
    std::cout << "After modifying assigned[1] to 88:" << std::endl;
    std::cout << "assigned[1] = " << assigned[1] << std::endl;
    std::cout << "numbers[1] = " << numbers[1] << std::endl;

    std::cout << "\n-const operator:" << std::endl;
    const Array<int>& constRef = numbers;
    std::cout << "constRef[2] = " << constRef[2] << std::endl;

    std::cout << "\n-out-of-bounds access:" << std::endl;
    try
    {
        std::cout << "Trying to access numbers[5]..." << std::endl;
        numbers[5] = 0;
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }

    std::cout << "\n-out-of-bounds access:" << std::endl;
    try
    {
        unsigned int invalidIdx = -1;
        std::cout << "Trying to access numbers[-1]..." << std::endl;
        numbers[invalidIdx] = 0;
    }
    catch (const std::out_of_range& e)
    {
        std::cout << "Caught expected exception: " << e.what() << std::endl;
    }

    return 0;
}