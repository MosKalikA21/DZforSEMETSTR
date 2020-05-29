#ifndef DIFFICULTY1_AUTH_H
#define DIFFICULTY1_AUTH_H

#include <stdio.h>
#include <stdbool.h>

typedef enum AuthMode {
    BOOKS,
    STUDENTS,
    ALL,
    ERROR
} AuthMode;

typedef struct User {
    char login[256];
    char password[256];
    int books_permission;
    int students_permission;
} User;

AuthMode auth(const char* filename);
bool find_user(FILE* file, User* user);
bool parse_user_if_login(char* string, User* user);

#endif //DIFFICULTY1_AUTH_H
