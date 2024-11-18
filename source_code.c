#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define USERNAME "student.administration@gsv.ac.in"
#define PASSWORD "GSV#2028"
#define FILE_NAME "students.csv"

// Function prototypes
void authenticate();
void view_records();
void add_student();
void find_student();
void delete_student();
void update_student();
int is_authenticated();

void main() {
    authenticate();

    int choice;
    while (1) {
        printf("\nStudent Management System\n");
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
    }
}

// Additional authentication for update and delete actions
int is_authenticated() {
    char input_username[50], input_password[20];
    printf("Re-enter Username: ");
    scanf("%s", input_username);
    printf("Re-enter Password: ");
    scanf("%s", input_password);

    return (strcmp(input_username, USERNAME) == 0 && strcmp(input_password, PASSWORD) == 0);
}

// Add a new student record
void add_student() {
    FILE *file = fopen(FILE_NAME, "a");

    if (!file) {
        perror("Error opening file to add student");
        return;
    }
    char first_name[30], last_name[30], roll_number[20], branch[30], email[50], gender[10], dob[11], blood_group[5], med_cond[100];
    int em_i, ep, cp, im_c, irse, avg_attendance;

    printf("Enter First Name: ");
    scanf("%s", first_name);
    printf("Enter Last Name: ");
    scanf("%s", last_name);
    printf("Enter Roll Number: ");
    scanf("%s", roll_number);
    printf("Enter Branch: ");
    scanf("%s", branch);
    printf("Enter Gender: ");
    scanf("%s", gender);
    printf("Enter Date of Birth (YYYY-MM-DD): ");
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

    // Calculate average attendance
    avg_attendance = (em_i + ep + cp + im_c + irse) / 5;

    // Write new student data to file
    fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d\n",
            first_name, last_name, roll_number, branch, email, gender, dob, blood_group,med_cond,
            avg_attendance, em_i, ep, cp, im_c, irse);

    fclose(file);
    printf("Student added successfully.\n");
}

// View all student records
void view_records() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        perror("Error opening file to view records");
        return;
    }

    char line[1024];
    printf("All Student Records:\n");
    printf("--------------------------------------------------------------------------------------------------------------------------------\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}

// Find a student by Roll Number, First Name, or Branch
void find_student() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        perror("Error opening file to find student");
        return;
    }

    int choice;
    printf("Search by:\n1. Roll Number\n2. First Name\n3. Branch\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    char line[1024], search_term[50];
    int found = 0;

    // Input the search term based on choice
    printf("Enter search term: ");
    scanf("%s", search_term);

    // Read each line in the file and check if it matches the search term
    while (fgets(line, sizeof(line), file)) {
        char first[30], last[30], csv_roll[20], branch[30];
        sscanf(line, "%[^,],%[^,],%[^,],%[^,]", first, last, csv_roll, branch);

        if ((choice == 1 && strcmp(csv_roll, search_term) == 0) ||
            (choice == 2 && strcmp(first, search_term) == 0) ||
            (choice == 3 && strcmp(branch, search_term) == 0)) {
            printf("%s", line);
            found = 1;
        }
    }

    if (!found) {
        printf("No matching record found.\n");
    }

    fclose(file);
}

// Delete a student record by Roll Number
void delete_student() {
    FILE *file = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.csv", "w");

    if (!file || !temp) {
        perror("Error opening file to delete student");
        return;
    }

    char roll_number[20];
    printf("Enter Roll Number to delete: ");
    scanf("%s", roll_number);

    char line[1024];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        char current_roll[20];
        sscanf(line, "%*[^,],%*[^,],%[^,]", current_roll);

        if (strcmp(current_roll, roll_number) == 0) {
            found = 1;
            printf("Deleted student with Roll Number %s\n", roll_number);
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
    }
}

// Update a student's details by Roll Number
void update_student() {
    FILE *file = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.csv", "w");
    if (!file || !temp) {
        perror("Error opening file to update student");
        return;}
    char roll_number[20], line[1024];
    int found = 0;
    printf("Enter Roll Number to update: ");
    scanf("%s", roll_number);
    // Loop through the CSV file and allow field updates
    while (fgets(line, sizeof(line), file)) {
        int average_attendance, em_i, ep, cp, im_c, irse;
        char first_name[30], last_name[30], current_roll[20], branch[30], email[50], gender[10], date_of_birth[11], blood_group[5], medical_condition[100];
        
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%d,%d,%d,%d,%d",
               first_name, last_name, current_roll, branch, email, gender, date_of_birth, blood_group, medical_condition,
               &average_attendance, &em_i, &ep, &cp, &im_c, &irse);
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
                        printf("Enter new Gender: "); 
                        scanf("%s", gender); 
                        break;
                    case 6: 
                        printf("Enter new Date of Birth (YYYY-MM-DD): "); 
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
                    case 14: break;  // Exit and save changes
                    default: 
                        printf("Invalid choice. Please try again.\n"); 
                        break;
                }
            } while (choice != 14);

            // Recalculate average attendance after all updates
            average_attendance = (em_i + ep + cp + im_c + irse) / 5;

            // Write the updated record to the temp file
            fprintf(temp, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d\n",
                    first_name, last_name, current_roll, branch, email, gender, date_of_birth,
                    blood_group, medical_condition, average_attendance, em_i, ep, cp, im_c, irse);
        } else {
            // If no update, just write the current record as is to the temp file
            fputs(line, temp);
        }}
    fclose(file);
    fclose(temp);

    // Replace the original file with the updated file only if data was updated
    if (found) {
        remove(FILE_NAME);
        rename("temp.csv", FILE_NAME);
        printf("Student record updated successfully.\n");
    } else {
        // If no record was updated, just delete the temp file
        remove("temp.csv");
        printf("No records found to update.\n");
    }
}
