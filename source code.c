#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main() {
    int choice, roll_number;

    while (1) {
        printf("\nStudent Management System\n");
        printf("1. Add the Student Details\n");
        printf("2. Find the Student Details\n");
        printf("3. Delete the Students\n");
        printf("4. Update the Students\n");
        printf("5. To Exit\n");
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
                printf("Enter Roll Number to Delete: ");
                scanf("%d", &roll_number);
                delete_student(roll_number);
                break;
            case 4:
                printf("Enter Roll Number to Update: ");
                scanf("%d", &roll_number);
                update_student(roll_number);
                break;
            case 5:
                save_data_csv();
                printf("Data saved to CSV. Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
