#pragma once

#include <iostream>
#include <fstream>
#include <string>

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
    string* courseID = new string[7];
    Mark *Result = new Mark[7];
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
};

struct SchoolYear {
    string Name;
    string start_date;
    string end_date;
    Semester* SemestersList;
    int NumOfClasses = 50;
    Class* ClassesList;
};


void addNewClasses(Class *&NewClasses, int &numOfClass);
void addClasses(SchoolYear &sy, Class *OldClasses, int NumOldClasses);
void createSchoolYear(SchoolYear &sy, Class *OldClasses, int NumOldClasses);
void deleteSchoolYear(SchoolYear &sy);