#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doubly_linked_list.h"
#include "bubble_sort.h"

void scan_list(DoublyLinkedList* list) {
    int n;
    printf("Enter count of states: ");
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        Science_pub data;

        printf("Name: ");
        scanf("%s", data.name);

        printf("Surname: ");
        scanf("%s", data.surname);

        printf("Initials: ");
        scanf("%s", data.initials);

        printf("Journal Name: ");
        scanf(" %s", data.journal_name);

        printf("Year: ");
        scanf("%d", &data.year);

        printf("Volume: ");
        scanf("%d", &data.volume);

        int RSCI;
        printf("RSCI (1 for Yes, 0 for No): ");
        scanf("%d", &RSCI);
        data.RSCI = RSCI;

        printf("Pages: ");
        scanf("%d", &data.pages);

        printf("Citations: ");
        scanf("%d", &data.citations);
        add_to_back(list, data);
    }
}

void print_list_in_file(DoublyLinkedList* list, FILE *file) {
    Node* current = get_head(list);
    while (current != NULL) {
        fprintf(file, "%s,", current->data.name);
        fprintf(file, "%s,", current->data.surname);
        fprintf(file, "%s,", current->data.initials);
        fprintf(file, "%s,", current->data.journal_name);
        fprintf(file, "%d,", current->data.year);
        fprintf(file, "%d,", current->data.volume);
        fprintf(file, "%s,", current->data.RSCI ? "Yes" : "No");
        fprintf(file, "%d,", current->data.pages);
        fprintf(file, "%d", current->data.citations);
        fprintf(file, "\n");
        current = get_next(current);
    }
    printf("Successfully written to file\n");
}

void print_list(DoublyLinkedList* list) {
    Node* current = get_head(list);
    while (current != NULL) {
        printf("Name: %s\n", current->data.name);
        printf("Surname: %s\n", current->data.surname);
        printf("Initials: %s\n", current->data.initials);
        printf("Journal Name: %s\n", current->data.journal_name);
        printf("Year: %d\n", current->data.year);
        printf("Volume: %d\n", current->data.volume);
        printf("RSCI: %s\n", current->data.RSCI ? "Yes" : "No");
        printf("Pages: %d\n", current->data.pages);
        printf("Citations: %d\n", current->data.citations);
        printf("\n");
        current = get_next(current);
    }
}

void print_table(DoublyLinkedList* list) {
    printf("%-20s %-20s %-10s %-30s %-5s %-5s %-5s %-5s %-5s\n",
           "Name", "Surname", "Initials", "Journal Name", "Year", "Volume", "RSCI", "Pages", "Citations");
    printf("----------------------------------------------------------------------------------------------------------------------------------\n");

    Node *current = list->head;
    while (current != NULL) {
        printf("%-20s %-20s %-10s %-30s %-5d %-5d %-5s %-5d %-5d\n",
               current->data.name,
               current->data.surname,
               current->data.initials,
               current->data.journal_name,
               current->data.year,
               current->data.volume,
               current->data.RSCI ? "true" : "false",
               current->data.pages,
               current->data.citations);
        current = current->next;
    }
}

void print_table_in_file(DoublyLinkedList* list, FILE *file) {
    fprintf(file, "%-20s %-20s %-10s %-30s %-5s %-5s %-5s %-5s %-5s\n",
           "Name", "Surname", "Initials", "Journal Name", "Year", "Volume", "RSCI", "Pages", "Citations");
    fprintf(file, "----------------------------------------------------------------------------------------------------------------------------------\n");

    Node *current = list->head;
    while (current != NULL) {
        fprintf(file, "%-20s %-20s %-10s %-30s %-5d %-5d %-5s %-5d %-5d\n",
               current->data.name,
               current->data.surname,
               current->data.initials,
               current->data.journal_name,
               current->data.year,
               current->data.volume,
               current->data.RSCI ? "true" : "false",
               current->data.pages,
               current->data.citations);
        current = current->next;
    }
}

int main(int argc, char *argv[]) {
    (void)argc;
    if ((strcmp(argv[1], "--generate") == 0) || (strcmp(argv[1], "-g") == 0)) {
        int N = atoi(argv[2]);
        DoublyLinkedList* list = init();
        generate_random_science_pubs_list(list, N);

        if (argc > 3 && strcmp(argv[3], "-o") == 0) {
            FILE *file = fopen(argv[4], "w");
            if (file == NULL) {
                perror("fopen");
                return 1;
            }
            print_list_in_file(list, file);
            fclose(file);
        } else {
            print_list(list);
        }
    }

    if ((strcmp(argv[1], "--sort") == 0) || (strcmp(argv[1], "-s") == 0)) {
        DoublyLinkedList* list = init();
        if (strcmp(argv[5], "-i") == 0) {
            read_csv(list, argv[6]);
        }
        if (strcmp(argv[2], "-i") == 0) {
            read_csv(list, argv[3]);
        }
        if ((argc > 5 && strcmp(argv[5], "-i") != 0) && (argc > 2 && strcmp(argv[2], "-i") != 0)) {
            scan_list(list);
        }
        bubble_sort(list);
        if (strcmp(argv[2], "-o") == 0) {
            FILE *file = fopen(argv[3], "w");
            print_list_in_file(list, file);
            fclose(file);
        }
        if (strcmp(argv[5], "-o") == 0) {
            FILE *file = fopen(argv[6], "w");

            print_list_in_file(list, file);
            fclose(file);
        }
        if ((strcmp(argv[5], "-o") != 0) && (strcmp(argv[2], "-o") != 0)) {
            print_list(list);
        }
    }

    if ((strcmp(argv[1], "-print") == 0) || (strcmp(argv[1], "-P") == 0)) {
        DoublyLinkedList* list = init();
        if (strcmp(argv[4], "-i") == 0) {
            read_csv(list, argv[5]);
        }
        if (strcmp(argv[2], "-i") == 0) {
            read_csv(list, argv[3]);
        }
        if ((strcmp(argv[4], "-i") != 0) && (strcmp(argv[2], "-i") != 0)) {
            scan_list(list);
        }

        if (strcmp(argv[2], "-o") == 0) {
            FILE *file = fopen(argv[3], "w");
            print_table_in_file(list, file);
            fclose(file);
        }
        if (strcmp(argv[4], "-o") == 0) {
            FILE *file = fopen(argv[5], "w");
            print_table_in_file(list, file);
            fclose(file);
        }
        if ((strcmp(argv[4], "-o") != 0) && (strcmp(argv[2], "-o") != 0)) {
            print_table(list);
        }
    }

    return 0;
}
