#include "Function.h"

void updateSchoolYearList(SchoolYear* SyList, int numSY)
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

void updateCourseList(Course* CourseList, int numOfCourse, string filename)
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

void updateClassList(Class* ClassList, int numClass, string filename)
{
	ofstream fout(filename);
	fout << numClass << endl;
	for (int i = 0; i < numClass; ++i) {
		fout << ClassList[i].Name << endl;
		//updateStudentsInClass("../ClassesStudents/" + ClassList[i].Name + "/" + ClassList[i].Name + ".csv");
	}
	fout.close();
}

void updateStudentToFile(Node<Student>* pHead, string filename) {
	ofstream fout(filename);
	fout << "No,Student ID,First name,Last name,Gender,Date of Birth,Social ID,Password\n";
	Node<Student>* pCur = pHead;
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

void updateStaffToFile(Node<User>* pHead, string filename) {
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

void updateCourseID(Course& course, string newID) {
    if (!newID.empty())
        course.ID = newID;
}

void updateCourseName(Course& course, string newName) {
    if (!newName.empty())
        course.Name = newName;
}

void updateCourseLecturer(Course& course, string lecturer) {
    if (!lecturer.empty())
        course.Lecturer = lecturer;
}

void updateCourseDayOfWeek(Course& course, string newDay) {
    if (!newDay.empty())
        course.DayOfWeek = newDay;
}

bool updateCourseMaxStudents(Course &course, int newMax) {
    if (newMax < 0) return false;
    course.maxStudent = newMax;
    return true;
}


bool updateCourseNumOfCredits(Course &course, int newNumOfCredits) {
    if (newNumOfCredits < 0) return false;
    course.NumOfCredits = newNumOfCredits;
    return true;
}


bool updateCourseSession(Course& course, int newSession) {
    if (newSession < 1 || newSession > 4) return false;
    course.session = newSession;
    return true;
}

/*
Switch case options:
1. Change ID
2. Change name;
3. Change lecturer
4. Change maxStudents
5. Change numOfCredits
6. Change session dayOfWeek
7. Change session time
*/

void updateCourseInfo(Course& course, int option) {
    switch (option) {
        case 1: {
            string newID;
            cout << "Enter new course ID: ";
            getline(cin, newID);
            updateCourseID(course, newID);
            break;
        }
        case 2: {
            string newName;
            cout << "Enter new course name: ";
            getline(cin, newName);
            updateCourseName(course, newName);
            break;
        }
        case 3: {
            string newLecturer;
            cout << "Enter new course lecturer's name: ";
            getline(cin, newLecturer);
            updateCourseLecturer(course, newLecturer);
            break;
        }
        case 4: {
            int newMaxOfStudents;
            cout << "Enter new max number of students: ";
            cin >> newMaxOfStudents;
            if (!updateCourseMaxStudents(course, newMaxOfStudents)) {
                cout << "Invalid number of max students!";
            }
            break;
        }
        case 5: {
            int newNumOfCredits;
            cout << "Enter new number of credits: ";
            cin >> newNumOfCredits;
            if (!updateCourseNumOfCredits(course, newNumOfCredits)) {
                cout << "Invalid number of credits!";
            }
            break;
        }
        case 6: {
            string newDayOfWeek;
            cout << "Enter new course day of the week: ";
            getline(cin, newDayOfWeek);
            updateCourseDayOfWeek(course, newDayOfWeek);
            break;
        }
        case 7: {
            int newSession;
            cout << "Enter new course session hour: ";
            cin >> newSession;
            if (updateCourseSession(course, newSession)) {
                cout << "Invalid session hour!";
            }
            break;
        }
    }
}
