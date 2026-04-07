#include<iostream>
#include<cstdlib>

#include "ui/Display.h"
#include "service/StudentService.h"
using namespace std;

int main(){
    string DatabaseFilePath = "./install/storage";
    string DatabaseFileName = "Student_Database.txt";
    StudentService service(DatabaseFilePath, DatabaseFileName);
    int choice;
    Menu:
    cout << "----------------------------------------------------------------------------------------" << endl;
    cout << printCentre("Student Database Management System", 88) << endl;
    cout << "----------------------------------------------------------------------------------------" << endl;
    cout << "Menu: -" << endl;
    cout << "\t1) Add a Student" << endl;
    cout << "\t2) View All Enrolled Students" << endl;
    cout << "\t3) Search Student" << endl;
    cout << "\t4) Update Student Record" << endl;
    cout << "\t5) Delete a Student" << endl;
    cout << "\t6) Exit Application" << endl;
    cout << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    
switch(choice){
        case 1 : service.AddStudent();
                system("clear");
                goto Menu;
        case 2 : service.DisplayAllStudent();
                system("clear");
                goto Menu;
        case 3 : service.SearchStudent();
                system("clear");
                goto Menu;
        case 4 : service.UpdateStudent();
                system("clear");
                goto Menu;
        case 5 : service.DeleteStudent();
                system("clear");
                goto Menu;
        case 6 : break;
        default : cout << "Ah-Oh! Invalid Option, Please Enter a Valid Option (TRY AGAIN)!" << endl;
                system("clear");
                goto Menu;
    }

    cout << "EXITING APPLICATION..." << endl;
    exit(EXIT_SUCCESS);
}
