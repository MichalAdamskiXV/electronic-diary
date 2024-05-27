#include <cppconn/driver.h> 
#include <cppconn/exception.h> 
#include <cppconn/statement.h> 
#include <iostream> 
#include <mysql_connection.h> 
#include <mysql_driver.h> 

#include <iomanip> 
#include <utility>
#include <vector>
#include <string>
#include "Teacher.h"
#include "Student.h"
#include "Database.h"

using namespace std;


int loginAs() {
	int loginAs;
	cout << "Login as: [1] Teacher [2] Student ";
	cin >> loginAs;

	return loginAs;
}

void showTeacherOptions() {
	cout << endl;
	cout << "Write number of operation" << endl;
	cout << "[1] Select student "; //DZIAŁA
	cout << "[2] Enter Test ";
	cout << "[3] Frequency";
	cout << "[4] Enter Ratings ";
	cout << "[5] Exit ";
}

void showStudentOptions() {
	cout << endl;
	cout << "[1] Lesson Plan "; //DZIAŁA
	cout << "[2] Grades "; //DZIAŁA
	cout << "[3] Messages ";
	cout << "[4] Frequency ";
	cout << "[5] Tests ";
	cout << "[6] Exit";
}

int main()
{
	//Fetching teachers data
	Database database;
	vector<vector<string>> teachersData = database.fetchTeachers();

	//Teacher class
	Teacher teacher("John", "Doe", "jdoe", "password123");

	//Student class;
	Student student;

	vector<string> teacherStudentsClassId;

	int loginAsOperation = loginAs();

	if (loginAsOperation == 1) { //OBS£UGA NAUCZYCIELA
		system("CLS");
		teacherStudentsClassId = teacher.loginMethod(teachersData);

		database.fetchStudentsClass(teacherStudentsClassId[0]);

		//Fetch list of students
		vector<vector<string>> studentsList = database.fetchStudentsList(teacherStudentsClassId[0]);

		int selectedOperationMain;
		pair<vector<vector<string>>, int> seletedStudentDetails;

		showTeacherOptions();
		cin >> selectedOperationMain;
		bool isWhileTrue = true;

		while (selectedOperationMain && isWhileTrue) {
			if (selectedOperationMain == 1) {
				seletedStudentDetails = teacher.selectStudent(studentsList);

				isWhileTrue = true;

				if (seletedStudentDetails.second == 1) {
					cout << "INSERT: ";
					pair<vector<vector<string>>, bool> insertDataToDatabase = teacher.insertDegree(seletedStudentDetails.first);

					for (const auto& data : insertDataToDatabase.first) {
						database.insertDegreeForSpecyficStudent(data[0], data[1], teacherStudentsClassId[0]);
					}

					if (insertDataToDatabase.second == true) {
						isWhileTrue = true;
						system("CLS");
						studentsList = database.fetchStudentsList(teacherStudentsClassId[0]);

						showTeacherOptions();

						cin >> selectedOperationMain;
					}
				}

				if (seletedStudentDetails.second == 2) {
					isWhileTrue = false;
					vector<vector<string>> messageData = teacher.sendMessage(seletedStudentDetails.first);
					database.sendMessage(messageData);
				}

			}
			else if (selectedOperationMain == 2) {
				isWhileTrue = false;
				cout << "JSADHSAJGDSADJASJGDSA";
			}
		}
	}
	if (loginAsOperation == 2) { //OBS£UGA STUDENTA
		system("CLS");

		vector<vector<string>> allStudents = database.fetchAllStudents();
		vector<vector<string>> studentDetails = student.studentLogin(allStudents);

		int back = 0;

		showStudentOptions();
		int selectOperation;

		cout << endl;
		cout << "Number: "; cin >> selectOperation;

		while (back == 0) {
			//Plan lekcji
			if (selectOperation == 1) {
				vector<vector<string>> lessonPlan;

				for (const auto& student : studentDetails) {
					lessonPlan = database.fetchLessonPlan(student[3]);
				}

				back = student.showLessonPlan(lessonPlan);
			} //OCENY
			if (selectOperation == 2) {

				vector<string> gradesData;
				for (const auto& student : studentDetails) {
					gradesData = database.fetchStudentGrades(student[0]);
				}

				back = student.showGrades(gradesData);
			} //WIADOMOŚCI
			if (selectOperation == 3) {
				vector<string> messageDetails;
				for (const auto& student : studentDetails) {
					messageDetails = database.fetchMessages(student[3]);
				}

				int selectedOption = student.showMessages(messageDetails);

				if (selectedOption == 1) {
					vector<vector<string>> returnedMessageDetails = student.replyToMessage(messageDetails);
					back = 1;
				}
				else if (selectedOption == 2) {

					vector<vector<string>> allTeachers = database.fetchTeachers();
					int selectedOperation = student.messageToTeacher(allTeachers);

					if (selectedOperation == 1) {
						vector<vector<string>> messageToTeacherDetails = student.writeMessageToTeacher(allTeachers);
						vector<vector<string>> allMessages;

						for (const auto& student : studentDetails) {
							allMessages = database.fetchMessageToTeacher(student[0], messageToTeacherDetails[0][0]);
						}

						for (int i = 0; i < allMessages.size(); i++) {
							cout << allMessages[0][i];
						}

							for (const auto& student : studentDetails) {
								database.insertMessageToTeacher(messageToTeacherDetails, student[0]);
							}
						

						//back = 1;
						break;
					}
					else if (selectedOperation == 2) {
						back = 1;
					}
				}
				else if (selectedOption == 3) {
					back = 1;
				}

			}

			//-----------------------------

			while (back) {
				system("CLS");

				for (const auto& student : studentDetails) {
					cout << "Hello " << student[1] << "!" << endl;
				}

				showStudentOptions();

				cout << endl;
				cout << "Number: "; cin >> selectOperation;
				back = 0;
			}
		}
	}

	return 0;
}