//admin file written by Nuno Bazarian
#ifndef ADMIN_H
#define ADMIN_H

#include "user.h"
using namespace std;
class admin_c: public user_c{
    public:
        void printAll() { //print admin's info
            print();
        }
        void addCourse(sqlite3* DB){ //add course from system
                string CRN, title, department, time, day, semester, year, credit;//parameters for COURSE object
                cout << "Enter the CRN, title, department, time, day(s) of the week, semester, year and credits, separated by a space:";
                cin >> CRN >> title >> department >> time >> day >> semester >> year >> credit; //take in user inputs after prompt
                string userInput("INSERT INTO COURSE VALUES(" + CRN + ",'" + title + "','" + department + "','" + time + "','" + day + "','" + semester + "'," + year + "," + credit + ");" //create insert co$
                                                "SELECT * FROM INSTRUCTOR where DEPT='" + department+"'"); //display if any professors are available to teach the course

                rfc = sqlite3_exec(DB, userInput.c_str(), callback, NULL, NULL);

                if (rfc != SQLITE_OK){
                        std::cerr << "Error Insert" << std::endl;
                        sqlite3_free(messageError);
                }
                else
                        std::cout << "Course created Successfully!" << std::endl;

        }

        void removeCourse(sqlite3* DB){ //remove course  from system
		string CRN;
		cout << "Enter the CRN of the course to delete:";
		cin >> CRN;
        	string userInput("DELETE from COURSE where CRN="+ CRN + ";");

        	rfc = sqlite3_exec(DB,userInput.c_str(),callback,NULL,NULL);

        	if (rfc !=SQLITE_OK)
        	{
                	std::cerr << "Error Insert" << std::endl;
                	sqlite3_free(messageError);
        	}
        	else
                	std::cout << "Records deleted Successfully!" << std::endl;

        }
	//Placeholder functions for final product (I am lazy and don't want to rewrite them for this assignment)
        void modUSystem(){ //add/remove user from system
            std::cout << "User removed. \n";
        }

        void modSCourse(){ //add/remove student from course
            std::cout << "Student removed from course.\n";
        }
	//this function differs because the Admin will be able to see personal data about users, not just information about courses
        void searchData(){ //function to search for data in the system and print it
            std::cout << "Information found and displayed from system.\n";
        }

        admin_c(std::string fName, std::string lName, std::string inD):user_c(fName, lName, inD){}
};

#endif
