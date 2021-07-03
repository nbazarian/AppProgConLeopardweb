#ifndef INSTRUCTOR_H
#define INSTRUCTOR_H

#include "user.h"


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

    void addToRoster(sqlite3* DB)
    {
        cout << "Instructors can teach a maximum of 4 courses a semester." << endl;

        for (int i = 0; i < 4; i++)
        {
            do
            {
                cout << "Enter the CRN of course #" << i + 1 << " in the instructor's roster: ";
                cin >> roster[i];
                cout << "Continue adding courses? (1 for yes, 0 for no): ";
                cin >> addMore;

            } while (addMore == 1);
        }

        std::string rosterString = "UPDATE INSTRUCTOR("
            "SET CLASS1 = " + roster[0] + ","
            "SET CLASS2 = " + roster[1] + ","
            "SET CLASS3 = " + roster[2] + ","
            "SET CLASS4 = " + roster[3] + ");";

        rfc = sqlite3_exec(DB, rosterString.c_str(), callback, NULL, NULL);
    }
    void printRoster(sqlite3* DB)
    {
        string userID = "";

        cout << "Enter the instructor's user ID: ";
        cin >> userID;

        string course1 = "SELECT CLASS1 FROM INSTRUCTOR WHERE ID = " + userID;
        cout << "\n" << course1 << "\n";
        rfc = sqlite3_exec(DB, course1.c_str(), callback, NULL, NULL);

        string course2 = "SELECT CLASS2 FROM INSTRUCTOR WHERE ID = " + userID;
        cout << "\n" << course2 << "\n";
        rfc = sqlite3_exec(DB, course2.c_str(), callback, NULL, NULL);

        string course3 = "SELECT CLASS3 FROM INSTRUCTOR WHERE ID = " + userID;
        cout << "\n" << course3 << "\n";
        rfc = sqlite3_exec(DB, course3.c_str(), callback, NULL, NULL);

        string course4 = "SELECT CLASS4 FROM INSTRUCTOR WHERE ID = " + userID;
        cout << "\n" << course4 << "\n";
        rfc = sqlite3_exec(DB, course4.c_str(), callback, NULL, NULL);

    }

    instructor_c(std::string fName, std::string lName, std::string inD) :user_c(fName, lName, inD) {}

};


#endif