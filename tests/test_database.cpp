#include <gtest/gtest.h>
#include <string>
#include <fstream>
#include <cstdio>   // for std::remove
#include "../src/storage/Database.h"

// Helper function to read file
std::string readFile(const std::string& path) {
    std::ifstream file(path);
    std::string content = "", line;

    while (getline(file, line)) {
        content += line + "\n";
    }
    return content;
}

// ================= FIXTURE =================
class DatabaseTest : public ::testing::Test {
protected:
    std::string path = "./tests/storage";
    std::string filename = "Student_Database.txt";
    std::string fullPath = path + "/" + filename;

    void SetUp() override {
        // 🔥 Delete file before each test → ensures clean state
        std::remove(fullPath.c_str());
    }

    void TearDown() override {
        // Optional cleanup (not required since SetUp handles it)
        // std::remove(fullPath.c_str());
    }
};

// ================= TEST CASES =================

// Test Case 1: Save writes to file
TEST_F(DatabaseTest, SaveWritesToFile) {
    Database db(path, filename);

    std::string testLine = "|| New test Student Data ||";

    db.Save(testLine);

    std::string content = readFile(fullPath);

    EXPECT_NE(content.find(testLine), std::string::npos);
}

// Test Case 2: Search finds inserted data
TEST_F(DatabaseTest, SearchFindsInsertedData) {
    Database db(path, filename);

    std::string testLine = "|| UniqueStudent123 ||";

    db.Save(testLine);

    auto results = db.Search("UniqueStudent123");

    EXPECT_FALSE(results.empty());
}

// Test Case 3: Delete removes data
TEST_F(DatabaseTest, DeleteRemovesData) {
    Database db(path, filename);

    std::string testLine = "|| DeleteMe123 ||";

    db.Save(testLine);
    db.Delete("DeleteMe123");

    auto results = db.Search("DeleteMe123");

    EXPECT_TRUE(results.empty());
}

// Test Case 4: Search returns empty if not found
TEST_F(DatabaseTest, SearchReturnsEmptyIfNotFound) {
    Database db(path, filename);

    auto results = db.Search("ThisShouldNotExist");

    EXPECT_TRUE(results.empty());
}

// Test Case 5: Save empty string
TEST_F(DatabaseTest, SaveEmptyString) {
    Database db(path, filename);

    bool result = db.Save("");

    EXPECT_TRUE(result);
}