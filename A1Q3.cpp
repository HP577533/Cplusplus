#include <iostream>
#include <list>
#include <map>
#include <string>
#include <set>

using namespace std;

class Graph {
private:
    map<string, list<string>> adjList; // Map to store adjacency list with student names
    map<string, set<string>> clubs; // Map to store clubs and their members
    map<string, set<string>> studentClubs; // Map to store students and their clubs

public:
    // Add a student to the graph
    void addStudent(const string& student) {
        adjList[student]; // This will create an entry for the student if it doesn't exist
    }

    // Add a student to a club
    void addStudentToClub(const string& student, const string& club) {
        addStudent(student); // Ensure the student is in the graph
        clubs[club].insert(student);
        studentClubs[student].insert(club);

        // Create edges with other club members
        for (const auto& member : clubs[club]) {
            if (member != student) {
                addEdge(student, member);
            }
        }
    }

    // Remove a student from a club
    void removeStudentFromClub(const string& student, const string& club) {
        if (clubs[club].find(student) != clubs[club].end()) {
            clubs[club].erase(student);
            studentClubs[student].erase(club);

            // Remove edges with other club members
            for (const auto& member : clubs[club]) {
                adjList[student].remove(member);
                adjList[member].remove(student);
            }
        }
    }

    // Add an edge between two students (shared club membership)
    void addEdge(const string& student1, const string& student2) {
        adjList[student1].push_back(student2);
        adjList[student2].push_back(student1); // For undirected graph
    }

    // Display the adjacency list
    void display() {
        for (const auto& pair : adjList) {
            cout << "Student " << pair.first << ": ";
            for (const auto& neighbor : pair.second) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    // Find all clubs a student is a member of
    void findClubsOfStudent(const string& student) {
        if (studentClubs.find(student) != studentClubs.end()) {
            cout << "Clubs of student " << student << ": ";
            for (const auto& club : studentClubs[student]) {
                cout << club << " ";
            }
            cout << endl;
        } else {
            cout << "Student " << student << " is not a member of any clubs." << endl;
        }
    }

    // Find all students who are in a specific club
    void findStudentsInClub(const string& club) {
        if (clubs.find(club) != clubs.end()) {
            cout << "Students in club " << club << ": ";
            for (const auto& student : clubs[club]) {
                cout << student << " ";
            }
            cout << endl;
        } else {
            cout << "Club " << club << " does not exist or has no members." << endl;
        }
    }

    // Add a new student to the system
    void addNewStudent(const string& student) {
        addStudent(student);
        cout << "Student " << student << " added to the system." << endl;
    }

    // Create a new club
    void createNewClub(const string& club) {
        clubs[club]; // This will create an entry for the club if it doesn't exist
        cout << "Club " << club << " created." << endl;
    }
};

int main() {
    Graph g;

    // Add new students
    g.addNewStudent("Alice");
    g.addNewStudent("Bob");

    // Create new clubs
    g.createNewClub("Chess");
    g.createNewClub("Robotics");

    // Add students to clubs
    g.addStudentToClub("Alice", "Chess");
    g.addStudentToClub("Bob", "Chess");
    g.addStudentToClub("Charlie", "Robotics");
    g.addStudentToClub("David", "Robotics");
    g.addStudentToClub("Eve", "Chess");

    // Display the adjacency list
    cout << "Adjacency List of the Graph:" << endl;
    g.display();

    // Find clubs of a student
    g.findClubsOfStudent("Alice");

    // Find students in a club
    g.findStudentsInClub("Chess");

    // Remove a student from a club
    g.removeStudentFromClub("Alice", "Chess");

    // Display the adjacency list after removal
    cout << "Adjacency List of the Graph after removal:" << endl;
    g.display();

    return 0;
}
