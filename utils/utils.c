#include "utils.h"
#include <stdio.h>
#include <string.h>

char* read_csv_value(char* dst, char* src) {
    // Ищем подстроку ";" p - это указатель на первый символ ";" в строке
    char* p = strstr(src, ";");
    if (p) {
        // Копируем строку в структуру книги (p-string+1 -- количество символов от начала строки до ";")
        snprintf(dst, p-src+1, "%s", src);
    } else {
        // Копируем всю строку до конца (считаем, что строка не превышает 255 символов)
        snprintf(dst, 256, "%s", src);
    }

    // Вовзращаем указатель строки на следующий после ";" символ
    return p+1;
}

void read_value(char* buffer, int size) {
    fgets(buffer, size, stdin);
    // Проставляем нуль-терминант в последний символ строки, т.к. fgets записывает туда "\n"
    buffer[strlen(buffer)-1] = 0;
}

void discard_unused_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}