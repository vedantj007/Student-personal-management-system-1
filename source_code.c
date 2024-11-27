#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "gsv.admin@gsv.ac.in"
#define PASSWORD "GSV#2028"
#define FILE_NAME "students.csv"
#define USERNAME2 "ADMIN"
#define PASS2 "Password"

// Define a structure for student data
typedef struct {
    char first_name[30];
    char last_name[30];
    char roll_number[20];
    char branch[30];
    char email[50];
    char gender[10];
    char dob[11];
    char blood_group[5];
    char medical_condition[100];
    int em_i; 
    int ep; 
    int cp;
    int im_c;
    int irse;
} Student;

// Function prototypes
void authenticate();
void view_records();
void add_student();
void find_student();
void delete_student();
void update_student();
int is_authenticated();
void print_headers();
void print_student(const Student *student);

void main() {
    authenticate();

    int choice;
    while (1) {
        printf("\n\t**Student Personal Record Management System**\n");
        printf("1. Add Student Details\n");
        printf("2. Find Student Details\n");
        printf("3. Delete Student Details\n");
        printf("4. Update Student Details\n");
        printf("5. View Student Records\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                add_student(); 
                break;
            case 2: 
                find_student(); 
                break;
            case 3:
                if (is_authenticated()) delete_student();
                break;
            case 4:
                if (is_authenticated()) update_student();
                break;
            case 5: 
                view_records(); 
                break;
            case 6: 
                printf("Exiting...");
                exit(0);
            default: 
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Authentication at the start
void authenticate() {
    char input_username[50], input_password[20];
    printf("Enter Username: ");
    scanf("%s", input_username);
    printf("Enter Password: ");
    scanf("%s", input_password);
    if (strcmp(input_username, USERNAME) != 0 || strcmp(input_password, PASSWORD) != 0) {
        printf("Authentication failed. Exiting...\n");
        exit(1);
    } else {
        printf("Authentication successful.\n");
        printf("\n\t\t\t**WELCOME TO**");
    }
}

// Additional authentication for update and delete actions
int is_authenticated() {
    char input_username[50], input_password[20];
    printf("Enter Username: ");
    scanf("%s", input_username);
    printf("Enter Password: ");
    scanf("%s", input_password);

    if(strcmp(input_username, USERNAME2) == 0 && strcmp(input_password, PASS2) == 0){
        printf("Authentication Succesfull.\n");
        return 1;
    } else {
        printf("Incorrect Credentials. Going Back to Main Menu...\n");
        return 0;
    }
}

// Add a new student record
void add_student() {
    FILE *file = fopen(FILE_NAME, "a");

    if (file==NULL) {
        perror("Error opening file to add student");
        return;
    }
    char first_name[30], last_name[30], roll_number[20], branch[30], email[50], gender[10], dob[11], blood_group[5], med_cond[100];
    int em_i, ep, cp, im_c, irse;

    printf("Enter First Name: ");
    scanf("%s", first_name);
    printf("Enter Last Name: ");
    scanf("%s", last_name);
    printf("Enter Roll Number: ");
    scanf("%s", roll_number);
    printf("Enter Branch: ");
    scanf("%s", branch);
    printf("Enter Gender (M:Male/F:Female/O:Other): ");
    scanf("%s", gender);
    printf("Enter Date of Birth (DD/MM/YYYY): ");
    scanf("%s", dob);
    printf("Enter Blood Group: ");
    scanf("%s", blood_group);
    printf("Enter Medical Condition(N/A for none): ");
    scanf(" %[^\n]", med_cond);  // Read multi-word input

    // Generate email automatically

    strcpy(email, first_name);
    strcat(email, ".");
    strcat(email, last_name);
    strcat(email, "_btech24@gsv.ac.in");

    // Prompt for attendance
    printf("Enter EM-I Attendance: ");
    scanf("%d", &em_i);
    printf("Enter EP Attendance: ");
    scanf("%d", &ep);
    printf("Enter CP Attendance: ");
    scanf("%d", &cp);
    printf("Enter IM&C Attendance: ");
    scanf("%d", &im_c);
    printf("Enter IRSE Attendance: ");
    scanf("%d", &irse);

    // Write new student data to file
    fprintf(file, "\n%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%d,%d,%d,%d\n",
            first_name, last_name, roll_number, branch, email, gender, dob, blood_group,med_cond,
            em_i, ep, cp, im_c, irse);

    fclose(file);
    printf("Student added successfully. Going Back to Main Menu...\n");
}

// Function to print the table header
void print_header() {
    printf("\n%-15s %-15s %-15s %-10s %-38s %-15s %-13s %-5s %-10s %-5s %-5s %-5s %-5s %-5s\n",
           "First Name", "Last Name", "Roll No", "Branch", "Email", "Gender", "DOB", "B.G",
           "Medical Cond.   Attendance in:", "EM-I", "EP", "CP", "IM&C", "IRSE");
    printf("==================================================================================================================================================================================================\n");
}

// Function to print a single student's record
void print_student(const Student *student) {
    printf("%-15s %-15s %-15s %-10s %-38s %-15s %-13s %-5s %-31s %-5d %-5d %-5d %-5d %-5d\n",
           student->first_name, student->last_name, student->roll_number, student->branch, student->email,
           student->gender, student->dob, student->blood_group, student->medical_condition,
           student->em_i, student->ep, student->cp, student->im_c, student->irse);
}

// Function to view all student records
void view_records() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file==NULL) {
        perror("Error opening file to view records");
        return;
    }

    Student student;
    char line[512];

    // Print header
    print_header();

    // Print each student record
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%d,%d,%d,%d",
                   student.first_name, student.last_name, student.roll_number, student.branch, student.email,
                   student.gender, student.dob, student.blood_group, student.medical_condition,
                   &student.em_i, &student.ep, &student.cp, &student.im_c, &student.irse) == 14) {
            print_student(&student);
        }
    }

    fclose(file);
}

