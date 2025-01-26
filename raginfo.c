#include <stdio.h>
#include <stdlib.h>
#include "raginfo.h"
#include "utils.h"

void ThingsUnderRagging() {
    system("cls");
    printf("=======+++++****------------****+++++=======\n");
    printf("      *Things Considered Under Ragging      \n");
    printf("=======+++++****------------****+++++=======\n\n");

    FILE *file = fopen("raginfo.txt", "r");
    if(file == NULL) {
        printf("Sorry! No information was found!");
        return;
    }

    char c;
    while((c = fgetc(file)) != EOF) {
        putchar(c);
    }
    fclose(file);
    printf("\n");
    press();
}
