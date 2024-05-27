#include "Teacher.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <utility>
#include <conio.h>
using namespace std;

Teacher::Teacher(string name, string lastname, string login, string password)
    : name(name), lastname(lastname), login(login), password(password) {}

vector<string> Teacher::loginMethod(const vector<vector<string>>& teachersData) {
    string login, password;
    string teacherCLass = "";
    vector<string> teacherDetails;
    bool checkData = true;

    while (checkData) {
        if (checkData) {
            cout << "Login: "; cin >> login;
            cout << "Password: "; cin >> password;
            system("CLS");
        }
        for (const auto& teacher : teachersData) {
            if (login == teacher[1] && password == teacher[2]) {
                system("CLS");
                cout << "Hello " << teacher[0] << "!" << endl;
                checkData = false;
                teacherCLass = teacher[3];
                teacherDetails.push_back(teacher[3]);
                teacherDetails.push_back(teacher[4]);
            }
        }
    }
    return teacherDetails;
}



void showAllStudents(const vector<vector<string>>& studentsList) {
    system("CLS");

    cout << "Students: \n" << endl;
    for (const auto& student : studentsList) {
        cout << "[" << student[0] << "] ";
        cout << student[1] << " ";
        cout << student[2];
        cout << endl;
    }
}

string selectSpecyficStudent() {
    string selectedStudent;

    cout << endl;
    cout << "Select your student number ";
    cin >> selectedStudent;

    return selectedStudent;
}

vector<vector<string>> showSpecyficStudent(const vector<vector<string>>& studentsList, string selectedStudent) {
    system("CLS");
    vector<vector<string>> selectedStudentDetails;
    vector<string> studentDetails;
    for (const auto& student : studentsList) {
        if (selectedStudent == student[0]) {
            cout << "[" << student[0] << "] ";
            cout << student[1] << " ";
            cout << student[2];
            cout << endl;

            studentDetails.push_back(student[0]);
            studentDetails.push_back(student[1]);
            studentDetails.push_back(student[2]);
            selectedStudentDetails.push_back(studentDetails);

            return selectedStudentDetails;
        }
    }
}

int singleStudentOperations() {
    int singleStudentSelectedOperation;

    cout << endl;
    cout << "Select operation \n";
    cout << "[1] Insert Degree ";
    cout << "[2] Write Message ";
    cout << "[3] Back ";

    cin >> singleStudentSelectedOperation;
    return singleStudentSelectedOperation;
}

pair<vector<vector<string>>, int> Teacher::selectStudent(const vector<vector<string>>& studentsList) {
    string selectedStudent;
    int singleStudentSelectedOperation;

    showAllStudents(studentsList);

    selectedStudent = selectSpecyficStudent();
    vector<vector<string>> seletedStudentDetails = showSpecyficStudent(studentsList, selectedStudent);

    singleStudentSelectedOperation = singleStudentOperations();

    bool isWhileTrue = true;

    while (singleStudentSelectedOperation && isWhileTrue) {
        if (singleStudentSelectedOperation == 1) {
            isWhileTrue = false;

            return make_pair(seletedStudentDetails, singleStudentSelectedOperation);
        }
        if (singleStudentSelectedOperation == 2) {
            isWhileTrue = false;
            system("CLS");
            return make_pair(seletedStudentDetails, singleStudentSelectedOperation);
        }
        if (singleStudentSelectedOperation == 3) {
            showAllStudents(studentsList);
            selectedStudent = selectSpecyficStudent();
            showSpecyficStudent(studentsList, selectedStudent);
            singleStudentSelectedOperation = singleStudentOperations();
            isWhileTrue = true;
        }
    }
}

pair<vector<vector<string>>, bool> Teacher::insertDegree(vector<vector<string>> seletedStudentDetails) {
    system("CLS");
    vector<vector<string>> insertDataToDatabase;
    vector<string> data;

    cout << "Student: ";
    for (const auto& studentDetails : seletedStudentDetails) {
        cout << "[" << studentDetails[0] << "] " << studentDetails[1] << " " << studentDetails[2] << endl;
        data.push_back(studentDetails[0]);
    }


    //TUTAJ SPRAWDZIÆ CZY DANE S¥ POPRAWNE 
    string degree;
    cout << "Degree: "; cin >> degree;
    data.push_back(degree);


    insertDataToDatabase.push_back(data);

    bool finishInsertDegree = false;
    if (degree.size() > 0) {
        finishInsertDegree = true;
    }

    return make_pair(insertDataToDatabase, finishInsertDegree);
}

vector<vector<string>> Teacher::sendMessage(vector<vector<string>> seletedStudentDetails) {
    system("CLS");
    vector<vector<string>> sendMessageData;

    cout << "Send message to: ";
    for (const auto& studentDetails : seletedStudentDetails) {
        cout << studentDetails[1] << " ";
        cout << studentDetails[2] << endl << endl;
    }

    string message;
    char key;

    cout << "Press escape to send message." << endl;
    cout << "Message: " << endl;

    while (true) {
        key = _getch();

        if (key == 27) {
            break;
        }

        if (key == '\r') {
            message += "\n";
            cout << endl;
        }
        else if (key == '\b') {
            if (!message.empty()) {
                message.pop_back();
                cout << "\b \b";
            }
        }
        else {
            message += key;
            cout << key;
        }
    }

    vector<string> messageData;
    if (key == 27) {
        system("CLS");
        cout << "WIADOMOŒÆ WYS£ANA";
        messageData.push_back(message);
    }

    for (const auto& studentDetails : seletedStudentDetails) {
        messageData.push_back(studentDetails[0]);
    }
    sendMessageData.push_back(messageData);

    return sendMessageData;


    //cout << messageToStudent;

}