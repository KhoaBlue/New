#include "Function.h"

bool isValid(const SchoolYear &schoolYear, const Course &newCourse) { // Method check valid course to add
    if (newCourse.ID == "") {
        cout << "Error: Course ID cannot be empty" << endl;
        return false;
    }
    if (newCourse.maxStudent <= 0) {
        cout << "Error: Max number of students must be greater than 0" << endl;
        return false;
    }
    if (newCourse.NumOfCredits <= 0) {
        cout << "Error: Number of credits must be greater than 0" << endl;
        return false;
    }
    if (newCourse.Name == "") {
        cout << "Error: Course name cannot be empty" << endl;
        return false;
    }
    if (newCourse.ClassName == "") {
        cout << "Error: Class name cannot be empty" << endl;
        return false;
    }
    if (newCourse.Lecturer == "") {
        cout << "Error: Lecturer name cannot be empty" << endl;
        return false;
    }

    for (int i = 0; i < 3; ++i) {
        const Semester &semester = schoolYear.SemestersList[i];
        for (int j = 0; j < semester.numOfCourses; ++j) {
            if (semester.CoursesList[j].ID == newCourse.ID) {
                cout << "Error: Course ID already exists" << endl;
                return false;
            }
        }
    }

    return true;
}

void addCourse(SchoolYear& schoolYear) {
    string startYear;
    cout << "Enter startYear: ";
    cin >> startYear;
    string endYear;
    cout << "Enter endYear: ";
    cin >> endYear;
    string semesterName;
    cout << "Enter semester: ";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, semesterName);

    Semester se;
    // Find se with info
    for (int i = 0; i < 3; i++) {
        if (schoolYear.SemestersList[i].start_date == startYear && schoolYear.SemestersList[i].end_date == endYear) {
            se = schoolYear.SemestersList[i];
            break;
        }
    }

    if (se.CoursesList == nullptr) {
        se.CoursesList = new Course[1];
    }
    else {
        Course* newCoursesList = new Course[se.numOfCourses + 1];
        for (int i = 0; i < se.numOfCourses; ++i) {
            newCoursesList[i] = se.CoursesList[i];
        }
        delete[] se.CoursesList;
        se.CoursesList = newCoursesList;
    }

    Course newCourse;
    //Course ID,Course Name,Class,Lecturer,Number of credits,Max number of students,Number of Students
    cout << "Enter Course ID: ";
    getline(cin, newCourse.ID);
    cout << "Enter Course Name: ";
    getline(cin, newCourse.Name);
    cout << "Enter Class: ";
    getline(cin, newCourse.ClassName);
    cout << "Enter Lecturer: ";
    getline(cin, newCourse.Lecturer);
    cout << "Enter Number of credits: ";
    cin >> newCourse.NumOfCredits;
    cout << "Enter Max number of students: ";
    cin >> newCourse.maxStudent;
    newCourse.numOfStudent = 0;

    if (!isValid(schoolYear, newCourse)) {
        return;
    }

    se.CoursesList[se.numOfCourses++] = newCourse;

    string fileName = "../data/SchoolYears/" + startYear + "-" + endYear + "/" + semesterName + "/CourseList.csv";
    cout << "fileName: " << fileName << endl;
    ofstream file(fileName, ios::app);
    if (!file.is_open()) {
        cout << "Error: Cannot open file CourseList.csv" << endl;
        return;
    }
    file << newCourse.ID << "," << newCourse.Name << "," << newCourse.ClassName << ","
        << newCourse.Lecturer << "," << newCourse.NumOfCredits << "," << newCourse.maxStudent
        << "," << newCourse.numOfStudent << endl;
    file.close();
}

