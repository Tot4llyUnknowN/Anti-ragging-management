#include <stdio.h>
#include <stdlib.h>
#include "auth.h"
#include "admin.h"
#include "volunteer.h"
#include "victim.h"
#include "raginfo.h"
#include "antirag.h"
#include "utils.h"
#include "types.h"
#include "volunteerrecruitment.h"

void Homepage() {
    int option;
    do {
        system("cls");
        printf("=======+++++****-------------****+++++=======\n");
        printf("                SAY NO TO RAG                \n");
        printf("=======+++++****-------------****+++++=======\n\n");
        printf("1. Are you/someone known to you a victim?\n");
        printf("2. Things considered under ragging\n");
        printf("3. Contact with anti-ragging comittee\n");
        printf("\n4. Join as a volunteer\n");
        printf("\n5. Admin login\n");
        printf("6. Volunteer login\n");
        printf("7. Exit\n");
        printf("\n\nChoose an option: \n");
        scanf("%d", &option);

        switch(option) {
            case 1: VictimPart(); break;
            case 2: ThingsUnderRagging(); break;
            case 3: ContactUs(); break;
            case 4: volunteer(); break;
            case 5: AdminLogin(); break;
            case 6: VolunteerLogin(); break;
            case 7: exit(0);
            default: printf("Please choose a valid option..."); press();
        }
    } while(option != 7);
}

int main() {
    LoadCredentials();
    Homepage();
    return 0;
}
