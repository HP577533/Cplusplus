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
            return academicYear < other.academicYear; // Higher academic year gets higher priority
        if (isCoreCourse != other.isCoreCourse)
            return !isCoreCourse; // Core courses get higher priority
        return timestamp > other.timestamp; // Earlier requests get higher priority
    }
};

int main() {
    // Dummy data for testing
    // Courses:
    Course course1("PRG622", "Programming", "Lab", 10);
    Course course2("IS622", "Information Systems", "Lecture", 20);
    Course course3("DBI600", "Database Systems", "Lecture", 20);
    
    // Students:
    Student student1("S001", "Programming", 1);
    Student student2("S002", "Programming", 2);
    Student student3("S003", "Information Systems", 1);
    Student student4("S004", "Information Systems", 2);
    Student student5("S005", "Programming", 3);
    Student student6("S006", "Programming", 1);
    Student student7("S007", "Information Systems", 3);
    Student student8("S008", "Programming", 2);
    Student student9("S009", "Information Systems", 1);
    Student student10("S010", "Programming", 3);
    Student student11("S011", "Information Systems", 2);
    Student student12("S012", "Programming", 1);
    Student student13("S013", "Information Systems", 3);
    Student student14("S014", "Programming", 2);
    Student student15("S015", "Information Systems", 1);
    Student student16("S016", "Programming", 3);
    Student student17("S017", "Information Systems", 2);
    Student student18("S018", "Programming", 1);
    Student student19("S019", "Information Systems", 3);
    Student student20("S020", "Programming", 2);
    Student student21("S021", "Information Systems", 1);
    Student student22("S022", "Programming", 3);
    Student student23("S023", "Database Systems", 1);
    Student student24("S024", "Database Systems", 2);
    Student student25("S025", "Database Systems", 3);
    Student student26("S026", "Database Systems", 1);
    Student student27("S027", "Database Systems", 2);
    Student student28("S028", "Database Systems", 3);
    Student student29("S029", "Database Systems", 1);
    Student student30("S030", "Database Systems", 2);

    // Rooms:
    Room room1("R101", "Lecture", 20);
    Room room2("R102", "Lab", 10);

    // Core courses for each major
    map<string, vector<string>> coreCourses = {
        {"Programming", {"PRG622"}},
        {"Information Systems", {"IS622"}},
        {"Database Systems", {"DBI600"}}
    };

    // Priority queue for registration requests
    priority_queue<RegistrationRequest> registrationQueue;

    // Example registration requests
    registrationQueue.push({"S001", "PRG622", 1, true, time(nullptr)});
    registrationQueue.push({"S002", "IS622", 2, true, time(nullptr) - 10});
    registrationQueue.push({"S003", "DBI600", 3, true, time(nullptr) - 20});
    registrationQueue.push({"S004", "PRG622", 1, false, time(nullptr) - 30});

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