void addStudentToCourse(SchoolYear& currentSchoolYear)
{
    // Input student ID
    string studentID;
    cout << "Enter student ID: ";
    cin >> studentID;

    // Input course ID
    string courseID;
    cout << "Enter course ID: ";
    cin >> courseID;

    // Find student with studentID
    Student st;
    cout << " currentSchoolYear.NumOfClasses: " << currentSchoolYear.NumOfClasses << "" << endl;

    for (int i = 0; i < currentSchoolYear.NumOfClasses; i++) {
        Node<Student>* current = currentSchoolYear.ClassesList[i].stHead;
        while (current != nullptr) {
            if (current->data.StID == studentID) {
                st = current->data;
                break;
            }
            current = current->next;
        }
    }
    if (st.StID == "") {
        cout << "Error: Student ID not found" << endl;
        return;
    }

    // Find course with courseID
    Course co;
    for (int i = 0; i < currentSchoolYear.numOfSemesters; i++) {
        for (int j = 0; j < currentSchoolYear.SemestersList[i].numOfCourses; j++) {
            cout << "Check courseId = " << currentSchoolYear.SemestersList[i].CoursesList[j].ID << endl;
            if (currentSchoolYear.SemestersList[i].CoursesList[j].ID == courseID) {
                co = currentSchoolYear.SemestersList[i].CoursesList[j];
                break;
            }
        }
    }
    if (co.ID == "") {
        cout << "Error: Course ID not found" << endl;
        return;
    }

    // Check if course is full
    if (co.numOfStudent >= co.maxStudent) {
        cout << "Error: Course is full" << endl;
        return;
    }

    string fileName = "../data/ClassesStudents/" + st.Class + "/CourseAttending/" + st.StID + ".txt";
    ifstream file(fileName);
    if (!file.is_open()) {
        ofstream fileOut(fileName);
    }
    else {
        string currentCourseID = "";
        while (getline(file, currentCourseID)) {
            if (currentCourseID == "") {
                break;
            }
            if (currentCourseID == courseID) {
                cout << "Error: Student is already in course" << endl;
                return;
            }
        }
        file.close();
    }


    // Add student to course
    for (int i = 0; i < 7; i++) {
        if (st.courseID[i] == "") {
            st.courseID[i] = courseID;
            break;
        }
    }

    // Add course to student
    for (int i = 0; i < 7; i++) {
        if (co.stHead == nullptr) {
            co.stHead = new Node<Student>;
            co.stHead->data = st;
            co.stHead->next = nullptr;
            co.numOfStudent++;
            break;
        }
        else {
            Node<Student>* current = co.stHead;
            while (current->next != nullptr) {
                current = current->next;
            }
            Node<Student>* newStudentNode = new Node<Student>;
            newStudentNode->data = st;
            newStudentNode->next = nullptr;
            current->next = newStudentNode;
            co.numOfStudent++;
            break;
        }
    }

    // Update student in class
    for (int i = 0; i < currentSchoolYear.NumOfClasses; i++) {
        Node<Student>* current = currentSchoolYear.ClassesList[i].stHead;
        while (current != nullptr) {
            if (current->data.StID == studentID) {
                current->data = st;
                break;
            }
            current = current->next;
        }
    }

    // Update course in semester
    for (int i = 0; i < currentSchoolYear.numOfSemesters; i++) {
        for (int j = 0; j < currentSchoolYear.SemestersList[i].numOfCourses; j++) {
            if (currentSchoolYear.SemestersList[i].CoursesList[j].ID == courseID) {
                currentSchoolYear.SemestersList[i].CoursesList[j] = co;
                break;
            }
        }
    }

    // Add courseId to file
    ofstream fileOut(fileName, ios::app);
    if (!fileOut.is_open()) {
        cout << "Error: Cannot open file " << fileName << endl;
        return;
    }
    fileOut << courseID << endl;
    fileOut.close();

    cout << "Add student to course successfully" << endl;
}

bool copyCLassList(const Class *source, int numOfSources, Class *des) {
    for (int i = 0; i < numOfSources; ++i) {
        des[i].Name = source[i].Name;
        Node<Student> *cur = nullptr;
        Node<Student> *sourceCur = source[i].stHead;
        while (sourceCur) {
            if (cur == nullptr) {
                cur = new Node<Student>;
                cur->next = nullptr;
                cur->data = sourceCur->data;
                cur->data.courseID = new string[8];
                cur->data.courseName = new string[8];
                cur->data.Result = new Mark[8];
                for (int j = 0; j < cur->data.numOfCoursesAttending; ++j) {
                    cur->data.courseID[j] = sourceCur->data.courseID[j];
                    cur->data.courseName[j] = sourceCur->data.courseName[j];
                    cur->data.Result[j] = sourceCur->data.Result[j];
                }
                des[i].stHead = cur;
            }
            else {
                cur->next = new Node<Student>;
                cur = cur->next;
                cur->data = sourceCur->data;
                cur->next = nullptr;
                cur->data.courseID = new string[8];
                cur->data.courseName = new string[8];
                cur->data.Result = new Mark[8];
                for (int j = 0; j < cur->data.numOfCoursesAttending; ++j) {
                    cur->data.courseID[j] = sourceCur->data.courseID[j];
                    cur->data.courseName[j] = sourceCur->data.courseName[j];
                    cur->data.Result[j] = sourceCur->data.Result[j];
                }
            }
            sourceCur = sourceCur->next;
        }
    }
    return true;
}

