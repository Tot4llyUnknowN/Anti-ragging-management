#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "antirag.h"
#include "utils.h"

void ContactUs() {
    system("cls");
    printf("=======+++++****-------------****+++++=======\n");
    printf("           *Anti-Ragging Committee           \n");
    printf("=======+++++****-------------****+++++=======\n\n");

    FILE *file = fopen("committee.txt", "r");
    if(file == NULL) {
        printf("Sorry! No information was found!");
        return;
    }

    char name[50], email[50], phone[30];
    char c;
    while((c = fgetc(file)) != EOF) {
        fgets(name, sizeof(name), file);
        strtok(name, "\n");
        fscanf(file, "%29s %49s", phone, email);

        printf("Name: %s\nPhone: %s, Email: %s\n\n", name, email, phone);
    }
    fclose(file);
    press();
}
