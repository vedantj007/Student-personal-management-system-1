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
int get_next_serial_number();

int main() {
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
    return 0;
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
