#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "admin.h"
#include "globals.h"
#include "utils.h"
#include "auth.h"

void AdminLogin() {
    char username[200], password[200];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    int i = 0;
    char ch;
    while((ch = _getch()) != 13 && i < 199) {
        if(ch == 8) {
            if(i > 0) {
                i--;
                printf("\b \b");
            }
        }
        else {
            password[i++] = ch;
            printf("*");
        }
    }
    password[i] = '\0';
    printf("\n");
    getchar();

    if(strcmp(username, AdminUsername) == 0 && strcmp(password, AdminPassword) == 0) {
        int option;
        do {
            system("cls");
            printf("=======+++++****-------------****+++++=======\n");
            printf("                 Admin Panel                 \n");
            printf("=======+++++****-------------****+++++=======\n\n");
            printf("1. View unsorted complaints\n");
            printf("2. View verified complaints\n");
            printf("\n3. Volunteer recruitment\n");
            printf("4. View current volunteers\n");
            printf("5. Write notice for volunteers\n");
            printf("\n6. Change Admin and Volunteer Credentials\n");
            printf("7. Logout\n");
            printf("\n\nChoose an option: \n");
            scanf("%d", &option);

            switch(option) {
                case 1: ViewComplaints(); break;
                case 2: ViewVerifiedComplaints(); break;
                case 3: AddVolunteer(); break;
                case 4: ViewVolunteers(); break;
                case 5: WriteNotice(); break;
                case 6: ChangeCredentials(); break;
                case 7: return;
                default: printf("Please choose a valid option..."); press();
            }
        } while(option != 7);
    } else {
        printf("Invalid username or password. Please try again...\n");
        press();
        return;
    }
}

