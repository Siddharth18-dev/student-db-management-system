#ifndef DATABASE_H
#define DATABASE_H
#include<string>
#include<vector>
using namespace std;

class Database{
    private:
        std::string fileName;
        std::string filePath;
        void createFileWithDir();
    public:
        Database(const std::string& filePath, const std::string& fileName);

        void DisplayStudents() const;
        std::vector<std::string> Search(const std::string& key);
        bool Save(const std::string& line);
        bool Update(const std::string& key, const std::vector<std::string>& updatedLines);
        bool Delete(const std::string& key);
};

#endif
