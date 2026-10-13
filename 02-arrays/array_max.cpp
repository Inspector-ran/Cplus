#include <cstddef>
#include <iostream>

int main()
{
    const int numbers[] = {4, 1, 9, 3, 7};
    const std::size_t count = sizeof numbers / sizeof numbers[0];
    int maximum = numbers[0];

    for (std::size_t index = 1; index < count; ++index) {
        if (numbers[index] > maximum) {
            maximum = numbers[index];
        }
    }

    std::cout << maximum << '\n';
    return 0;
}
