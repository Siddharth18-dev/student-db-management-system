#include "StudentService.h"
#include "../storage/Database.h"
#include "../ui/Display.h"
#include "../ui/Colors.h"
#include<limits>
#include<iostream>

StudentService::StudentService(const std::string& DatabaseFilePath, const std::string& DatabaseFileName){
    this -> DatabaseFilePath = DatabaseFilePath;
    this -> DatabaseFileName = DatabaseFileName;
}

void StudentService::AddStudent(){
    system("clear");
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int S_roll;
    int choice;
    std::string S_Name;
    std::string S_Branch;
    std::string S_Class;
    std::string S_CourseName;

    cout << "--------------------------------------------------------------------------" << endl;
    cout << printCentre("Student Addition Page", 74) << endl;
    cout << "--------------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "Enter Student Name: ";
    getline(cin, S_Name);
    cout << "Enter Roll Number: ";
    cin >> S_roll;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter Branch: ";
    getline(cin, S_Branch);
    cout << "Enter Class: ";
    getline(cin, S_Class);
    cout << "Enter Course Name: ";
    getline(cin, S_CourseName);

    Students Student(S_roll, S_Name, S_Branch, S_Class, S_CourseName);
    Header();
    DisplayEachRecord(Student);

    cout << endl;
    cout << "1) Save Student and Return to Main Menu?" << endl;
    cout << "2) Update any component?" << endl;
    cout << "3) Exit Without Saving?" << endl;
    Menu:
    cout << "Enter Your Choice: ";
    cin >> choice;

    switch(choice){
        case 1: if(!SaveDatabase(Student)){
                    cout << RED << "DATABASE ERROR" << RESET << endl;
                    exit(EXIT_FAILURE);
                } else
                    return;
                break;
        case 2: UpdateEachRecord(Student);
                cout << "Saving Your changes to Student Database" << endl;
                SaveDatabase(Student);
                break;
        case 3: break;
        default: cout << YELLOW << "Ah-Oh! Invalid Option, Please Try Again!" << RESET << endl;
                goto Menu;
    }
    return;
}

void StudentService::SearchStudent() {
    system("clear");
    std::string choice;
    std::string key;

    cout << "----------------------------------------------------------------------------------------" << endl;
    cout << printCentre("Student Searching System", 88) << endl;
    cout << "----------------------------------------------------------------------------------------" << endl;
    Menu:
    cout << "Enter Searching Key: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, key);

    SearchAndDisplayRecord(key);

    cout << "Search Again(Y/N)? ";
    cin >> choice;
    if(choice == "yes" || choice == "Y" || choice == "Yes" || choice == "y") goto Menu;
    else{
        cout << "Press 'M + Enter' to return to Main Menu ";
        cin >> choice;
        return;
    }
}

