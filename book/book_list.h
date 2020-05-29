#ifndef DZ_SEM2_BOOK_ARRAY_H
#define DZ_SEM2_BOOK_ARRAY_H

#include <stdbool.h>
#include "book.h"

// Структура данных лист
typedef struct BookNode {
    Book val;
    struct BookNode* next;
    struct BookNode* prev;
} BookNode;

// Узел листа
typedef struct BookList {
    BookNode* head;
    BookNode* tail;
} BookList;

// Создает пустой лист
BookList* create_book_list();
// Возвращает флаг, пустой ли лист
bool is_book_list_empty(BookList* list);
// Возвращает узел с указанным ISBN, если такого узла нет, то NULL
BookNode* get_book_node_with_isbn(BookList* list, const char* isbn);
// Удаляет переданный узел из списка
void remove_book_node(BookList* list, BookNode* node);
// Добавляет книгу в конец списка
void push_book_list(BookList* list, Book book);
// Освобождает память, занимаемую листом
void destroy_book_list(BookList* list);

#endif //DZ_SEM2_BOOK_ARRAY_H
