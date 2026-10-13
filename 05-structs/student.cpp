#include <iomanip>
#include <iostream>
#include <string>

struct Student {
    std::string name;
    int age;
    double score;
};

void print_student(const Student& student)
{
    std::cout << "Name: " << student.name << '\n';
    std::cout << "Age: " << student.age << '\n';
    std::cout << std::fixed << std::setprecision(1);
    std::cout << "Score: " << student.score << '\n';
}

int main()
{
    const Student student{"Chen", 19, 88.5};
    print_student(student);
    return 0;
}
