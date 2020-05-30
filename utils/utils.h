#ifndef DIFFICULTY1_UTILS_H
#define DIFFICULTY1_UTILS_H

// Читает значение в строке до ";", копирует его в dst
char* read_csv_value(char* dst, char* src);

// Читает строку с stdin
void read_value(char* buffer, int size);

// Используется, чтобы "перескочить" через неиспользуемые символы из stdin
void discard_unused_input();

#endif //DIFFICULTY1_UTILS_H
