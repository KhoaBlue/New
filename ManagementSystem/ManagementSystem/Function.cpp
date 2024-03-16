#include "Function.h"


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
