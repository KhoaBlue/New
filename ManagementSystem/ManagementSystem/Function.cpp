#include "Function.h"
#include <string>
#include <sstream>

void addNewClasses(Class*& NewClasses, int& numOfClass)
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
		loadStudentFromFile(ClassList[i].stHead, "../data/ClassesStudents/" + ClassList[i].Name + "/" + ClassList[i].Name + ".csv");
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

//void displayClassesList(Node <Class>*& pHead, string Name, int& n) {
//	Node <Class>* pTem = pHead;
//	for (int i = 0; i < n; i++) {
//		cout << pTem->data.Name << " ";
//		pTem = pTem->next;
//	}
//}

// Method view list course of student
void viewListCourse(const Student& st, SchoolYear schoolYear) {
    cout << "View list course of student: " << st.FirstName << " " << st.LastName << endl;
    for (int i = 0; i < 3; ++i) {
        const Semester& semester = schoolYear.SemestersList[i];
        for (int j = 0; j < semester.numOfCourses; ++j) {
            const Course& course = semester.CoursesList[j];
            for (int k = 0; k < 7; ++k) {
                if (st.courseID[k] == course.ID) {
                    cout << "Course " << k + 1 << ": " << course.Name << endl;
                }
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

    for (int i = 0; i < 3; ++i) {
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



// Method add student to course
void addStudentToCourse(Course &co, Student st) {
    // Input student ID
    string studentID;
    cout << "Enter student ID: ";
    cin >> studentID;

    // Input course ID
    string courseID;
    cout << "Enter course ID: ";
    cin >> courseID;

    // Find student with studentID : function 1
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

    // Find course with courseID : function 2
    Course co;
    for (int i = 0; i < 3; i++) {
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
    for (int i = 0; i < 3; i++) {
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
void loadStudentFromFile(Node<Student> *&pHead, string filename) {
	ifstream fin;
	fin.open("../data/ClassesStudents/" + filename + "/" + filename + ".csv");
	Node<Student>* pCur = nullptr;
	string line;
	if (fin.is_open()) {
		getline(fin, line);
		while (getline(fin, line)) {
			if (pCur == nullptr) {
				pCur = new Node<Student>;
				pHead = pCur;
			}
			else {
				pCur->next = new Node<Student>;
				pCur = pCur->next;
			}
			stringstream inputString(line);
			string no;
			getline(inputString, no, ',');
			getline(inputString, pCur->data.StID, ',');
			getline(inputString, pCur->data.FirstName, ',');
			getline(inputString, pCur->data.LastName, ',');
			string genderFromFile;
			getline(inputString, genderFromFile, ',');
			pCur->data.Gender = (genderFromFile[0] == 'M'); 
			string dob;
			getline(inputString, dob, ',');
			pCur->data.getDOB(dob);
			getline(inputString, pCur->data.SocialID, ',');
			getline(inputString, pCur->data.Password, '\n');
		}
	}
	fin.close();
}

void loadStaffFromFile(Node<User>*& pHead) {
	ifstream fin;
	fin.open("../data/StaffList.csv");
	Node<User>* pCur = nullptr;
	string line;
	if (fin.is_open()) {
		getline(fin, line);
		while (getline(fin, line)) {
			if (pCur == nullptr) {
				pCur = new Node<User>;
				pHead = pCur;
			}
			else {
				pCur->next = new Node<User>;
				pCur = pCur->next;
			}
			stringstream inputString(line);
			getline(inputString, pCur->data.Fullname, ',');
			string dob;
			getline(inputString, dob, ',');
			pCur->data.getDOB(dob);
			string genderFromFile;
			getline(inputString, genderFromFile, ',');
			pCur->data.Gender = (genderFromFile[0] == 'M');
			getline(inputString, pCur->data.Username, ',');
			getline(inputString, pCur->data.Password, ',');
			getline(inputString, pCur->data.Email, '\n');
		}
	}
	fin.close();
}