// Function to find and print student details by criteria
void find_student() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file==NULL) {
        perror("Error opening file to find student");
        return;
    }

    Student student;
    char line[512];
    int choice;
    char search_term[50];
    int found = 0;

    printf("\nSearch by:\n1. Roll Number\n2. First Name\n3. Branch\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    printf("Enter search term: ");
    scanf("%s", search_term);

    // Print header
    print_header();

    // Search for matching records
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%d,%d,%d,%d",
                   student.first_name, student.last_name, student.roll_number, student.branch, student.email,
                   student.gender, student.dob, student.blood_group, student.medical_condition,
                   &student.em_i, &student.ep, &student.cp, &student.im_c, &student.irse) == 14) {
            if ((choice == 1 && strcmp(student.roll_number, search_term) == 0) ||
                (choice == 2 && strcmp(student.first_name, search_term) == 0) ||
                (choice == 3 && strcmp(student.branch, search_term) == 0)) {
                print_student(&student);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("\nNo matching records found. Going Back to Main Menu...\n");
    }

    fclose(file);
}
// Delete a student record by Roll Number
void delete_student() {
    FILE *file = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.csv", "w");

    if (file==NULL || !temp) {
        perror("Error opening file to delete student");
        return;
    }

    char roll_number[20];
    printf("\nEnter Roll Number to delete: ");
    scanf("%s", roll_number);

    char line[1024];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        char current_roll[20];
        sscanf(line, "%*[^,],%*[^,],%[^,]", current_roll);

        if (strcmp(current_roll, roll_number) == 0) {
            found = 1;
            printf("Deleted student with Roll Number %s\n", roll_number);
            printf("Going Back to Main Menu...\n\n");
        } else {
            fputs(line, temp);
        }
    }

    fclose(file);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.csv", FILE_NAME);

    if (!found) {
        printf("No student found with Roll Number %s\n", roll_number);
        printf("Going Back to Main Menu...\n\n");
    }
}

