#include <sqlite3.h>
#include "admin.h"
#include "student.h"
#include "instructor.h"

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
//header of file developed by Nuno Bazarian. Variable names can be blamed on me (Nuno)
int main(void){
sqlite3* DB;
int selection,rfc; 
string input, hold;  
char logout;
char* messageError; 
rfc = sqlite3_open("assignment5.db",&DB); //open Assignment5.db (database file)


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


//admin functions (Nuno Bazarian)
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


  // Assemble and print course roster, Brendan Gibbons 
 
  // Creates object for instructor
  instructor_c instructor("Example", "Professor", "1093"); // Sample values
  
  // Creates new columns for courses for instuctors, allows for four classes
  std::string assembleRoster = "ALTER TABLE INSTRUCTOR ADD CLASS1 INT;";
  rfc = sqlite3_exec(DB, assembleRoster.c_str(), callback, NULL, NULL);
  
  assembleRoster = "ALTER TABLE INSTRUCTOR ADD CLASS2 INT;";
  rfc = sqlite3_exec(DB, assembleRoster.c_str(), callback, NULL, NULL);
  
  assembleRoster = "ALTER TABLE INSTRUCTOR ADD CLASS3 INT;";
  rfc = sqlite3_exec(DB, assembleRoster.c_str(), callback, NULL, NULL);
  
  assembleRoster = "ALTER TABLE INSTRUCTOR ADD CLASS4 INT;";
  rfc = sqlite3_exec(DB, assembleRoster.c_str(), callback, NULL, NULL);
  
  int choice = 0;
  cout << "Select an option:\n\n1. Assemble roster\n2. Print roster\n\nSelect: ";
  cin >> choice;
  
  switch(choice)
  {
    case 1:
      instructor.addToRoster(DB);
      break;
      
    case 2:
      instructor.printRoster(DB);
      break;
      
    default:
      break;
  }
  
  // Search courses by parameters, Brendan Gibbons
  std::string crnIn = "", yearIn = "";
  std::string deptIn = "", instructorIn = "";
  cout << "Enter CRN and year of course separated by a space: ";
  cin >> crnIn >> yearIn;
  
  string query = "SELECT * FROM COURSE WHERE YEAR = " + yearIn + " AND CRN = " + crnIn;
  
  cout << "Which parameters do you want to search by?\n\n1. Instructor\n2. Department\n\nMake a selection: ";
  cin >> choice;
  
  switch(choice)
  {
    case 1:
    
      cout << "Enter the instructor of the course: ";
      cin >> instructorIn;
      
      query = query + " AND INSTRUCTOR = '" + crnIn + "'";
    
      break;
    
    case 2:
      cout << "Enter the department of the course: ";
      cin >> deptIn;
      
      query = query + " AND DEPARTMENT = '" + deptIn + "'";
    
      break;
    
    default:
      
      cout << "Invalid selection.";
    
      break;
      
  }
   
   cout << endl << query << endl;
   rfc = sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
  
                 


sqlite3_close(DB);
}