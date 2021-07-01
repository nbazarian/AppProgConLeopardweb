#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <list>
#include <stdio.h>
#include <sqlite3.h>

using namespace std;
class user_c{
    private:
        std::string  firstName, lastName, ID; //ID is string for implementation in institutions that user letters for identification
    public: 
char* messageError;
int rfc = 0; 
/*************************************************************************************************
 The callback() function is invoked for each result row coming out of the evaluated SQL statement
 1st argument - the 4th argument provided by sqlite3_exec() and is typically not used
 2nd argument - number of columns in the result
 3rd argument - an array of strings containing the fields in that row
 4th argument - an array of strings containing the names of the columns
*************************************************************************************************/
static int callback(void* data, int argc, char** argv, char** azColName)
{
        int i;

        for (i = 0; i < argc; i++)
                {
                printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        }

        printf("\n");

                return 0;
}


        void setFirst(std::string fName){ firstName = fName;} //set first name of user
        void setLast(std::string lName){ lastName = lName;} //set last name of user
        void setID(std::string input){ID = input;} //set ID of user 

        //print all
		void print(){
                	std::cout << "User's name: " << firstName << " " << lastName << std::endl;
                	std::cout << "User's ID: " << ID << std::endl;
            }

		void searchAllCourse(sqlite3* DB){ //search all courses
			string query = "SELECT * FROM COURSE";
        		sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);

		}

		void searchParamCourse(sqlite3* DB){
			string strChoice1, strChoice2;
			int selection;
			cout << "Enter the semester and year to search for the course in:";
			cin >> strChoice1 >> strChoice2;
			string query = "SELECT * FROM COURSE WHERE SEMESTER = '" + strChoice1 +"'AND YEAR = " + strChoice2;
			cout << "1.Search by CRN\n2.Search by department\n3.Search by title\n4.Skip\nChoose additional parameter:";
			cin >> selection;

				if (selection == 1){
					cout << "Enter CRN:";
					cin >> strChoice1;
					query = query + " AND CRN =" + strChoice1;
				}
				else if (selection == 2){
					cout << "Enter department:";
					cin >> strChoice1;
					query = query + " AND DEPARTMENT = '" + strChoice1 + "'";
				}
				else if (selection == 3){
					cout << "Enter title:";
					cin >> strChoice1;
					query = query + " AND TITLE = '" + strChoice1 + "'";
				}
			cout << strChoice1;
			rfc = sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
               		if (rfc !=SQLITE_OK){
                        	cout << "No course found with those parameters.\n";
                	}


		}
        user_c(){
            std::string input;
            std::cout << "Please enter the user's first name: ";
            std::cin >> input;
            setFirst(input);
            std::cout << "Please enter the user's last name: ";
            std::cin >> input;
            setLast(input);
            std::cout << "Please enter the user's ID: ";
            std::cin >> input;
            setID(input);
        }; //constructor
        user_c(std::string fName, std::string lName, std::string inD) {
            setFirst(fName);
            setLast(lName);
            setID(inD);
        }
        ~user_c(){}; //deconstructor

};

#endif
