#include <iostream>
#include <vector>

using namespace std;

class Student {
    private:
        string strName;
        string strSurname;
        string strStudentID;
        vector<string> vecCourses;

    public:
        Student(string name, string surname, string studentID) {
            strName = name;
            strSurname = surname;
            strStudentID = studentID;
        }

        void addCourse(string course){
            vecCourses.push_back(course);
        }

        void displayDetails() {
            cout << "Name: : " << strName << endl;
            cout << "Surname: " << strSurname << endl;
            cout << "Student ID: " << strStudentID << endl;
            cout << "Courses: ";
            for (const string course : vecCourses) {
                cout << course << " ";
            }

        }
};

int main() {
    vector<Student> lisStudnets;
    Student student1("Henry", "Johnson", "40230960");
    Student student2("Ben", "Ten", "20250425");
    
    student1.addCourse("Math 101");
    student2.addCourse("Math 201");

    lisStudnets.push_back(student1);
    lisStudnets.push_back(student2);

    for(int i = 0; i < lisStudnets.size(); i++){
        cout << "Student " << i + 1 << endl;
        lisStudnets[i].displayDetails();
        cout << endl;
        cout << "-------------------------" << endl;
    }

    return 0;
}