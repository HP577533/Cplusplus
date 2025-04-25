#include <iostream>
#include <list>
#include <map>
#include <string>
#include <set>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Graph {
private:
    map<string, set<string>> adjList;       // Map to store adjacency list with student names
    map<string, set<string>> clubs;         // Map to store clubs and their members
    map<string, set<string>> studentClubs;  // Map to store students and their clubs

public:
    // a.) Add a new student to the system
    void addNewStudent(const string& student) {
        adjList[student];
        cout << "Student " << student << " added to the system." << endl;
    }

    // b.) Create a new club
    void createNewClub(const string& club) {
        clubs[club]; // Ensure the club exists
        cout << "Club " << club << " created." << endl;
    }

    // c.) Add a student to a club
    void addStudentToClub(const string& student, const string& club) {
        addNewStudent(student); // Ensure the student exists
        createNewClub(club);    // Ensure the club exists

        clubs[club].insert(student);
        studentClubs[student].insert(club);

        // Create edges with other club members
        for (const auto& member : clubs[club]) {
            if (member != student) {
                adjList[student].insert(member);
                adjList[member].insert(student);
            }
        }
    }

    // d.) Remove a student from a club
    void removeStudentFromClub(const string& student, const string& club) {
        if (clubs[club].erase(student)) {
            studentClubs[student].erase(club);

            // Remove edges with other club members
            for (const auto& member : clubs[club]) {
                adjList[student].erase(member);
                adjList[member].erase(student);
            }
        }
    }

    // Display the adjacency list
    void display() const {
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

    // Sort students by last name
    void displaySortedStudents() const {
        vector<string> students;
        for (const auto& pair : adjList) {
            students.push_back(pair.first);
        }

        sort(students.begin(), students.end(), [](const string& a, const string& b) {
            size_t posA = a.find_last_of(' ');
            size_t posB = b.find_last_of(' ');
            return a.substr(posA + 1) < b.substr(posB + 1);
        });

        cout << "Students sorted by last name:" << endl;
        for (const auto& student : students) {
            cout << student << endl;
        }
    }

    // Save the current state of the system to a file
    void saveStateToFile(const string& filename) {
        ofstream outFile(filename);

// Save students and their adjacency list
        outFile << "Students:" << endl;
        for (const auto& pair : adjList) {
            outFile << pair.first << ":";
            for (const auto& neighbor : pair.second) {
                outFile << neighbor << ",";
            }
            outFile << endl;
        }

// Save clubs and their members
        outFile << "Clubs:" << endl;
        for (const auto& pair : clubs) {
            outFile << pair.first << ":";
            for (const auto& member : pair.second) {
                outFile << member << ",";
            }
            outFile << endl;
        }

        outFile.close();
        cout << "State saved to file: " << filename << endl;
    }

    // Load the state of the system from a file
    void loadStateFromFile(const string& filename) {
        ifstream inFile(filename);

        adjList.clear();
        clubs.clear();
        studentClubs.clear();

        string line;
        bool isStudentSection = false, isClubSection = false;

        while (getline(inFile, line)) {
            if (line == "Students:") {
                isStudentSection = true;
                isClubSection = false;
                continue;
            } else if (line == "Clubs:") {
                isStudentSection = false;
                isClubSection = true;
                continue;
            }

            if (isStudentSection) {
                size_t colonPos = line.find(':');
                string student = line.substr(0, colonPos);
                string neighbors = line.substr(colonPos + 1);
                size_t pos = 0;
                while ((pos = neighbors.find(',')) != string::npos) {
                    string neighbor = neighbors.substr(0, pos);
                    adjList[student].insert(neighbor);
                    neighbors.erase(0, pos + 1);
                }
            } else if (isClubSection) {
                size_t colonPos = line.find(':');
                string club = line.substr(0, colonPos);
                string members = line.substr(colonPos + 1);
                size_t pos = 0;
                while ((pos = members.find(',')) != string::npos) {
                    string member = members.substr(0, pos);
                    clubs[club].insert(member);
                    studentClubs[member].insert(club);
                    members.erase(0, pos + 1);
                }
            }
        }

        inFile.close();
        cout << "State loaded from file: " << filename << endl;
    }
};

// Load the state from a file
int main() {
    Graph g;

// Load the state from a file
    g.loadStateFromFile("graph_state.txt");
    g.display();

    int choice;
    string student, club, filename;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add New Student\n";
        cout << "2. Create New Club\n";
        cout << "3. Add Student to Club\n";
        cout << "4. Find Clubs of a Student\n";
        cout << "5. Find Students in a Club\n";
        cout << "6. Remove Student from Club\n";
        cout << "7. Display Adjacency List\n";
        cout << "8. Display Sorted Students\n";
        cout << "9. Save State to File\n";
        cout << "10. Load State from File\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter student name: ";
                cin.ignore();
                getline(cin, student);
                g.addNewStudent(student);
                break;

            case 2:
                cout << "Enter club name: ";
                cin.ignore();
                getline(cin, club);
                g.createNewClub(club);
                break;

            case 3:
                cout << "Enter student name: ";
                cin.ignore();
                getline(cin, student);
                cout << "Enter club name: ";
                getline(cin, club);
                g.addStudentToClub(student, club);
                break;

            case 4:
                cout << "Enter student name: ";
                cin.ignore();
                getline(cin, student);
                g.findClubsOfStudent(student);
                break;

            case 5:
                cout << "Enter club name: ";
                cin.ignore();
                getline(cin, club);
                g.findStudentsInClub(club);
                break;

            case 6:
                cout << "Enter student name: ";
                cin.ignore();
                getline(cin, student);
                cout << "Enter club name: ";
                getline(cin, club);
                g.removeStudentFromClub(student, club);
                break;

            case 7:
                cout << "Adjacency List of the Graph:\n";
                g.display();
                break;

            case 8:
                g.displaySortedStudents();
                break;

            case 9:
                cout << "Enter filename to save state: ";
                cin.ignore();
                getline(cin, filename);
                g.saveStateToFile(filename);
                break;

            case 10:
                cout << "Enter filename to load state: ";
                cin.ignore();
                getline(cin, filename);
                g.loadStateFromFile(filename);
                break;

            case 0:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
