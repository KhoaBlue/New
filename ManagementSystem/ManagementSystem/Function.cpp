#include "Function.h"
#include <string>
#include <sstream>
void createNewClasses(Class *&NewClasses, int &numOfClass)
{
	cout << "Please input the number of new Classes";
	cin >> numOfClass;
	NewClasses = new Class[numOfClass];
	cout << "Please input the file name: ";
	string filename;
	getline(cin,filename);
	for (int i = 0; i < numOfClass; ++i) {
		cin >> NewClasses[i].Name;
		//readStudentsList(NewClasses[i].stHead, filename);
	}
}

void createSchoolYear(SchoolYear &sy)
{
	getline(cin, sy.Name);
	getline(cin, sy.start_date);
	getline(cin, sy.end_date);
	int numOfNewClasses;
	Class *NewClasses;
	createNewClasses(NewClasses, numOfNewClasses);
	Class *tmp = new Class[sy.NumOfClasses + numOfNewClasses];
	for (int i = 0; i < sy.NumOfClasses; ++i) {
		tmp[i] = sy.ClassesList[i];
	}
	for (int i = 0; i < numOfNewClasses; ++i) {
		tmp[i + sy.NumOfClasses] = NewClasses[i];
	}
	delete[] sy.ClassesList;
	sy.ClassesList = tmp;
	sy.NumOfClasses += numOfNewClasses;
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

