#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <tuple>
#include <ctime>
#include <algorithm>

using namespace std;

// Course Class
class Course {
public:
    string courseCode;
    string name;
    string roomType;
    int maxCapacity;
    set<string> enrolledStudents; // List of student IDs
    string scheduledTimeSlot; 

    Course(const string code = "", const string courseName = "", const string roomType = "", int capacity = 0)
        : courseCode(code), name(courseName), roomType(roomType), maxCapacity(capacity) {}
};

// Student Class
class Student {
public:
    string studentID;
    string major;
    int academicYear;
    vector<string> enrolledCourses; // List of course codes
    
    Student(const string id = "", const string studentMajor = "", int year = 0)
        : studentID(id), major(studentMajor), academicYear(year) {}
};

// Room Class
class Room {
public:
    string roomNumber;
    string type;
    int capacity;
    set<string> availableTimeSlots; 
    vector<string> specialEquipment; 

    Room(const string number = "", const string roomType = "", int roomCapacity = 0)
        : roomNumber(number), type(roomType), capacity(roomCapacity) {}
};

// Struct to represent a registration request
struct RegistrationRequest {
    string studentID;
    string courseCode;
    int academicYear;
    bool isCoreCourse;
    time_t timestamp;

    // Priority queue comparator
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

    map<string, Course> courseMap = {
        {"PRG622", course1},
        {"IS622", course2},
        {"DBI600", course3}
    };

    // Rooms:
    Room room1("R101", "Lecture", 20);
    room1.availableTimeSlots = {"Monday 9-11", "Wednesday 14-16"};

    Room room2("R102", "Lab", 10);
    room2.availableTimeSlots = {"Tuesday 10-12", "Thursday 15-17"};

    vector<Room> rooms = {room1, room2};

    // Core courses for each major
    map<string, vector<string>> coreCourses = {
        {"Programming", {"PRG622"}},
        {"Information Systems", {"IS622"}},
        {"Database Systems", {"DBI600"}}
    };

    // Priority queue for registration requests
    priority_queue<RegistrationRequest> registrationQueue;

    // Students and schedules
    map<string, Student> students;
    map<string, map<string, string>> studentSchedules; // studentID -> (courseCode -> timeSlot)
    map<string, set<string>> roomSchedules;            // roomNumber -> timeSlots used

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
        int i = 1;
        map<int, string> courseOptions;
        for (const auto& pair : courseMap) {
            cout << i << ". " << pair.second.courseCode << " (" << pair.second.name << ")" << endl;
            courseOptions[i] = pair.second.courseCode;
            ++i;
        }

        int courseChoice;
        cout << "Select Course (enter the number): ";
        cin >> courseChoice;

        if (courseOptions.find(courseChoice) != courseOptions.end()) {
            courseCode = courseOptions[courseChoice];
        } else {
            cout << "Invalid choice. Please try again." << endl;
            continue;
        }

        // Create a registration request
        RegistrationRequest req;
        req.studentID = studentID;
        req.courseCode = courseCode;
        req.academicYear = academicYear;
        req.isCoreCourse = find(coreCourses[major].begin(), coreCourses[major].end(), courseCode) != coreCourses[major].end();
        req.timestamp = time(nullptr);

        // Add the request to the queue
        registrationQueue.push(req);

        cout << "Registration request added successfully!" << endl;
    }

    // Process registration requests
    while (!registrationQueue.empty()) {
        RegistrationRequest req = registrationQueue.top();
        registrationQueue.pop();

        Course& course = courseMap[req.courseCode];

        // Skip if course is full
        if (course.enrolledStudents.size() >= course.maxCapacity) {
            cout << "Course " << course.courseCode << " full. Cannot enroll " << req.studentID << endl;
            continue;
        }

        // Add student if not exist
        if (students.find(req.studentID) == students.end()) {
            students[req.studentID] = Student(req.studentID, "", req.academicYear);
        }

        Student& student = students[req.studentID];

        // Check for scheduling conflict and find room
        bool scheduled = false;
        for (Room& room : rooms) {
            if (room.type != course.roomType || room.capacity < course.maxCapacity) continue;

            for (const string& slot : room.availableTimeSlots) {
                if (roomSchedules[room.roomNumber].count(slot)) continue;

                bool conflict = false;
                for (const auto& [_, scheduledSlot] : studentSchedules[req.studentID]) {
                    if (scheduledSlot == slot) {
                        conflict = true;
                        break;
                    }
                }

                if (!conflict) {
                    // Assign course and time slot
                    course.enrolledStudents.insert(req.studentID);
                    student.enrolledCourses.push_back(course.courseCode);
                    studentSchedules[req.studentID][course.courseCode] = slot;
                    roomSchedules[room.roomNumber].insert(slot);
                    course.scheduledTimeSlot = slot;

                    cout << "Enrolled " << req.studentID << " in " << course.courseCode
                         << " at " << slot << " in room " << room.roomNumber << endl;

                    scheduled = true;
                    break;
                }
            }

            if (scheduled) break;
        }

        if (!scheduled) {
            cout << "No available slot for " << req.studentID << " in " << course.courseCode << endl;
        }
    }

    // Output final student schedules
    cout << "\n--- Final Student Schedules ---\n";
    for (const auto& [studentID, courses] : studentSchedules) {
        cout << "Student ID: " << studentID << endl;
        for (const auto& [courseCode, slot] : courses) {
            cout << " - " << courseCode << " at " << slot << endl;
        }
    }

    return 0;
}
