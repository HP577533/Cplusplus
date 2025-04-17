#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Club; // Forward declaration

class Student {
private:
    string firstname;
    string lastname;
    vector<Club*> clubs;

public:
    Student(const string& firstname, const string& lastname) 
        : firstname(firstname), lastname(lastname) {}

    string getFirstName() const {
        return firstname;
    }

    string getLastName() const {
        return lastname;
    }

    string getFullName() const {
        return firstname + " " + lastname;
    }

    void addClub(Club* club) {
        clubs.push_back(club);
    }
};

class Club {
private:
    string name;
    vector<Student*> members;

public:
    const vector<Student*>& getMembers() const {
        return members;
    }

    vector<Student*>& getMembers() {
        return members;
    }

    Club(const string& name) : name(name) {}

    string getName() const {
        return name;
    }

    void addMember(Student* student) {
        members.push_back(student);
    }
};

// Add a new student to the system
void addStudent(const string& firstname, const string& lastname) {
    Student* newStudent = new Student(firstname, lastname);
    cout << "Student " << firstname << " " << lastname << " added." << endl;
}

// Create a new club
void createClub(const string& name) {
    Club* newClub = new Club(name);
    cout << "Club " << name << " created." << endl;
}

// Add a student to a club
void addStudentToClub(Student* student, Club* club) {
    club->addMember(student);
    student->addClub(club);
    cout << "Student " << student->getFullName() << " added to club " << club->getName() << "." << endl;
}

// Remove a student from a club
void removeStudentFromClub(Student* student, Club* club) {
    auto it = find(club->getMembers().begin(), club->getMembers().end(), student);
    if (it != club->getMembers().end()) {
        club->getMembers().erase(it);
        cout << "Student " << student->getFullName() << " removed from club " << club->getName() << "." << endl;
    } else {
        cout << "Student not found in the club." << endl;
    }
}

// A function to find all clubs a student is a member of
vector<Club*> findClubsByStudent(const string& firstname, const string& lastname) {
    vector<Club*> clubs;
    // Implementation depends on how students and clubs are stored globally
    return clubs;
}

// A function to find all students who are in a specific club
vector<Student*> findStudentsByClub(const string& clubName) {
    vector<Student*> students;
    // Implementation depends on how students and clubs are stored globally
    return students;
}
