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