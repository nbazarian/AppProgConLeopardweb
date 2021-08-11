
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
        void modUSystem(sqlite3* DB){ //add/remove user from system
        	int manChoice, typeChoice;
		string fame, lame, iD, dpart, yar, emil, tile;
		std::cout << "1.Add\n2.Remove\nSelect:";
		std::cin >>  manChoice;
		
		std::cout << "1.Student\n2.Instructor\nSelect:";
		std::cin >> typeChoice;

		if (manChoice == 1 && typeChoice == 1){
			std::cout << "Please enter the first name, last name, ID, major, year of graduation and email address of the student:";
			std::cin >> fame >> lame >> iD >> dpart >> yar >> emil;

                        string userInput("INSERT INTO STUDENT VALUES('"+ iD + "','" + fame +"','" + lame +"', '" + yar +"','"+ dpart+ "','" + emil+"', NULL, NULL, NULL, NULL, NULL);");

                        rfc = sqlite3_exec(DB,userInput.c_str(),callback,NULL,NULL);

                        if (rfc !=SQLITE_OK)
                        {
                                std::cerr << "Error Insert" << std::endl;
                        }
                        else
                                std::cout << "Student created Successfully!" << std::endl;


		}
		else if(manChoice == 1 && typeChoice == 2){
                        std::cout << "Please enter the first name, last name, ID, title, department, year of hire and email address of the instructor:";
                        std::cin >> fame >> lame >> iD >> tile >> dpart >> yar >> emil;

                        string userInput("INSERT INTO INSTRUCTOR VALUES('"+ iD + "','" + fame +"','" + lame +"', '" + yar +"','"+ tile + "','" + dpart+ "','" + emil+"', NULL, NULL, NULL, NULL, NULL);");

                        rfc = sqlite3_exec(DB,userInput.c_str(),callback,NULL,NULL);

                        if (rfc !=SQLITE_OK)
                        {
                                std::cerr << "Error Insert" << std::endl;
                        }
                        else
                                std::cout << "Instructor created Successfully!" << std::endl;


		}
		else if(manChoice == 2 && typeChoice ==1){
                        std::cout << "Please enter the ID of the instructor you wish to remove:";
                        std::cin >> iD;
                        string userInput("DELETE from STUDENT where ID="+ iD + ";");

	                rfc = sqlite3_exec(DB,userInput.c_str(),callback,NULL,NULL);

	                if (rfc !=SQLITE_OK)
        	        {
                	        std::cerr << "Error Insert" << std::endl;
	                }
	                else
        	                std::cout << "Student deleted Successfully!" << std::endl;

			}
		else if(manChoice == 2 && typeChoice == 2){
			std::cout << "Please enter the ID of the instructor you wish to remove:";
			std::cin >> iD;
			string userInput("DELETE from INSTRUCTOR where ID="+ iD + ";");

                        rfc = sqlite3_exec(DB,userInput.c_str(),callback,NULL,NULL);

                        if (rfc !=SQLITE_OK)
                        {
                                std::cerr << "Error Insert" << std::endl;
                        }
                        else
                                std::cout << "Instructor deleted Successfully!" << std::endl;
		}
		else
			std::cout << "Inputs not recognized.\n";
        }


        void changeSched(sqlite3* DB){ //modify schedules of users
		 string iD, courseNumber, CRN;
		int manChoice,typeChoice;
		std::cout << "1.Link\n2.Unlink\nSelect:";
		std:cin >> manChoice;

		std::cout << "1.Student\n2.Instructor\nSelect:";
		std::cin >> typeChoice;

		std::cout << "Please enter the ID of the user and the course to be changed:";
		std::cin >> iD >> courseNumber;
		if (manChoice == 1 && typeChoice == 1){

			std::cout << "Please input the CRN to link:";
			std::cin >> CRN;

			string userInput("UPDATE STUDENT SET COURSE"+ courseNumber +" = " + CRN +" WHERE ID = " + iD + ";");

                        rfc = sqlite3_exec(DB,userInput.c_str(),callback,NULL,NULL);

                        if (rfc !=SQLITE_OK)
                        {
                                std::cerr << "Error Insert" << std::endl;
                        }
                        else
                                std::cout << "Student linked Successfully!" << std::endl;
		}
		else if (manChoice == 1 && typeChoice == 2){
                        std::cout << "Please input the CRN to link:";
                        std::cin >> CRN;

                        string userInput("UPDATE INSTRUCTOR SET COURSE"+ courseNumber +" = " + CRN +" WHERE ID = " + iD + ";");

                        rfc = sqlite3_exec(DB,userInput.c_str(),callback,NULL,NULL);

                        if (rfc !=SQLITE_OK)
                        {
                                std::cerr << "Error Insert" << std::endl;
                        }
                        else
                                std::cout << "Instructor linked Successfully!" << std::endl;

		}
		else if (manChoice == 2 && typeChoice == 1){

                        string userInput("UPDATE STUDENT SET COURSE"+ courseNumber +" = NULL  WHERE ID = " + iD + ";");

                        rfc = sqlite3_exec(DB,userInput.c_str(),callback,NULL,NULL);

                        if (rfc !=SQLITE_OK)
                        {
                                std::cerr << "Error Insert" << std::endl;
                        }
                        else
                                std::cout << "Student unlinked successfully\n";

		}
		else if(manChoice == 2 && typeChoice == 2){

                        string userInput("UPDATE INSTRUCTOR SET COURSE"+ courseNumber +" = NULL  WHERE ID = " + iD + ";");

                        rfc = sqlite3_exec(DB,userInput.c_str(),callback,NULL,NULL);

                        if (rfc !=SQLITE_OK)
                        {
                                std::cerr << "Error Insert" << std::endl;
                        }
                        else
                                std::cout << "Instructor unlinked successfully\n";

		}
		else 
			cout << "Input not recognized\n";
        }
  
        admin_c(std::string fName, std::string lName, std::string inD):user_c(fName, lName, inD){}
};

#endif
