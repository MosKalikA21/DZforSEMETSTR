#include "book.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "book_list.h"
#include "utils.h"

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

    // Считываем строковые данные книги
    string = read_csv_value(book.isbn, string);
    string = read_csv_value(book.authors, string);
    string = read_csv_value(book.title, string);

    char buffer[16];
    string = read_csv_value(buffer, string);
    book.count = strtol(buffer, NULL, 10); // Конвертируем строку в int

    read_csv_value(buffer, string);
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
    read_value(book.isbn, 16);
    if (get_book_node_with_isbn(list, book.isbn)) {
        printf("Книга по данному ISBN уже имеется в библиотеке\n\n");
        return;
    }

    printf("Введите авторов: ");
    read_value(book.authors, 256);

    printf("Введите название: ");
    read_value(book.title, 256);

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