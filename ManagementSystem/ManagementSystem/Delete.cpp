#include "Function.h"

void deleteStaffList(Node<User>* StaffHead)
{
	Node<User>* cur = StaffHead;
	while (cur) {
		Node<User>* tmp = cur;
		cur = cur->next;
		delete tmp;
	}
}

void deleteStudentList(Node<Student>* pHead)
{
	Node<Student>* pCur = pHead;
	while (pCur) {
		Node<Student>* tmp = pCur;
		pCur = pCur->next;
		delete[] tmp->data.courseID;
		delete[] tmp->data.courseName;
		delete[] tmp->data.Result;
		delete tmp;
	}
}

void deleteClassList(Class* ClassList, int numOfClasses)
{
	for (int i = 0; i < numOfClasses; ++i) {
		deleteStudentList(ClassList[i].stHead);
	}
	delete[] ClassList;
}

void deleteSemesterList(Semester* SemesterList, int numOfSemester)
{
	for (int i = 0; i < numOfSemester; ++i) {
		deleteCourseList(SemesterList[i].CoursesList, SemesterList[i].numOfCourses);
	}
	delete[] SemesterList;
}

void deleteSchoolYearList(SchoolYear* SyList, int numOfSchoolYears) {
	for (int i = 0; i < numOfSchoolYears; ++i) {
		//deleteStudentList(SyList[i].ClassesList->stHead);
		deleteClassList(SyList[i].ClassesList, SyList[i].NumOfClasses);
		deleteSemesterList(SyList[i].SemestersList, SyList[i].numOfSemesters);
	}
	delete[] SyList;
}

void deleteCourseList(Course* CourseList, int numOfCourses)
{
	for (int i = 0; i < numOfCourses; ++i) {
		deleteStudentList(CourseList[i].stHead);
	}
	delete[] CourseList;
}

void removeStudentFromCourse(SchoolYear* SyList, Semester* SemestersList, Course* CourseList, int numSY) {
	cout << "Remove a student from a Course" << endl;
	viewListOfCourse(0, SyList, SemestersList, CourseList, numSY);
	cout << "Enter the course's ID:";
	bool find = false;
	string id; cin >> id;
	int i = 0;
	int j = 0;
	while (i < 3) {
		while (j < SyList[0].SemestersList[i].numOfCourses) {
			if (SyList[0].SemestersList[i].CoursesList[j].ID == id) {
				find = true;
				cout << "List of Student:" << endl;
				Node <Student>* pCur = SyList[0].SemestersList[i].CoursesList[j].stHead;
				while (pCur) {
					cout << pCur->data.Fullname << " " << pCur->data.StID << endl;
					pCur = pCur->next;
				}
				break;
			}
			j++;
		}
		if (find) break;
		i++;
	}
	if (!find) cout << "Course's ID doesn't exist";
	else {
		bool search = false;
		cout << "Enter the student's ID to remove:";
		string Id; cin >> Id;
		Node<Student>* current = SyList[0].SemestersList[i].CoursesList[j].stHead;
		if (current->data.StID == Id) {
			search = true;
			Node <Student>* del = current;
			current = current->next;
			delete del;
		}
		while (current->next) {
			if (current->next->data.StID == Id) {
				search = true;
				Node<Student>* del = current->next;
				current->next = current->next->next;
				delete del;
				break;
			}
			current = current->next;
		}
		if (!search) cout << "Student's ID doesn't exist in this course";
		else cout << "Remove successfully";
	}
}

void deleteCourse(SchoolYear* SyList, Semester* SemestersList, Course* CourseList, int numSY) {
	cout << "Delete a course";
	viewListOfCourse(0, SyList, SemestersList, CourseList, numSY);
	cout << "Enter the course's ID to delete:";
	string tem; cin >> tem;
	bool find = false;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < SyList[0].SemestersList[i].numOfCourses; ++j) {
			if (SyList[0].SemestersList[i].CoursesList[j].ID == tem) {
				find = true;
				for (int k = j; k < SyList[0].SemestersList[i].numOfCourses - 1; k++)
					SyList[0].SemestersList[i].CoursesList[k] = SyList[0].SemestersList[i].CoursesList[k + 1];
				SyList[0].SemestersList[i].numOfCourses--;
			}
		}
	}
	if (!find) cout << "The course's ID doesn't exist";
}