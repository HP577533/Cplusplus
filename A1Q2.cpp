<<<<<<< Updated upstream
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
    string Name;
    string roomType;
    int maxCapacity;
    vector<string> enrolledStudents;
    vector<string> timeSlots;
public:
    Course(string code, string name, string room, int capacity, vector<string> students, vector<string> slots)
        : courseCode(code), Name(name), roomType(room), maxCapacity(capacity), enrolledStudents(students), timeSlots(slots) {}

    string getCourseCode() const { return courseCode; }
};

// Student: Include student ID, major, list of enrolled courses, and academic year.
=======
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Forward declaration
class Course;

// Student Class
typedef unsigned int uint;
>>>>>>> Stashed changes
class Student {
private:
    string studentID;
    string major;
<<<<<<< Updated upstream
    vector<string> enrolledCourses;
    int academicYear;

public:
    Student(string id, string maj, vector<string> courses, int year) 
        : studentID(id), major(maj), enrolledCourses(courses), academicYear(year) {}

    int getAcademicYear() const { return academicYear; }
    string getMajor() const { return major; }
};

// Room: Include room number, type, capacity, available time slots, and any special equipment.
class Room {
private:
    string roomNum;
    string type;
    int capacity;
    vector<string> timeSlots;
    vector<string> specialEquipment;
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
    Student student1{"S001", "CS", {}, 2};
    Course course1{"CS101", "Intro to Computer Science", "Lecture Hall", 100, {}, {}};
    addRegistrationRequest(student1, course1);

    // Process registration requests
    while (!registrationQueue.empty()) {
        RegistrationRequest request = registrationQueue.top();
        registrationQueue.pop();
        // Process the request
        cout << "Processing registration for student " << request.student.getAcademicYear() << " for course " << request.course.getCourseCode() << endl;
    }

    return 0;
}

=======
    uint academicYear;
    vector<Course*> enrolledCourses;

public:
    Student(const string& id, const string& major, uint year) 
        : studentID(id), major(major), academicYear(year) {}

    void enroll(Course* course);
    void display() const;
};

// Room Class
class Room {
private:
    string roomNumber;
    string type;
    uint capacity;
    vector<string> availableTimeSlots;
    vector<string> specialEquipment;

public:
    Room(const string& number, const string& type, uint cap, const vector<string>& slots, const vector<string>& equipment = {})
        : roomNumber(number), type(type), capacity(cap), availableTimeSlots(slots), specialEquipment(equipment) {}
    
    void display() const;
};

// Course Class
class Course {
private:
    string courseCode;
    string name;
    string requiredRoomType;
    uint maxCapacity;
    vector<Student*> enrolledStudents;
    vector<string> scheduledTimeSlots;
    Room* assignedRoom;

public:
    Course(const string& code, const string& name, const string& roomType, uint capacity)
        : courseCode(code), name(name), requiredRoomType(roomType), maxCapacity(capacity), assignedRoom(nullptr) {}
    
    bool enrollStudent(Student* student);
    void assignRoom(Room* room);
    void display() const;
};

// Implementation of Student methods
void Student::enroll(Course* course) {
    enrolledCourses.push_back(course);
}

void Student::display() const {
    cout << "Student ID: " << studentID << " | Major: " << major << " | Year: " << academicYear << endl;
    cout << "Enrolled Courses: ";
    for (const auto& course : enrolledCourses) {
        cout << course->getCode() << " ";
    }
    cout << endl;
}

// Implementation of Room methods
void Room::display() const {
    cout << "Room Number: " << roomNumber << " | Type: " << type << " | Capacity: " << capacity << endl;
    cout << "Available Slots: ";
    for (const auto& slot : availableTimeSlots) {
        cout << slot << " ";
    }
    cout << endl;
    if (!specialEquipment.empty()) {
        cout << "Special Equipment: ";
        for (const auto& equip : specialEquipment) {
            cout << equip << " ";
        }
        cout << endl;
    }
}

// Implementation of Course methods
bool Course::enrollStudent(Student* student) {
    if (enrolledStudents.size() < maxCapacity) {
        enrolledStudents.push_back(student);
        student->enroll(this);
        return true;
    }
    return false;
}

void Course::assignRoom(Room* room) {
    if (room->getType() == requiredRoomType) {
        assignedRoom = room;
    }
}

void Course::display() const {
    cout << "Course: " << courseCode << " - " << name << " | Max Capacity: " << maxCapacity << endl;
    cout << "Scheduled Slots: ";
    for (const auto& slot : scheduledTimeSlots) {
        cout << slot << " ";
    }
    cout << endl;
    if (assignedRoom) {
        cout << "Assigned Room: " << assignedRoom->getRoomNumber() << endl;
    }
}

// Main function for testing
int main() {
    Student student1("S123", "Computer Science", 2);
    Student student2("S456", "Mathematics", 1);
    
    Course course1("CS101", "Data Structures", "Lab", 30);
    Course course2("MTH201", "Calculus", "Lecture Hall", 50);
    
    Room room1("A101", "Lab", 30, {"08:00-10:00", "10:00-12:00"}, {"Computers", "Projector"});
    Room room2("B202", "Lecture Hall", 100, {"08:00-10:00", "12:00-14:00"});
    
    course1.enrollStudent(&student1);
    course2.enrollStudent(&student2);
    
    course1.assignRoom(&room1);
    course2.assignRoom(&room2);
    
    student1.display();
    student2.display();
    course1.display();
    course2.display();
    room1.display();
    room2.display();
    
    return 0;
}
>>>>>>> Stashed changes
