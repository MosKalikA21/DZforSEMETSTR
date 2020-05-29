#ifndef DZ_SEM2_BOOK_H
#define DZ_SEM2_BOOK_H

#include <stdbool.h>

// Forward declaration
// Нельзя заинклюдить book_list.h, т.к. book_list.h инклюдит этот файл
struct BookList;
struct BookNode;

// Книга
typedef struct Book {
    char isbn[16];
    char authors[256];
    char title[256];
    int count;
    int available;
} Book;

// Восстанавливает состояние библиотеки из файла
struct BookList* read_books_from_file(const char* filename);
// Сохраняет состояние библиотеки в файл
void write_books_to_file(struct BookList*, const char* filename);
// Парсит книгу из строки в структуру
Book parse_book(char* string);
// Читает с консоли ISBN и получает из библиотеки-листа узел с книгой с таким ISBN, иначе NULL
struct BookNode* get_book_node(struct BookList*);
// Читает с консоли данные книги и добавляет ее в библиотеку
void add_book_to_library(struct BookList*);
// Использует get_book_node, чтобы получить узел, который нужно удалить и удаляет его из библиотеки
void remove_book_from_library(struct BookList*);
// Использует get_book_node, полученному узлу уменьшает количество доступных книг (если их > 0)
void give_book(struct BookList*);
// Использует get_book_node, полученному узлу увеличивает количество доступных книг (если их < book.count)
void return_book(struct BookList*);

#endif //DZ_SEM2_BOOK_H
