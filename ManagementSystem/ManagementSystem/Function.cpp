#include "Function.h"
#include <string>
#include <sstream>

SchoolYear *loadSchoolYearList(SchoolYear *&SyList, int &numSY)
{
	ifstream fin("../data/SchoolYears.txt");
	if (!fin) {
		cout << "Cannot loadSchoolYearList" << endl;
		return nullptr;
	}
	fin >> numSY;
	SyList = new SchoolYear[numSY];
	for (int i = 0; i < numSY; ++i) {
		fin >> SyList[i].Name;
		loadClassList(SyList[i].ClassesList, SyList[i].NumOfClasses, "../data/SchoolYears/" + SyList[i].Name + "/ClassesList.txt");
		SyList[i].SemestersList = new Semester[3];
		for (int j = 0; j < 3; ++j) {
			loadSemesterFromFile(SyList[i].SemestersList[j], "../data/SchoolYears/" + SyList[i].Name + "/Semester " + to_string(j + 1) + "/");
		}
	}
	fin.close();
	return SyList;
}

bool loadSemesterFromFile(Semester &se, string filename) {
	ifstream fin(filename + "SemesterInfo.txt");
	if (!fin) {
		cout << "Cannot loadSemesterFromFile - Info" << endl;
		return false;
	}
	getline(fin, se.name);
	if (fin.eof()) {
		cout << "No data";
		fin.close();
		return false;
	}
	getline(fin, se.start_date);
	getline(fin, se.end_date);
	fin.close();
	loadCourseList(se.CoursesList, se.numOfCourses, filename);
	return true;
}

void loadCourseList(Course *&CourseList, int &numOfCourse, string filename)
{
	ifstream fin(filename + "CoursesList.txt");
	if (!fin) {
		cout << "Cannot loadCourseList!" << endl;
		return;
	}
	fin >> numOfCourse;
	CourseList = new Course[numOfCourse];
	for (int i = 0; i < numOfCourse; ++i) {
		fin >> CourseList[i].ID;
		fin >> CourseList[i].ClassName;
		loadCourseInfoFromFile(CourseList[i], filename + "CoursesInfo/" + CourseList[i].ID + "_" + CourseList[i].ClassName + ".txt");
		loadCourseStudents(CourseList[i], filename + "CoursesStudents/" + CourseList[i].ID + "_" + CourseList[i].ClassName + ".csv");
	}
	fin.close();
}

void loadCourseInfoFromFile(Course &co, string filename)
{
	ifstream fin(filename);
	if (!fin) {
		cout << filename << endl;
		cout << "Cannot loadCourseInfoFromFile" << endl;
		return;
	}

	getline(fin, co.Name);
	getline(fin, co.Lecturer);
	fin >> co.NumOfCredits;
	getline(fin, co.Name);
	getline(fin, co.Lecturer);
	fin >> co.NumOfCredits;
	fin >> co.maxStudent;
	fin >> co.numOfStudent;
	getline(fin, co.DayOfWeek);
	fin >> co.session;
	getline(fin, co.start_date);
	getline(fin, co.end_date);
	fin.close();

}

void loadCourseStudents(Course &co, string filename)
{
	ifstream fin(filename);
	if (!fin) {
		cout << "Cannot loadCourseStudents" << endl;
		return;
	}
	string line;
	Node<Student> *cur = nullptr;
	getline(fin, line);
	while (getline(fin, line)) {
		if (cur == nullptr) {
			cur = new Node<Student>;
			cur->next = nullptr;
			co.stHead = cur;
		}
		else {
			cur->next = new Node<Student>;
			cur = cur->next;
			cur->next = nullptr;
		}
		stringstream inputString(line);
		string no;
		getline(inputString, no, ',');
		getline(inputString, cur->data.StID, ',');
		getline(inputString, cur->data.Fullname, ',');
		Mark res;
		string mark;
		getline(inputString, mark, ',');
		res.MidtermMark = 1.0 * stoi(mark);
		getline(inputString, mark, ',');
		res.FinalMark = 1.0 * stoi(mark);
		getline(inputString, mark, ',');
		res.OtherMark = 1.0 * stoi(mark);
		getline(inputString, mark, ',');
		res.TotalMark = 1.0 * stoi(mark);
		getline(inputString, mark, '\n');
		res.Type = mark;
		cur->data.setResult(co.ID, res);
	}
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

void loadStudentFromFile(Node<Student> *&pHead, string filename) {
	ifstream fin;
	fin.open(filename);
	Node<Student> *pCur = nullptr;
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
			getline(inputString, pCur->data.DOB, ',');
			getline(inputString, pCur->data.SocialID, ',');
			getline(inputString, pCur->data.Password, '\n');
		}
	}
	fin.close();
}

