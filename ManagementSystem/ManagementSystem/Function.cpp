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


