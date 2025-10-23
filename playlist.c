#include <stdio.h>
#include <stdlib.h>

struct song {
    char name[50];
    char artist[50];
    float duration;
    struct song *next;
};

struct song *head = NULL;

void copy(char *a, char *b) {
    int i = 0;
    while (b[i] != '\0') {
        a[i] = b[i];
        i++;
    }
    a[i] = '\0';
}

int same(char *a, char *b) {
    int i = 0;
    while (a[i] != '\0' || b[i] != '\0') {
        if (a[i] != b[i]) return 0;
        i++;
    }
    return 1;
}

struct song* createsong(char name[], char artist[], float duration) {
    struct song *newsong = (struct song*)malloc(sizeof(struct song));
    copy(newsong->name, name);
    copy(newsong->artist, artist);
    newsong->duration = duration;
    newsong->next = NULL;
    return newsong;
}

void addathead() {
    char name[50], artist[50];
    float duration;
    printf("Enter song name: ");
    scanf(" %[^\n]", name);
    printf("Enter artist: ");
    scanf(" %[^\n]", artist);
    printf("Enter duration: ");
    scanf("%f", &duration);

    struct song *newsong = createsong(name, artist, duration);

    if (head == NULL) {
        head = newsong;
        newsong->next = head;
        return;
    }

    struct song *temp = head;
    while (temp->next != head)
        temp = temp->next;

    newsong->next = head;
    temp->next = newsong;
    head = newsong;
    printf("Song added at head\n");
}

void addattail() {
    char name[50], artist[50];
    float duration;
    printf("Enter song name: ");
    scanf(" %[^\n]", name);
    printf("Enter artist: ");
    scanf(" %[^\n]", artist);
    printf("Enter duration: ");
    scanf("%f", &duration);

    struct song *newsong = createsong(name, artist, duration);

    if (head == NULL) {
        head = newsong;
        newsong->next = head;
        return;
    }

    struct song *temp = head;
    while (temp->next != head)
        temp = temp->next;

    temp->next = newsong;
    newsong->next = head;
    printf("Song added at tail\n");
}

void addinbetween() {
    if (head == NULL) {
        printf("Playlist empty\n");
        return;
    }

    char target[50], name[50], artist[50];
    float duration;
    printf("Enter song name after which to add: ");
    scanf(" %[^\n]", target);

    struct song *temp = head;
    int found = 0;

    do {
        if (same(temp->name, target)) {
            found = 1;
            break;
        }
        temp = temp->next;
    } while (temp != head);

    if (!found) {
        printf("Song not found\n");
        return;
    }

    printf("Enter new song name: ");
    scanf(" %[^\n]", name);
    printf("Enter artist: ");
    scanf(" %[^\n]", artist);
    printf("Enter duration: ");
    scanf("%f", &duration);

    struct song *newsong = createsong(name, artist, duration);
    newsong->next = temp->next;
    temp->next = newsong;
    printf("Song added after %s\n", target);
}

void deletehead() {
    if (head == NULL) {
        printf("Playlist empty\n");
        return;
    }

    if (head->next == head) {
        free(head);
        head = NULL;
        printf("Song deleted at head\n");
        return;
    }

    struct song *temp = head;
    while (temp->next != head)
        temp = temp->next;

    struct song *del = head;
    head = head->next;
    temp->next = head;
    free(del);
    printf("Song deleted at head\n");
}

void deletetail() {
    if (head == NULL) {
        printf("Playlist empty\n");
        return;
    }

    if (head->next == head) {
        free(head);
        head = NULL;
        printf("Song deleted at tail\n");
        return;
    }

    struct song *temp = head;
    struct song *prev = NULL;

    while (temp->next != head) {
        prev = temp;
        temp = temp->next;
    }

    prev->next = head;
    free(temp);
    printf("Song deleted at tail\n");
}

void deleteinbetween() {
    if (head == NULL) {
        printf("Playlist empty\n");
        return;
    }

    char target[50];
    printf("Enter song name to delete: ");
    scanf(" %[^\n]", target);

    struct song *temp = head;
    struct song *prev = NULL;

    do {
        if (same(temp->name, target)) break;
        prev = temp;
        temp = temp->next;
    } while (temp != head);

    if (!same(temp->name, target)) {
        printf("Song not found\n");
        return;
    }

    if (temp == head) {
        deletehead();
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("Song deleted from between\n");
}

void displaysongs() {
    if (head == NULL) {
        printf("Playlist empty\n");
        return;
    }

    struct song *temp = head;
    int count = 1;
    do {
        printf("%d. %s by %s (%.2f min)\n", count, temp->name, temp->artist, temp->duration);
        temp = temp->next;
        count++;
    } while (temp != head);
}

int main() {
    int choice;
    printf("Welcome to Circular Playlist\n");
    while (1) {
        printf("\n1. Add at Head\n2. Add at Tail\n3. Add in Between\n4. Delete Head\n5. Delete Tail\n6. Delete in Between\n7. Display\n8. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addathead(); break;
            case 2: addattail(); break;
            case 3: addinbetween(); break;
            case 4: deletehead(); break;
            case 5: deletetail(); break;
            case 6: deleteinbetween(); break;
            case 7: displaysongs(); break;
            case 8: printf("Exiting...\n"); return 0;
            default: printf("Invalid choice\n");
        }
    }
}
