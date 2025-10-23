#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct song {
    char name[50];
    char artist[50];
    float duration;
    struct song *next;
};

struct song *head = NULL;

struct song* createsong(char name[], char artist[], float duration) {
    struct song *newsong = (struct song*)malloc(sizeof(struct song));
    strcpy(newsong->name, name);
    strcpy(newsong->artist, artist);
    newsong->duration = duration;
    newsong->next = NULL;
    return newsong;
}

void removenewline(char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        if (str[i] == '\n') {
            str[i] = '\0';
            break;
        }
        i++;
    }
}

void addsong() {
    char name[50], artist[50];
    float duration;
    printf("\n enter song name: ");
    scanf(" %[^\n]", name);
    printf("Enter artist name: ");
    scanf(" %[^\n]", artist);
    printf("Enter duration (in minutes): ");
    scanf("%f", &duration);
    struct song *newsong = createsong(name, artist, duration);
    if (head == NULL) {
        head = newsong;
    } else {
        struct song *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newsong;
    }
    printf("\n song '%s' added successfully\n", name);
}

void displaysongs() {
    if (head == NULL) {
        printf("\n the playlist is empty\n");
        return;
    }
    struct song *temp = head;
    int count = 1;
    printf("\n your playlist:\n");
    while (temp != NULL) {
        printf("%d. %s by %s (%.2f min)\n", count, temp->name, temp->artist, temp->duration);
        temp = temp->next;
        count++;
    }
}

void addsongbetween() {
    if (head == NULL) {
        printf("\nplaylist is empty!\n");
        return;
    }
    char target[50];
    printf("\n enter the song name after which to add: ");
    scanf(" %[^\n]", target);
    struct song *temp = head;
    int found = 0;
    while (temp != NULL) {
        if (strcmp(temp->name, target) == 0) {
            found = 1;
            break;
        }
        temp = temp->next;
    }
    if (!found) {
        printf("\n song is not there !\n");
        return;
    }
    char name[50], artist[50];
    float duration;
    printf("Enter new song name: ");
    scanf(" %[^\n]", name);
    printf("Enter artist name: ");
    scanf(" %[^\n]", artist);
    printf("Enter duration (in minutes): ");
    scanf("%f", &duration);
    struct song *newsong = createsong(name, artist, duration);
    newsong->next = temp->next;
    temp->next = newsong;
    printf("\nsong '%s' added after '%s'!\n", name, target);
}

void deletesongbetween() {
    if (head == NULL) {
        printf("\nplaylist is empty\n");
        return;
    }
    char name[50];
    printf("\n enter the song name to delete: ");
    scanf(" %[^\n]", name);
    struct song *temp = head;
    struct song *prev = NULL;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0)
            break;
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("\n song not found!\n");
        return;
    }
    if (prev == NULL) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }
    free(temp);
    printf("\n song deleted\n");
}

int main() {
    int choice;
    printf(" Welcome\n");
    do {
        printf("\n----------------------------\n");
        printf("1. Add Song\n");
        printf("2. Display Songs\n");
        printf("3. Add Song In Between\n");
        printf("4. Delete Song\n");
        printf("5. Exit\n");
        printf("----------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addsong(); break;
            case 2: displaysongs(); break;
            case 3: addsongbetween(); break;
            case 4: deletesongbetween(); break;
            case 5: printf("\nexiting..\n"); break;
            default: printf("\ninvalid choice!\n");
        }
    } while (choice != 5);
    return 0;
}

