#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class ClubHub {
private:
    map<string, list<string>> adjList; // student graph
    map<string, vector<string>> clubs; // club name → list of students
    map<string, bool> students;        // student name → registered or not

public:
    // a. Add a new student
    void addStudent(string studentName) {
        if (students[studentName]) {
            cout << studentName << " is already in the system.\n";
        } else {
            students[studentName] = true;
            adjList[studentName] = list<string>();
            cout << studentName << " added to the system.\n";
        }
    }

    // b. Create a new club
    void createClub(string clubName) {
        if (clubs.find(clubName) != clubs.end()) {
            cout << "Club " << clubName << " already exists.\n";
        } else {
            clubs[clubName] = vector<string>();
            cout << "Club " << clubName << " created.\n";
        }
    }

    // c. Add a student to a club (connect with all other club members)
    void addStudentToClub(string studentName, string clubName) {
        if (!students[studentName]) {
            cout << studentName << " is not in the system. Add student first.\n";
            return;
        }
        if (clubs.find(clubName) == clubs.end()) {
            cout << "Club " << clubName << " does not exist. Create club first.\n";
            return;
        }

        // Connect student with other members
        for (string member : clubs[clubName]) {
            adjList[studentName].push_back(member);
            adjList[member].push_back(studentName);
        }

        clubs[clubName].push_back(studentName);
        cout << studentName << " added to club " << clubName << ".\n";
    }

    // d. Remove a student from a club (and remove edges)
    void removeStudentFromClub(string studentName, string clubName) {
        if (clubs.find(clubName) == clubs.end()) {
            cout << "Club " << clubName << " does not exist.\n";
            return;
        }

        auto members = clubs[clubName];
        auto it = find(members.begin(), members.end(), studentName);
        if (it == members.end()) {
            cout << studentName << " is not in club " << clubName << ".\n";
            return;
        }

        // Remove edges between student and other club members
        for (string member : members) {
            if (member != studentName) {
                adjList[member].remove(studentName);
                adjList[studentName].remove(member);
            }
        }

        // Remove from club
        members.erase(it);
        cout << studentName << " removed from club " << clubName << ".\n";
    }

    // Print the adjacency list
    void printGraph() {
        cout << "\nStudent Connection Graph:\n";
        for (auto pair : adjList) {
            cout << pair.first << " is connected to: ";
            for (string neighbor : pair.second) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    // Print clubs and their members
    void printClubs() {
        cout << "\nClubs and Members:\n";
        for (auto pair : clubs) {
            cout << pair.first << ": ";
            for (string member : pair.second) {
                cout << member << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    ClubHub ch;

    // Add students
    ch.addStudent("Alice");
    ch.addStudent("Bob");
    ch.addStudent("Charlie");
    ch.addStudent("Diana");
    ch.addStudent("Eve");

    // Create clubs
    ch.createClub("ChessClub");
    ch.createClub("DramaClub");
    ch.createClub("ScienceClub");

    // Add students to clubs
    ch.addStudentToClub("Alice", "ChessClub");
    ch.addStudentToClub("Bob", "ChessClub");
    ch.addStudentToClub("Charlie", "ChessClub");

    ch.addStudentToClub("Bob", "DramaClub");
    ch.addStudentToClub("Diana", "DramaClub");
    ch.addStudentToClub("Eve", "DramaClub");

    ch.addStudentToClub("Alice", "ScienceClub");
    ch.addStudentToClub("Eve", "ScienceClub");

    // Remove student from a club
    ch.removeStudentFromClub("Eve", "DramaClub");

    // Print final state
    ch.printClubs();
    ch.printGraph();

    return 0;
}
