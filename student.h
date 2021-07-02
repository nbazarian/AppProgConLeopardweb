#ifndef STUDENT_H
#define STUDENT_H

#include "user.h"
using namespace std;
class student_c: public user_c{
    public:
        void printAll() { //print admin's info
            print();
        }

        student_c(std::string fName, std::string lName, std::string inD):user_c(fName, lName, inD){}

 
 //Add or remove from course schedule 
	void addToSchedule(sqlite3* DB) {
		int another, count = 0;
     std::string courseToAdd[5];
		cout << "You may register for a maximum of 5 Courses\n";
		for (int i = 0; i < 5; i++) {
			do {
				cout << "Course " << i + 1 << " CRN?: ";
				cin >> courseToAdd[i];
				cout << "Another? (1 - Yes, 0 - No): ";
				cin >> another;
			} while (count < 6 && another == 1);
		}

		string addCourses = "UPDATE STUDENT("
			"SET COURSE1 = " + courseToAdd[0] + ","
			"SET COURSE2 = " + courseToAdd[1] + ","
			"SET COURSE3 = " + courseToAdd[2] + ","
			"SET COURSE4 = " + courseToAdd[3] + ","
			"SET COURSE5 = " + courseToAdd[4] + ");";
		rfc = sqlite3_exec(DB, addCourses.c_str(), callback, NULL, NULL);
	}
 
 
 //Remove course from schedule 
	void removeFromSchedule(sqlite3* DB) {
		int courseToRemove, courseCRN, another;
		string removeCourse;
		do {
			cout << "Which course would you like to remove?(1,2,3,4,5): ";
			cin >> courseToRemove;
			cout << "Enter the course CRN: ";
			cin >> courseCRN;
			switch (courseToRemove) {
				case 1:
					removeCourse = "UPDATE STUDENT SET COURSE1 = NULL";
					rfc = sqlite3_exec(DB, removeCourse.c_str(), callback, NULL, NULL);
				break;
				case 2:
					removeCourse = "UPDATE STUDENT SET COURSE2 = NULL";
					rfc = sqlite3_exec(DB, removeCourse.c_str(), callback, NULL, NULL);
				break;
				case 3:
					removeCourse = "UPDATE STUDENT SET COURSE3 = NULL";
					rfc = sqlite3_exec(DB, removeCourse.c_str(), callback, NULL, NULL);
				break;
				case 4:
					removeCourse = "UPDATE STUDENT SET COURSE4 = NULL";
					rfc = sqlite3_exec(DB, removeCourse.c_str(), callback, NULL, NULL);
				break;
				case 5:
					removeCourse = "UPDATE STUDENT SET COURSE5 = NULL";
					rfc = sqlite3_exec(DB, removeCourse.c_str(), callback, NULL, NULL);
				break;
			}

			cout << "\n\nAnother? (1 - Yes, 0 - No): ";
			cin >> another;

		} while (another == 1);

	}
};

#endif