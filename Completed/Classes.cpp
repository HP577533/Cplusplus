#include <iostream>
#include <string>

// Copilot Class: Person
class Person {
private:
    std::string name;
    int age;

public:
    // Constructor
    Person(std::string n, int a) : name(n), age(a) {}

    // Getter for name
    std::string getName() const {
        return name;
    }

    // Getter for age
    int getAge() const {
        return age;
    }

    // Setter for name
    void setName(std::string n) {
        name = n;
    }

    // Setter for age
    void setAge(int a) {
        age = a;
    }

    // Method to display person details
    void display() const {
        std::cout << "Name: " << name << ", Age: " << age << std::endl;
    }
};

int main() {
    // Create an object of Person
    Person person("John Doe", 30);

    // Display person details
    person.display();

    // Modify person details
    person.setName("Jane Doe");
    person.setAge(25);

    // Display modified person details
    person.display();

    return 0;
}