void loadStaffFromFile(Node<User> *&pHead) {
	ifstream fin;
	fin.open("../data/StaffList.csv");
	Node<User> *pCur = nullptr;
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
			getline(inputString, pCur->data.DOB, ',');
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

void updateSemesterToFile(Semester se, string filename) {
	ofstream fout(filename + "SemesterInfo.txt");
	fout << se.name << endl << se.start_date << endl << se.end_date;
	fout.close();
	updateCourseList(se.CoursesList, se.numOfCourses, filename + "CoursesList.txt");
}

void updateCourseList(Course *CourseList, int numOfCourse, string filename)
{
	ofstream fout(filename);
	fout << numOfCourse << endl;
	for (int i = 0; i < numOfCourse; ++i) {
		fout << CourseList[i].ID << " " << CourseList[i].ClassName << endl;
		updateCourseToFile(CourseList[i], filename + "CoursesInfo/" + CourseList[i].ID + "_" + CourseList[i].ClassName + ".txt");
	}
	fout.close();
}

void updateCourseToFile(Course co, string filename)
{
	ofstream fout(filename);
	fout << co.Name << endl;
	fout << co.Lecturer << endl;
	fout << co.NumOfCredits << endl;
	fout << co.maxStudent << endl;
	fout << co.numOfStudent << endl;
	fout << co.DayOfWeek << endl;
	fout << co.session << endl;
	fout << co.start_date << endl;
	fout << co.end_date << endl;
	fout.close();
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

void updateStudentToFile(Node<Student> *pHead, string filename) {
	ofstream fout(filename);
	fout << "No,Student ID,First name,Last name,Gender,Date of Birth,Social ID,Password\n";
	Node<Student> *pCur = pHead;
	int no = 1;
	while (pCur) {
		fout << no++ << "," << pCur->data.StID << "," << pCur->data.FirstName << "," << pCur->data.LastName << ",";
		fout << (pCur->data.Gender == true ? "Male" : "Female") << ",";
		fout << pCur->data.DOB << "," << pCur->data.SocialID << "," << pCur->data.Password << endl;
		pCur = pCur->next;
	}
	cout << "Update Student to File successfully" << endl;
	fout.close();
}

void updateStaffToFile(Node<User> *pHead, string filename) {
	ofstream fout(filename);
	fout << "Full name,DOB,Gender,Username,Password,Email\n";
	Node<User>* pCur = pHead;
	while (pCur) {
		fout << pCur->data.Fullname << "," << pCur->data.DOB << ",";
		fout << (pCur->data.Gender == 1 ? "Male" : "Female") << ",";
		fout << pCur->data.Username << "," << pCur->data.Password << "," << pCur->data.Email << endl;
		pCur = pCur->next;
	}
	cout << "Update Staff to File succesfully" << endl;
	fout.close();
}




//void displayClassesList(Node <Class>*& pHead, string Name, int& n) {
//	Node <Class>* pTem = pHead;
//	for (int i = 0; i < n; i++) {
//		cout << pTem->data.Name << " ";
//		pTem = pTem->next;
//	}
//}

void loadStudentCoursesInfo(Student *st, string filename)
{
	ifstream fin(filename);
}

void deleteStaffList(Node<User> *StaffHead)
{
	Node<User> *cur = StaffHead;
	while (cur) {
		Node<User> *tmp = cur;
		cur = cur->next;
		delete tmp;
	}
}

void deleteStudentList(Node<Student> *pHead)
{
	Node<Student> *pCur = pHead;
	while (pCur) {
		Node<Student> *tmp = pCur;
		pCur = pCur->next;
		delete[] tmp->data.courseID;
		delete[] tmp->data.courseName;
		delete[] tmp->data.Result;
		delete tmp;
	}
}

void outputStaffList(Node<User> *StaffHead)
{
	Node<User> *cur = StaffHead;
	while (cur) {
		cout << cur->data.Fullname << " " << cur->data.DOB << " " << cur->data.Email << " ";
		cout << cur->data.Gender << " " << cur->data.Password << " " << cur->data.Username << endl;
		cur = cur->next;
	}
}

void deleteClassList(Class *ClassList, int numOfClasses)
{
	for (int i = 0; i < numOfClasses; ++i) {
		deleteStudentList(ClassList[i].stHead);
	}
	delete[] ClassList;
}	

void deleteSemesterList(Semester *SemesterList, int numOfSemester)
{
	for (int i = 0; i < numOfSemester; ++i) {
		deleteCourseList(SemesterList[i].CoursesList, SemesterList[i].numOfCourses);
	}
	delete[] SemesterList;
}

void deleteSchoolYearList(SchoolYear *SyList, int numOfSchoolYears) {
	for (int i = 0; i < numOfSchoolYears; ++i) {
		//deleteStudentList(SyList[i].ClassesList->stHead);
		deleteClassList(SyList[i].ClassesList, SyList[i].NumOfClasses);
		deleteSemesterList(SyList[i].SemestersList, SyList[i].numOfSemesters);
	}
	delete[] SyList;
}


void outputStudentList(Node<Student> *StudentHead)
{
	Node<Student> *cur = StudentHead;
	while (cur) {
		outputStudent(cur->data);
		cur = cur->next;
	}
}

void outputStudent(Student x)
{
	cout << x.StID << " " << x.Fullname << " " << x.Gender << " " << x.Class << " ";
	cout << x.DOB << " " << x.SocialID << " " << x.Password << " " << endl;
}

void deleteCourseList(Course *CourseList, int numOfCourses)
{
	for (int i = 0; i < numOfCourses; ++i) {
		deleteStudentList(CourseList[i].stHead);
	}
	delete[] CourseList;
}

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

//void addStudentToCourse(Course &co, Student st) {
//    // Input student ID
//    string studentID;
//    cout << "Enter student ID: ";
//    cin >> studentID;
//
//    // Input course ID
//    string courseID;
//    cout << "Enter course ID: ";
//    cin >> courseID;
//
//    // Find student with studentID : function 1
//    Student st;
//    cout << " currentSchoolYear.NumOfClasses: " << currentSchoolYear.NumOfClasses << "" << endl;
//
//    for (int i = 0; i < currentSchoolYear.NumOfClasses; i++) {
//        Node<Student>* current = currentSchoolYear.ClassesList[i].stHead;
//        while (current != nullptr) {
//            if (current->data.StID == studentID) {
//                st = current->data;
//                break;
//            }
//            current = current->next;
//        }
//    }
//    if (st.StID == "") {
//        cout << "Error: Student ID not found" << endl;
//        return;
//    }
//
//    // Find course with courseID : function 2
//    Course co;
//    for (int i = 0; i < 3; i++) {
//        for (int j = 0; j < currentSchoolYear.SemestersList[i].numOfCourses; j++) {
//            cout << "Check courseId = " << currentSchoolYear.SemestersList[i].CoursesList[j].ID << endl;
//            if (currentSchoolYear.SemestersList[i].CoursesList[j].ID == courseID) {
//                co = currentSchoolYear.SemestersList[i].CoursesList[j];
//                break;
//            }
//        }
//    }
//    if (co.ID == "") {
//        cout << "Error: Course ID not found" << endl;
//        return;
//    }
//
//    // Check if course is full
//    if (co.numOfStudent >= co.maxStudent) {
//        cout << "Error: Course is full" << endl;
//        return;
//    }
//
//    string fileName = "../data/ClassesStudents/" + st.Class + "/CourseAttending/" + st.StID + ".txt";
//    ifstream file(fileName);
//    if (!file.is_open()) {
//        ofstream fileOut(fileName);
//    }
//    else {
//        string currentCourseID = "";
//        while (getline(file, currentCourseID)) {
//            if (currentCourseID == "") {
//                break;
//            }
//            if (currentCourseID == courseID) {
//                cout << "Error: Student is already in course" << endl;
//                return;
//            }
//        }
//        file.close();
//    }
//
//    // Add student to course
//    for (int i = 0; i < 7; i++) {
//        if (st.courseID[i] == "") {
//            st.courseID[i] = courseID;
//            break;
//        }
//    }
//
//    // Add course to student
//    for (int i = 0; i < 7; i++) {
//        if (co.stHead == nullptr) {
//            co.stHead = new Node<Student>;
//            co.stHead->data = st;
//            co.stHead->next = nullptr;
//            co.numOfStudent++;
//            break;
//        }
//        else {
//            Node<Student>* current = co.stHead;
//            while (current->next != nullptr) {
//                current = current->next;
//            }
//            Node<Student>* newStudentNode = new Node<Student>;
//            newStudentNode->data = st;
//            newStudentNode->next = nullptr;
//            current->next = newStudentNode;
//            co.numOfStudent++;
//            break;
//        }
//    }
//
//    // Update student in class
//    for (int i = 0; i < currentSchoolYear.NumOfClasses; i++) {
//        Node<Student>* current = currentSchoolYear.ClassesList[i].stHead;
//        while (current != nullptr) {
//            if (current->data.StID == studentID) {
//                current->data = st;
//                break;
//            }
//            current = current->next;
//        }
//    }
//
//    // Update course in semester
//    for (int i = 0; i < 3; i++) {
//        for (int j = 0; j < currentSchoolYear.SemestersList[i].numOfCourses; j++) {
//            if (currentSchoolYear.SemestersList[i].CoursesList[j].ID == courseID) {
//                currentSchoolYear.SemestersList[i].CoursesList[j] = co;
//                break;
//            }
//        }
//    }
//
//    // Add courseId to file
//    ofstream fileOut(fileName, ios::app);
//    if (!fileOut.is_open()) {
//        cout << "Error: Cannot open file " << fileName << endl;
//        return;
//    }
//    fileOut << courseID << endl;
//    fileOut.close();
//
//    cout << "Add student to course successfully" << endl;
//}

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

void addNewClasses(Class *&NewClasses, int &numOfClass)
{
	cout << "Please input the file name: ";
	string filename;
	getline(cin, filename);
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

void displayClassesList(SchoolYear SyList, Class* CLassList){
    cout << "List of Class in School Year " << SyList.Name << ":" << endl;
    for (int i = 0; i < SyList.NumOfClasses; ++i) {
        cout << SyList.ClassesList[i].Name << endl;
    }
}

void viewStudentsInClass(SchoolYear Sy, Class* ClassList) {
    cout << "List of CLass In School Year " << Sy.Name << ":" << Sy.NumOfClasses << endl;
    for (int i = 0; i < Sy.NumOfClasses; ++i) {
        cout << i + 1 << ": " << ClassList[i].Name << endl;
    }
    cout << "Enter the number to view the students in the class:";
    int n; cin >> n;
    cout << "The Student in the class " << ClassList[n - 1].Name << ":" << endl;
    Node<Student>* current = ClassList[n - 1].stHead;
    while (current) {
        cout << current->data.Fullname << endl;
        current = current->next;
    }
}

void viewListOfCourse(int Option, SchoolYear* SyList,Semester* SemesterList,Course* CourseList, int numSY){
    if (Option == 1) { //View All of Courses
        cout << "List Of All Courses:" << endl;
        for (int i = 0; i < numSY; ++i) {
            for (int j = 0; j < 3; ++j) {
                for (int k = 0; k < SyList[i].SemestersList[j].numOfCourses; ++k) {
                    cout << SyList[i].SemestersList[j].CoursesList[k].ClassName << ": " << SyList[i].SemestersList[j].CoursesList[k].ID << endl;
                }
               }
        }
    }
    else // Option = 0
    {
        cout << "List Of All Courses in School Year " << SyList[0].Name << ":" << endl;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < SyList[0].SemestersList[i].numOfCourses; ++j) {
                cout << SyList[0].SemestersList[i].CoursesList[j].ClassName << ": " << SyList[0].SemestersList[i].CoursesList[j].ID << endl;
            }
        }
    }
} 

void viewStudentsInCourse(SchoolYear* SyList, Semester* SemesterList, Course* CourseList, int numSY) {
    viewListOfCourse(0, SyList, SemesterList, CourseList, numSY); // 0 - School year nearly
    cout << "Enter the course's ID to view list of students:";
    string tem; cin >> tem;
    bool find = false;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < SyList[0].SemestersList[i].numOfCourses;++j) {
            if (SyList[0].SemestersList[i].CoursesList[j].ID == tem) {
                find = true;
                cout << "List of Student:" << endl;
                Node <Student>* current = SyList[0].SemestersList[i].CoursesList[j].stHead;
                while (current) {
                    cout << current->data.Fullname << endl;
                }
                break;
               }
        }
    }
    if (!find) cout << "Course's ID doesn't exist" << endl;
}

