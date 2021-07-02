#include <sqlite3.h>
#include "admin.h"
#include "student.h"

using namespace std;

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

int main(void){
sqlite3* DB;
int selection,rfc; 
string input, hold;  
char logout;
char* messageError; 
rfc = sqlite3_open("assignment5.db",&DB);


  //ADD Columns to Student and Instructor - Keeps track of the courses that they are taking/teaching 
	std::string addColumnCourses = "ALTER TABLE STUDENT ADD COURSE1 INT;";
	rfc = sqlite3_exec(DB, addColumnCourses.c_str(), callback, NULL, NULL);
  addColumnCourses = "ALTER TABLE STUDENT ADD COURSE2 INT;";
	rfc = sqlite3_exec(DB, addColumnCourses.c_str(), callback, NULL, NULL);
  addColumnCourses = "ALTER TABLE STUDENT ADD COURSE3 INT;";
	rfc = sqlite3_exec(DB, addColumnCourses.c_str(), callback, NULL, NULL);
  addColumnCourses = "ALTER TABLE STUDENT ADD COURSE4 INT;";
	rfc = sqlite3_exec(DB, addColumnCourses.c_str(), callback, NULL, NULL);
  addColumnCourses = "ALTER TABLE STUDENT ADD COURSE5 INT;";
	rfc = sqlite3_exec(DB, addColumnCourses.c_str(), callback, NULL, NULL);
 
  addColumnCourses = "ALTER TABLE INSTRUCTOR ADD COURSE1 INT;";
	rfc = sqlite3_exec(DB, addColumnCourses.c_str(), callback, NULL, NULL);
  addColumnCourses = "ALTER TABLE INSTRUCTOR ADD COURSE2 INT;";
	rfc = sqlite3_exec(DB, addColumnCourses.c_str(), callback, NULL, NULL);
  addColumnCourses = "ALTER TABLE INSTRUCTOR ADD COURSE3 INT;";
	rfc = sqlite3_exec(DB, addColumnCourses.c_str(), callback, NULL, NULL);
  addColumnCourses = "ALTER TABLE INSTRUCTOR ADD COURSE4 INT;";
	rfc = sqlite3_exec(DB, addColumnCourses.c_str(), callback, NULL, NULL);
   addColumnCourses = "ALTER TABLE INSTRUCTOR ADD COURSE5 INT;";
	rfc = sqlite3_exec(DB, addColumnCourses.c_str(), callback, NULL, NULL);
 
//CHECKING WHAT TYPE OF USER 
//First prompt user to Log In 
  int studentCheck = 0, instructorCheck = 0, adminCheck = 0;
	string idToCheck;
	char typeOfUser; //s - student, i - instructor, a - admin
	//Prompt user to enter their ID 
	cout << "Enter your ID: ";
	cin >> idToCheck;


	string checkIfStudent = "SELECT * FROM STUDENT WHERE ID = " + idToCheck + ";";
	studentCheck = sqlite3_exec(DB, checkIfStudent.c_str(), callback, NULL, NULL);
  if (studentCheck == SQLITE_OK){
		typeOfUser = 's';
  }
  
	string checkIfInstructor = "SELECT * FROM INSTRUCTOR WHERE ID = " + idToCheck + ";";
	instructorCheck = sqlite3_exec(DB, checkIfInstructor.c_str(), callback, NULL, NULL);
 	if (instructorCheck == SQLITE_OK){
		typeOfUser = 'i';
  }
 	string checkIfAdmin = "SELECT * FROM ADMIN WHERE ID = " + idToCheck + ";";
  adminCheck = sqlite3_exec(DB, checkIfInstructor.c_str(), callback, NULL, NULL);
	if (adminCheck == SQLITE_OK){
		typeOfUser = 'a';
  }
  
  
	//if ((typeOfUser != 's') || (typeOfUser != 'i') || (typeOfUser != 'a'))
	//	cout << "\nERROR: Please recheck your ID input\n";

	//Using if/else to only show user options that are applicable to them 
	if (typeOfUser == 's') {
		//Options for Students 
   cout << "\nSTUDENT LOGIN ACTIVATED\n";
	}

	else if (typeOfUser == 'i') {
		//Options for Instructors 
  cout << "\nINSTRUCTOR LOGIN ACTIVATED\n";
	}

	else if (typeOfUser == 'a') {
		//Options for Admins 
      cout << "\nADMIN LOGIN ACTIVATED\n";
	}
	else {
		cout << "Oops! Check your ID again, there seems to be a mistake\n";
	}

/*
//admin functions
do{
admin_c dummy("Dummy", "Info", "Woooo"); //occupy variable with login information
cout << "1.Search all courses\n2.Search with parameters\n3.Add/Remove course\nEnter choice:"; //prompt user with interface
cin >> selection;  //take user input
	if (selection == 1){
		dummy.searchAllCourse(DB);
	}
	else if (selection == 2){
		dummy.searchParamCourse(DB);
	}
	else if(selection == 3){
		cout << "1.Add course\n2.Remove course\nEnter choice:";
		cin >> selection;
			if (selection == 1){
				dummy.addCourse(DB);
			}
			else if (selection == 2){
				dummy.removeCourse(DB);
			}
			else
				cout << "Input not recognized\n";
	
	}
	cout << "Continue?(Y/N)";
	cin >> logout;
}while (logout != 'N');
*/


sqlite3_close(DB);
}