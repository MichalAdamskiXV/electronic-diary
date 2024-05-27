#pragma once
#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Student {
public:
	vector<vector<string>> studentLogin(vector<vector<string>> allStudents);
	int showLessonPlan(vector<vector<string>> lessonPlan);

	int showGrades(vector<string> gradesData);
	int showMessages(vector<string> message);
	vector<vector<string>> replyToMessage(vector<string> message);
	int messageToTeacher(vector<vector<string>> allTeachers);
	vector<vector<string>> writeMessageToTeacher(vector<vector<string>> allTeachers);
};