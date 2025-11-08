
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Ration {
    int card_no;
    char name[50];
    int rice;
    int sugar;
    int oil;
};

void addRation() {
    struct Ration r;
    FILE *fp = fopen("ration.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Ration Card Number: ");
    scanf("%d", &r.card_no);
    getchar();
    printf("Enter Name: ");
    fgets(r.name, sizeof(r.name), stdin);
    r.name[strcspn(r.name, "\n")] = '\0';

    printf("Enter quantity of Rice (kg): ");
    scanf("%d", &r.rice);
    printf("Enter quantity of Sugar (kg): ");
    scanf("%d", &r.sugar);
    printf("Enter quantity of Oil (litres): ");
    scanf("%d", &r.oil);

    fprintf(fp, "%d,%s,%d,%d,%d\n", r.card_no, r.name, r.rice, r.sugar, r.oil);
    fclose(fp);
    printf("\nRation record added successfully!\n");
}

void displayRation() {
    struct Ration r;
    FILE *fp = fopen("ration.txt", "r");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n--- RATION DETAILS ---\n");
    printf("Card No | Name               | Rice | Sugar | Oil\n");
    printf("--------------------------------------------------\n");

    while (fscanf(fp, "%d,%49[^,],%d,%d,%d\n", &r.card_no, r.name, &r.rice, &r.sugar, &r.oil) != EOF) {
        printf("%-8d | %-18s | %-4d | %-5d | %-3d\n", r.card_no, r.name, r.rice, r.sugar, r.oil);
    }

    fclose(fp);
}

void searchRation() {
    struct Ration r;
    int card, found = 0;
    FILE *fp = fopen("ration.txt", "r");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("Enter Ration Card Number to search: ");
    scanf("%d", &card);

    while (fscanf(fp, "%d,%49[^,],%d,%d,%d\n", &r.card_no, r.name, &r.rice, &r.sugar, &r.oil) != EOF) {
        if (r.card_no == card) {
            printf("\n--- RATION DETAILS ---\n");
            printf("Card No: %d\nName: %s\nRice: %d kg\nSugar: %d kg\nOil: %d litres\n",
                   r.card_no, r.name, r.rice, r.sugar, r.oil);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nNo record found with that card number!\n");

    fclose(fp);
}

void updateRation() {
    struct Ration r;
    FILE *fp = fopen("ration.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    int card, found = 0;

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("Enter Ration Card Number to update: ");
    scanf("%d", &card);

    while (fscanf(fp, "%d,%49[^,],%d,%d,%d\n", &r.card_no, r.name, &r.rice, &r.sugar, &r.oil) != EOF) {
        if (r.card_no == card) {
            printf("\nEnter new Rice (kg): ");
            scanf("%d", &r.rice);
            printf("Enter new Sugar (kg): ");
            scanf("%d", &r.sugar);
            printf("Enter new Oil (litres): ");
            scanf("%d", &r.oil);
            found = 1;
        }
        fprintf(temp, "%d,%s,%d,%d,%d\n", r.card_no, r.name, r.rice, r.sugar, r.oil);
    }

    fclose(fp);
    fclose(temp);

    remove("ration.txt");
    rename("temp.txt", "ration.txt");

    if (found)
        printf("\nRecord updated successfully!\n");
    else
        printf("\nRecord not found!\n");
}

int main() {
    int choice;

    while (1) {
        printf("\n=== RATION MANAGEMENT SYSTEM ===\n");
        printf("1. Add Ration Record\n");
        printf("2. Display All Records\n");
        printf("3. Search Record\n");
        printf("4. Update Record\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addRation();
                break;
            case 2:
                displayRation();
                break;
            case 3:
                searchRation();
                break;
            case 4:
                updateRation();
                break;
            case 5:
                printf("Exiting... Thank you!\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}






