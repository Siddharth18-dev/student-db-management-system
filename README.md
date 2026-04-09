# 🎓 Student Database Management System (C++)

A modular, file-based **Student Database Management System** built in **C++17**, designed with a layered architecture and enhanced with **unit testing, CI/CD, and production-grade build systems**.

---

## 🚀 Features

* 📌 Add, View, Search, Update, and Delete student records
* 📂 File-based persistent storage system
* 🧱 Layered architecture (UI → Service → Storage → Model)
* ⚙️ Makefile with **Debug & Release builds**
* 🧪 Unit Testing using **Google Test**
* 🔁 Regression-safe testing with test isolation
* 🔄 CI/CD pipeline using **GitHub Actions**
* 📦 Automated build artifacts & versioned releases

---

## 🏗️ Project Structure

```
project/
│
├── src/
│   ├── model/          # Student data structure
│   ├── service/        # Business logic
│   ├── storage/        # File handling (Database)
│   └── ui/             # Display & formatting
│
├── tests/              # Google Test cases
│
├── build/              # Object files (debug/release)
├── install/
│   └── bin/
│       └── storage/    # Runtime database storage
│
├── Makefile
└── README.md
```

---

## 🧠 Architecture Overview

```
UI Layer → Service Layer → Storage Layer → File System
```

* **UI Layer**: Handles user interaction and formatting
* **Service Layer**: Business logic (CRUD operations)
* **Storage Layer**: File-based database handling
* **Model Layer**: Student data representation

---

## ⚙️ Build System

The project uses a **custom Makefile** supporting multiple build configurations:

### 🔴 Debug Build

* Includes debug symbols (`-g`)
* No optimization (`-O0`)

```bash
make BUILD_TYPE=debug
make run
```

### 🟢 Release Build (Default)

* Optimized (`-O2`)

```bash
make
make run
```

### 🧹 Clean Build Files

```bash
make clean
```

---

## 🧪 Testing (Google Test)

Unit tests are implemented for **Database CRUD operations**.

### ▶️ Run Tests

```bash
make test
```

### ✅ Testing Highlights

* Uses **test fixtures (`SetUp`)** to ensure clean state
* Prevents data contamination between tests
* Covers:

  * Save
  * Search
  * Update
  * Delete

---

## 🔄 CI/CD Pipeline

Integrated with **GitHub Actions**:

### 🔁 On Every Push / PR:

* Build project
* Run unit tests
* Validate code

### 📦 CD Features:

* Generate downloadable artifacts
* Create versioned releases (`v1.0.0`)

---

## 📁 Data Storage

* Database stored at:

```
install/bin/storage/Student_Database.txt
```

* Automatically created if not present
* Structured table format with headers

---

## 🧑‍💻 Usage

Run the application:

```bash
make
make run
```

### Menu Options:

1. Add Student
2. View All Students
3. Search Student
4. Update Student
5. Delete Student
6. Exit

---

## 📌 Key Learnings

This project demonstrates:

* Modular software design
* File-based persistence
* Build systems (Makefile)
* Debug vs Release engineering
* Unit & regression testing
* CI/CD automation
* Production-ready workflow

---

## 🚀 Future Improvements

* Add logging system
* Introduce configuration file (remove hardcoded paths)
* Implement dependency injection
* Add mock-based testing
* Convert to REST API (backend service)

---

## 📜 License

This project is open-source and available under the MIT License.

---

## 🙌 Author

**Siddharth Jha**

---

⭐ If you found this project useful, consider giving it a star!
