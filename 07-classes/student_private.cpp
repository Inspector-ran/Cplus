#include <iomanip>
#include <iostream>
#include <string>

class Student {
private:
    std::string name_ = "Chen";
    int age_ = 19;
    double score_ = 88.5;

public:
    void print() const
    {
        std::cout << "Name: " << name_ << '\n';
        std::cout << "Age: " << age_ << '\n';
        std::cout << "Score: " << std::fixed
                  << std::setprecision(1) << score_ << '\n';
    }
};

int main()
{
    const Student student{};
    student.print();
    return 0;
}
