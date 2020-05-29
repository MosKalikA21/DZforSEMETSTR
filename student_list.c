#include "student_list.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Функция вставки первого узла
void push_student_first_node(StudentList* list, Student val);

StudentList* create_student_list() {
    // Выделяем память под лист
    StudentList* list = (StudentList*) malloc(sizeof(StudentNode));
    if (!list) {
        return NULL;
    }

    // Проставляем указатели на первый и последний элемент NULL
    list->head = NULL;
    list->tail = NULL;

    return list;
}

bool is_student_list_empty(StudentList* list) {
    if (!list) {
        return true;
    }

    // Признак пустоты это первый и последний элементы NULL
    return list->head == NULL && list->tail == NULL;
}

StudentNode* get_student_node_with_id(StudentList* list, const char* id) {
    if (!list) return NULL;

    // Перебираем все узлы, пока не найдем студента с нужным ID
    StudentNode* node = list->head;
    while (node != NULL) {
        if (!strcmp(node->val.id, id)) return node;
        node = node->next;
    }

    return NULL;
}

void remove_student_node(StudentList* list, StudentNode* node) {
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

void push_student_list(StudentList* list, Student book) {
    if (!list) {
        return;
    }

    // Если лист пуст, воспользуемся специальным методом
    if (is_student_list_empty(list)) {
        return push_student_first_node(list, book);
    }

    // Создаем узел и сохраняем в него студента
    StudentNode* node = (StudentNode*) malloc(sizeof(StudentNode));
    node->val = book;

    // Соединяем узлы
    node->next = NULL;
    node->prev = list->tail;

    list->tail->next = node;
    // Узел становится последним
    list->tail = node;
}

void push_student_first_node(StudentList* list, Student val) {
    StudentNode* node = (StudentNode*) malloc(sizeof(StudentNode));
    node->val = val;

    node->next = NULL;
    node->prev = NULL;

    list->head = node;
    list->tail = node;
}

void destroy_student_list(StudentList* list) {
    if (!list) {
        return;
    }

    // Освобождаем память всех узлов
    StudentNode* node = list->head;
    while (node != NULL) {
        StudentNode* next_node = node->next;
        free(node);
        node = next_node;
    }

    // Обнуляем указатели
    list->head = NULL;
    list->tail = NULL;

    // Освобождаем память самого листа
    free(list);
}