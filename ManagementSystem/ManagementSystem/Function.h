#pragma once
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>


using namespace std;

template <typename DT>
struct Node {
    DT data;
    Node* next = nullptr;
};

struct Time
{
    short Hour;
    short Minute;
};

struct Mark {
    string CourseID;
    string Type;
    float TotalMark = -1;
    float FinalMark = -1;
    float MidtermMark = -1;
    float OtherMark = -1;
};

struct User {
    string Username;
    string Password;
    string Fullname;
    bool Gender; //true: male, false: female
    string DOB;
    string Email;
};

struct Student : User
{
    string StID;
    string FirstName;
    string LastName;
    string Class;
    string SocialID;
    string *courseID = new string[7];
    string *courseName = new string[7];
    int numOfCoursesAttending;
    Mark *Result = new Mark[7];
    void setResult(string CourseID, Mark res) {
        for (int i = 0; i < numOfCoursesAttending; ++i) {
            if (courseID[i] == CourseID) {
                Result[i] = res;
                break;
            }
        }
    }
};

struct Course {
    string ID;
    string Name;
    short NumOfCredits;
    string ClassName;
    string Lecturer;
    string DayOfWeek;
    int session; ////1: 7:30; 2: 9:30; 3: 13:30; 4: 15:30.
    int maxStudent = 50;
    int numOfStudent = 0;
    Node<Student>* stHead = nullptr;
    string start_date;
    string end_date;
};

struct Class {
    string Name;
    Node<Student>* stHead = nullptr;
};

struct Semester {
    string name;
    string start_date;
    string end_date;
    Course* CoursesList = nullptr;
    int numOfCourses;   
    Semester() : start_date(""), end_date(""), numOfCourses(0), CoursesList(nullptr), name("") {}
    Semester(const string &start, const string &end)
        : start_date(start), end_date(end), numOfCourses(0), CoursesList(nullptr), name("") {}
};

struct SchoolYear {
    string Name;
    string start_date;
    string end_date;
    int numOfSemesters = 0;
    Semester* SemestersList;
    int NumOfClasses = 50;
    Class* ClassesList;
};

//functions for loading data from file
SchoolYear *loadSchoolYearList(SchoolYear *&SyList, int &numSY);
bool loadSemesterFromFile(Semester &se, string filename);
void loadCourseList(Course *&CourseList, int &numOfCourse, string filename);
void loadCourseInfoFromFile(Course &co, string filename);
void loadClassList(Class *&ClassList, int &numClass, string filename);
void loadCourseStudents(Course &co, string filename);
void loadStudentFromFile(Node<Student>*& pHead, string filename);
void loadStudentCoursesInfo(Student *st, string filename);
void loadStaffFromFile(Node<User>*& pHead);

//functions for updating data to file
void updateSchoolYearList(SchoolYear *SyList, int numSY);
void updateSemesterToFile(Semester se, string filename);
void updateCourseList(Course *CourseList, int numOfCourse, string filename);
void updateCourseToFile(Course co, string filename);
void updateClassList(Class *ClassList, int numClass, string filename);
void updateStudentToFile(Node<Student> *pHead, string filename);
void updateStaffToFile(Node<User> *pHead);

//functions for deleting data:
void deleteStaffList(Node<User> *StaffHead);
void deleteStudentList(Node<Student> *pHead);
void deleteClassList(Class *ClassList, int numOfClasses);
void deleteSemesterList(Semester *SemesterList, int numOfSemesters);
void deleteCourseList(Course *CourseList, int numOfCourses);
void deleteSchoolYearList(SchoolYear *SyList, int numOfSchoolYears);
void deleteCourse(SchoolYear* SyList, Semester* SemestersList, Course* CourseList, int numSY);
void removeStudentFromCourse(SchoolYear* SyList, Semester* SemestersList, Course* CourseList, int numSY);

//functions for ouputting
void outputStaffList(Node<User> *StaffHead);
void outputStudent(Student x);
void outputStudentList(Node<Student> *StudentHead);

void displayClassesList(Node <Class>*& pHead, string Name, int& n);
void addNewClasses(Class*& NewClasses, int& numOfClass);
void addClasses(SchoolYear& sy, Class* OldClasses, int NumOldClasses);
void initSchoolYear(SchoolYear& sy, Class* OldClasses, int NumOldClasses);
void createSchoolYear(SchoolYear*& SyList, int& numSY);

void initData(SchoolYear& currentSchoolYear);
void addCourse(SchoolYear& schoolYear);
void addStudentToCourse(SchoolYear &schoolYear); 

void initSemester(Semester& sem);
void createSemester(SchoolYear& sy);

//View a list of his/her courses. He/she will study these courses in this semester.
void viewListCourse(const Student& student, Semester& semester);

void viewScoreboard(SchoolYear currentSchoolYear);
void updateStudentResult(SchoolYear currentSchoolYear, Student student, Course course, int newPoint);
void viewScoreboardInfo(Semester semester, string courseID, string className);
void updateStudentResultInCourse(Semester semester, string studentId, string courseId, string className, int newPoint);


void viewListCourse(const Student& st, SchoolYear schoolYear);


void displayClassesList(SchoolYear SyList, Class* CLassList);
void viewStudentsInClass(SchoolYear Sy, Class* ClassList);
void viewListOfCourse(int Option, SchoolYear* SyList, Semester* SemesterList, Course* CourseList, int numSY);
void viewStudentsInCourse(SchoolYear* SyList, Semester* SemesterList, Course* CourseList, int numSY);
void exportListOfStudentsInCourse(SchoolYear* SyList, Semester* SemesterList, Course* CourseList, int numSY);


// 
bool checkLogin(bool& role, Node<User>*& pUser, Node<Student>*& pStudent, string username, string password, SchoolYear*& currentSchoolYear, Node<User>* StaffHead);
void viewScoreboardOfClass(Class clazz, Semester semester);
void viewScoreboardOfStudent(Student student, Semester semester);
void importScoreboardOfCourse(string pathFile, Semester semester);