# 🎓 Student Record Management System (C)

This is a menu-driven student record system built in C. It runs straight from the terminal, handles all your data in files, and skips databases entirely. The whole idea is to show off some core C skills—think file handling, solid logic, and tidy structure.


## 🚀 Project Overview

Right out of the box, you can manage student records and keep them safe in a file—no data disappears when you close the program. It covers all the basics: add, view, update, and delete records. You can search, sort, get stats, and the program takes care of mistakes so you don’t have to worry about breaking anything. It’s a full-featured C project—perfect for your resume or talking points in an interview.



## 🛠️ Tech Stack

- **Language:** C
- **Key Concepts:**
  - Structures
  - File handling
  - Modular functions
  - Conditionals and loops
  - String handling
  - Sorting and searching
  - Input checks and error management


## ✨ Features

### 🔹 Core Features

- Add new student records
- View all records at once
- Search for students by ID or name
- Update details for existing students
- Delete records if you need to
- Exit the program safely


### 🔹 Advanced Search & Operations

- Find students by course, class, or section
- Get the total student count
- Sort records by ID, name, or marks


### 🔹 Statistics

- See the average marks
- Find out who scored highest and lowest


### 🔹 Data Integrity & Error Handling

- Checks to block duplicate IDs or empty/invalid fields
- Handles file errors, missing records, or bad input without crashing


## 📂 File Handling Details

- All records go into `students.txt`
- If the file’s missing, the program just creates it
- Data sticks around between sessions—no need to re-enter every time
- File handling stands in for a database, but keeps things light and simple
