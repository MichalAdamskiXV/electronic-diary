#include "Database.h"

#include <cppconn/connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

//Reusable connection with database
sql::Connection* getConnection() {
	sql::mysql::MySQL_Driver* driver;
	sql::Connection* con;

	driver = sql::mysql::get_mysql_driver_instance();
	con = driver->connect("tcp://localhost:3306", "root", "");
	con->setSchema("electronic_diary"); // your database name

	return con;
}

vector<vector<string>> Database::fetchTeachers() {
	vector<vector<string>> teachersData;
	try {
		sql::Connection* con = getConnection();

		sql::Statement* stmt;
		stmt = con->createStatement();

		string selectDataSQL = "SELECT * FROM teachers"; //SELECT DATA

		sql::ResultSet* res
			= stmt->executeQuery(selectDataSQL);

		// Loop through the result set and display data 
		int count = 0;
		while (res->next()) {
			vector<string> teacher;
			teacher.push_back(res->getString("name_t"));
			teacher.push_back(res->getString("login_t"));
			teacher.push_back(res->getString("password_t"));
			teacher.push_back(res->getString("id_class"));
			teacher.push_back(res->getString("id_subject"));
			teacher.push_back(res->getString("id_teacher"));
			teacher.push_back(res->getString("lastname_t"));
			teachersData.push_back(teacher);
		}

		delete res;
		delete stmt;
		delete con;

		return teachersData;
	}
	catch (sql::SQLException& e) {
		std::cerr << "SQL Error: " << e.what() << std::endl;
	}
}

vector<vector<string>> Database::fetchAllStudents() {
	vector<vector<string>> allStudentsData;
	try {
		sql::Connection* con = getConnection();

		sql::Statement* stmt;
		stmt = con->createStatement();

		string selectDataSQL = "SELECT * FROM students_list"; //SELECT DATA

		sql::ResultSet* res = stmt->executeQuery(selectDataSQL);

		// Loop through the result set and display data 
		int count = 0;
		while (res->next()) {
			vector<string> student;
			student.push_back(res->getString("id_student"));
			student.push_back(res->getString("name_s"));
			student.push_back(res->getString("lastname_s"));
			student.push_back(res->getString("id_class"));
			student.push_back(res->getString("login_s"));
			student.push_back(res->getString("password_s"));
			allStudentsData.push_back(student);
		}

		delete res;
		delete stmt;
		delete con;

		return allStudentsData;
	}
	catch (sql::SQLException& e) {
		std::cerr << "SQL Error: " << e.what() << std::endl;
	}
}

void Database::fetchStudentsClass(string studentsClass) {
	try {
		sql::Connection* con = getConnection();

		sql::Statement* stmt;
		stmt = con->createStatement();

		stringstream selectDataSQL;
		selectDataSQL << "SELECT * FROM students_class WHERE id_class = '" << studentsClass << "'";

		sql::ResultSet* res = stmt->executeQuery(selectDataSQL.str());

		while (res->next()) {
			cout << endl;
			cout << "Class: " << res->getString("class_number") << endl;
		}

		delete res;
		delete stmt;
		delete con;
	}
	catch (sql::SQLException& e) {
		std::cerr << "SQL Error: " << e.what() << std::endl;
	}
}

vector<vector<string>> Database::fetchStudentsList(string studentsClass) {

	vector<vector<string>> studentsList;

	try {
		sql::Connection* con = getConnection();
		sql::Statement* stmt;
		stmt = con->createStatement();


		stringstream selectDataSQL;
		selectDataSQL << "SELECT * FROM students_list WHERE id_class = '" << studentsClass << "'";

		sql::ResultSet* res = stmt->executeQuery(selectDataSQL.str());

		//int count = 0;
		while (res->next()) {
			vector<string> student;
			//count++;
			//cout << "["<<count<<"] " << res->getString("name_s") << " " << res->getString("lastname_s") << endl;
			student.push_back(res->getString("id_student"));
			student.push_back(res->getString("name_s"));
			student.push_back(res->getString("lastname_s"));
			studentsList.push_back(student);
		}

		for (const auto& student : studentsList) {
			cout << student[0] << " ";
			cout << student[1] << " ";
			cout << student[2] << " ";
			cout << endl;
		}

		delete res;
		delete stmt;
		delete con;

		return studentsList;
	}
	catch (sql::SQLException& e) {
		std::cerr << "SQL Error: " << e.what() << std::endl;
	}
}

void Database::insertDegreeForSpecyficStudent(string degree, string studentId, string id_subject) {
	try {
		sql::Connection* con = getConnection();
		sql::Statement* stmt;
		stmt = con->createStatement();

		stringstream insertDegree;
		insertDegree << "INSERT INTO degrees VALUES (NULL, " << degree << ", " << studentId << ", " << id_subject << ")";
			
		stmt->executeUpdate(insertDegree.str());;

		delete stmt;
		delete con;
	}
	catch (sql::SQLException& e) {
		std::cerr << "SQL Error: " << e.what() << std::endl;
	}
}

void Database::sendMessage(vector<vector<string>> messageData) {
	for (const auto& data : messageData) {
		cout << "HERE" << endl;
		cout << data[0];
		cout << data[1];
	}
}

