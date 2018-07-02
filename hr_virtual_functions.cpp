#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

class Person {
    std::string name;
    int age;
public:
    Person() : name(), age() { }
    virtual void getdata() { std::cin >> name >> age; }
    virtual void putdata() { std::cout << name << " " << std::to_string(age); }
};

class Professor : public Person {
    static int g_id;
    int cur_id, publications;
public:
    Professor() : Person(), cur_id(g_id), publications() { g_id += 1; }
    void getdata() override {
        Person::getdata();
        std::cin >> publications;
    }
    void putdata() override {
        Person::putdata();
        std::cout << " " << std::to_string(publications)
            << " " << std::to_string(cur_id) << "\n";
    }
};
int Professor::g_id = 1;

class Student : public Person
{
    static int g_id;
    int cur_id, marks[6];
public:
    Student() : Person(), cur_id(g_id), marks() { g_id += 1; }
    void getdata() override {
        Person::getdata();
        std::for_each(marks, marks+6, [](int& n) { std::cin >> n; });
    }
    void putdata() override {
        int sum = 0;
        for (auto n : marks)
            sum += n;
        Person::putdata();
        std::cout << " " << std::to_string(sum)
            << " " << std::to_string(cur_id) << "\n";
    }
};
int Student::g_id = 1;

int main() {
    int nop; // number of persons
    std::cin >> nop;
    std::vector<Person *> persons(nop);
    for (auto& p : persons) {
        int person_type = 0;
        std::cin >> person_type;
        if (person_type == 1)
            p = new Professor();
        else if (person_type == 2)
            p = new Student();
        p->getdata();
    }
    for (auto p : persons)
        p->putdata();
    return 0;
}
