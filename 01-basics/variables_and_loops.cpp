#include <iostream>

int main()
{
    const int limit = 5;
    int sum = 0;

    for (int number = 1; number <= limit; ++number) {
        sum += number;
    }

    std::cout << sum << '\n';
    return 0;
}