void StudentService::UpdateStudent() {
    system("clear");
    int choice;
    std::string updatedValue;
    std::string key;
    std::vector<std::string> EachStudentDetail;

    cout << "----------------------------------------------------------------------------------------" << endl;
    cout << printCentre("Student Record Updation System", 88) << endl;
    cout << "----------------------------------------------------------------------------------------" << endl;
    cout << "Enter Key: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, key);
    cout << YELLOW << RESET << "Kindly check below detail(s): " << endl;

    std::vector<std::vector<std::string>> AllStudentDetails(StudentDetails(SearchAndDisplayRecord(key)));

    if(AllStudentDetails.empty()){
        cout << "Press E to return to main menu: ";
        cin >> key;
        return;
    }

    Menu:
    cout << endl;
    cout << "Which Component do you want to Update? " << endl;
    cout << "\t1) Roll Number" << endl;
    cout << "\t2) Name" << endl;
    cout << "\t3) Branch" << endl;
    cout << "\t4) Class" << endl;
    cout << "\t5) Course Name" << endl;
    cout << "Enter Your choice: ";
    cin >> choice;

    switch(choice){
        case 1: cout << "Enter Updated Roll Number: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, updatedValue);
                MakeChange(AllStudentDetails, 0, updatedValue);
                cout << GREEN << "Roll Number Updated" << RESET << endl;
                break;
        case 2: cout << "Enter Updated Name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, updatedValue);
                MakeChange(AllStudentDetails, 1, updatedValue);
                cout << GREEN << "Name Updated" << RESET << endl;
                break;
        case 3: cout << "Enter Updated Branch: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, updatedValue);
                MakeChange(AllStudentDetails, 2, updatedValue);
                cout << GREEN << "Branch Updated" << RESET << endl;
                break; 
        case 4: cout << "Enter Updated Class: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, updatedValue);
                MakeChange(AllStudentDetails, 3, updatedValue);
                cout << GREEN << "Class Updated" << RESET << endl;
                break;
        case 5: cout << "Enter updated Course Name: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                getline(cin, updatedValue);
                MakeChange(AllStudentDetails, 4, updatedValue);
                cout << GREEN << "Course Name Updated" << RESET << endl;
                break;
        default: cout << "Invalid Option, Try Entering Valid Option" << endl;
                goto Menu;
    }

    for(int i = 0; i < AllStudentDetails.size(); i++){
        EachStudentDetail.push_back(FormatDetail(AllStudentDetails[i]));
    }

    cout << endl;
    cout << "1) Save Updated Student(s) and Return to Main Menu?" << endl;
    cout << "2) Exit Without Saving?" << endl;
    Menu_again:
    cout << "Enter Your Choice: ";
    cin >> choice;

    switch(choice){
        case 1: if(!UpdateDatabase(key, EachStudentDetail)){
                    cout << RED << "DATABASE UPDATE ERROR" << RESET << endl;
                    exit(EXIT_FAILURE);
                } else
                    return;
                break;
        case 2: return;
        default: cout << YELLOW << "Ah-Oh! Invalid Option, Please Try Again!" << RESET << endl;
                goto Menu_again;
    }
}

void StudentService::DeleteStudent() {
    system("clear");
    std::string choice;
    std::string key;
    cout << "----------------------------------------------------------------------------------------" << endl;
    cout << printCentre("Deletion System", 88) << endl;
    cout << "----------------------------------------------------------------------------------------" << endl;
    cout << YELLOW << RESET << "This Deletion System Works by First Searching the user - inputed key, then it deletes, " << endl;
    cout << "the entire record of that Student, if user inputed key matched with any record. " << endl;
    cout <<  endl;
    cout << "Enter Your Key: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, key);

    cout << YELLOW << RESET << "Below Detail(s) are going to be deleted: - " << endl;
    SearchAndDisplayRecord(key);

    cout << "Are you Sure, you want to Delete above record(s) (Y/N) ?: ";
    cin >> choice;
    if(choice == "yes" || choice == "Y" || choice == "Yes" || choice == "y"){
        if(!DeleteRecord(key)){
            cout << RED << RESET << "Deletion of Record(s) failure!" << endl;
            exit(EXIT_FAILURE);
        }
    } else{
        cout << "Press 'E + Enter' to return to Main Menu ";
        cin >> choice;
        return;
    }
}

void StudentService::DisplayAllStudent(){      
    std::string choice;
    Database db(DatabaseFilePath, DatabaseFileName);
    db.DisplayStudents();
    cout << endl << endl;
    cout << "Press 'E + Enter' to return to Main Menu?";
    cin >> choice;
    return;
}

bool StudentService::SaveDatabase(Students& Student) {
    Database db(DatabaseFilePath, DatabaseFileName);
    std::string line = "||" + printCentre(std::to_string(Student.getRollNumber()), 13) + "| " + printLeft(Student.getName(), 28) + "|" + printCentre(Student.getBranch(), 12) + "|" + printCentre(Student.getClass(), 7) + "|" + printLeft(Student.getCourse_Name(), 19) + "||";
    if(!db.Save(line))
        return false;
    return true;    
}

