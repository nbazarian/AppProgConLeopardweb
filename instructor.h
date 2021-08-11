#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include "user.h"
#include <string>


using namespace std;

class instructor_c : public user_c
{
public:

    void printAll()
    {
        print();
    }

    int addMore = 0;
    string roster[];


    void printRoster(sqlite3* DB, string userID)
    {

        sqlite3_stmt* stmt;

        string statement, query;
        int rc, rfc;
        string temp[5];
        string courses[5] = { "COURSE1", "COURSE2", "COURSE3", "COURSE4", "COURSE5" };

        for (int i = 0; i < 5; i++)
        {
            statement = "SELECT " + courses[i] + " FROM INSTRUCTOR WHERE ID = '" + userID + "'";
            rc = sqlite3_prepare_v2(DB, statement.c_str(), statement.length(), &stmt, NULL);

            while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
                temp[i] = (char*)sqlite3_column_text(stmt, 0);
            }
        }

        cout << "\n\n\n==== Instructor Roster ====\n\n";

        for (int i = 0; i < 5; i++)
        {
            query = "SELECT TITLE, TIME, DAYS, CRN FROM COURSE WHERE CRN = '" + temp[i] + "';";
            cout << endl;
            rfc = sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);
        }


    }

    void searchRoster(sqlite3* DB, string userID)
    {
        int rc, rfc, select;
        string CRN, statement, query, currentValue, exitPrompt;
        string temp[5];
        string courses[5] = { "COURSE1", "COURSE2", "COURSE3", "COURSE4", "COURSE5" };
        bool matchFound = false, cont = true;;

        sqlite3_stmt* stmt;

        printRoster(DB, userID);
        cout << endl << endl;

        while (cont == true)
        {
            cout << "\n\n========================\n\nEnter the CRN of the course you would like to search for: ";
            cin >> CRN;

            for (int i = 0; i < 5; i++)
            {
                statement = "SELECT " + courses[i] + " FROM INSTRUCTOR WHERE ID = '" + userID + "'";
                rc = sqlite3_prepare_v2(DB, statement.c_str(), statement.length(), &stmt, NULL);

                while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
                    temp[i] = (char*)sqlite3_column_text(stmt, 0);
                }
            }

            for (int i = 0; i < 5; i++)
            {

                if (temp[i] == (CRN))
                {
                    matchFound = true;
                    currentValue = temp[i];
                    query = "SELECT TITLE, TIME, DAYS FROM COURSE WHERE CRN = '" + currentValue + "';";
                    cout << endl;
                    rfc = sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);

                }
            }

            if (matchFound == false)
            {
                cout << "\n\n===== No matches found! =====\n\n";
            }

            cout << "Enter 1 to continue, any other number to return to the menu: ";
            cin >> select;

            if(select != 1)
            {
                cont = false;
            }
        }

        return;
    }


    instructor_c(std::string fName, std::string lName, std::string inD) :user_c(fName, lName, inD) {}

};


#endif