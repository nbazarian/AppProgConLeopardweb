#include <sqlite3.h>
#include "admin.h"
#include "student.h"
#include <vector>
using namespace std;
//Callback function that prints out the SQL query 
static int callback(void* data, int argc, char** argv, char** azColName)
{
        int i;
        
        for (i = 0; i < argc; i++)
        {
          //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
          if(argv[i]){
            printf("%s", argv[i]);
          }
          else 
            printf ("NULL"); 
        }

        printf("\n");
        
        return 0;
}

  
int main(void){
  sqlite3* DB;
  int selection,rfc; 
  string exit;
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
 
  // *************************************************************************************
  // ********************************LOG IN LOG OUT **************************************
  // *************************************************************************************
  //           STILL NEEDS TO BE COMPLETED 
  string userID, userType, userEmail, storedEmail, storedID;
  int type;
  cout << "***** LOG IN TO BEGIN *****\n\n";
  cout << "Are you a Student(1), Instructor(2), or Admin(3)?: ";
  cin >> type;
  cout << "Enter your ID: ";
  cin >> userID;
  //CHECK what type of user 
  if (type == 1)
    userType = "STUDENT";
  else if (type == 2)
    userType = "INSTRUCTOR"; 
  else if (type == 3)
    userType = "ADMIN";
  else 
    cout << "\nERROR: INVALID ID\n";
    
    //CHECK if ID actually exists 
  sqlite3_stmt *stmt;
  string statement = "SELECT ID FROM '" + userType + "' WHERE ID = '" + userID + "';";
  int rc = sqlite3_prepare_v2(DB, statement.c_str(), statement.length(), &stmt, NULL);
  if (rc != SQLITE_OK) {
   // handle the error
   cout << "ERROR\n";
  }
  // Loop through the results, a row at a time.
  while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
    storedID = sqlite3_column_int(stmt, 0);
  }
 
  //Student Functions 
  string stuFirstName, stuLastName;
  int menuPick, cont = 1;
  cout << "Enter your first name, last name seperated by spaces: ";
  cin >> stuFirstName >> stuLastName;
  student_c studentTest(stuFirstName, stuLastName, userID); //creating student object with information 
  while (cont == 1){
    cout << "\n********  MENU ********\n";
    cout << "1.Add Courses to Schedule\n2.Remove Courses from Schedule\nEnter Choice: "; //menu prompt 
    cin >> menuPick;
    if(menuPick == 1){
      studentTest.addToSchedule(DB, userID);
    }
    else if(menuPick == 2){
      studentTest.removeFromSchedule(DB, userID);
    }
    else{
      cout << "ERROR: Invalid choice\n";
    }
    
    cout << "Another? (1 - Yes, 0 - No): ";
    cin >> cont;
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