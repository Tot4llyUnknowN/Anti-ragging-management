#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "volunteer.h"
#include "globals.h"
#include "utils.h"

void VolunteerLogin() {
    char username[10], password[10];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    int i = 0;
    char ch;
    while((ch = _getch()) != 13 && i < 9) {
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

    if (strcmp(username, VolunteerUsername) == 0 && strcmp(password, VolunteerPassword) == 0) {
        int option;
        do {
            system("cls");
            printf("=======+++++****-------------****+++++=======\n");
            printf("               Volunteer Section             \n");
            printf("=======+++++****-------------****+++++=======\n\n");
            printf("1. View Complaints\n");
            printf("2. Notice board\n");
            printf("3. Logout\n");
            printf("Choose an option: \n");
            scanf("%d", &option);

            switch(option) {
                case 1: SelectComplaint(); break;
                case 2: NoticeBoard(); break;
                case 3: return;
                default: printf("Please choose a valid option...\n"); press();
            }
        } while(option != 3);
    } else {
        printf("Invalid username or password. Please try again...\n");
        press();
    }
}

void SelectComplaint() {
    system("cls");
    printf("=======+++++****-------------****+++++=======\n");
    printf("              Complaint Section              \n");
    printf("=======+++++****-------------****+++++=======\n\n");

    FILE *pending = fopen("complaints.txt", "r");
    FILE *approved = fopen("verified.txt", "a");
    FILE *invalid = fopen("notverified.txt", "a");

    if(pending == NULL) {
        printf("Sorry! No information was found!\n");
        press();
        return;
    }

    if(approved == NULL || invalid == NULL) {
        printf("Error accessing complaints.\n");
        fclose(pending);
        press();
        return;
    }

    int select, id;
    char line[200];
    int found = 0;

    fseek(pending, 0, SEEK_END);
    long size = ftell(pending);
    rewind(pending);

    if(size == 0) {
        printf("No complaints have been filed yet...\n");
        fclose(pending);
        fclose(approved);
        fclose(invalid);
        press();
        return;
    }

    printf("All complaints: \n");

    char c;
    while((c = fgetc(pending)) != EOF) {
        putchar(c);
    }

    rewind(pending);

    printf("Select complaint id (0 to return): ");
    scanf("%d", &select);

    if(select == 0) {
        fclose(pending);
        fclose(approved);
        fclose(invalid);
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if(temp == NULL) {
        printf("An unexpected error occurred...");
        fclose(pending);
        fclose(approved);
        fclose(invalid);
        press();
        return;
    }

    while(fgets(line, sizeof(line), pending)) {
        if(sscanf(line, "Complaint serial number: %d", &id) == 1) {
            if(id == select) {
                int choice;
                printf("\n1. Valid\n2. Not valid\n3. Deselect and return\nSelect an option: ");
                scanf("%d", &choice);

                if(choice == 3) {
                    fprintf(temp, "%s", line);
                    while(fgets(line, sizeof(line), pending) && line[0] != '-') {
                        fprintf(temp, "%s", line);
                    }
                    fprintf(temp, "---------------------------------------------\n");
                } else if(choice == 1) {
                    fprintf(approved, "%s", line);
                    printf("Complaint transferred to the committee...\n");
                    while(fgets(line, sizeof(line), pending) && line[0] != '-') {
                        fprintf(approved, "%s", line);
                    }
                    fprintf(approved, "---------------------------------------------\n");
                } else if(choice == 2) {
                    fprintf(invalid, "%s", line);
                    printf("Thank you for working with us...\n");
                    while(fgets(line, sizeof(line), pending) && line[0] != '-') {
                        fprintf(invalid, "%s", line);
                    }
                    fprintf(invalid, "---------------------------------------------\n");
                } else {
                    printf("Invalid option. Please choose again...");
                    fprintf(temp, "%s", line);
                    while(fgets(line, sizeof(line), pending) && line[0] != '-') {
                        fprintf(temp, "%s", line);
                    }
                    fprintf(temp, "---------------------------------------------\n");
                }
                found = 1;
            } else {
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
    fclose(invalid);
    fclose(temp);

    remove("complaints.txt");
    rename("temp.txt", "complaints.txt");

    if(!found) {
        printf("Select an existing id please.\n");
    }
    press();
}

void NoticeBoard() {
    system("cls");
    printf("=======+++++****-------------****+++++=======\n");
    printf("                NOTICE BOARD!                \n");
    printf("=======+++++****-------------****+++++=======\n\n");

    FILE *file = fopen("notices.txt", "r");
    if(file == NULL) {
        printf("No notices available.\n");
        return;
    }

    char c;
    while((c = fgetc(file)) != EOF) {
        putchar(c);
    }
    fclose(file);
    press();
}
