#include <iostream>

int max_of_two(int first, int second)
{
    return first > second ? first : second;
}

double max_of_two(double first, double second)
{
    return first > second ? first : second;
}

int main()
{
    std::cout << "Int max: " << max_of_two(3, 7) << '\n';
    std::cout << "Double max: " << max_of_two(2.5, 3.5) << '\n';
    return 0;
}
