#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "victim.h"
#include "utils.h"

void VictimPart() {
    int option;
    do {
        system("cls");
        printf("=======+++++****-------------****+++++=======\n");
        printf("               *Victim Section               \n");
        printf("=======+++++****-------------****+++++=======\n\n");
        printf("1. File a Complaint\n");
        printf("2. Medical Assistance\n");
        printf("3. Homepage\n");
        printf("\n\nChoose an option: \n");
        scanf("%d", &option);

        switch(option) {
            case 1: FileComplaint(); break;
            case 2: MedicalAssistance(); break;
            case 3: return;
            default: printf("Please choose a valid option..."); press();
        }
    } while(option != 3);
}

void FileComplaint() {
    system("cls");
    printf("=======+++++****-------------****+++++=======\n");
    printf("      *Please fillup the complaint form      \n");
    printf("=======+++++****-------------****+++++=======\n\n");

    information submit;
    char details[500], info[100];
    FILE *file = fopen("complaints.txt", "a");
    FILE *serialfile = fopen("serial.txt", "r+");
    int serialnum = 1;

    if(serialfile == NULL) {
    serialfile = fopen("serial.txt", "w");
    fprintf(serialfile, "1");
    rewind(serialfile);
    }

    if(file == NULL || serialfile == NULL) {
        printf("Sorry! Cannot take complaints right now!");
        if(serialfile) {
            fclose(serialfile);
        }
        return;
    }

    fscanf(serialfile, "%d", &serialnum);
    rewind(serialfile);
    fprintf(serialfile, "%d", serialnum + 1);
    fclose(serialfile);

    printf("Complaint serial number: %d\nComplaint against:\n", serialnum);
    printf("Name: ");
    getchar();
    fgets(submit.name, sizeof(submit.name), stdin);
    strtok(submit.name, "\n");

    printf("Year: ");
    fgets(submit.year, sizeof(submit.year), stdin);
    strtok(submit.year, "\n");

    printf("Term: ");
    fgets(submit.term, sizeof(submit.term), stdin);
    strtok(submit.term, "\n");

    printf("Roll: ");
    fgets(submit.roll, sizeof(submit.roll), stdin);
    strtok(submit.roll, "\n");

    printf("Hall: ");
    fgets(submit.hall, sizeof(submit.hall), stdin);
    strtok(submit.hall, "\n");

    printf("Tell us what happened(up to 500 characters): \n");
    fgets(details, sizeof(details), stdin);
    details[sizeof(details) - 1] = '\0';
    strtok(details, "\n");

    printf("How can we contact with you?(name, phone number, address etc): \n");
    fgets(info, sizeof(info), stdin);
    strtok(info, "\n");

    fprintf(file, "Complaint serial number: %d\nName: %s\nYear: %s\nTerm: %s\nRoll: %s\nHall: %s\nDetails: %s\nContact info: %s\n",
            serialnum, submit.name, submit.year, submit.term, submit.roll, submit.hall, details, info);

    for(int i = 0; i < 45; i++) {
        fputc('-', file);
    }
    fputc('\n', file);
    fclose(file);

    printf("Your complaint has been accepted. Kindly note down your serial number for further enquiry");
    press();
}

void MedicalAssistance() {
    system("cls");
    printf("=======+++++****-------------****+++++=======\n");
    printf("         *Emergency Medical Contacts         \n");
    printf("=======+++++****-------------****+++++=======\n\n");

    FILE *file = fopen("medical.txt", "r");
    if(file == NULL) {
        printf("Sorry! No information was found!");
        return;
    }

    char c;
    while((c = fgetc(file)) != EOF) {
        putchar(c);
    }
    fclose(file);
    press();
}
