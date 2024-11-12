# Student Management System

## Features

- **Authentication**: User verification before accessing or modifying student records.

- **Add Student**: Add new student details to the CSV file.

- **Find Student**: Search for a student by roll number, first name, or branch.

- **Delete Student**: Remove a student’s record from the CSV file.

- **Update Student**: Modify a student’s existing details in the CSV file.

- **View All Records**: Display all student records in the console.


## Requirements

- **C Compiler**: GCC or any compatible C compiler.

## Installation

1. Clone or download this repository.
2. Compile the program using a C compiler.

## Usage
On running the program, you will be prompted for a username and password.

Username: student.administration@gsv.ac.in

Password: GSV#2028

Once authenticated, you will have access to the main menu with the following options:

**Add Student Details**: Adds a new student to students.csv. Enter the student's details, including their roll number, first and last name, branch, email, gender, date of birth, blood group, and other relevant information.
**Find Student Details:** Allows searching for a student by roll number, first name, or branch.
**Delete Student Details:** Deletes a student record by roll number. For security, re-authentication is required.
**Update Student Details:** Updates an existing student’s record. Re-authentication is also required for this action.
**View Student Records:** Displays all student records stored in the students.csv file.
**Exit:** Exit the program.

## Security
Authentication: The program requires a username and password for access. This ensures that only authorized users can view or modify records.
Re-authentication: Additional authentication prompts before performing sensitive actions (e.g., deleting or updating records).
