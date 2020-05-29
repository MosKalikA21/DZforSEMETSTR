#ifndef DIFFICULTY1_STUDENT_LIST_H
#define DIFFICULTY1_STUDENT_LIST_H

#include <stdbool.h>
#include "student.h"

// Структура данных лист
typedef struct StudentNode {
    Student val;
    struct StudentNode* next;
    struct StudentNode* prev;
} StudentNode;

// Узел листа
typedef struct StudentList {
    StudentNode* head;
    StudentNode* tail;
} StudentList;

// Создает пустой лист
StudentList* create_student_list();
// Возвращает флаг, пустой ли лист
bool is_student_list_empty(StudentList* list);
// Возвращает узел с указанным ID, если такого узла нет, то NULL
StudentNode* get_student_node_with_id(StudentList* list, const char* id);
// Удаляет переданный узел из списка
void remove_student_node(StudentList* list, StudentNode* node);
// Добавляет студента в конец списка
void push_student_list(StudentList* list, Student student);
// Освобождает память, занимаемую листом
void destroy_student_list(StudentList* list);

#endif //DIFFICULTY1_STUDENT_LIST_H
