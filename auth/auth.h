#ifndef DIFFICULTY1_AUTH_H
#define DIFFICULTY1_AUTH_H

#include <stdio.h>
#include <stdbool.h>

// Режим авторизации
typedef enum AuthMode {
    BOOKS,
    STUDENTS,
    ALL,
    ERROR
} AuthMode;

// Структура пользователя
typedef struct User {
    char login[256];
    char password[256];
    int books_permission;
    int students_permission;
} User;

// Авторизирует пользователя, читая логин/пароль с консоли возвращая режим авторизации
AuthMode auth(const char* filename);
// Ищет юзера по логину и возвращает успех поиска
bool find_user(FILE* file, User* user);
// Парсит строку в структуру юзера, если логин совпадает с искомым
bool parse_user_if_login(char* string, User* user);

#endif //DIFFICULTY1_AUTH_H
