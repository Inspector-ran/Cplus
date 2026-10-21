#include <iomanip>
#include <iostream>
#include <string>

class Student {
private:
    std::string name_;
    int age_;
    double score_;

public:
    // This introductory example assumes valid arguments.
    Student(const std::string& name, int age, double score)
        : name_(name), age_(age), score_(score)
    {
    }

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
    const Student student{"Chen", 19, 88.5};
    student.print();
    return 0;
}