void StudentService::UpdateEachRecord(Students& Student) {
    int choice;
    int Roll_Number;
    std::string Name;
    std::string Branch;
    std::string Class;
    std::string Course_Name;

    Menu:
    cout << endl;
    cout << "Which Component do you want to Update? " << endl;
    cout << "\t1) Roll Number" << endl;
    cout << "\t2) Name" << endl;
    cout << "\t3) Branch" << endl;
    cout << "\t4) Class" << endl;
    cout << "\t5) Course Name" << endl;
    cout << "Enter Your choice: ";
    cin >> choice;
    switch(choice){
        case 1: cout << "Enter Updated Roll Number: ";
                cin >> Roll_Number;
                Student.setRollNumber(Roll_Number);
                cout << GREEN << "Roll Number Updated" << RESET << endl;
                break;
        case 2: cout << "Enter Updated Name: ";
                cin >> Name;
                Student.setName(Name);
                cout << GREEN << "Name Updated" << RESET << endl;
                break;
        case 3: cout << "Enter Updated Branch: ";
                cin >> Branch;
                Student.setBranch(Branch);
                cout << GREEN << "Branch Updated" << RESET << endl;
                break; 
        case 4: cout << "Enter Updated Class: ";
                cin >> Class;
                Student.setClass(Class);
                cout << GREEN << "Class Updated" << RESET << endl;
                break;
        case 5: cout << "Enter updated Course Name: ";
                cin >> Course_Name;
                Student.setCourse_Name(Course_Name);
                cout << GREEN << "Course Name Updated" << RESET << endl;
                break;
        default: cout << "Invalid Option, Try Entering Single Valid Option" << endl;
                goto Menu;
    }

    cout << "Updated Student Record: -" << endl;
    Header();
    DisplayEachRecord(Student);

    std::string option;
    cout << endl;
    cout << "Update More Changes (Y/N)?: ";
    cin >> option;
    if(option == "Y" || option == "y" || option == "yes" || option == "Yes") goto Menu;
    return;
}

std::vector<std::string> StudentService::SearchAndDisplayRecord(const std::string& key){
    Database db(DatabaseFilePath, DatabaseFileName);
    std::vector<std::string> List(db.Search(key));
    if(List.empty()){
        cout << endl;
        cout << YELLOW << RESET << "No Search Record for Key: " << key << endl;
    }

    for(int line = 0; line < List.size(); line++){
        int startIdx = -1, endIdx = 0;
        for(int charachter = 0; charachter < List[line].size(); charachter++){
            if(key.size() == endIdx)
                break;
            if(List[line][charachter] == key[endIdx] && startIdx == -1){
                startIdx = charachter;
                endIdx++;
            } else if(List[line][charachter] == key[endIdx])
                endIdx++;
            else{
                startIdx = -1;
                endIdx = 0;
            }
        }
        HighlightSearchedStudent(List[line], startIdx, endIdx);
    }
    return List;
}

std::vector<std::vector<std::string>> StudentService::StudentDetails(const std::vector<std::string>& List){
    std::vector<std::vector<std::string>> AllStudentDetails;

    for(int line = 0; line < List.size(); line++){
        std::string word = "";
        std::vector<std::string> StudentDetail;
        for(int charachter = 0; charachter < List[line].size(); charachter++){
            if(List[line][charachter] == '|' && word != ""){
                StudentDetail.push_back(word);
                word = "";
            } else if(List[line][charachter] == ' ' && List[line][charachter + 1] != ' ' && List[line][charachter - 1] != ' ' && List[line][charachter - 1] != '|'){
                word += List[line][charachter];
            } else if(List[line][charachter] != ' ' && List[line][charachter] != '|'){
                word += List[line][charachter];
            }
        }
        AllStudentDetails.push_back(StudentDetail);
    }
    return AllStudentDetails;
}

void StudentService::MakeChange(std::vector<std::vector<std::string>>& AllStudentDetails,int updatedColumn, std::string updatedValue){
    for(int i = 0; i < AllStudentDetails.size(); i++){
        AllStudentDetails[i][updatedColumn] = updatedValue;
    }
}

std::string StudentService::FormatDetail(std::vector<std::string> StudentDetail){
    std::string str = "||" + printCentre(StudentDetail[0], 13) + "| " + printLeft(StudentDetail[1], 28) + "|" + printCentre(StudentDetail[2], 12) + "|" + printCentre(StudentDetail[3], 7) + "|" + printLeft(StudentDetail[4], 19) + "||";
    return str;
}

bool StudentService::UpdateDatabase(const std::string& key, const std::vector<std::string>& EachStudentDetail) {
    Database db(DatabaseFilePath, DatabaseFileName);
    if(!db.Update(key, EachStudentDetail)) return false;
    return true;
}

bool StudentService::DeleteRecord(const std::string& key){
    Database db(DatabaseFilePath, DatabaseFileName);
    if(!db.Delete(key)) return false;
    return true;
}
