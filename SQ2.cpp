#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <ctime>

using namespace std;

// Course class
class Course {
public:
    string code, name, roomType;
    int maxStudents;
    set<string> enrolled;  // set to avoid duplicate students
    string timeSlot;  // the scheduled time slot for the course

    // Constructor to initialize the course
    Course(string c, string n, string rType, int max)
        : code(c), name(n), roomType(rType), maxStudents(max) {}
};

// Student class
class Student {
public:
    string id, major;
    int year;
    vector<string> courses;  // list of course codes the student is enrolled in

    // Constructor to initialize the student
    Student(string i, string m, int y)
        : id(i), major(m), year(y) {}
};

// Room class
class Room {
public:
    string number, type;
    int capacity;
    set<string> timeSlots;  // time slots for the room
    vector<string> equipment;  // special equipment for the room (optional)

    // Constructor to initialize the room
    Room(string num, string t, int cap, initializer_list<string> slots)
        : number(num), type(t), capacity(cap), timeSlots(slots) {}
};

// Registration request
struct Request {
    Student* student;  // pointer to the student making the request
    Course* course;  // pointer to the course the student is requesting
    bool isCore;  // whether the course is a core course for the student's major
    time_t time;  // the timestamp when the request was made

    // Constructor for request initialization
    Request(Student* s, Course* c, bool core)
        : student(s), course(c), isCore(core), time(std::time(nullptr)) {}

    // Priority logic for the queue
    bool operator<(const Request& other) const {
        // Prioritize by academic year, then by whether it's a core course, then by timestamp
        if (student->year != other.student->year)
            return student->year < other.student->year;
        if (isCore != other.isCore)
            return !isCore;  // core courses have higher priority
        return time > other.time;  // earlier requests get priority
    }
};

// Scheduler class that handles scheduling logic
class Scheduler {
    map<string, Course*> courseList;  // map of courses by their code
    map<string, Student*> studentList;  // map of students by their ID
    map<string, Room*> roomList;  // map of rooms by their number
    priority_queue<Request> requestQueue;  // queue to hold the registration requests

public:
    // Add course to the scheduler
    void addCourse(Course* c) {
        courseList[c->code] = c;
    }

    // Add student to the scheduler
    void addStudent(Student* s) {
        studentList[s->id] = s;
    }

    // Add room to the scheduler
    void addRoom(Room* r) {
        roomList[r->number] = r;
    }

    // Make a registration request for a student
    void makeRequest(string studentID, string courseCode, bool isCore) {
        if (studentList.count(studentID) && courseList.count(courseCode)) {
            requestQueue.push(Request(studentList[studentID], courseList[courseCode], isCore));
        }
    }

    // Schedule courses based on the requests in the queue
    void scheduleCourses() {
        while (!requestQueue.empty()) {
            Request req = requestQueue.top();
            requestQueue.pop();

            Student* s = req.student;
            Course* c = req.course;

            // If the course is full, skip it
            if (c->enrolled.size() >= c->maxStudents) continue;

            // If the course already has a time slot, check for conflict and enroll if possible
            if (!c->timeSlot.empty()) {
                if (!checkConflict(s, c->timeSlot)) {
                    c->enrolled.insert(s->id);
                    s->courses.push_back(c->code);
                }
                continue;
            }

            // Try to assign the course to an available room
            for (auto& [roomNum, room] : roomList) {
                if (room->type != c->roomType || room->capacity < c->maxStudents) continue;

                // Try to find an available time slot in the room
                for (string slot : room->timeSlots) {
                    if (!checkConflict(s, slot)) {
                        c->timeSlot = slot;
                        room->timeSlots.erase(slot);
                        c->enrolled.insert(s->id);
                        s->courses.push_back(c->code);
                        break;
                    }
                }

                if (!c->timeSlot.empty()) break;
            }
        }
    }

    // Check if a student has a conflict with a given time slot
    bool checkConflict(Student* s, string slot) {
        for (auto& code : s->courses) {
            if (courseList[code]->timeSlot == slot)
                return true;
        }
        return false;
    }

    // Print out the schedules for all students
    void printSchedules() {
        for (auto& [id, s] : studentList) {
            cout << "\nSchedule for Student " << id << ":\n";
            for (auto& cCode : s->courses) {
                Course* c = courseList[cCode];
                cout << "  " << c->name << " (" << c->code << ") - " << c->timeSlot << "\n";
            }
        }
    }
};

// Main function to run the program
int main() {
    Scheduler scheduler;

    // Process scheduling
    scheduler.scheduleCourses();

    // Show schedules
    scheduler.printSchedules();

    return 0;
}