vector<vector<string>> Database::fetchLessonPlan(string studentsClass) {
	try {
		sql::Connection* con = getConnection();
		sql::Statement* stmt;
		stmt = con->createStatement();


		stringstream selectDataSQL;
		selectDataSQL << "SELECT * FROM lesson_plan WHERE id_class = '" << studentsClass << "'";

		sql::ResultSet* res = stmt->executeQuery(selectDataSQL.str());
		

		vector<vector<string>> lessonPlan;

		vector<string> days;

		days.push_back("Monday");
		days.push_back("Tuesday");
		days.push_back("Wednesday");
		days.push_back("Thursday");
		days.push_back("Friday");

		while (res->next()) {
			days.push_back(res->getString("monday"));
			days.push_back(res->getString("tuesday"));
			days.push_back(res->getString("wednesday"));
			days.push_back(res->getString("thursday"));
			days.push_back(res->getString("friday"));
		}

		lessonPlan.push_back(days);
		delete res;
		delete stmt;
		delete con;

		return lessonPlan;
	}
	catch (sql::SQLException& e) {
		std::cerr << "SQL Error: " << e.what() << std::endl;
	}
}

vector<string> Database::fetchStudentGrades(string studentId) {
	try {
		sql::Connection* con = getConnection();
		sql::Statement* stmt = con->createStatement();

		stringstream selectDataSQL;

		selectDataSQL << "SELECT subjects.subject, GROUP_CONCAT(degrees.degree SEPARATOR ', ') AS degrees "
			<< "FROM degrees "
			<< "INNER JOIN subjects ON degrees.id_subject = subjects.id_subject "
			<< "WHERE degrees.id_student = '" << studentId << "' "
			<< "GROUP BY subjects.subject;";

		sql::ResultSet* res = stmt->executeQuery(selectDataSQL.str());

		vector<string> gradesData;

		while (res->next()) {
			gradesData.push_back(res->getString("subject"));
			gradesData.push_back(res->getString("degrees"));
		}

		return gradesData;

		delete res;
		delete stmt;
		delete con;
	}
	catch (sql::SQLException& e) {
		cerr << "SQL Error: " << e.what() << endl;
	}
}

vector<string> Database::fetchMessages(string studentsClass) {
	try {
		sql::Connection* con = getConnection();
		sql::Statement* stmt = con->createStatement();

		stringstream selectDataSQL;

		selectDataSQL << "SELECT messages.id_message, messages.message, messages.id_class, messages.id_teacher, teachers.name_t, teachers.lastname_t FROM messages INNER JOIN teachers ON teachers.id_teacher = messages.id_teacher WHERE messages.id_class = '" << studentsClass << "'";

		sql::ResultSet* res = stmt->executeQuery(selectDataSQL.str());

		vector<string> message;

		while (res->next()) {
			message.push_back(res->getString("id_message"));
			message.push_back(res->getString("message"));
			//cout << res->getString("id_class");
			//message.push_back(res->getString("id_teacher"));
			message.push_back(res->getString("name_t"));
			message.push_back(res->getString("lastname_t"));
		}

		return message;

		delete res;
		delete stmt;
		delete con;
	}
	catch (sql::SQLException& e) {
		cerr << "SQL Error: " << e.what() << endl;
	}
}

void Database::insertMessageToTeacher(vector<vector<string>> messageToTeacherDetails, string studentId) {
	try {
		sql::Connection* con = getConnection();
		sql::Statement* stmt = con->createStatement();

		std::string studentOrTeacher = "STUDENT";

		for (const auto& messageToTeacher : messageToTeacherDetails) {
			if (messageToTeacher.size() < 2) {
				std::cerr << "Invalid messageToTeacherDetails format" << std::endl;
				continue;
			}

			std::stringstream insertMessage;
			insertMessage << "INSERT INTO message_to_teacher VALUES(NULL, '"
				<< messageToTeacher[1] << "', '"
				<< studentId << "', '"
				<< messageToTeacher[0] << "', '"
				<< studentOrTeacher << "');";

			std::string query = insertMessage.str();
			if (!query.empty()) {
				stmt->executeUpdate(query);
			}
			else {
				std::cerr << "Generated query was empty" << std::endl;
			}
		}

		delete stmt;
		delete con;
	}
	catch (sql::SQLException& e) {
		std::cerr << "SQL Error: " << e.what() << std::endl;
	}
}

vector<vector<string>> Database::fetchMessageToTeacher(string studentId, string teacherId) {
	try {
		vector<vector<string>> messageToTeacher;
		vector<string> details;
		sql::Connection* con = getConnection();
		sql::Statement* stmt = con->createStatement();

		std::stringstream selectDataSQL;
		selectDataSQL << "SELECT * FROM message_to_teacher WHERE id_student = '"
			<< studentId << "' AND id_teacher = '" << teacherId << "'";

		sql::ResultSet* res = stmt->executeQuery(selectDataSQL.str());

		while (res->next()) {
			details.push_back(res->getString("message"));
			details.push_back(res->getString("student_or_teacher"));
		}

		messageToTeacher.push_back(details);

		return messageToTeacher;

		delete res;
		delete stmt;
		delete con;
	}
	catch (sql::SQLException& e) {
		std::cerr << "SQL Error: " << e.what() << std::endl;
	}
}