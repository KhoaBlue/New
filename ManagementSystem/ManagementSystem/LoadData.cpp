#include "Function.h"


SchoolYear* loadSchoolYearList(SchoolYear*& SyList, int& numSY)
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
		fin >> SyList[i].numOfSemesters;
		loadClassList(SyList[i].ClassesList, SyList[i].NumOfClasses, "../data/SchoolYears/" + SyList[i].Name + "/ClassesList.txt");
		SyList[i].SemestersList = new Semester[3];
		for (int j = 0; j < SyList[i].numOfSemesters; ++j) {
			if (!loadSemesterFromFile(SyList[i].SemestersList[j], "../data/SchoolYears/" + SyList[i].Name + "/Semester " + to_string(j + 1) + "/")) {
				cout << "Cannot load Semesters of " << SyList[i].Name << endl;
			}
		}
	}
	fin.close();
	return SyList;
}

bool loadSemesterFromFile(Semester& se, string filename) {
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
	if (!loadCourseList(se.CoursesList, se.numOfCourses, filename)) {
		cout << "Cannot load CoursesList: " << filename << endl;
		return false;
	}
	return true;
}

bool loadCourseList(Course*& CourseList, int& numOfCourse, string filename)
{
	ifstream fin(filename + "CoursesList.txt");
	if (!fin) {
		cout << "Cannot loadCourseList!" << endl;
		return false;
	}
	fin >> numOfCourse;
	CourseList = new Course[numOfCourse];
	for (int i = 0; i < numOfCourse; ++i) {
		fin >> CourseList[i].ID;
		fin >> CourseList[i].ClassName;
		if (!loadCourseInfoFromFile(CourseList[i], filename + "CoursesInfo/" + CourseList[i].ID + "_" + CourseList[i].ClassName + ".txt")) {
			return false;
		}
		if (!loadCourseStudents(CourseList[i], filename + "CoursesStudents/" + CourseList[i].ID + "_" + CourseList[i].ClassName + ".csv")) {
			return false;
		}
	}
	fin.close();
	return true;
}

bool loadCourseInfoFromFile(Course& co, string filename)
{
	ifstream fin(filename);
	if (!fin) {
		cout << filename << endl;
		cout << "Cannot loadCourseInfoFromFile" << endl;
		return false;
	}

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
	return true;
}

bool loadCourseStudents(Course& co, string filename)
{
	ifstream fin(filename);
	if (!fin) {
		cout << "Cannot loadCourseStudents" << endl;
		return false;
	}
	string line;
	Node<Student>* cur = nullptr;
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
	return true;
}

bool loadClassList(Class*& ClassList, int& numClass, string filename)
{
	ifstream fin(filename);
	if (!fin) {
		cout << "Cannot loadClassList!";
		return false;
	}
	fin >> numClass;
	ClassList = new Class[numClass];
	for (int i = 0; i < numClass; ++i) {
		fin >> ClassList[i].Name;
		if (!loadStudentFromFile(ClassList[i].stHead, "../data/ClassesStudents/" + ClassList[i].Name + "/" + ClassList[i].Name + ".csv")) {
			return false;
		}
		Node<Student> *pCur = ClassList[i].stHead;
		while (pCur) {
			pCur->data.Class = ClassList[i].Name;
			pCur = pCur->next;
		}
		if (!loadStudentsCoursesAttending(ClassList[i].stHead,"../data/ClassesStudents/" + ClassList[i].Name + "/CourseAttending/")) {
			return false;
		}
	}
	fin.close();
	return true;
}

bool loadStudentFromFile(Node<Student>*& pHead,  string filename) {
	ifstream fin;
	fin.open(filename);
	if (!fin) {
		cout << "Cannot open file " << filename << endl;
		return false;
	}
	Node<Student>* pCur = nullptr;
	string line;
	if (!fin) return false;
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
	fin.close();
	return true;
}

bool loadStudentsCoursesAttending(Node<Student> *stHead, string filename)
{
	Node<Student> *pCur = stHead;
	while (pCur) {
		if (!loadStudentCourses(pCur, filename + pCur->data.StID + ".txt")) {
			return false;
		}
		pCur = pCur->next;
	}
	return true;
}

bool loadStudentCourses(Node<Student> *student, string filename)
{
	ifstream fin(filename);
	if (!fin) {
		cout << "Cannot load " << filename << endl;
		return false;
	}
	fin >> student->data.numOfCoursesAttending;
	fin.ignore();
	for (int i = 0; i < student->data.numOfCoursesAttending; ++i) {
		getline(fin, student->data.courseID[i]);
		getline(fin, student->data.courseName[i]);
	}
	fin.close();
	return true;
}

bool loadStaffFromFile(Node<User>*& pHead) {
	ifstream fin;
	fin.open("../data/StaffList.csv");
	if (!fin) {
		return false;
	}
	Node<User>* pCur = nullptr;
	string line;
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
	fin.close();
	return true;
}