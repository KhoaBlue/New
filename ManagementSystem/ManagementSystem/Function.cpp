#include "Function.h"


void addNewClasses(Class *&NewClasses, int &numOfClass)
{
	cout << "Please input the file name: ";
	string filename;
	getline(cin,filename);
	for (int i = 0; i < numOfClass; ++i) {
		cin >> NewClasses[i].Name;
		//readStudentsList(NewClasses[i].stHead, filename);
	}
}

void addClasses(SchoolYear &sy, Class *OldClasses, int NumOldClasses)
{
	int NumNewClasses;
	cout << "Please input the number of new Classes";
	cin >> NumNewClasses;
	sy.NumOfClasses = NumNewClasses + NumOldClasses;
	sy.ClassesList = new Class[sy.NumOfClasses];
	
	addNewClasses(sy.ClassesList, NumNewClasses);
	for (int i = 0; i < NumOldClasses; ++i) {
		sy.ClassesList[i + NumNewClasses] = OldClasses[i];
	}
}

void initSchoolYear(SchoolYear &sy, Class *OldClasses, int NumOldClasses)
{
	cout << "Input Name of School Year: ";
	getline(cin, sy.Name);
	cout << "Input Start date: ";
	getline(cin, sy.start_date);
	cout << "Input End date: ";
	getline(cin, sy.end_date);
	addClasses(sy, OldClasses, NumOldClasses);
	sy.SemestersList = new Semester[3];
	for (int i = 0; i < 3; ++i) {
		sy.SemestersList[i].CoursesList = new Course[100];
	}
}

void createSchoolYear(SchoolYear *&SyList, int &numSY) {
	SchoolYear newSY;
	initSchoolYear(newSY, SyList[numSY - 1].ClassesList, SyList[numSY - 1].NumOfClasses);
	SchoolYear *newSchoolYearList = new SchoolYear[numSY + 1];
	for (int i = 0; i < numSY; ++i) {
		newSchoolYearList[i] = SyList[i];
	}
	newSchoolYearList[numSY] = newSY;
	delete[] SyList;
	SyList = newSchoolYearList;
	numSY++;
	updateSchoolYearList(SyList, numSY);
}

void deleteSchoolYear(SchoolYear &sy)
{
	for (int i = 0; i < 3; ++i) {
		delete[] sy.SemestersList[i].CoursesList;
	}
	delete[] sy.SemestersList;
	delete[] sy.ClassesList;
}

void loadClassList(Class *&ClassList, int &numClass, string filename)
{
	ifstream fin(filename);
	if (!fin) {
		cout << "Cannot loadClassList!";
		return;
	}
	fin >> numClass;
	ClassList = new Class[numClass];
	for (int i = 0; i < numClass; ++i) {
		fin >> ClassList[i].Name;
		//readStudentsList(ClassList[i].stHead, "../data/ClassesStudents/" + ClassList[i].Name + "/" + ClassList[i].Name + ".csv");
	}
	fin.close();
}

void loadSchoolYearList(SchoolYear *&SyList, int &numSY)
{
	ifstream fin("../data/SchoolYears.txt");
	if (!fin) {
		cout << "Cannot loadSchoolYearList" << endl;
		return;
	}
	fin >> numSY;
	SyList = new SchoolYear[numSY];
	for (int i = 0; i < numSY; ++i) {
		fin >> SyList[i].Name;
		loadClassList(SyList[i].ClassesList, SyList[i].NumOfClasses, "../data/SchoolYears/" + SyList[i].Name + "/ClassList.txt");
	}
	fin.close();
}

void updateClassList(Class *ClassList, int numClass, string filename)
{
	ofstream fout(filename);
	fout << numClass << endl;
	for (int i = 0; i < numClass; ++i) {
		fout << ClassList[i].Name << endl;
		//updateStudentsInClass("../ClassesStudents/" + ClassList[i].Name + "/" + ClassList[i].Name + ".csv");
	}
	fout.close();
}


void updateSchoolYearList(SchoolYear *SyList, int numSY)
{
	ofstream fout("../data/SchoolYears.txt");
	fout << numSY << endl;
	for (int i = 0; i < numSY; ++i) {
		fout << SyList[i].Name << endl;
		updateClassList(SyList[i].ClassesList, SyList[i].NumOfClasses, "../data/SchoolYears/" + SyList[i].Name + "/ClassList.txt");
	}
	fout.close();
}

