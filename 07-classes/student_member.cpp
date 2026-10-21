#include <iomanip>
#include <iostream>
#include <string>

struct Student {
    std::string name;
    int age;
    double score;

    void print() const
    {
        std::cout << "Name: " << name << '\n';
        std::cout << "Age: " << age << '\n';
        std::cout << "Score: " << std::fixed
                  << std::setprecision(1) << score << '\n';
    }
};

int main()
{
    const Student student{"Chen", 19, 88.5};
    student.print();
    return 0;
}
