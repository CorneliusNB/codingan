#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct restaurant {
    char name[100];
    char city[100];
    int cost;
    char currency[50];
    int price;
    float rate;
    char text[50];
    int votes;
};

struct restaurant db[8000];
int idx = 0;

void read_file() {
    FILE *fp;
    char line[1024];
    
    fp = fopen("restaurant.csv", "r");
    
    if (fp == NULL) {
        printf("cannot open file\n");
        return;
    }
    
    fgets(line, 1024, fp);
    
    while (fgets(line, 1024, fp)) {
        char *token;
        
        token = strtok(line, ",");
        if (token != NULL) strcpy(db[idx].name, token);
        
        token = strtok(NULL, ",");
        if (token != NULL) strcpy(db[idx].city, token);
        
        token = strtok(NULL, ",");
        if (token != NULL) db[idx].cost = atoi(token);
        
        token = strtok(NULL, ",");
        if (token != NULL) strcpy(db[idx].currency, token);
        
        token = strtok(NULL, ",");
        if (token != NULL) db[idx].price = atoi(token);
        
        token = strtok(NULL, ",");
        if (token != NULL) db[idx].rate = atof(token);
        
        token = strtok(NULL, ",");
        if (token != NULL) strcpy(db[idx].text, token);
        
        token = strtok(NULL, ",");
        if (token != NULL) db[idx].votes = atoi(token);
        
        idx++;
    }
    
    fclose(fp);
}

void print_data() {
    int n;
    int i;
    
    printf("Number of rows: \n");
    scanf("%d", &n);
    
    printf("\n%-25s %-25s %-10s %-25s %-6s %-6s %-15s %s\n", 
           "Name", "City", "Cost", "Currency", "Price", "Rate", "Text", "Votes");
    
    if (n > idx) {
        n = idx;
    }
    
    for (i = 0; i < n; i++) {
        printf("%-25s %-25s %-10d %-25s %-6d %-6.1f %-15s %d\n", 
               db[i].name, 
               db[i].city, 
               db[i].cost, 
               db[i].currency, 
               db[i].price, 
               db[i].rate, 
               db[i].text, 
               db[i].votes);
    }
}

void search_data() {
    int menu;
    char search[100];
    int i;
    int found = 0;
    int header_printed = 0;
    
    printf("Choose column:\n");
    printf("1. Restaurant name\n");
    printf("2. City\n");
    printf("3. Rating text\n");
    printf("Choice: \n");
    scanf("%d", &menu);
    
    getchar();
    
    printf("What data do you want to find? \n");
    scanf("%[^\n]", search);
    
    printf("\nSearch Results:\n");

    for (i = 0; i < idx; i++) {
        int match = 0;

        if (menu == 1) {
            if (strcmp(db[i].name, search) == 0) match = 1;
        }
        else if (menu == 2) {
            if (strcmp(db[i].city, search) == 0) match = 1;
        }
        else if (menu == 3) {
            if (strcmp(db[i].text, search) == 0) match = 1;
        }

        if (match == 1) {
            if (header_printed == 0) {
                printf("%-25s %-25s %-10s %-25s %-6s %-6s %-15s %s\n", 
                       "Name", "City", "Cost", "Currency", "Price", "Rate", "Text", "Votes");
                header_printed = 1;
            }
            
            printf("%-25s %-25s %-10d %-25s %-6d %-6.1f %-15s %d\n", 
                   db[i].name, db[i].city, db[i].cost, db[i].currency, 
                   db[i].price, db[i].rate, db[i].text, db[i].votes);
            found = 1;
        }
    }
    
    if (found == 0) {
        printf("Data not found!\n");
    }
}

void sort_data() {
    int menu;
    char type[10];
    int i;
    int j;
    struct restaurant temp;
    
    printf("Choose column:\n");
    printf("1. Cost\n");
    printf("2. Rating\n");
    printf("3. Votes\n");
    printf("Choice: ");
    scanf("%d", &menu);
    
    while (1) {
        printf("Sort ascending (asc) or descending (desc)? ");
        scanf("%s", type);
        
        if (strcmp(type, "asc") == 0 || strcmp(type, "desc") == 0) {
            break;
        }
        printf("Invalid input. Please type exactly 'asc' or 'desc'.\n");
    }
    
    for (i = 0; i < idx - 1; i++) {
        for (j = 0; j < idx - i - 1; j++) {
            int swap = 0;
            if (menu == 1) {
                if (strcmp(type, "asc") == 0) { if (db[j].cost > db[j+1].cost) swap = 1; } 
                else { if (db[j].cost < db[j+1].cost) swap = 1; }
            }
            else if (menu == 2) {
                if (strcmp(type, "asc") == 0) { if (db[j].rate > db[j+1].rate) swap = 1; } 
                else { if (db[j].rate < db[j+1].rate) swap = 1; }
            }
            else if (menu == 3) {
                if (strcmp(type, "asc") == 0) { if (db[j].votes > db[j+1].votes) swap = 1; } 
                else { if (db[j].votes < db[j+1].votes) swap = 1; }
            }

            if (swap) {
                temp = db[j];
                db[j] = db[j+1];
                db[j+1] = temp;
            }
        }
    }
    
    printf("\nTop 10 Sorted Data:\n");
    printf("%-25s %-25s %-10s %-25s %-6s %-6s %-15s %s\n", 
           "Name", "City", "Cost", "Currency", "Price", "Rate", "Text", "Votes");

    int limit = (idx > 10) ? 10 : idx;
    
    for (i = 0; i < limit; i++) {
        printf("%-25s %-25s %-10d %-25s %-6d %-6.1f %-15s %d\n", 
               db[i].name, db[i].city, db[i].cost, db[i].currency, 
               db[i].price, db[i].rate, db[i].text, db[i].votes);
    }
}

void export_data() {
    char name[100];
    char fullname[110];
    FILE *fp;
    int i;
    
    printf("File name: \n");
    scanf("%s", name);
    
    sprintf(fullname, "%s.csv", name);
    
    fp = fopen(fullname, "w");
    
    if (fp == NULL) {
        printf("error creating file\n");
        return;
    }
    
    fprintf(fp, "Restaurant name,City,Cost for two,Currency,Price range,Rating,Rating text,Votes\n");
    
    for (i = 0; i < idx; i++) {
        fprintf(fp, "%s,%s,%d,%s,%d,%.1f,%s,%d\n", 
                db[i].name, db[i].city, db[i].cost, db[i].currency, 
                db[i].price, db[i].rate, db[i].text, db[i].votes);
    }
    
    fclose(fp);
    printf("Data successfully written to file %s!\n", fullname);
}

int main() {
    int choice;
    
    read_file();
    
    do {
        printf("\n");
        printf("What do you want to do?\n");
        printf("1. Display data\n");
        printf("2. Search Data\n");
        printf("3. Sort Data\n");
        printf("4. Export Data\n");
        printf("5. Exit\n");
        printf("Your choice: \n");
        scanf("%d", &choice);
        
        if (choice == 1) print_data();
        else if (choice == 2) search_data();
        else if (choice == 3) sort_data();
        else if (choice == 4) export_data();
        else if (choice == 5) printf("Exiting...\n");
        else printf("Invalid choice!\n");
        
    } while (choice != 5);
    
    return 0;
}
