#include "Function.h"


void addNewClasses(Class *&NewClasses, int &numOfClass)
{
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
	cout << "Please input the file name: ";
	addNewClasses(sy.ClassesList, NumNewClasses);
	for (int i = 0; i < NumOldClasses; ++i) {
		sy.ClassesList[i + NumNewClasses] = OldClasses[i];
	}
}

void createSchoolYear(SchoolYear &sy, Class *OldClasses, int NumOldClasses)
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

void deleteSchoolYear(SchoolYear &sy)
{
	for (int i = 0; i < 3; ++i) {
		delete[] sy.SemestersList[i].CoursesList;
	}
	delete[] sy.SemestersList;
	delete[] sy.ClassesList;
}
