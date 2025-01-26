#include <stdio.h>
#include <string.h>
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

void ChangeCredentials() {
    int option;
    printf("Change Credentials\n");
    printf("1. Change Admin Username/Password\n");
    printf("2. Change Volunteer Username/Password\n");
    printf("Choose an option: ");
    scanf("%d", &option);

    if (option == 1) {
        char newAdminUsername[10], newAdminPassword[10];
        printf("Enter new Admin username: ");
        scanf("%s", newAdminUsername);
        printf("Enter new Admin password: ");
        scanf("%s", newAdminPassword);

        strcpy(AdminUsername, newAdminUsername);
        strcpy(AdminPassword, newAdminPassword);
        printf("Admin credentials updated successfully!\n");
    }
    else if (option == 2) {
        char newVolunteerUsername[10], newVolunteerPassword[10];
        printf("Enter new Volunteer username: ");
        scanf("%s", newVolunteerUsername);
        printf("Enter new Volunteer password: ");
        scanf("%s", newVolunteerPassword);

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
