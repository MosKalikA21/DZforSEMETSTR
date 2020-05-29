#include "book_list.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Функция вставки первого узла
void push_first_node(BookList* list, Book val);

BookList* create_book_list() {
    // Выделяем память под лист
    BookList* list = (BookList*) malloc(sizeof(BookList));
    if (!list) {
        return NULL;
    }

    // Проставляем указатели на первый и последний элемент NULL
    list->head = NULL;
    list->tail = NULL;

    return list;
}

bool is_book_list_empty(BookList* list) {
    if (!list) {
        return true;
    }

    // Признак пустоты это первый и последний элементы NULL
    return list->head == NULL && list->tail == NULL;
}

BookNode* get_book_node_with_isbn(BookList* list, const char* isbn) {
    if (!list) return NULL;

    // Перебираем все узлы, пока не найдем узел с книгой с нужным ISBN
    BookNode* node = list->head;
    while (node != NULL) {
        if (!strcmp(node->val.isbn, isbn)) return node;
        node = node->next;
    }

    return NULL;
}

void remove_book_node(BookList* list, BookNode* node) {
    if (!list || !node) return;

    // Если в списке 1 узел
    if (node == list->head && node == list->tail) {
        free(node);
        list->head = NULL;
        list->tail = NULL;
        return;
    }

    // Если удаляемый узел -- первый
    if (node == list->head) {
        list->head = node->next;
        list->head->prev = NULL;
        free(node);
    // Если удаляемый узел -- последний
    } else if (node == list->tail) {
        list->tail = node->prev;
        list->tail->next = NULL;
        free(node);
    // Общий случай
    } else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        free(node);
    }
}

void push_book_list(BookList* list, Book book) {
    if (!list) {
        return;
    }

    // Если лист пуст, воспользуемся специальным методом
    if (is_book_list_empty(list)) {
        return push_first_node(list, book);
    }

    // Создаем узел и сохраняем в него книгу
    BookNode* node = (BookNode*) malloc(sizeof(BookNode));
    node->val = book;

    // Соединяем узлы
    node->next = NULL;
    node->prev = list->tail;

    list->tail->next = node;
    // Узел становится последним
    list->tail = node;
}

void push_first_node(BookList* list, Book val) {
    BookNode* node = (BookNode*) malloc(sizeof(BookNode));
    node->val = val;

    node->next = NULL;
    node->prev = NULL;

    list->head = node;
    list->tail = node;
}

void destroy_book_list(BookList* list) {
    if (!list) {
        return;
    }

    // Освобождаем память всех узлов
    BookNode* node = list->head;
    while (node != NULL) {
        BookNode* next_node = node->next;
        free(node);
        node = next_node;
    }

    // Обнуляем указатели
    list->head = NULL;
    list->tail = NULL;

    // Освобождаем память самого листа
    free(list);
}