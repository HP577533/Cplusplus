#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <tuple>
#include <ctime>

using namespace std;

class Course {
public:
    string courseCode;
    string name;
    string roomType;
    int maxCapacity;
    vector<string> enrolledStudents; // List of student IDs
    vector<string> scheduledTimeSlots; 

    Course() : courseCode(""), name(""), roomType(""), maxCapacity(0) {}

    Course(const string& code, const string& courseName, const string& roomType, int capacity)
        : courseCode(code), name(courseName), roomType(roomType), maxCapacity(capacity) {}
};

class Student {
public:
    string studentID;
    string major;
    vector<string> enrolledCourses; // List of course codes
    int academicYear;

    Student(const string& id, const string& studentMajor, int year)
        : studentID(id), major(studentMajor), academicYear(year) {}
};

class Room {
public:
    string roomNumber;
    string type;
    int capacity;
    vector<string> availableTimeSlots; 
    vector<string> specialEquipment; 

    Room(const string& number, const string& roomType, int roomCapacity)
        : roomNumber(number), type(roomType), capacity(roomCapacity) {}
};

// Struct to represent a registration request
struct RegistrationRequest {
    string studentID;
    string courseCode;
    int academicYear;
    bool isCoreCourse;
    time_t timestamp;

    // Custom comparator for priority queue
    bool operator<(const RegistrationRequest& other) const {
        if (academicYear != other.academicYear)
            return academicYear < other.academicYear;   // Higher academic year gets higher priority
        if (isCoreCourse != other.isCoreCourse)
            return !isCoreCourse;                       // Core courses get higher priority
        return timestamp > other.timestamp;             // Earlier requests get higher priority
    }
};

int main() {
    // Dummy data for testing
    // Courses:
    Course course1("PRG622", "Programming", "Lab", 10);
    Course course2("IS622", "Information Systems", "Lecture", 20);
    Course course3("DBI600", "Database Systems", "Lecture", 20);

    // Rooms:
    Room room1("R101", "Lecture", 20);
    room1.availableTimeSlots = {"Monday 9-11", "Wednesday 14-16"};

    Room room2("R102", "Lab", 10);
    room2.availableTimeSlots = {"Tuesday 10-12", "Thursday 15-17"};

    // Core courses for each major
    map<string, vector<string>> coreCourses = {
        {"Programming", {"PRG622"}},
        {"Information Systems", {"IS622"}},
        {"Database Systems", {"DBI600"}}
    };

    // Priority queue for registration requests
    priority_queue<RegistrationRequest> registrationQueue;

    // Input system for student registration
    while (true) {
        cout << "Enter student details for registration (or type 'exit' to stop):" << endl;

        string studentID, major, courseCode;
        int academicYear;
        cout << "Student ID: ";
        cin >> studentID;
        if (studentID == "exit") break;

        cout << "Available Majors:" << endl;
        map<int, string> majors = {
            {1, "Programming"},
            {2, "Information Systems"},
            {3, "Database Systems"}
        };

        for (const auto& majorPair : majors) {
            cout << majorPair.first << ". " << majorPair.second << endl;
        }

        int majorChoice;
        cout << "Select Major (enter the number): ";
        cin >> majorChoice;

        if (majors.find(majorChoice) != majors.end()) {
            major = majors[majorChoice];
        } else {
            cout << "Invalid choice. Please try again." << endl;
            continue;
        }

        cout << "Academic Year (1-4): ";
        cin >> academicYear;

        cout << "Available courses: " << endl;
        map<int, Course> courses = {
            {1, course1},
            {2, course2},
            {3, course3}
        };

        for (const auto& coursePair : courses) {
            cout << coursePair.first << ". " << coursePair.second.courseCode 
             << " (" << coursePair.second.name << ")" << endl;
        }

        int courseChoice;
        cout << "Select Course (enter the number): ";
        cin >> courseChoice;

        if (courses.find(courseChoice) != courses.end()) {
            courseCode = courses[courseChoice].courseCode;
        } else {
            cout << "Invalid choice. Please try again." << endl;
            continue;
        }

        // Create a registration request
        RegistrationRequest req;
        req.studentID = studentID;
        req.courseCode = courseCode;
        req.academicYear = academicYear;
        req.isCoreCourse = (!coreCourses[major].empty() && coreCourses[major][0] == courseCode);
        req.timestamp = time(nullptr);

        // Add the request to the queue
        registrationQueue.push(req);

        cout << "Registration request added successfully!" << endl;
    }

    // Process registration requests
    while (!registrationQueue.empty()) {
        RegistrationRequest req = registrationQueue.top();
        registrationQueue.pop();

        cout << "Processing registration for Student ID: " << req.studentID
             << ", Course Code: " << req.courseCode
             << ", Academic Year: " << req.academicYear
             << ", Core Course: " << (req.isCoreCourse ? "Yes" : "No")
             << ", Timestamp: " << req.timestamp << endl;
    }

    return 0;
}