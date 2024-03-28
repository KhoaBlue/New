#pragma once
#include<sstream>
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

struct Date {
    short Day;
    short Month;
    short Year;
};

struct Session
{
    string Day;
    short time; //1: 7:30; 2: 9:30; 3: 13:30; 4: 15:30.
};

struct Mark {
    string CourseID;
    string Type;
    float TotalMark;
    float FinalMark;
    float MidtermMark;
    float OtherMark;
};

struct User {
    string Username;
    string Password;
    string Fullname;
    bool Gender;
    Date DOB;
    string Email;
    void getDOB() {};
};

struct Student : User
{
    string StID;
    string FirstName;
    string LastName;
    string Class;
    string SocialID;
    string* courseName = new string[7];
    string* courseID = new string[7];
    int numOfCoursesAttending;
    Mark* Result = new Mark[7];
};

struct Course {
    string ID;
    string Name;
    short NumOfCredits;
    string ClassName;
    string Lecturer;
    int maxStudent = 50;
    int numOfStudent = 0;
    Node<Student>* stHead = nullptr;
};

struct Class {
    string Name;
    Node<Student>* stHead = nullptr;
};

struct Semester {
    string start_date;
    string end_date;
    Course* CoursesList;
    string name;
    int numOfCourses;

    Semester() : start_date(""), end_date(""), numOfCourses(0), CoursesList(nullptr), name("") {}

    Semester(const string& start, const string& end)
        : start_date(start), end_date(end), numOfCourses(0), CoursesList(nullptr), name("") {}
};

struct SchoolYear {
    string Name;
    string start_date;
    string end_date;
    Semester* SemestersList;
    int NumOfClasses = 50;
    Class* ClassesList;
    int numOfSemesters;
};

void LoadFileClass(Node <Class>*& pHead, string Name, int& n);
void displayClassesList(Node <Class>*& pHead, string Name, int& n);
void addNewClasses(Class*& NewClasses, int& numOfClass);
void addClasses(SchoolYear& sy, Class* OldClasses, int NumOldClasses);
void initSchoolYear(SchoolYear& sy, Class* OldClasses, int NumOldClasses);
void createSchoolYear(SchoolYear*& SyList, int& numSY);
void deleteSchoolYear(SchoolYear& sy);
void loadClassList(Class*& ClassList, int& numClass, string filename);
void loadSchoolYear(SchoolYear& sy);
void loadSchoolYearList(SchoolYear*& SyList, int& numSY);
void updateClassList(Class* ClassList, int numClass, string filename);
void updateSchoolYear(SchoolYear* SyList);
void updateSchoolYearList(SchoolYear* SyList, int numSY);
void initData(SchoolYear& currentSchoolYear);

void addCourse(SchoolYear& schoolYear);
void addStudentToCourse(SchoolYear& schoolYear);
//View a list of his/her courses. He/she will study these courses in this semester.
void viewListCourse(const Student& student, Semester& semester);

void viewScoreboard(SchoolYear currentSchoolYear);
void updateStudentResult(SchoolYear currentSchoolYear, Student student, Course course, int newPoint);
void viewScoreboardInfo(Semester semester, string courseID, string className);
void updateStudentResultInCourse(Semester semester, string studentId, string courseId, string className, int newPoint);
