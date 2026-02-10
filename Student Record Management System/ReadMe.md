# 🏫 School Management System (C Language)

A **complete, menu-driven School Management System** developed in **C language**, designed to manage **students, teachers, parents, academics, classes, subjects, and results** using **file handling**.

This project runs entirely in the **terminal/command line**, stores data persistently in files, and does **not use any database**, making it lightweight, fast, and perfect for demonstrating **core C programming skills**.

---

## 📌 Project Overview

The **School Management System** simulates how a real school operates digitally.  
It is built with **three role-based dashboards**, ensuring proper access control and clean separation of responsibilities.

### 🎯 Key Goals of the Project
- Manage school records efficiently
- Maintain persistent data using files
- Implement real-world logic using C
- Demonstrate structured and modular programming
- Handle errors and invalid input safely

---

## 🧠 Dashboards Included

1. 🎓 **Student Dashboard**
2. 👩‍🏫 **Teacher Dashboard**
3. 👨‍👩‍👧 **Parent Dashboard**

Each dashboard provides **specific features** based on the role.

---

## 🛠️ Technology Stack

### 🔧 Language & Tools
- **Programming Language:** C
- **Compiler:** GCC
- **Platform:** Terminal / Command Line

### 🧠 Concepts Used
- Structures (`struct`)
- File Handling (`fopen`, `fread`, `fwrite`, `fseek`, `rewind`)
- Modular Programming
- Menu-Driven Architecture
- Input Validation
- Searching & Filtering
- String Manipulation
- Temporary File Technique (Safe Update/Delete)

---

## 📂 File Handling & Storage

All data is stored in **binary `.dat` files**.

| File Name | Description |
|---------|------------|
| `Student_information.dat` | Student personal details |
| `Student_academic.dat` | Student academic & result data |
| `Teacher_information.dat` | Teacher personal details |
| `Teacher_Academic.dat` | Teacher professional & academic data |
| `temp.dat` | Temporary file for safe update/delete |

📌 If a file does not exist, the program **creates it automatically**.

---

## 🎓 Student Dashboard – Features (In Order)

1. **Add Student Personal Information**
   - Name, DOB, gender, caste
   - Address & contact details
   - Auto-generated registration number
   - Auto-generated school email ID

2. **Add Student Academic Information**
   - Class & section assignment
   - Stream selection (Class 11–12)
   - Subject allocation

3. **View Student Academic Details**
   - Class, section, stream, subjects

4. **Update Student Information**
   - Name, address, contact details
   - Safe update using temp files

5. **View All Students**
   - Display all student records

6. **View Courses Under Student**
   - Subjects based on class & stream

7. **Search Student**
   - By name
   - By registration number
   - By school email
   - By personal email
   - By mobile number

8. **View Student Result**
   - Subject-wise marks
   - Total, percentage
   - Pass/Fail status

9. **Count Total Students**
   - By class
   - By section
   - Entire school count

10. **Delete Student Record**
    - Deletes both personal & academic data safely

---

## 👩‍🏫 Teacher Dashboard – Features (In Order)

1. **Add Teacher Personal Information**
   - Name, DOB, gender, caste
   - Contact & address
   - Auto-generated registration number
   - Auto-generated school email ID

2. **Add Teacher Professional Information**
   - Designation (PRT / TGT / PGT)
   - Employment type (Permanent / Contract / Visiting)
   - Qualification & specialization
   - Teaching level
   - Subjects taught
   - Preferred classes

3. **Update Teacher Information**
   - Personal details
   - Professional details
   - Subjects & class preferences

4. **View All Teachers**
   - Displays teacher list with registration numbers

5. **View Student Under Teacher**
   - Shows only students assigned to that teacher

6. **View Courses Under Teacher**
   - Subjects taught by teacher

7. **View Total Students Under Teacher**
   - Count of students assigned

8. **View Classes Under Teacher**
   - Classes handled by teacher

9. **Assign New Class**
   - Dynamically add new classes

10. **Search Teacher**
    - By name
    - By registration number
    - By school email

11. **View Student Result Under Teacher**
    - Access limited to assigned students only

12. **Add Student Result**
    - Subject-wise marks entry
    - Automatic total & percentage calculation

---

## 👨‍👩‍👧 Parent Dashboard – Features

1. **View Student Details**
   - Personal & academic information

2. **View Student Result**
   - Marks, percentage, pass/fail status

3. **Update Student Details**
   - Address & contact information

4. **Remove Student**
   - Delete student record with confirmation

---

## 🔐 Security & Validation Features

- Prevents invalid class, section, marks
- Blocks duplicate registration numbers
- Teacher can access **only assigned students**
- Safe update & delete using `temp.dat`
- Handles missing files gracefully
- Prevents program crash on wrong input

---

## 📊 Result System

- Subject-wise marks entry
- Automatic total calculation
- Percentage calculation
- Pass/Fail status generation

---

## ▶️ How to Compile & Run

```bash
gcc student.c -o student
./student