void exportListOfStudentsInCourse(SchoolYear* SyList, Semester* SemesterList, Course* CourseList, int numSY) { // At the end of semester
    viewListOfCourse(0, SyList, SemesterList, CourseList, numSY); 
    cout << "Enter the course's ID to export list of students:";
    string tem; cin >> tem;
    ofstream fout;
    string filename = "../data/Export/" + SyList[0].Name + "/Semester2/" + tem + ".csv";
    fout.open(filename);
    bool find = false;
    if (!fout.is_open()) cout << "Can't export the list";
    else {
        for (int i = 0; i < SyList[0].SemestersList[1].numOfCourses; ++i) {
            if (tem == SyList[0].SemestersList[1].CoursesList[i].ID) {
                find = true;
                Node <Student>* current = SyList[0].SemestersList[1].CoursesList[i].stHead;
                fout << SyList[0].SemestersList[1].CoursesList[i].numOfStudent << endl;
                fout << "ID,Fullname,StudentID" << endl;
                int cnt = 1;
                while (current) {
                    fout << cnt++ << ",";
                    fout << current->data.Fullname << ",";
                    fout << current->data.StID;
                    fout << endl;
                }
                break;
            }
        }
        if (!find) cout << "Course's ID doesn't exist" << endl;
    }
}