void initSchoolYear(SchoolYear *sy, const SchoolYear &oldSY, Class *NewClasses, int numOfNewClasses)
{
    createFolder(sy->Name, "../data/SchoolYears");
    createFolder("Semester 1", "../data/SchoolYears/" + sy->Name);
    createFolder("Semester 2", "../data/SchoolYears/" + sy->Name);
    createFolder("Semester 3", "../data/SchoolYears/" + sy->Name);
    createFolder("CoursesInfo", "../data/SchoolYears/" + sy->Name + "/Semester 1");
    createFolder("CoursesInfo", "../data/SchoolYears/" + sy->Name + "/Semester 2");
    createFolder("CoursesInfo", "../data/SchoolYears/" + sy->Name + "/Semester 3");
    createFolder("CoursesStudents", "../data/SchoolYears/" + sy->Name + "/Semester 1");
    createFolder("CoursesStudents", "../data/SchoolYears/" + sy->Name + "/Semester 2");
    createFolder("CoursesStudents", "../data/SchoolYears/" + sy->Name + "/Semester 3");

    sy->SemestersList = new Semester[3];
    sy->numOfSemesters = 0;

    int numOfOldClasses = oldSY.NumOfClasses;
    sy->NumOfClasses = numOfNewClasses + numOfOldClasses;
    sy->ClassesList = new Class[sy->NumOfClasses];
    copyCLassList(oldSY.ClassesList, numOfOldClasses, sy->ClassesList);
    cout << numOfOldClasses << endl;
    for (int i = 0; i < numOfNewClasses; ++i) {
        sy->ClassesList[i + numOfOldClasses] = NewClasses[i];
    }
    delete[] NewClasses;
}

bool createSchoolYear(SchoolYear *&SyList, int &numSY, string name, Class *NewClasses, int numOfNewClasses, SchoolYear *&currentSchoolYear) {
    if (SyList == nullptr || numSY == 0) {
        numSY++;
        SyList = new SchoolYear[1];
        SyList->Name = name;
        SyList->ClassesList = NewClasses;
        SyList->NumOfClasses = numOfNewClasses;
        currentSchoolYear = SyList;
        return true;
    }
    for (int i = 0; i < numSY; ++i) {
        if (SyList[i].Name == name) return false;
    }
    SchoolYear *newSchoolYearList = new SchoolYear[numSY + 1];
    newSchoolYearList[numSY].Name = name;
    initSchoolYear(newSchoolYearList + numSY, SyList[numSY - 1], NewClasses, numOfNewClasses);
    for (int i = 0; i < numSY; ++i) {
        newSchoolYearList[i] = SyList[i];
    }
    delete[] SyList;
    SyList = newSchoolYearList;
    ++numSY;
    currentSchoolYear = SyList + numSY - 1;
    return true;
}

void initSemester(Semester& sem) {
    string name, start_date, end_date;
    cout << "Input the name of this semester (1, 2, or 3): ";
    cin >> name;
    cout << "Input the start date of this semester: ";
    cin >> start_date;
    cout << "Input the end_date of this semester: ";
    cin >> end_date;
    sem = Semester(start_date, end_date);
    sem.name = name;
}

void createSemester(SchoolYear& sy) {
    if (sy.numOfSemesters == 3) {
        cout << "Number of semesters is full.";
    }
    else {
        sy.numOfSemesters++;
        initSemester(sy.SemestersList[sy.numOfSemesters - 1]);
    }
}