#include "menu.h"

#include <stdio.h>
#include "book.h"
#include "book_list.h"
#include "student.h"
#include "student_list.h"
#include "utils.h"

// Пути к csv файлам
const char* BOOK_FILENAME = "../db/books.csv";
const char* STUDENTS_FILENAME = "../db/students.csv";

bool run_book_menu(bool can_return) {
    BookList* book_list = read_books_from_file(BOOK_FILENAME);

    if (!book_list) {
        printf("Не удалось загрузить библиотеку\n");
        return false;
    }

    bool should_return = false;

    while (true) {
        printf("Команды:\n");
        if (can_return) {
            printf("0 - вернуться в основное меню\n");
        }
        printf("1 - Добавить новую книгу\n2 - Удалить книгу\n"
               "3 - Выдать книгу\n4 - Вернуть книгу\n5 - Завершить работу\n\n");

        int cmd;
        scanf("%d", &cmd);
        discard_unused_input();

        if (cmd == 0 && can_return) {
            should_return = true;
            break;
        } else if (cmd == 1) {
            add_book_to_library(book_list);
        } else if (cmd == 2) {
            remove_book_from_library(book_list);
        } else if (cmd == 3) {
            give_book(book_list);
        } else if (cmd == 4) {
            return_book(book_list);
        } else if (cmd == 5) {
            printf("Работа с библиотекой завершена\n\n");
            break;
        } else {
            printf("Неизвестная команда\n\n");
        }
    }

    write_books_to_file(book_list, BOOK_FILENAME);
    destroy_book_list(book_list);

    return should_return;
}

bool run_students_menu(bool can_return) {
    StudentList* list = read_students_from_file(STUDENTS_FILENAME);
    if (!list) {
        printf("Не удалось загрузить студентов\n");
        return false;
    }

    bool should_return = false;

    while (true) {
        printf("Команды:\n");
        if (can_return) {
            printf("0 - вернуться в основное меню\n");
        }
        printf("1 - Добавить студента\n2 - Удалить студента\n"
               "3 - Редактировать данные студента\n4 - Показать данные студента\n5 - Завершить работу\n\n");

        int cmd;
        scanf("%d", &cmd);
        discard_unused_input();

        if (cmd == 0 && can_return) {
            should_return = true;
            break;
        } else if (cmd == 1) {
            add_student(list);
        } else if (cmd == 2) {
            remove_student(list);
        } else if (cmd == 3) {
            edit_student(list);
        } else if (cmd == 4) {
            show_student(list);
        } else if (cmd == 5) {
            printf("Работа со студентами завершена\n\n");
            break;
        } else {
            printf("Неизвестная команда\n\n");
        }
    }

    write_students_to_file(list, STUDENTS_FILENAME);
    destroy_student_list(list);

    return should_return;
}

bool run_all_menu() {
    bool should_continue = true;

    while (should_continue) {
        printf("Команды:\n");
        printf("1 - Меню книг\n2 - Меню студентов\n3 - Завершить работу\n\n");

        int cmd;
        scanf("%d", &cmd);
        discard_unused_input();

        if (cmd == 1) {
            should_continue = run_book_menu(true);
        } else if (cmd == 2) {
            should_continue = run_students_menu(true);
        } else if (cmd == 3) {
            should_continue = false;
        } else {
            printf("Неизвестная команда\n\n");
        }
    }
}