#pragma once
#include <vector>
#include <string>

using namespace std;

class Database {
public:
    vector<vector<string>> fetchTeachers();
    vector<vector<string>> fetchAllStudents();
    void fetchStudentsClass(string studentsClass);
    vector<vector<string>> fetchStudentsList(string studentsClass);
    void insertDegreeForSpecyficStudent(string degree, string studentId, string id_subject);
    void sendMessage(vector<vector<string>> messageData);


    vector<vector<string>> fetchLessonPlan(string studentsClass);
    vector<string> fetchStudentGrades(string studentId);
    vector<string> fetchMessages(string studentsClass);
    void insertMessageToTeacher(vector<vector<string>> messageToTeacherDetails, string studentId);

    vector<vector<string>> fetchMessageToTeacher(string studentId, string teacherId);
};