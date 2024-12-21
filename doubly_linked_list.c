#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>


typedef struct {
    char name[150];
    char surname[50];
    char initials[10];
    char journal_name[100];
    int year;
    int volume;
    bool RSCI;
    int pages;
    int citations;
} Science_pub;

typedef struct Node {
    Science_pub data;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    int size;
} DoublyLinkedList;

// Инициализация списка
DoublyLinkedList* init() {
    DoublyLinkedList* list = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

// Получение текущего размера списка
int get_size(DoublyLinkedList* list) {
    return list->size;
}

// Получение произвольного элемента по индексу
Science_pub* get_at_index(DoublyLinkedList* list, int index) {
    if (index < 0 || index >= list->size) {
        return NULL;
    }
    Node* current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return &current->data;
}

// Получение указателей на начало и конец
Node* get_head(DoublyLinkedList* list) {
    return list->head;
}

Node* get_tail(DoublyLinkedList* list) {
    return list->tail;
}

// Получение следующего и предыдущего элемента от указателя
Node* get_next(Node* node) {
    return node->next;
}

Node* get_prev(Node* node) {
    return node->prev;
}

// Добавление элемента в начало
void add_to_front(DoublyLinkedList* list, Science_pub data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = list->head;
    new_node->prev = NULL;
    if (list->head != NULL) {
        list->head->prev = new_node;
    } else {
        list->tail = new_node;
    }
    list->head = new_node;
    list->size++;
}

// Добавление элемента в конец
void add_to_back(DoublyLinkedList* list, Science_pub data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = list->tail;
    if (list->tail != NULL) {
        list->tail->next = new_node;
    } else {
        list->head = new_node;
    }
    list->tail = new_node;
    list->size++;
}

// Добавление элемента в произвольное место
void add_at_index(DoublyLinkedList* list, Science_pub data, int index) {
    if (index < 0 || index > list->size) {
        return;
    }
    if (index == 0) {
        add_to_front(list, data);
        return;
    }
    if (index == list->size) {
        add_to_back(list, data);
        return;
    }
    Node* current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = current;
    new_node->prev = current->prev;
    current->prev->next = new_node;
    current->prev = new_node;
    list->size++;
}

// Удаление элемента из начала
void remove_from_front(DoublyLinkedList* list) {
    if (list->head == NULL) {
        return;
    }
    Node* temp = list->head;
    list->head = list->head->next;
    if (list->head == NULL) {
        list->tail = NULL;
    } else {
        list->head->prev = NULL;
    }
    free(temp);
    list->size--;
}

// Удаление элемента из конца
void remove_from_back(DoublyLinkedList* list) {
    if (list->tail == NULL) {
        return;
    }
    Node* temp = list->tail;
    list->tail = list->tail->prev;
    if (list->tail == NULL) {
        list->head = NULL;
    } else {
        list->tail->next = NULL;
    }
    free(temp);
    list->size--;
}

// Удаление элемента из произвольного места
void remove_at_index(DoublyLinkedList* list, int index) {
    if (index < 0 || index >= list->size) {
        return;
    }
    if (index == 0) {
        remove_from_front(list);
        return;
    }
    if (index == list->size - 1) {
        remove_from_back(list);
        return;
    }
    Node* current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    current->prev->next = current->next;
    current->next->prev = current->prev;
    free(current);
    list->size--;
}

// Замена пары элементов друг на друга
void swap_elements(DoublyLinkedList* list, int index1, int index2) {
    if (index1 < 0 || index1 >= list->size || index2 < 0 || index2 >= list->size) {
        return;
    }
    Node* node1 = list->head;
    for (int i = 0; i < index1; i++) {
        node1 = node1->next;
    }
    Node* node2 = list->head;
    for (int i = 0; i < index2; i++) {
        node2 = node2->next;
    }
    Science_pub temp = node1->data;
    node1->data = node2->data;
    node2->data = temp;
}

// Преобразование массива в структуру-контейнер
void array_to_list(DoublyLinkedList* list, Science_pub* array, int array_size) {
    for (int i = 0; i < array_size; i++) {
        add_to_back(list, array[i]);
    }
}

// Преобразование структуры-контейнера в массив
void list_to_array(DoublyLinkedList* list, Science_pub* array) {
    Node* current = list->head;
    for (int i = 0; i < list->size; i++) {
        array[i] = current->data;
        current = current->next;
    }
}

// Очистка списка
void clear(DoublyLinkedList* list) {
    while (list->head != NULL) {
        remove_from_front(list);
    }
}

// Освобождение памяти
void free_list(DoublyLinkedList* list) {
    clear(list);
    free(list);
}


// Генерация случайных строк
void generate_random_string(char *str, int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < length; i++) {
        int key = rand() % (sizeof(charset) - 1);
        str[i] = charset[key];
    }
    str[length] = '\0';
}

// Функция для генерации случайных данных
void generate_random_science_pub(Science_pub *pub) {
    generate_random_string(pub->name, 149);
    generate_random_string(pub->surname, 49);
    generate_random_string(pub->initials, 9);
    generate_random_string(pub->journal_name, 99);
    pub->year = 1300 + rand() % 725;
    pub->volume = 1 + rand() % 100; 
    pub->RSCI = rand() % 2;
    pub->pages = 1 + rand() % 5000;
    pub->citations = rand() % 100; 
}

// Функция для генерации массива случайных данных
void generate_random_science_pubs_list(DoublyLinkedList* list, int N) {
    for (int i = 0; i < N; i++) {
        Science_pub pub;
        generate_random_science_pub(&pub);
        add_to_back(list, pub);
    }
}
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