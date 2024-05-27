#pragma once
#include <string>
#include <vector>
#include <utility>

using namespace std;

class Teacher {
protected:
	string name;
	string lastname;
	string login;
	string password;

public:
	Teacher(string name, string lastname, string login, string password);
	vector<string> loginMethod(const vector<vector<string>>& teachersData);
	pair<vector<vector<string>>, int> selectStudent(const vector<vector<string>>& studentsList);
	pair<vector<vector<string>>, bool> insertDegree(vector<vector<string>> seletedStudentDetails);
	vector<vector<string>> sendMessage(vector<vector<string>> seletedStudentDetails);
};