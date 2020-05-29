#include "book.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "book_list.h"

BookList* read_books_from_file(const char* filename) {
    // Открываем файл с режимом на чтение, если не открылся возвращаем NULL
    FILE* file = fopen(filename, "r");
    if (!file) {
        return NULL;
    }

    // Создаем библиотеку
    BookList* list = create_book_list();
    if (!list) {
        fclose(file); // Закрываем файл, т.к. он уже был открыт
        return list;
    }

    // Заполняем библиотеку содержимым файла
    char buffer[1024];
    while (fgets(buffer, 1024, file)) {
        push_book_list(list, parse_book(buffer)); // Парсим книгу и добавляем в конец листа
    }

    fclose(file);

    return list;
}

Book parse_book(char* string) {
    Book book;

    // Ищем подстроку ";" p - это указатель на первый символ ";" в строке
    char* p = strstr(string, ";");
    // Копируем строку в структуру книги (p-string+1 -- количество символов от начала строки до ";")
    snprintf(book.isbn, p-string+1, "%s", string);
    // Перемещаем указатель строки на следующий после ";" символ
    string = p+1;

    p = strstr(string, ";");
    snprintf(book.authors, p-string+1, "%s", string);
    string = p+1;

    p = strstr(string, ";");
    snprintf(book.title, p-string+1, "%s", string);
    string = p+1;

    p = strstr(string, ";");
    // Конвертируем строку в int. Число будет взято до первого невалидного символа (в данном случае ";") или конца строки
    book.count = strtol(string, NULL, 10);
    string = p+1;

    book.available = strtol(string, NULL, 10);

    return book;
}

void write_books_to_file(struct BookList* list, const char* filename) {
    if (!list) {
        return;
    }

    // Открываем файл с режимом на запись
    FILE* file = fopen(filename, "w");
    if (!file) {
        return;
    }

    // Перебираем весь список. Когда доберемся до конца списка итератор node будет NULL
    BookNode* node = list->head;
    while (node != NULL) {
        Book* book = &node->val;
        // Сохраняем в файл строки записей в формате CSV
        fprintf(file, "%s;%s;%s;%d;%d\n", book->isbn, book->authors, book->title, book->count, book->available);

        node = node->next;
    }

    fclose(file);
}

BookNode* get_book_node(struct BookList* list) {
    if (!list) {
        return NULL;
    }

    char isbn[16];
    printf("Введите ISBN: ");
    fgets(isbn, 16, stdin);
    isbn[strlen(isbn)-1] = 0; // Проставляем нуль-терминант в последний символ строки, т.к. fgets записывает туда "\n"

    return get_book_node_with_isbn(list, isbn);
}

void add_book_to_library(BookList* list) {
    if (!list) {
        return;
    }

    Book book;

    printf("Введите ISBN: ");
    fgets(book.isbn, 16, stdin);
    // Проставляем нуль-терминант в последний символ строки, т.к. fgets записывает туда "\n"
    book.isbn[strlen(book.isbn)-1] = 0;
    if (get_book_node_with_isbn(list, book.isbn)) {
        printf("Книга по данному ISBN уже имеется в библиотеке\n\n");
        return;
    }

    printf("Введите авторов: ");
    fgets(book.authors, 256, stdin);
    book.authors[strlen(book.authors)-1] = 0;

    printf("Введите название: ");
    fgets(book.title, 256, stdin);
    book.title[strlen(book.title)-1] = 0;

    printf("Введите количество книг: ");
    scanf("%d", &book.count);

    book.available = book.count;

    push_book_list(list, book);
    printf("\nКнига успешно добавлена в библиотеку\n\n");
}

void remove_book_from_library(BookList* list) {
    if (!list) {
        return;
    }

    BookNode* node = get_book_node(list);
    if (!node) {
        printf("Книги по данному ISBN нет в библиотеке\n\n");
        return;
    }

    remove_book_node(list, node);

    printf("\nКнига успешно удалена\n\n");
}

void give_book(BookList* list) {
    if (!list) {
        return;
    }

    BookNode* node = get_book_node(list);
    if (!node) {
        printf("Книги по данному ISBN нет в библиотеке\n\n");
        return;
    }

    if (node->val.available == 0) {
        printf("Нет доступных книг\n");
        return;
    }

    node->val.available -= 1;

    printf("\nКнига успешно выдана\n\n");
}

void return_book(BookList* list) {
    if (!list) {
        return;
    }

    BookNode* node = get_book_node(list);
    if (!node) {
        printf("Книги по данному ISBN нет в библиотеке\n\n");
        return;
    }

    if (node->val.available == node->val.count) {
        printf("Все доступные книги уже в библиотеке\n");
        return;
    }

    node->val.available += 1;

    printf("\nКнига успешно возвращена\n\n");
}