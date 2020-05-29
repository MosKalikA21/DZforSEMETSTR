#include "menu.h"
#include "auth.h"

const char* USERS_FILENAME = "../db/users.csv";

int main() {
    // Получаем режим авторизации
    AuthMode mode = auth(USERS_FILENAME);
    if (mode == ERROR) {
        printf("Во время авторизации произошла ошибка\n");
        return 1;
    }

    if (mode == BOOKS) {
        run_book_menu(false);
    } else if (mode == STUDENTS) {
        run_students_menu(false);
    } else if (mode == ALL) {
        run_all_menu();
    }
}

