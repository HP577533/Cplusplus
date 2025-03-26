#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

class ClubHub {
private:
    // Adjacency list to represent the graph
    std::unordered_map<std::string, std::vector<std::string>> adjList;

public:
    // Function to add a new student to the system
    void addStudent(const std::string& studentName) {
        // Check if the student already exists
        if (adjList.find(studentName) == adjList.end()) {
            adjList[studentName] = {}; // Add the student with an empty list of connections
            std::cout << "Student \"" << studentName << "\" added to the system.\n";
        } else {
            std::cout << "Student \"" << studentName << "\" already exists in the system.\n";
        }
    }

    // Function to display all students and their connections
    void displayStudents() const {
        std::cout << "ClubHub Students and Connections:\n";
        for (const auto& pair : adjList) {
            std::cout << pair.first << ": ";
            for (const auto& connection : pair.second) {
                std::cout << connection << " ";
            }
            std::cout << "\n";
        }
    }
};

int main() {
    ClubHub clubHub;

    // Adding students to the system
    clubHub.addStudent("Alice");
    clubHub.addStudent("Bob");
    clubHub.addStudent("Charlie");

    // Displaying all students
    clubHub.displayStudents();

    return 0;
}