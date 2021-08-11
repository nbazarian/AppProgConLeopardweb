#ifndef STUDENT_H
#define STUDENT_H
#include <vector>

#include "user.h"
using namespace std;
class student_c: public user_c{
    public:
        void printAll() { //print admin's info
            print();
        }

        student_c(std::string fName, std::string lName, std::string inD):user_c(fName, lName, inD){}

 
 //Add or remove from course schedule 
	void addToSchedule(sqlite3* DB, string ID) {
		int another, error, numCourses = -1, already, count;
		std::string courseToAdd[5] = {"NULL", "NULL", "NULL", "NULL", "NULL"};
		vector<string> registeredCourses;

		//Display all available courses 
		cout << "LIST OF ALL COURSES\n\n";
		string courseList = "SELECT CRN, TITLE FROM COURSE";
		rfc = sqlite3_exec(DB, courseList.c_str(), callback, NULL, NULL);
		cout << "You may register for a maximum of 5 Courses\n";

		while (numCourses > 6 || numCourses < 0) {
			cout << "\nHow many courses would you like to register for?: ";
			cin >> numCourses;
			if (numCourses > 6) {
				cout << "ERROR: You can only take upto 5 classes a semester. Please try again.\n";
			}
			else if (numCourses < 0) {
				cout << "ERROR: You cannot add less than 0 courses. Please try again.\n";
			}
		}

		count = 0;
		while (count < numCourses) {
			do {
				cout << "Course " << count + 1 << " CRN?: ";
				cin >> courseToAdd[count];

				for (int j = 0; j < registeredCourses.size(); j++) {
					if (courseToAdd[count] == registeredCourses[j]) {
						cout << "ERROR: Course already in Schedule\n";
						courseToAdd[count] = "NULL";
						already = 1;
					}
				}

				if (already != 1) {
					error = 0;
					registeredCourses.push_back(courseToAdd[count]);
					count++;
				}
				already = 0;
			} while (error == 1);
		}

		//Update database to add courses 
		string addCourses = "UPDATE STUDENT SET COURSE1 = '" + courseToAdd[0] + "', COURSE2 = '" + courseToAdd[1] + "', COURSE3 = '" + courseToAdd[2] + "', COURSE4 = '" + courseToAdd[3] +                         "', COURSE5 = '" + courseToAdd[4] + "' WHERE ID = '" + ID + "'";
		rfc = sqlite3_exec(DB, addCourses.c_str(), callback, NULL, NULL);
		
		//Print Student's schedule
		cout << "\n**********\n SCHEDULE\n**********\n";
		string printCourses = "SELECT * FROM STUDENT WHERE ID = '" + ID + "';";
		rfc = sqlite3_exec(DB, printCourses.c_str(), callback, NULL, NULL);
	}
 
 
 //Remove course from schedule 
	void removeFromSchedule(sqlite3* DB, string ID) {
		int courseToRemove, another = 1;
		string removeCourse;
		string emptyString = "NULL";

		//Continue looping until user no longer wants to remove another course 
		while (another == 1) {
			string printCourses = "SELECT NAME, COURSE1, COURSE2, COURSE3, COURSE4, COURSE5 FROM STUDENT WHERE ID = '" + ID + "';";
			rfc = sqlite3_exec(DB, printCourses.c_str(), callback, NULL, NULL);
			
			cout << "Which course would you like to remove?(1,2,3,4,5): ";
			cin >> courseToRemove;

			//Update database to remove desired course(s)
			switch (courseToRemove) {
				case 1:
					removeCourse = "UPDATE STUDENT SET COURSE1 = NULL WHERE ID = '" + ID + "'";
					rfc = sqlite3_exec(DB, removeCourse.c_str(), callback, NULL, NULL);
				break;
				case 2:
					removeCourse = "UPDATE STUDENT SET COURSE2 = NULL WHERE ID = '" + ID + "'";
					rfc = sqlite3_exec(DB, removeCourse.c_str(), callback, NULL, NULL);
				break;
				case 3:
					removeCourse = "UPDATE STUDENT SET COURSE3 = NULL WHERE ID = '" + ID + "'";
					rfc = sqlite3_exec(DB, removeCourse.c_str(), callback, NULL, NULL);
				break;
				case 4:
					removeCourse = "UPDATE STUDENT SET COURSE4 = NULL WHERE ID = '" + ID + "'";
					rfc = sqlite3_exec(DB, removeCourse.c_str(), callback, NULL, NULL);
				break;
				case 5:
					removeCourse = "UPDATE STUDENT SET COURSE5 = NULL WHERE ID = '" + ID + "'";
					rfc = sqlite3_exec(DB, removeCourse.c_str(), callback, NULL, NULL);
				break;
				default: 
					"ERROR: Invalid\n";
				break;

			}

			cout << "\n\nRemove another Course? (1 - Yes, 0 - No): ";
			cin >> another;
		} 

		//Print out updated student schedule 
		cout << "\n**********\n SCHEDULE\n**********\n";
		string printCourses = "SELECT NAME, COURSE1, COURSE2, COURSE3, COURSE4, COURSE5 FROM STUDENT WHERE ID = '" + ID + "';";
		rfc = sqlite3_exec(DB, printCourses.c_str(), callback, NULL, NULL);
	}


	void printSchedule(sqlite3* DB, string ID) {
		cout << "\n\n**********\n SCHEDULE\n**********\n";
		string printCourses = "SELECT NAME, COURSE1, COURSE2, COURSE3, COURSE4, COURSE5 FROM STUDENT WHERE ID = '" + ID + "';";
		int rfc = sqlite3_exec(DB, printCourses.c_str(), callback, NULL, NULL);
	}
};

#endif
