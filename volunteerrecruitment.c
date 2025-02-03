#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "volunteerrecruitment.h"
#include "utils.h"

void volunteer() {
    system("cls");
    printf("=======+++++****-------------****+++++=======\n");
    printf("   Fill up the Form to Join as A Volunteer   \n");
    printf("=======+++++****-------------****+++++=======\n\n");
    information v;
    char email[50], address[100];
    FILE *file = fopen("vpending.txt", "a");
    FILE *serialfile = fopen("id.txt", "r+");
    int serialnum = 1;

    if(file == NULL || serialfile == NULL) {
        printf("Sorry! Cannot take application right now!");
        if(serialfile) {
            fclose(serialfile);
        }
        return;
    }

    fscanf(serialfile, "%d", &serialnum);
    rewind(serialfile);
    fprintf(serialfile, "%d", serialnum + 1);
    fclose(serialfile);

    printf("Application serial number: %d\nGive the required informations:\n", serialnum);

    printf("Name: ");
    getchar();
    fgets(v.name, sizeof(v.name), stdin);
    strtok(v.name, "\n");

    printf("Year: ");
    fgets(v.year, sizeof(v.year), stdin);
    strtok(v.year, "\n");

    printf("Term: ");
    fgets(v.term, sizeof(v.term), stdin);
    strtok(v.term, "\n");

    printf("Roll: ");
    fgets(v.roll, sizeof(v.roll), stdin);
    strtok(v.roll, "\n");

    printf("Hall: ");
    fgets(v.hall, sizeof(v.hall), stdin);
    strtok(v.hall, "\n");

    printf("Email: ");
    fgets(email, sizeof(email), stdin);
    strtok(email, "\n");

    printf("Address: ");
    fgets(address, sizeof(address), stdin);
    strtok(address, "\n");

    fprintf(file, "Application serial number: %d\nName: %s\nYear: %s\nTerm: %s\nRoll: %s\nHall: %s\nEmail: %s\nAddress: %s\n",
            serialnum, v.name, v.year, v.term, v.roll, v.hall, email, address);

    for(int i = 0; i < 45; i++) {
        fputc('-', file);
    }
    fputc('\n', file);
    fclose(file);

    printf("Your application has been submitted for review. We will contact you soon.\n");
    press();
}
