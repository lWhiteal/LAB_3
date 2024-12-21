#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doubly_linked_list.h"
#include "bubble_sort.h"


void read_csv(DoublyLinkedList *list, const char *filename) {
    FILE *file = fopen(filename, "r");
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        Science_pub data;
        char *token;

        token = strtok(line, ",");
        if (token) strncpy(data.name, token, sizeof(data.name) - 1);

        token = strtok(NULL, ",");
        if (token) strncpy(data.surname, token, sizeof(data.surname) - 1);

        token = strtok(NULL, ",");
        if (token) strncpy(data.initials, token, sizeof(data.initials) - 1);

        token = strtok(NULL, ",");
        if (token) strncpy(data.journal_name, token, sizeof(data.journal_name) - 1);

        token = strtok(NULL, ",");
        if (token) data.year = atoi(token);

        token = strtok(NULL, ",");
        if (token) data.volume = atoi(token);

        token = strtok(NULL, ",");
        if (token) data.RSCI = atoi(token);

        token = strtok(NULL, ",");
        if (token) data.pages = atoi(token);

        token = strtok(NULL, ",");
        if (token) data.citations = atoi(token);

        add_to_back(list, data);
    }


    fclose(file);
}

void bubble_sort(DoublyLinkedList *list) {
    if (list->head == NULL) {
        return;
    }

    int swapped;
    do {
        swapped = 0;
        for (int i = 0; i < list->size - 1; i++) {
            if (strcmp(list->head->data.name, list->head->next->data.name) > 0) {
                swap_elements(list, i, i + 1);
                swapped = 1;
            }
            list->head = list->head->next;
        }
        list->head = list->head->prev;
    } while (swapped);
}