void ViewComplaints() {
    system("cls");
    printf("=======+++++****-------------****+++++=======\n");
    printf("             Unsorted Complaints             \n");
    printf("=======+++++****-------------****+++++=======\n\n");

    FILE *file = fopen("complaints.txt", "r");
    if(file == NULL) {
        printf("Sorry! No information was found!");
        return;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    if(size == 0) {
        printf("No complaints have been filed yet...\n");
    } else {
        char c;
        while((c = fgetc(file)) != EOF) {
            putchar(c);
        }
    }
    fclose(file);
    press();
}

void ViewVerifiedComplaints() {
    system("cls");
    printf("=======+++++****-------------****+++++=======\n");
    printf("             Verified Complaints             \n");
    printf("=======+++++****-------------****+++++=======\n\n");

    FILE *file = fopen("verified.txt", "r");
    if(file == NULL) {
        printf("Sorry! No information was found!");
        return;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    if(size == 0) {
        printf("No complaints have been filed yet...\n");
    } else {
        char line[200];
        while(fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
    }
    fclose(file);
    press();
}

void NotVerifiedComplaints() {
    system("cls");
    printf("=======+++++****-------------****+++++=======\n");
    printf("         Rejected Complaints Storage         \n");
    printf("=======+++++****-------------****+++++=======\n\n");

    FILE *file = fopen("notverified.txt", "r");
    if(file == NULL) {
        printf("Sorry! No information was found!");
        return;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    if(size == 0) {
        printf("No rejected complaints...\n");
    } else {
        char c;
        while((c = fgetc(file)) != EOF) {
            putchar(c);
        }
    }
    fclose(file);
    press();
}

void AddVolunteer() {
    system("cls");
    printf("=======+++++****-------------****+++++=======\n");
    printf("           Volunteer Applications            \n");
    printf("=======+++++****-------------****+++++=======\n\n");

    FILE *pending = fopen("vpending.txt", "r");
    FILE *approved = fopen("vapproved.txt", "a");

    if(pending == NULL) {
        printf("No pending application available.\n");
        press();
        return;
    }

    if(approved == NULL) {
        printf("Error accessing applications.\n");
        fclose(pending);
        press();
        return;
    }

    int select, id, n = 0;
    char line[200];
    int found = 0;

    while(fgets(line, sizeof(line), pending)) {
        printf("%s", line);
        n = 1;
    }

    if (!n) {
        printf("No application to show.\n");
        fclose(pending);
        fclose(approved);
        press();
        return;
    }
    printf("\nPending applications: \n");

    rewind(pending);

    printf("Select application id (0 to return): ");
    scanf("%d", &select);

    if(select == 0) {
        fclose(pending);
        fclose(approved);
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if(temp == NULL) {
        printf("An unexpected error occurred...");
        fclose(pending);
        fclose(approved);
        press();
        return;
    }

    while(fgets(line, sizeof(line), pending)) {
        if(sscanf(line, "Application serial number: %d", &id) == 1) {
            if(id == select) {
                int choice;
                printf("\n1. Approve\n2. Delete\n3. Deselect and return\nSelect an option: ");
                scanf("%d", &choice);

                if(choice == 3) {
                    fprintf(temp, "%s", line);
                    while(fgets(line, sizeof(line), pending) && line[0] != '-') {
                        fprintf(temp, "%s", line);
                    }
                    fprintf(temp, "---------------------------------------------\n");
                }
                else if(choice == 1) {
                    fprintf(approved, "%s", line);
                    printf("Volunteer added...\n");
                    while(fgets(line, sizeof(line), pending) && line[0] != '-') {
                        fprintf(approved, "%s", line);
                    }
                    fprintf(approved, "---------------------------------------------\n");
                }
                else if(choice == 2) {
                    printf("Application rejected");
                    while(fgets(line, sizeof(line), pending) && line[0] != '-') {
                        // Skip the rejected application
                    }
                }
                else {
                    printf("Invalid option. Please choose again...");
                    fprintf(temp, "%s", line);
                    while(fgets(line, sizeof(line), pending) && line[0] != '-') {
                        fprintf(temp, "%s", line);
                    }
                    fprintf(temp, "---------------------------------------------\n");
                }
                found = 1;
            }
            else {
                fprintf(temp, "%s", line);
                while(fgets(line, sizeof(line), pending) && line[0] != '-') {
                    fprintf(temp, "%s", line);
                }
                fprintf(temp, "---------------------------------------------\n");
            }
        }
    }

    fclose(pending);
    fclose(approved);
    fclose(temp);

    remove("vpending.txt");
    rename("temp.txt", "vpending.txt");

    if(!found) {
        printf("Select an existing id please.\n");
    }
    press();
}

void ViewVolunteers() {
    system("cls");
    printf("=======+++++****-------------****+++++=======\n");
    printf("             *Current Volunteers             \n");
    printf("=======+++++****-------------****+++++=======\n\n");

    FILE *file = fopen("vapproved.txt", "r");
    if(file == NULL) {
        printf("No volunteer information available.\n");
        press();
        return;
    }

    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0) {
        printf("No registered volunteer available.\n");
        fclose(file);
        press();
        return;
    }
    rewind(file);

    char line[200];
    while(fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    int choice;
    printf("\nChoose an option:\n");
    printf("1. Remove a volunteer\n");
    printf("2. Return to previous page\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if(choice == 2) {
        fclose(file);
        return;
    }
    else if(choice == 1) {
        int select;
        printf("\nEnter the ID of the volunteer to remove: ");
        scanf("%d", &select);

        FILE *temp = fopen("temp.txt", "w");
        if(temp == NULL) {
            printf("An unexpected error occurred...");
            fclose(file);
            press();
            return;
        }

        int found = 0;
        int id;
        rewind(file);

        while(fgets(line, sizeof(line), file)) {
            if(sscanf(line, "Application serial number: %d", &id) == 1) {
                if(id == select) {
                    printf("Volunteer removed successfully!\n");
                    while(fgets(line, sizeof(line), file) && line[0] != '-') {
                        // Skip the removed volunteer
                    }
                    found = 1;
                }
                else {
                    fprintf(temp, "%s", line);
                    while(fgets(line, sizeof(line), file) && line[0] != '-') {
                        fprintf(temp, "%s", line);
                    }
                    fprintf(temp, "---------------------------------------------\n");
                }
            }
        }

        fclose(file);
        fclose(temp);
        remove("vapproved.txt");
        rename("temp.txt", "vapproved.txt");

        if(!found) {
            printf("Select an existing id please.\n");
        }
    }
    else {
        printf("Invalid choice!\n");
    }
    press();
}

void WriteNotice() {
    printf("\n*****Write a Notice!*****\n");
    FILE *file = fopen("notices.txt", "a");
    if(file == NULL) {
        printf("Error! Cannot access notice section...");
        press();
        return;
    }

    char notice[500];
    printf("Write notice(up to 500 characters): \n");
    getchar();
    fgets(notice, sizeof(notice), stdin);
    strtok(notice, "\n");

    fprintf(file, "%s\n\n", notice);
    fclose(file);
    printf("Notice board updated!\n");
    press();
}