// Update a student's details by Roll Number
void update_student() {
    FILE *file = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.csv", "w");
    if (file==NULL || !temp) {
        perror("Error opening file to update student");
        return;}

    char roll_number[20], line[1024];
    int found = 0;
    printf("\nEnter Roll Number to update: ");
    scanf("%s", roll_number);

    // Loop through the CSV file and allow field updates
    while (fgets(line, sizeof(line), file)) {
        int em_i, ep, cp, im_c, irse;
        char first_name[30], last_name[30], current_roll[20], branch[30], email[50], gender[10], date_of_birth[11], blood_group[5], medical_condition[100];
        
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%d,%d,%d,%d",
               first_name, last_name, current_roll, branch, email, gender, date_of_birth, blood_group, medical_condition,
               &em_i, &ep, &cp, &im_c, &irse);
        if (strcmp(current_roll, roll_number) == 0) {
            found = 1;
            int choice;
            // Continuously prompt for fields to update until user chooses to exit

            do {
                printf("\nSelect the field to update:\n");
                printf("1. First Name\n2. Last Name\n3. Branch\n4. Email ID\n5. Gender\n");
                printf("6. Date of Birth\n7. Blood Group\n8. Medical Condition\n9. EM-I Attendance\n");
                printf("10. EP Attendance\n11. CP Attendance\n12. IM&C Attendance\n13. IRSE Attendance\n14. Exit and Save Changes\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);
                switch (choice) {
                    case 1: 
                        printf("Enter new First Name: "); 
                        scanf("%s", first_name); 
                        break;
                    case 2: 
                        printf("Enter new Last Name: "); 
                        scanf("%s", last_name); 
                        break;
                    case 3:    
                        printf("Enter new Branch: "); 
                        scanf("%s", branch); 
                        break;
                    case 4:    
                        printf("Enter new Email ID: "); 
                        scanf("%s", email); 
                        break;
                    case 5: 
                        printf("Enter new Gender (M/F/O): "); 
                        scanf("%s", gender); 
                        break;
                    case 6: 
                        printf("Enter new Date of Birth (DD/MM/YYYY): "); 
                        scanf("%s", date_of_birth); 
                        break;
                    case 7: 
                        printf("Enter new Blood Group: "); 
                        scanf("%s", blood_group); 
                        break;
                    case 8: 
                        printf("Enter new Medical Condition(N/A for none): "); 
                        scanf("%s", medical_condition); 
                        break;
                    case 9: 
                        printf("Enter new EM-I Attendance: "); 
                        scanf("%d", &em_i); 
                        break;
                    case 10: 
                        printf("Enter new EP Attendance: "); 
                        scanf("%d", &ep); 
                        break;
                    case 11: 
                        printf("Enter new CP Attendance: "); 
                        scanf("%d", &cp); 
                        break;
                    case 12: 
                        printf("Enter new IM&C Attendance: "); 
                        scanf("%d", &im_c); 
                        break;
                    case 13: 
                        printf("Enter new IRSE Attendance: "); 
                        scanf("%d", &irse); 
                        break;
                    case 14: 
                        break;  // Exit and save changes
                    default: 
                        printf("Invalid choice. Please try again.\n"); 
                        break;
                }
            } while (choice != 14);

            // Write the updated record to the temp file
            fprintf(temp, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%d,%d,%d,%d\n",
                    first_name, last_name, current_roll, branch, email, gender, date_of_birth,
                    blood_group, medical_condition, em_i, ep, cp, im_c, irse);
        } else {
            // If no update, just write the current record as is to the temp file
            fputs(line, temp);
        }
    }
    fclose(file);
    fclose(temp);

    // Replace the original file with the updated file only if data was updated
    if (found) {
        remove(FILE_NAME);
        rename("temp.csv", FILE_NAME);
        printf("Student record updated successfully.\nGoing Back to Main Menu...\n");
    } else {
        // If no record was updated, just delete the temp file
        remove("temp.csv");
        printf("No records found to update.\nGoing Back to Main Menu...\n");
    }
}
