#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include "user.h"

using namespace std;

class instructor_c : public user_c
{
public:

    sqlite3* DB;
    int rfc = sqlite3_open("assignment5.db", &DB);

    void printAll()
    {
        print();
    }

    int addMore = 0;
    string roster[4];
    string instID = "";

    void addToRoster(sqlite3* DB)
    {
        cout << "Enter ID of instructor you would like to assign courses to: ";
        cin >> instID;
        
        
        cout << "Instructors can teach a maximum of 4 courses a semester." << endl;

   
        int i = 0;

        for (i = 0; i < 4; i++)
        {
            cout << "Enter the CRN of course #" << i + 1 << " in the instructor's roster: ";
            cin >> roster[i];

            if (i < 4)
            {
                cout << "Continue adding courses? (1 for yes, 0 for no): ";
                cin >> addMore;
            }
            else
            {
                break;
            }

            if (addMore == 1)
            {
                continue;
            }
            else if(addMore == 0)
            {
                break;
            }
            else
            {
                break;
            }

        }


        //string adminUpdate("UPDATE ADMIN SET TITLE = 'Vice-President' WHERE ID = 30002");
        //std::cout << "Title updated for ID 30002" << std::endl;
        //exit = sqlite3_exec(DB, adminUpdate.c_str(), NULL, 0, &messageError);

        std::string rosterString = "UPDATE INSTRUCTOR SET CLASS1 = " + roster[0] + " WHERE ID = " + instID;
        rfc = sqlite3_exec(DB, rosterString.c_str(), callback, NULL, NULL);

        rosterString = "UPDATE INSTRUCTOR SET CLASS2 = " + roster[1] + " WHERE ID = " + instID;
        rfc = sqlite3_exec(DB, rosterString.c_str(), callback, NULL, NULL);

        rosterString = "UPDATE INSTRUCTOR SET CLASS3 = " + roster[2] + " WHERE ID = " + instID;
        rfc = sqlite3_exec(DB, rosterString.c_str(), callback, NULL, NULL);

        rosterString = "UPDATE INSTRUCTOR SET CLASS4 = " + roster[3] + " WHERE ID = " + instID;
        rfc = sqlite3_exec(DB, rosterString.c_str(), callback, NULL, NULL);

        cout << "Roster for instructor with ID " + instID + " built." << endl;

    }

    void removeFromRoster(sqlite3* DB)
    {
        int courseToRemove = 0;

        cout << "Enter ID of instructor whose roster you would like to adjust: ";
        cin >> instID;

        cout << endl << endl;

        string course1 = "SELECT CLASS1 FROM INSTRUCTOR WHERE ID = " + instID;
        cout << "\n" << course1 << "\n";
        rfc = sqlite3_exec(DB, course1.c_str(), callback, NULL, NULL);

        string course2 = "SELECT CLASS2 FROM INSTRUCTOR WHERE ID = " + instID;
        cout << "\n" << course2 << "\n";
        rfc = sqlite3_exec(DB, course2.c_str(), callback, NULL, NULL);

        string course3 = "SELECT CLASS3 FROM INSTRUCTOR WHERE ID = " + instID;
        cout << "\n" << course3 << "\n";
        rfc = sqlite3_exec(DB, course3.c_str(), callback, NULL, NULL);

        string course4 = "SELECT CLASS4 FROM INSTRUCTOR WHERE ID = " + instID;
        cout << "\n" << course4 << "\n";
        rfc = sqlite3_exec(DB, course4.c_str(), callback, NULL, NULL);

        cout << "\nWhich course would you like to remove? (1-4): ";
        cin >> courseToRemove;

        string removeRoster = "";
        int execute = 0;

        switch (courseToRemove)
        {
        case 1:

            removeRoster = "UPDATE INSTRUCTOR SET CLASS1 = NULL WHERE ID = '" + instID + "'";
            execute = sqlite3_exec(DB, removeRoster.c_str(), callback, NULL, NULL);

            cout << "Course #1 removed.\n\n";

            break;
        case 2:

            removeRoster = "UPDATE INSTRUCTOR SET CLASS2 = NULL WHERE ID = '" + instID + "'";
            execute = sqlite3_exec(DB, removeRoster.c_str(), callback, NULL, NULL);

            cout << "Course #2 removed.\n\n";

            break;
        case 3:

            removeRoster = "UPDATE INSTRUCTOR SET CLASS3 = NULL WHERE ID = '" + instID + "'";
            execute = sqlite3_exec(DB, removeRoster.c_str(), callback, NULL, NULL);

            cout << "Course #3 removed.\n\n";

            break;
        case 4:

            removeRoster = "UPDATE INSTRUCTOR SET CLASS4 = NULL WHERE ID = '" + instID + "'";
            execute = sqlite3_exec(DB, removeRoster.c_str(), callback, NULL, NULL);

            cout << "Course #4 removed.\n\n";

            break;
        default:
            break;
        }


    }

    void printRoster(sqlite3* DB)
    {
        string userID = "";

        cout << "Enter the instructor's user ID: ";
        cin >> userID;

        string course1 = "SELECT CLASS1 FROM INSTRUCTOR WHERE ID = " + userID;
        rfc = sqlite3_exec(DB, course1.c_str(), callback, NULL, NULL);

        string course2 = "SELECT CLASS2 FROM INSTRUCTOR WHERE ID = " + userID;
        rfc = sqlite3_exec(DB, course2.c_str(), callback, NULL, NULL);

        string course3 = "SELECT CLASS3 FROM INSTRUCTOR WHERE ID = " + userID;
        rfc = sqlite3_exec(DB, course3.c_str(), callback, NULL, NULL);

        string course4 = "SELECT CLASS4 FROM INSTRUCTOR WHERE ID = " + userID;
        rfc = sqlite3_exec(DB, course4.c_str(), callback, NULL, NULL);

    }

    instructor_c(std::string fName, std::string lName, std::string inD) :user_c(fName, lName, inD) {}

};


#endif