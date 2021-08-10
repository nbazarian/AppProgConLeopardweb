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
	void addToSchedule(sqlite3* DB, string ID) {
		int another = 1, count = 0;
    std::string courseToAdd[5] = {"NULL", "NULL", "NULL", "NULL", "NULL"};
    cout << "LIST OF ALL COURSES\n\n";
    string courseList = "SELECT CRN, TITLE FROM COURSE";
    rfc = sqlite3_exec(DB, courseList.c_str(), callback, NULL, NULL);
	  cout << "You may register for a maximum of 5 Courses\n\n";
   
    while ((count < 6) && (another == 1)){
      cout << "Course " << count+1 << " CRN?: ";
      cin >> courseToAdd[count];
      cout << "\nAnother? (1 - Yes, 0 - No): ";
      cin >> another;
      count++;
    }

    string addCourses = "UPDATE STUDENT SET COURSE1 = '" + courseToAdd[0] + "', COURSE2 = '" + courseToAdd[1] + "', COURSE3 = '" + courseToAdd[2] + "', COURSE4 = '" + courseToAdd[3] +                         "', COURSE5 = '" + courseToAdd[4] + "' WHERE ID = '" + ID + "'";
		rfc = sqlite3_exec(DB, addCourses.c_str(), callback, NULL, NULL);
    string printCourses = "SELECT * FROM STUDENT WHERE ID = '" + ID + "';";
    rfc = sqlite3_exec(DB, printCourses.c_str(), callback, NULL, NULL);
	}
 
 
 //Remove course from schedule 
	void removeFromSchedule(sqlite3* DB, string ID) {
		int courseToRemove, another = 1;
		string removeCourse;
    string emptyString = "NULL";
		while (another == 1) {
      string printCourses = "SELECT NAME, COURSE1, COURSE2, COURSE3, COURSE4, COURSE5 FROM STUDENT WHERE ID = '" + ID + "';";
      rfc = sqlite3_exec(DB, printCourses.c_str(), callback, NULL, NULL);
			
      cout << "Which course would you like to remove?(1,2,3,4,5): ";
			cin >> courseToRemove;
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
			}

			cout << "\n\nAnother? (1 - Yes, 0 - No): ";
			cin >> another;
		} 
    string printCourses = "SELECT NAME, COURSE1, COURSE2, COURSE3, COURSE4, COURSE5 FROM STUDENT WHERE ID = '" + ID + "';";
    rfc = sqlite3_exec(DB, printCourses.c_str(), callback, NULL, NULL);
	}

};

#endif