bool isStaff(string username) {
	return (!isdigit(username[0]));
}

Node<Student>* findUserStudent(string username, string password, Class* classList, int numOfClasses) {
	Node<Student>* pCur = nullptr;
	for (int i = 0; i < numOfClasses; i++) {
		pCur = classList[i].stHead;
		while (pCur) {
			if (username == pCur->data.StID && password == pCur->data.Password) {
				return pCur;
			}
			pCur = pCur->next;
		}
	}
	return nullptr;
}
Node<User>* findUserStaff(string username, string password, Node<User>* pStaffList) {
	Node<User>* pCur = pStaffList;
	while (pCur) {
		if (username == pCur->data.Username && password == pCur->data.Password) {
			return pCur;
		}
		pCur = pCur->next;
	}
	return nullptr;
}

// return true if user is in data, return false otherwise
bool checkLogin(bool &role, Node<User> *&pUser, Node<Student> *&pStudent, string username, string password, SchoolYear *&currentSchoolYear, Node<User> *StaffHead) {
	if (isStaff(username)) {
		role = true;
		pUser = findUserStaff(username, password, StaffHead);
	}
	else {
		role = false;
		pStudent = findUserStudent(username, password, currentSchoolYear->ClassesList, currentSchoolYear->NumOfClasses);
	}
	return (pStudent != nullptr || pUser != nullptr);
}

