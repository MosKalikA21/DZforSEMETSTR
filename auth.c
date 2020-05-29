#include "auth.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AuthMode auth(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        return ERROR;
    }

    User user;

    printf("Введите логин: ");
    scanf("%255s", user.login);

    char password[256];
    printf("Введите пароль: ");
    scanf("%255s", password);

    if (!find_user(file, &user) || strcmp(user.password, password)) {
        fclose(file);
        return ERROR;
    }

    AuthMode mode;
    if (user.students_permission == 1 && user.books_permission == 1) {
        mode = ALL;
    } else if (user.books_permission == 1) {
        mode = BOOKS;
    } else if (user.students_permission == 1) {
        mode = STUDENTS;
    } else {
        mode = ERROR;
    }

    fclose(file);

    return mode;
}

bool find_user(FILE* file, User* user) {
    char buffer[512];
    while (fgets(buffer, 512, file)) {
        if (parse_user_if_login(buffer, user)) {
            return true;
        }
    }

    return false;
}

bool parse_user_if_login(char* string, User* user) {
    char login[256];

    char* p = strstr(string, ";");
    snprintf(login, p-string+1, "%s", string);
    string = p+1;

    if (strcmp(user->login, login)) {
        return false;
    }

    p = strstr(string, ";");
    snprintf(user->password, p-string+1, "%s", string);
    string = p+1;

    p = strstr(string, ";");
    user->books_permission = strtol(string, NULL, 10);
    string = p+1;

    user->students_permission = strtol(string, NULL, 10);

    return true;
}