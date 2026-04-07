#include "Display.h"
#include "Colors.h"
#include<iostream>

std::string printLeft(std::string text, int Width){
    int padding = Width - text.length();
    std::string result = "";
    result += text;
    for(int i = 0; i < padding; i++) result += " ";

    return result;
}

std::string printRight(std::string text, int Width){
    int padding = Width - text.length();
    std::string result = "";
    for(int i = 0; i < padding; i++) result += " ";
    result += text;
    return result;
}

std::string printCentre(std::string text, int Width){
    int padding = (Width - text.length()) / 2;
    std::string result = "";
    for(int i = 0; i < padding; i++) result += " ";
    result += text;
    for(int i = 0; i < padding; i++) result += " ";
    return result;
}

void Header(){
    std::cout << std::endl;
    std::cout << "=======================================================================================" << std::endl;
    std::cout << "||" << printCentre("STUDENT DATABASE MANAGEMENT SYSTEM", 84) << "||" << std::endl;
    std::cout << "=======================================================================================" << std::endl;
    std::cout << "|| Roll Number |  Name                       |  Branch   | Class | Course Name        ||" << std::endl;
    std::cout << "=======================================================================================" << std::endl;
    return;
}

void DisplayEachRecord(Students& Student){
    std::string roll_no = std::to_string(Student.getRollNumber());
    std::cout << "||" << printCentre(roll_no, 13) << "| " << printLeft(Student.getName(), 28) << "|" << printCentre(Student.getBranch(), 12) << "|" << printCentre(Student.getClass(), 7) << "|" << printLeft(Student.getCourse_Name(), 19) << "||" << std::endl;
    std::cout << "---------------------------------------------------------------------------------------" << std::endl;
    return;
}

void HighlightSearchedStudent(const std::string& Line, const int& startIdx, const int& endIdx) {
    for(int idx = 0; idx < Line.size(); idx++){
        if(idx == startIdx){
            for(idx; idx <= startIdx + endIdx; idx++){
                std::cout << "\033[32m" << Line[idx] << RESET;
            }
        }
        std::cout << Line[idx];
    }
    std::cout << std::endl;
    std::cout << "----------------------------------------------------------------------------------------" << std::endl;
}