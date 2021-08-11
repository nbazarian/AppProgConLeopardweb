#include <sqlite3.h>
#include "admin.h"
#include "student.h"
#include "instructor.h"
#include <vector>
using namespace std;
using std::vector;
 
int main(void){
  sqlite3* DB;
  int selection,rfc; 
  //string exit;
  int exit = 0;;
  string input, hold;  
  char logout;
  char* messageError; 
  rfc = sqlite3_open("assignment5.db",&DB);

 
 
  // *************************************************************************************
  // ********************************LOG IN LOG OUT **************************************
  // *************************************************************************************
  //           STILL NEEDS TO BE COMPLETED 
  

   string userID, userType, userEmail, storedID, storedEmail;
   int type;
   cout << "\n***** LOG IN TO BEGIN *****\n\n";

     
     
   //Loop until user enters correct credentials 
   int validLogin = 0, invalidCount = 1;
   while (validLogin == 0){
     cout << "Enter your ID: ";
     cin >> userID;
     cout << "Enter your Email: ";
     cin >> userEmail;


     //CHECK what type of user 
     
     if (userID[0] == '1'){
       userType = "STUDENT";
       type = 1;
     }
     else if (userID[0] == '2'){
       userType = "INSTRUCTOR"; 
       type = 2;
     } 
     else if (userID[0] == '3'){
       userType = "ADMIN";
       type = 3;
     }
     else 
       cout << "\nERROR: INVALID ID\n";
  
    //*******
    // Store return value of query that selects ID, and Email of user 
    //*******
    
    sqlite3_stmt *stmt, *stmt2;
    string statement = "SELECT ID FROM '" + userType + "' WHERE ID = '" + userID + "';";
    int rc = sqlite3_prepare_v2(DB, statement.c_str(), statement.length(), &stmt, NULL);
    if (rc != SQLITE_OK) {
     // handle the error
    }
    // Loop through the results, a row at a time.
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
     storedID = (char*)sqlite3_column_text(stmt, 0);
     // etc.
    }
    
    statement = "SELECT EMAIL FROM '" + userType + "' WHERE ID = '" + userID + "';";
    rc = sqlite3_prepare_v2(DB, statement.c_str(), statement.length(), &stmt, NULL);
    if (rc != SQLITE_OK) {
     // handle the error
    }
    // Loop through the results, a row at a time.
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
     storedEmail = (char*)sqlite3_column_text(stmt, 0);
     // etc.
    }
    // Free the statement when done.
    sqlite3_finalize(stmt);
    
    //Check if user has entered valid credentials: 
    if ((userID == storedID) && (userEmail == storedEmail)){
      validLogin = 1;
      cout << "\n\n*********************";
      cout << "\n   LOGIN ACTIVATED   ";
      cout << "\n*********************\n\n";
    }
    else if (invalidCount >= 3){
      cout << "ERROR: Too Many Invalid Attempt: Try Again Later\n";
      break;
    }
    else {
      cout << "\nERROR: INVALID LOGIN CREDENTIALS: TRY AGAIN\n"; 
      invalidCount++;
    }
  }
  
  //Giving user options based on their userType and if their login is valid 
  if ((type == 1) && (validLogin != 0)){
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
      
      cout << "Another Menu Option? (1 - Yes, 0 - No): ";
      cin >> cont;
      if (cont == 0){
        cout << "LOGOUT? (Y/N): ";
        cin >> logout; 
        if (logout == 'Y'){
          //If user would like to log out, erase all their credentials 
          userID = ""; 
          userEmail = "";
          storedID = ""; 
          storedEmail = ""; 
        }
      }
    }
  }
  
  else if ((type == 2) && (validLogin != 0)){
    //INSTRUCTOR MENU OPTIONS AND FUNCTIONS 
    cout << "INSTRUCTOR FUNCTIONS...\n";

    string instructorName, instructorSurname;
    int selection, cont = 1;
    cout << "Enter your first name, last name separated by spaces: ";
    cin >> instructorName >> instructorSurname;
    instructor_c instructorTest(instructorName, instructorSurname, userID);

    

    while (cont == 1)
    {
        cout << "\n********  INSTRUCTOR MENU ********\n1. Print course teaching schedule\n2. Print and Search course roster\n3. Exit\n\nMake a selection: ";
        cin >> selection;

        switch (selection)
        {
        case 1:

            instructorTest.printRoster(DB, userID);

            break;
        case 2:

            instructorTest.searchRoster(DB, userID);

            break;
        case 3:

            cont = 0;
            break;

        default:

            cout << "\n\nInvalid input. Try again.\n\n";

            break;
        }

        if (cont != 1) {
            cout << "LOGOUT? (Y/N): ";
            cin >> logout;
            if (logout == 'Y') {
                //If user would like to log out, erase all their credentials 
                userID = "";
                userEmail = "";
                storedID = "";
                storedEmail = "";
            }
        }
    }

  }
  
  else if ((type == 3) && (validLogin != 0))
   {
    //ADMIN MENU OPTIONS AND FUNCTIONS 
    cout << "ADMIN FUNCTIONS...\n";
  }


sqlite3_close(DB);
return 0;
}





