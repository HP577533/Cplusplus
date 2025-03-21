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

// Struct to represent a course registration request
struct RegistrationRequest {
    string studentID;
    string courseCode;
    int academicYear;
    bool isCoreCourse;
    time_t timestamp;

    RegistrationRequest(const string& student, const string& course, int year, bool core, time_t time)
        : studentID(student), courseCode(course), academicYear(year), isCoreCourse(core), timestamp(time) {}
};

// Comparator for the priority queue
struct CompareRequests {
    bool operator()(const RegistrationRequest& a, const RegistrationRequest& b) {
        // Higher academic year gets higher priority
        if (a.academicYear != b.academicYear)
            return a.academicYear < b.academicYear;

        // Core courses get higher priority
        if (a.isCoreCourse != b.isCoreCourse)
            return !a.isCoreCourse;

        // Earlier timestamps get higher priority
        return a.timestamp > b.timestamp;
    }
};

int main() {
    // Priority queue to manage registration requests
    priority_queue<RegistrationRequest, vector<RegistrationRequest>, CompareRequests> registrationQueue;

    // Example data
    time_t now = time(0);
    registrationQueue.push(RegistrationRequest("S001", "CS101", 3, true, now - 10)); // Core course, junior
    registrationQueue.push(RegistrationRequest("S002", "CS102", 4, false, now - 5)); // Non-core course, senior
    registrationQueue.push(RegistrationRequest("S003", "CS103", 2, true, now - 20)); // Core course, sophomore

    // Process the registration requests
    while (!registrationQueue.empty()) {
        RegistrationRequest req = registrationQueue.top();
        registrationQueue.pop();
        cout << "Processing request: StudentID=" << req.studentID
             << ", CourseCode=" << req.courseCode
             << ", AcademicYear=" << req.academicYear
             << ", IsCoreCourse=" << (req.isCoreCourse ? "Yes" : "No")
             << ", Timestamp=" << req.timestamp << endl;
    }

    return 0;
}