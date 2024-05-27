#include "Student.h"
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <utility>
#include <conio.h>
#include <iomanip> 
using namespace std;

vector<vector<string>> Student::studentLogin(vector<vector<string>> allStudents) {
    vector<vector<string>> singleStudent;
    vector<string> stDetails;
    string login, password;

    bool checkData = true;

    while (checkData) {
        if (checkData) {
            cout << "Login: "; cin >> login;
            cout << "Password: "; cin >> password;
            system("CLS");
        }
        for (const auto& student : allStudents) {
            if (login == student[4] && password == student[5]) {
                system("CLS");
                cout << "Hello " << student[1] << "!" << endl;
                checkData = false;

                stDetails.push_back(student[0]);
                stDetails.push_back(student[1]);
                stDetails.push_back(student[2]);
                stDetails.push_back(student[3]);
                stDetails.push_back(student[4]);
                stDetails.push_back(student[5]);

                singleStudent.push_back(stDetails);

                return singleStudent;
            }
        }
    }
    //return teacherCLass;
}

int Student::showLessonPlan(vector<vector<string>> lessonPlan) {
    system("CLS");
    cout << "Lesson Plan \n" << endl;

    int maxLength = 0;
    for (const auto& plan : lessonPlan) {
        for (const auto& subject : plan) {
            if (subject.length() > maxLength) {
                maxLength = subject.length();
            }
        }
    }
    maxLength += 2;

    for (const auto& plan : lessonPlan) {
        for (int i = 0; i < plan.size(); i++) {
            if (i % 5 == 0 && i != 0) {
                cout << endl;
            }
            cout << left << setw(maxLength) << plan[i];
        }
        cout << endl;
    }

    int back;
    cout << endl;
    cout << "[1] Back "; cin >> back;

    return back;
}

//OCENY
int Student::showGrades(vector<string> gradesData) {
    system("CLS");
    cout << "Your grades \n" << endl;

    const int subjectWidth = 20;
    const int gradesWidth = 50;

    cout << left << setw(subjectWidth) << "Subject" << setw(gradesWidth) << "Grades" << endl;

    for (int i = 0; i < gradesData.size(); i += 2) {
        if (i + 1 < gradesData.size()) {
            cout << left << setw(subjectWidth) << gradesData[i] << setw(gradesWidth) << gradesData[i + 1] << endl;
        }
    }

    int back;
    cout << endl;
    cout << "[1] Back "; cin >> back;

    return back;
}


void showAllMessages(vector<string> message) {
    for (int i = 0; i < message.size(); i++) {
        if (i % 4 == 0) {
            cout << endl;
        }
        cout << message[i] << " ";
    }
    cout << endl;
}

int Student::showMessages(vector<string> message) {
    system("CLS");
    cout << "Messages: " << endl;

    showAllMessages(message);

    int selectedOption;

    cout << endl;
    cout << "[1] Reply to message ";
    cout << "[2] Write message to teacher ";
    cout << "[3] Back "; 
    cin >> selectedOption;

    return selectedOption;
}

vector<vector<string>> Student::replyToMessage(vector<string> message) {
    system("CLS");

    vector<vector<string>> returnedMessageDetails;
    vector<string> messageDetail;

    cout << "Messages: " << endl;
    showAllMessages(message);
    cout << endl;

    string numberOfMessage;
    cout << "Number of message: "; cin >> numberOfMessage;
    messageDetail.push_back(numberOfMessage);

    system("CLS");

    string yourMessage;
    char key;

    cout << "Press escape to send message." << endl;
    cout << "Message: " << endl;

    while (true) {
        key = _getch();

        if (key == 27) {
            break;
        }

        if (key == '\r') {
            yourMessage += "\n";
            cout << endl;
        }
        else if (key == '\b') {
            if (!yourMessage.empty()) {
                yourMessage.pop_back();
                cout << "\b \b";
            }
        }
        else {
            yourMessage += key;
            cout << key;
        }
    }

    messageDetail.push_back(yourMessage);
    returnedMessageDetails.push_back(messageDetail);

    return returnedMessageDetails;
}

int Student::messageToTeacher(vector<vector<string>> allTeachers) {
    system("CLS");

    cout << "Teachers: " << endl;

    for (const auto& teacher : allTeachers) {
        cout << teacher[5] << " ";
        cout << teacher[0] << " ";
        cout << teacher[6] << " ";
        cout << endl;
    }
    cout << endl;

    int selectedOperation;
    cout << "[1] Write message ";
    cout << "[2] Back ";
    cin >> selectedOperation;

    return selectedOperation;
}

vector<vector<string>> Student::writeMessageToTeacher(vector<vector<string>> allTeachers) {
    system("CLS");

    cout << "Teachers: " << endl;

    for (const auto& teacher : allTeachers) {
        cout << teacher[5] << " ";
        cout << teacher[0] << " ";
        cout << teacher[6] << " ";
        cout << endl;
    }
    cout << endl;


    vector<vector<string>> messageToTeacherDetails;
    vector<string> details;

    string teacherNumber;
    cout << "Teacher number: ";
    cin >> teacherNumber;

    details.push_back(teacherNumber);

    system("CLS");

    string yourMessage;
    char key;

    cout << "Press escape to send message." << endl;
    cout << "Message: " << endl;

    while (true) {
        key = _getch();

        if (key == 27) {
            break;
        }

        if (key == '\r') {
            yourMessage += "\n";
            cout << endl;
        }
        else if (key == '\b') {
            if (!yourMessage.empty()) {
                yourMessage.pop_back();
                cout << "\b \b";
            }
        }
        else {
            yourMessage += key;
            cout << key;
        }
    }

    details.push_back(yourMessage);
    messageToTeacherDetails.push_back(details);

    return messageToTeacherDetails;
}