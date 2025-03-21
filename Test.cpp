#include <iostream>
#include <string>
#include <vector>
#include <map>

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

int main() {
    // Example usage
    Course course1("CS101", "Introduction to Programming", "Computer Lab", 30);
    course1.scheduledTimeSlots.push_back("Monday 10:00-12:00");
    course1.enrolledStudents.push_back("S12345");

    Student student1("S12345", "Computer Science", 1);
    student1.enrolledCourses.push_back("CS101");

    Room room1("R101", "Computer Lab", 30);
    room1.availableTimeSlots.push_back("Monday 10:00-12:00");
    room1.specialEquipment.push_back("Projector");

    cout << "Course: " << course1.name << ", Room Type: " << course1.roomType << endl;
    cout << "Student: " << student1.studentID << ", Major: " << student1.major << endl;
    cout << "Room: " << room1.roomNumber << ", Type: " << room1.type << endl;

    return 0;
}