#include <sqlite3.h>
#include "admin.h"
#include "student.h"
#include "instructor.h"

#include <vector>
using namespace std;
using std::vector;

int main(void) {
    sqlite3* DB;
    int selection, rfc;
    //string exit;
    int exit = 0, cont = 1;
    string input, hold;
    char logout = 'N';
    char* messageError;
    rfc = sqlite3_open("registrationDatabase.db", &DB);



    // *************************************************************************************
    // ********************************LOG IN LOG OUT **************************************
    // *************************************************************************************

    string userID, userType, userEmail, storedID, storedEmail;
    int type;
    cout << "\n***** LOG IN TO BEGIN *****\n\n";


    //Loop until user enters correct credentials 
    int validLogin = 0, invalidCount = 1;
    while (validLogin == 0) {
        cout << "Enter your ID: ";
        cin >> userID;
        cout << "Enter your Email: ";
        cin >> userEmail;


        //CHECK what type of user 

        if (userID[0] == '1') {
            userType = "STUDENT";
            type = 1;
        }
        else if (userID[0] == '2') {
            userType = "INSTRUCTOR";
            type = 2;
        }
        else if (userID[0] == '3') {
            userType = "ADMIN";
            type = 3;
        }
        else
            cout << "\nERROR: INVALID ID\n";

        //*******
        // Store return value of query that selects ID, and Email of user 
        //*******

        sqlite3_stmt* stmt, * stmt2;
        string statement = "SELECT ID FROM '" + userType + "' WHERE ID = '" + userID + "';";
        int rc = sqlite3_prepare_v2(DB, statement.c_str(), statement.length(), &stmt, NULL);

        // Loop through the results, a row at a time.
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            storedID = (char*)sqlite3_column_text(stmt, 0);
            // etc.
        }

        statement = "SELECT EMAIL FROM '" + userType + "' WHERE ID = '" + userID + "';";
        rc = sqlite3_prepare_v2(DB, statement.c_str(), statement.length(), &stmt, NULL);

        // Loop through the results, a row at a time.
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            storedEmail = (char*)sqlite3_column_text(stmt, 0);
            // etc.
        }
        // Free the statement when done.
        sqlite3_finalize(stmt);


        //Check if user has entered valid credentials: 
        if ((userID == storedID) && (userEmail == storedEmail)) {
            validLogin = 1;
            cout << "\n\n*********************";
            cout << "\n   LOGIN ACTIVATED   ";
            cout << "\n*********************\n\n";
        }
        else if (invalidCount >= 3) {
            cout << "ERROR: Too Many Invalid Attempt: Try Again Later\n";
            break;
        }
        else {
            cout << "\nERROR: INVALID LOGIN CREDENTIALS: TRY AGAIN\n";
            invalidCount++;
        }
    }

    //Giving user options based on their userType and if their login is valid 
    if ((type == 1) && (validLogin != 0)) {
        //Student Functions 
        string stuFirstName, stuLastName;
        int menuPick = 0;

        //Create student_c studentCreated so that the functions of student.h can be accessed 
        cout << "Enter your first name, last name seperated by spaces: ";
        cin >> stuFirstName >> stuLastName;
        student_c studentCreated(stuFirstName, stuLastName, userID); //creating student object with information 

        //While loop to continue prompting menu and options until user decides otherwise 
        while ((cont == 1) && (logout == 'N')) {
            cout << "\n********  MENU ********\n";
            cout << "1.Add Courses to Schedule\n2.Remove Courses from Schedule\n3.Print Schedule\nEnter Choice: "; //menu prompt 
            cin >> menuPick;

            //if/else for user's choice from menu 
            if (menuPick == 1) {
                studentCreated.addToSchedule(DB, userID);
            }
            else if (menuPick == 2) {
                studentCreated.removeFromSchedule(DB, userID);
            }
            else if (menuPick == 3) {
                studentCreated.printSchedule(DB, userID);
            }
            else {
                cout << "ERROR: Invalid choice\n";
            }

            cout << "Another Menu Option? (1 - Yes, 0 - No): ";
            cin >> cont;

            if (cont == 0) {
                cout << "LOGOUT? (Y/N): ";
                cin >> logout;
                if (logout == 'Y') {
                    //If user would like to log out, erase all their credentials 
                    userID = "";
                    userEmail = "";
                    storedID = "";
                    storedEmail = "";
                }
                else {
                    logout = 'N';
                    cont = 1;
                }
            }
        }
    }

    else if ((type == 2) && (validLogin != 0)) {
        //INSTRUCTOR MENU OPTIONS AND FUNCTIONS 

    }


    else if ((type == 3) && (validLogin != 0)) {
        //ADMIN MENU OPTIONS AND FUNCTIONS 
        cout << "ADMIN FUNCTIONS...\n";
    }

    sqlite3_close(DB);
    return 0;
}