void LoadFileClass(Node <Class>*& pHead, string Name, int& n) {
	ifstream fin;
	fin.open("../data/ClassesList.txt");
	if (fin.is_open()) {
		fin >> n;
		while (fin.get() != '\n');
		Node <Class>* pCur = nullptr;
		for (int i = 0; i < n; i++) {
			if (pHead == nullptr) {
				pHead = new Node <Class>;
				pCur = pHead;
			}
			else {
				pCur->next = new Node <Class>;
				pCur = pCur->next;
			}
			getline(fin, pCur->data.Name);
		}
	}
	fin.close();
}

void displayClassesList(Node <Class>*& pHead, string Name, int& n) {
	LoadFileClass(pHead, Name, n);
	Node <Class>* pTem = pHead;
	for (int i = 0; i < n; i++) {
		cout << pTem->data.Name << " ";
		pTem = pTem->next;
	}
}

// Method view list course of student
void viewListCourse(const Student& student, Semester& semester) //tìm trong semester hiện tại
{
    cout << "View list course of student: " << student.FirstName << " " << student.LastName << endl;
    for (int j = 0; j < semester.numOfCourses; ++j) {
        const Course& course = semester.CoursesList[j];
        for (int k = 0; k < 7; ++k) {
            if (student.courseID[k] == course.ID) {
                cout << "Course " << k + 1 << ": " << course.Name << endl;
            }
        }
    }
}

// Method check valid course to add
bool isValid(const SchoolYear& schoolYear, const Course& newCourse) {
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

    for (int i = 0; i < schoolYear.numOfSemesters; ++i) {
        const Semester& semester = schoolYear.SemestersList[i];
        for (int j = 0; j < semester.numOfCourses; ++j) {
            if (semester.CoursesList[j].ID == newCourse.ID) {
                cout << "Error: Course ID already exists" << endl;
                return false;
            }
        }
    }

    return true;
}

