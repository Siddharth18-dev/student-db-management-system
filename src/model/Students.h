#ifndef STUDENTS_H
#define STUDENTS_H

#include<string>

class Students{
    protected:
        struct StudentDetails {
            int Roll_Number;
            std::string Name;
            std::string Branch;
            std::string Class;
            std::string Course_Name;

            StudentDetails(int roll, 
                           std::string name,
                           std::string branch,
                           std::string Class,
                           std::string course_name);
        };

        StudentDetails Student;
    public:
        Students();
        
        Students(int Roll_Number,
                std::string Name,
                std::string Branch,
                std::string Class, 
                std::string Course_Name);

        void setRollNumber(const int& Roll_Number);
        void setName(const std::string& Name);
        void setBranch(const std::string& Branch);
        void setClass(const std::string& Class);
        void setCourse_Name(const std::string& Course_Name);
        
        int getRollNumber() const;
        std::string getName() const;
        std::string getBranch() const;
        std::string getClass() const;
        std::string getCourse_Name() const;
};

#endif