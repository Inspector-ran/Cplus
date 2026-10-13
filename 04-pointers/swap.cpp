#include <iostream>

// Both pointers must refer to valid, writable int objects.
void swap_values(int* first, int* second)
{
    const int temporary = *first;
    *first = *second;
    *second = temporary;
}

int main()
{
    int first = 3;
    int second = 7;

    std::cout << "Before: " << first << ", " << second << '\n';
    swap_values(&first, &second);
    std::cout << "After: " << first << ", " << second << '\n';
    return 0;
}
