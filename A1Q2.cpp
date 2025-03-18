/*Richfield needs a new course scheduling system. As an outsourced Junior C++ developer, you have been tasked to develop an 
intelligent system to optimize class schedules, room allocations, and student registrations.

Design and implement the following classes: 
o Course: Include attributes for course code, name, required room type, maximum capacity, enrolled students, 
    and scheduled time slots.
o Student: Include student ID, major, list of enrolled courses, and academic year.
o Room: Include room number, type, capacity, available time slots, and any special equipment.

• Implement a priority queue to manage course registration requests. The queue should prioritize based on the student's academic 
    year, core courses for their major, and request timestamp.
• Develop a schedule optimization algorithm that:
    o Processes registration requests from the priority queue o Assigns courses to appropriate rooms based on type and 
        capacity o Resolves scheduling conflicts o Balances class sizes
    o Generates individual student schedules*/

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <tuple>
#include <chrono>

using namespace std;

// Course: Include attributes for course code, name, required room type, maximum capacity, enrolled students, 
// and scheduled time slots.
class Course {
private:
    string courseCode;
    string name;
    string requiredRoomType;
    int maxCapacity;
    vector<string> enrolledStudents;
    vector<string> scheduledTimeSlots;

public:
    Course(string code, string name, string roomType, int capacity)
        : courseCode(code), name(name), requiredRoomType(roomType), maxCapacity(capacity) {}

    string getCourseCode() const { return courseCode; }
    string getRequiredRoomType() const { return requiredRoomType; }
    int getMaxCapacity() const { return maxCapacity; }
};

// Student: Include student ID, major, list of enrolled courses, and academic year.
class Student {
private:
    string studentID;
    string major;
    vector<string> enrolledCourses;
    int academicYear;

public:
    Student(string id, string maj, int year)
        : studentID(id), major(maj), academicYear(year) {}

    int getAcademicYear() const { return academicYear; }
    string getMajor() const { return major; }
};

// Room: Include room number, type, capacity, available time slots, and any special equipment.
class Room {
private:
    string roomNumber;
    string type;
    int capacity;
    vector<string> availableTimeSlots;
    vector<string> specialEquipment;

public:
    Room(string number, string type, int cap, vector<string> slots, vector<string> equipment = {})
        : roomNumber(number), type(type), capacity(cap), availableTimeSlots(slots), specialEquipment(equipment) {}

    string getType() const { return type; }
    int getCapacity() const { return capacity; }
};

// Implement a priority queue to manage course registration requests. The queue should prioritize based on the student's academic 
// year, core courses for their major, and request timestamp.

struct RegistrationRequest {
    Student student;
    Course course;
    std::chrono::time_point<std::chrono::system_clock> timestamp;

    bool operator<(const RegistrationRequest& other) const {
        // Prioritize by academic year (higher is better)
        if (student.getAcademicYear() != other.student.getAcademicYear()) {
            return student.getAcademicYear() < other.student.getAcademicYear();
        }
        // Prioritize core courses for their major (assuming core courses have a specific naming convention or list)
        bool isCoreCourse = (course.getCourseCode().find(student.getMajor()) != std::string::npos);
        bool isOtherCoreCourse = (other.course.getCourseCode().find(other.student.getMajor()) != std::string::npos);
        if (isCoreCourse != isOtherCoreCourse) {
            return !isCoreCourse;
        }
        // Prioritize by request timestamp (earlier is better)
        return timestamp > other.timestamp;
    }
};

std::priority_queue<RegistrationRequest> registrationQueue;

void addRegistrationRequest(const Student& student, const Course& course) {
    RegistrationRequest request{student, course, std::chrono::system_clock::now()};
    registrationQueue.push(request);
}

int main() {
    // Example usage
    Student student1{"S001", "CS", 2};
    Course course1{"CS101", "Intro to Computer Science", "Lecture Hall", 100};
    addRegistrationRequest(student1, course1);

    // Process registration requests
    while (!registrationQueue.empty()) {
        RegistrationRequest request = registrationQueue.top();
        registrationQueue.pop();
        // Process the request
        cout << "Processing registration for student with academic year " << request.student.getAcademicYear()
             << " for course " << request.course.getCourseCode() << endl;
    }

    return 0;
}
