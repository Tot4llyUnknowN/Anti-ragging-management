#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include "auth.h"
#include "globals.h"
#include "utils.h"

void LoadCredentials() {
    FILE *file = fopen("credentials.txt", "r");
    if (file != NULL) {
        fscanf(file, "AdminUsername=%s\n", AdminUsername);
        fscanf(file, "AdminPassword=%s\n", AdminPassword);
        fscanf(file, "VolunteerUsername=%s\n", VolunteerUsername);
        fscanf(file, "VolunteerPassword=%s\n", VolunteerPassword);
        fclose(file);
    }
}

void SaveCredentials() {
    FILE *file = fopen("credentials.txt", "w");
    if (file != NULL) {
        fprintf(file, "AdminUsername=%s\n", AdminUsername);
        fprintf(file, "AdminPassword=%s\n", AdminPassword);
        fprintf(file, "VolunteerUsername=%s\n", VolunteerUsername);
        fprintf(file, "VolunteerPassword=%s\n", VolunteerPassword);
        fclose(file);
    }
}

int strongpass(const char *password){
    int upr=0;
    int lwr=0;
    int num=0;
    int spc=0;
    int length=strlen(password);

    if(length<8){
        printf("Password must be at least 8 characters long!\n");
        return 0;
    }

    for(int i=0; password[i]!='\0';i++){
        if(isupper(password[i])){
            upr=1;
        }
        if(islower(password[i])){
            lwr=1;
        }
        if(isdigit(password[i])){
            num=1;
        }
        if(ispunct(password[i])){
            spc=1;
        }
    }
    if(!upr){
        printf("Password must contain at least one uppercase, one lowercase, one number and one special character!\n");
        return 0;
    }
    if(!lwr){
        printf("Password must contain at least one uppercase, one lowercase, one number and one special character!\n");
        return 0;
    }
    if(!num){
        printf("Password must contain at least one uppercase, one lowercase, one number and one special character!\n");
        return 0;
    }
    if(!spc){
        printf("Password must contain at least one uppercase, one lowercase, one number and one special character!\n");
        return 0;
    }
    return 1;
}

void ChangeCredentials() {
    int option;
    printf("Change Credentials\n");
    printf("1. Change Admin Username/Password\n");
    printf("2. Change Volunteer Username/Password\n");
    printf("Choose an option: ");
    scanf("%d", &option);

    if (option == 1) {
        char newAdminUsername[200], newAdminPassword[200];
        printf("Enter new admin username: ");
        scanf("%s", newAdminUsername);
        do{
           int i = 0;
           char ch;
           printf("Enter new admin password: ");
           while((ch = _getch()) != 13 && i < 199) {
                if(ch == 8) {
                   if(i > 0) {
                   i--;
                   printf("\b \b");
                   }
                }
            else {
               newAdminPassword[i++] = ch;
               printf("*");
            }
        }
        newAdminPassword[i] = '\0';
        printf("\n");
        getchar();

        if (strcmp(newAdminUsername, newAdminPassword) == 0) {
                printf("Password cannot be the same as username!\n");
                continue;
            }
        }while(!strongpass(newAdminPassword));

        strcpy(AdminUsername, newAdminUsername);
        strcpy(AdminPassword, newAdminPassword);
        printf("Admin credentials updated successfully!\n");
    }
    else if (option == 2) {
        char newVolunteerUsername[200], newVolunteerPassword[200];
        printf("Enter new volunteer username: ");
        scanf("%s", newVolunteerUsername);

        do{
           int i = 0;
           char ch;
           printf("Enter new volunteer password: ");
           while((ch = _getch()) != 13 && i < 199) {
                if(ch == 8) {
                   if(i > 0) {
                   i--;
                   printf("\b \b");
                   }
                }
            else {
               newVolunteerPassword[i++] = ch;
               printf("*");
            }
        }
        newVolunteerPassword[i] = '\0';
        printf("\n");
        getchar();

        if (strcmp(newVolunteerUsername, newVolunteerPassword) == 0) {
                printf("Password cannot be the same as username!\n");
                continue;
            }
        }while(!strongpass(newVolunteerPassword));

        strcpy(VolunteerUsername, newVolunteerUsername);
        strcpy(VolunteerPassword, newVolunteerPassword);
        printf("Volunteer credentials updated successfully!\n");
    }
    else {
        printf("Invalid choice!\n");
    }
    SaveCredentials();
    press();
}
