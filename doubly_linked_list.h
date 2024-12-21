#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H
#include <stdbool.h>

// Структура данных для хранения научных публикаций
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

// Структура узла двусвязного списка
typedef struct Node {
    Science_pub data;
    struct Node* next;
    struct Node* prev;
} Node;

// Структура двусвязного списка
typedef struct {
    Node* head;
    Node* tail;
    int size;
} DoublyLinkedList;

// Инициализация списка
DoublyLinkedList* init();

// Получение текущего размера списка
int get_size(DoublyLinkedList* list);

// Получение произвольного элемента по индексу
Science_pub* get_at_index(DoublyLinkedList* list, int index);

// Получение указателей на начало и конец
Node* get_head(DoublyLinkedList* list);
Node* get_tail(DoublyLinkedList* list);

// Получение следующего и предыдущего элемента от указателя
Node* get_next(Node* node);
Node* get_prev(Node* node);

// Добавление элемента в начало
void add_to_front(DoublyLinkedList* list, Science_pub data);

// Добавление элемента в конец
void add_to_back(DoublyLinkedList* list, Science_pub data);

// Добавление элемента в произвольное место
void add_at_index(DoublyLinkedList* list, Science_pub data, int index);

// Удаление элемента из начала
void remove_from_front(DoublyLinkedList* list);

// Удаление элемента из конца
void remove_from_back(DoublyLinkedList* list);

// Удаление элемента из произвольного места
void remove_at_index(DoublyLinkedList* list, int index);

// Замена пары элементов друг на друга
void swap_elements(DoublyLinkedList* list, int index1, int index2);

// Преобразование массива в структуру-контейнер
void array_to_list(DoublyLinkedList* list, Science_pub* array, int array_size);

// Преобразование структуры-контейнера в массив
void list_to_array(DoublyLinkedList* list, Science_pub* array);

// Очистка списка
void clear(DoublyLinkedList* list);

// Освобождение памяти
void free_list(DoublyLinkedList* list);

// Генерация случайных строк
void generate_random_string(char *str, int length);

// Функция для генерации случайных данных
void generate_random_science_pub(Science_pub *pub);

// Функция для генерации массива случайных данных
void generate_random_science_pubs_list(DoublyLinkedList* list, int N);

void read_csv(DoublyLinkedList *list, const char *filename);

void bubble_sort(DoublyLinkedList *list);

#endif // DOUBLY_LINKED_LIST_H

