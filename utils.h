#ifndef DIFFICULTY1_UTILS_H
#define DIFFICULTY1_UTILS_H

#include <stdio.h>

// Используется, чтобы "перескочить" через неиспользуемые символы из stdin
void discard_unused_input() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

#endif //DIFFICULTY1_UTILS_H
