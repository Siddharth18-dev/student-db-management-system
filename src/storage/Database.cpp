#include<iostream>
#include<fstream>
#include<filesystem>
#include "Database.h"
#include "../ui/Display.h"

void Database::createFileWithDir() {
    std::filesystem::path dirPath(filePath);
    std::filesystem::path fullPath = dirPath / fileName;

    if (!dirPath.empty() && !std::filesystem::exists(dirPath)) {
        std::filesystem::create_directories(dirPath);
    }

    if (!std::filesystem::exists(fullPath)) {
        std::ofstream file(fullPath);
    }
}

Database::Database(const std::string& filePath, const std::string& fileName){
    this -> filePath = filePath;
    this -> fileName = fileName;
    if(!std::filesystem::exists(filePath + "/" + fileName)){
        createFileWithDir();
        std::ofstream file(filePath + "/" + fileName);
        if(file.is_open()){
            file << "=======================================================================================" << std::endl;
            file << "||" << printCentre("STUDENT DATABASE MANAGEMENT SYSTEM", 84) << "||" << std::endl;
            file << "=======================================================================================" << std::endl;
            file << "|| Roll Number |  Name                       |  Branch   | Class | Course Name        ||" << std::endl;
            file << "=======================================================================================" << std::endl;
        } else {
            std::cout << "DATABASE FILE OPENING ISSUE" << std::endl;
        }
    }
}

void Database::DisplayStudents() const {
    std::string line = "";
    ifstream file(filePath + "/" + fileName);
    if(file.is_open()){
        while(getline(file, line)){
            std::cout << line << std::endl;
        }
        file.close();
    }
}

std::vector<std::string> Database::Search(const std::string& key){
    ifstream file(filePath + "/" + fileName);
    std::string line = "";
    std::vector<std::string> linesFound;

    if(file.is_open()){
        while(getline(file, line)){
            if(line.find(key) != std::string::npos){
                linesFound.push_back(line);
            }
        }
        file.close();
    }
    return linesFound;
}

bool Database::Save(const std::string& line){
    ofstream file(filePath + "/" + fileName, ios::app);
    if(file.is_open()){
        file << line << std::endl;
        file << "---------------------------------------------------------------------------------------" << std::endl;
        file.close();
    } else
        return false;
    return true;
}

bool Database::Update(const std::string& key, const std::vector<std::string>& updatedLines){
    ifstream file(filePath + "/" + fileName);
    ofstream tempFile(filePath + "/tempFile.txt");
    std::string line = "";
    int lineNo = 0;

    if(file.is_open() && tempFile.is_open()){
        while(getline(file, line)){
            if(!(line.find(key) != std::string::npos)){
                tempFile << line << std::endl;
            } else {
                tempFile << updatedLines[lineNo++] << std::endl;
            }
        }
        file.close();
        tempFile.close();
        std::filesystem::remove(filePath + "/" + fileName);
        std::filesystem::rename(filePath + "/tempFile.txt", filePath + "/" + fileName);
    } else
        return false;
    return true;
}

bool Database::Delete(const std::string& key){
    ifstream file(filePath + "/" + fileName);
    ofstream tempFile(filePath + "/tempFile.txt");
    std::string line = "";
    bool skipLine = false;

    if(file.is_open() && tempFile.is_open()){
        while(getline(file, line)){
            if(skipLine){
                skipLine = false;
                continue;
            }
            if(!(line.find(key) != std::string::npos)){
                tempFile << line << std::endl;
            } else {
                skipLine = true;
            }
        }
        file.close();
        tempFile.close();
        std::filesystem::remove(filePath + "/" + fileName);
        std::filesystem::rename(filePath + "/tempFile.txt", filePath + "/" + fileName);
    } else
        return false;
    return true;
}