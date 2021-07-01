#include <sqlite3.h>
#include "admin.h"

using namespace std;

int main(void){
sqlite3* DB;
int selection,rfc; 
string input, hold;  
char logout;
char* messageError; 
rfc = sqlite3_open("assignment3.db",&DB);

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



sqlite3_close(DB);
}