// Method add course
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
    for (int i = 0; i < schoolYear.numOfSemesters; i++) {
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



// Method add student to course
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

// Đọc thông tin của một học kỳ từ các tệp tin
void initData(SchoolYear& currentSchoolYear) {
    // Init data từ hệ thống file hiện tại 
}

void viewScoreboard(SchoolYear currentSchoolYear) {
    string courseId;
    cout << "Enter course ID: ";
    cin >> courseId;
    Semester* semestersList = currentSchoolYear.SemestersList;

    for (int i = 0; i < currentSchoolYear.numOfSemesters; i++) {
        Semester semester = semestersList[i];
        if (semester.numOfCourses <= 0) {
            continue;
        }

        Course* coursesList = semester.CoursesList;
        for (int j = 0; j < semester.numOfCourses; j++) {
            if (coursesList[j].ID == courseId) {
                viewScoreboardInfo(semester, courseId, coursesList[j].ClassName);
            }
        }
    }
}

void viewScoreboardInfo(Semester semester, string courseId, string className) {
    // Read file in path
    string path = "../data/SchoolYears/"
        + semester.start_date
        + "-" + semester.end_date
        + "/" + semester.name
        + "/CoursesStudents/"
        + courseId + "_" + className + ".csv";

    // Read file
    ifstream file(path);
    if (!file.is_open()) {
        cout << "Error: Cannot open file " << path << endl;
        return;
    }

    cout << "With class " << className << " and course " << courseId << endl;
    cout << "\t" << left << setw(10) << "No" << setw(20) << "Student ID" << setw(30) << "Student Full Name" << setw(10) << "Midterm" << setw(10) << "Final" << setw(10) << "Other" << setw(10) << "Total" << setw(10) << "GPA" << endl;
    // Read data
    string line;
    bool firstLine = true;
    while (getline(file, line)) {
        // Data of line: No,Student ID,Student Full Name,Midterm Mark,Final Mark,Other Mark,Total Mark,GPA
        string token;
        if (firstLine) {
            firstLine = false;
            continue;
        }
        istringstream iss(line);
        getline(iss, token, ',');
        cout << "\t" << left << setw(10) << token;
        cout << setw(20);
        getline(iss, token, ',');
        cout << token;
        cout << setw(30);
        getline(iss, token, ',');
        cout << token;
        cout << setw(10);
        getline(iss, token, ',');
        cout << token;
        cout << setw(10);
        getline(iss, token, ',');
        cout << token;
        cout << setw(10);
        getline(iss, token, ',');
        cout << token;
        cout << setw(10);
        getline(iss, token, ',');
        cout << token;
        cout << setw(10);
        getline(iss, token, ',');
        cout << token << endl;
    }
    file.close();
}

// Function 22: Update a student's result.
void updateStudentResult(SchoolYear currentSchoolYear, Student student, Course course, int newPoint) {

    Semester* semestersList = currentSchoolYear.SemestersList;

    for (int i = 0; i < currentSchoolYear.numOfSemesters; i++) {
        Semester semester = semestersList[i];
        if (semester.numOfCourses <= 0) {
            continue;
        }

        Course* coursesList = semester.CoursesList;
        for (int j = 0; j < semester.numOfCourses; j++) {
            if (coursesList[j].ID == course.ID) {
                updateStudentResultInCourse(semester, student.StID, course.ID, coursesList[j].ClassName, newPoint);
            }
        }
    }
}

void updateStudentResultInCourse(Semester semester, string studentId, string courseId, string className, int newPoint) {
    string path = "../data/SchoolYears/"
        + semester.start_date
        + "-" + semester.end_date
        + "/" + semester.name
        + "/CoursesStudents/"
        + courseId + "_" + className + ".csv";

    // Read file
    ifstream file(path);
    if (!file.is_open()) {
        cout << "Error: Cannot open file " << path << endl;
        return;
    }

    // Read data
    string line;
    Node<string>* lines = nullptr;
    while (getline(file, line)) {
        Node<string>* newNode = new Node<string>;
        newNode->data = line;
        newNode->next = nullptr;
        if (lines == nullptr) {
            lines = newNode;
        }
        else {
            Node<string>* current = lines;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    // Update new point
    //No,Student ID,Student Full Name,Midterm Mark,Final Mark,Other Mark,Total Mark,GPA
    Node<string>* currentLine = lines;
    while (currentLine != nullptr) {
        string line = currentLine->data;
        istringstream iss(line);
        string no;
        getline(iss, no, ',');
        string studentIDFile;
        getline(iss, studentIDFile, ','); // Student Id
        string fullname;
        getline(iss, fullname, ','); // Student Full Name
        string midtermMark;
        getline(iss, midtermMark, ','); // Midterm Mark
        string finalMark;
        getline(iss, finalMark, ','); // Final Mark
        string otherMark;
        getline(iss, otherMark, ','); // Other Mark
        string totalMark;
        getline(iss, totalMark, ','); // Total Mark
        string gpa;
        getline(iss, gpa, ','); // GPA

        if (studentIDFile == studentId) {
            // Update new point
            int yourChoose = 0;
            cout << "Choose the point you want to update: " << endl;
            cout << "1. Midterm Mark" << endl;
            cout << "2. Final Mark" << endl;
            cout << "3. Other Mark" << endl;
            cout << "4. Total Mark" << endl;

            while (yourChoose <= 0 || yourChoose > 4)
            {
                cout << "Enter your choose: ";
                cin >> yourChoose;
                if (yourChoose == 1) {
                    midtermMark = to_string(newPoint);
                }
                else if (yourChoose == 2) {
                    finalMark = to_string(newPoint);
                }
                else if (yourChoose == 3) {
                    otherMark = to_string(newPoint);
                }
                else if (yourChoose == 4) {
                    totalMark = to_string(newPoint);
                }
                else {
                    cout << "Invalid choose. Please choose again!" << endl;
                }
            }

        }

        currentLine->data = no + "," + studentIDFile + "," + fullname + "," + midtermMark + "," + finalMark + "," + otherMark + "," + totalMark + "," + gpa;
        currentLine = currentLine->next;
    }

    // Write to file
    ofstream fileOut(path);
    if (!fileOut.is_open()) {
        cout << "Error: Cannot open file " << path << endl;
        return;
    }

    Node<string>* current = lines;
    while (current != nullptr) {
        fileOut << current->data << endl;
        current = current->next;
    }
    fileOut.close();
}
