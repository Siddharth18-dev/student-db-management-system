#ifndef STUDENTSERVICE_H
#define STUDENTSERVICE_H

#include "../model/Students.h"
#include<vector>
#include<string>

class StudentService {
    public:
        StudentService(const std::string& DatabaseFilePath, const std::string& DatabaseFileName);

        void AddStudent();
        void SearchStudent();
        void UpdateStudent();
        void DeleteStudent();
        void DisplayAllStudent();

    private:
        std::string DatabaseFilePath;
        std::string DatabaseFileName;

        bool SaveDatabase(Students& Student);
        void UpdateEachRecord(Students& Student);
        std::vector<std::string> SearchAndDisplayRecord(const std::string& key);
        std::vector<std::vector<std::string>> StudentDetails(const std::vector<std::string>& List);
        void MakeChange(std::vector<std::vector<std::string>>& AllStudentDetails,
                        int updatedColumn, 
                        std::string updatedValue);
        std::string FormatDetail(std::vector<std::string> StudentDetail);
        bool UpdateDatabase(const std::string& key, 
                            const std::vector<std::string>& EachStudentDetail);
        bool DeleteRecord(const std::string& key);
};

#endif