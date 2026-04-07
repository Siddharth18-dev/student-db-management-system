#include "Students.h"

Students::StudentDetails::StudentDetails(int roll, std::string name, std::string branch, std::string Class, std::string course_name){
    Roll_Number = roll;
    Name = name;
    Branch = branch;
    this -> Class = Class;
    Course_Name = course_name;
}

Students::Students() : Student(0, "N/A", "B.Tech", "6-A", "Computer Networks") {}

Students::Students(int Roll_Number, std::string Name, std::string Branch, std::string Class, std::string Course_Name) : Student(Roll_Number, Name, Branch, Class, Course_Name) {}

void Students::setRollNumber(const int& Roll_Number){
    this -> Student.Roll_Number = Roll_Number;
}

void Students::setName(const std::string& Name){
    this -> Student.Name = Name;
}

void Students::setBranch(const std::string& Branch){
    this -> Student.Branch = Branch;
}

void Students::setClass(const std::string& Class){
    this -> Student.Class = Class;
}

void Students::setCourse_Name(const std::string& Course_Name){
    this -> Student.Course_Name = Course_Name;
}

int Students::getRollNumber() const {
    return Student.Roll_Number;
}

std::string Students::getName() const {
    return Student.Name;
}

std::string Students::getBranch() const {
    return Student.Branch;
}

std::string Students::getClass() const {
    return Student.Class;
}

std::string Students::getCourse_Name() const {
    return Student.Course_Name;
}