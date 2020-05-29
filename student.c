#include "student.h"
#include <stdio.h>
#include <string.h>
#include "student_list.h"

StudentList* read_students_from_file(const char* filename) {
    // Открываем файл с режимом на чтение, если не открылся возвращаем NULL
    FILE* file = fopen(filename, "r");
    if (!file) {
        return NULL;
    }

    // Создаем библиотеку
    StudentList * list = create_student_list();
    if (!list) {
        fclose(file); // Закрываем файл, т.к. он уже был открыт
        return list;
    }

    // Заполняем студентов содержимым файла
    char buffer[1024];
    while (fgets(buffer, 1024, file)) {
        push_student_list(list, parse_student(buffer)); // Парсим студента и добавляем в конец листа
    }

    fclose(file);

    return list;
}

// Парсит студента из строки в структуру
Student parse_student(char* string) {
    Student s;

    // Ищем подстроку ";" p - это указатель на первый символ ";" в строке
    char* p = strstr(string, ";");
    // Копируем строку в структуру книги (p-string+1 -- количество символов от начала строки до ";")
    snprintf(s.id, p - string + 1, "%s", string);
    // Перемещаем указатель строки на следующий после ";" символ
    string = p+1;

    p = strstr(string, ";");
    snprintf(s.f, p - string + 1, "%s", string);
    string = p+1;

    p = strstr(string, ";");
    snprintf(s.i, p - string + 1, "%s", string);
    string = p+1;

    p = strstr(string, ";");
    snprintf(s.o, p - string + 1, "%s", string);
    string = p+1;

    p = strstr(string, ";");
    snprintf(s.faculty, p - string + 1, "%s", string);
    string = p+1;

    snprintf(s.specialty, 256, "%s", string);
    size_t len = strlen(s.specialty);
    if (s.specialty[len - 1] == '\n') {
        s.specialty[len - 1] = 0;
    }

    return s;
}

void write_students_to_file(struct StudentList* list, const char* filename) {
    if (!list) {
        return;
    }

    // Открываем файл с режимом на запись
    FILE* file = fopen(filename, "w");
    if (!file) {
        return;
    }

    // Перебираем весь список. Когда доберемся до конца списка итератор node будет NULL
    StudentNode * node = list->head;
    while (node != NULL) {
        Student* s = &node->val;
        // Сохраняем в файл строки записей в формате CSV
        fprintf(file, "%s;%s;%s;%s;%s;%s\n", s->id, s->f, s->i, s->o, s->faculty, s->specialty);

        node = node->next;
    }

    fclose(file);
}

StudentNode* get_student_node(struct StudentList* list) {
    if (!list) {
        return NULL;
    }

    char id[16];
    printf("Введите номер зачетной книжки: ");
    fgets(id, 16, stdin);
    id[strlen(id)-1] = 0; // Проставляем нуль-терминант в последний символ строки, т.к. fgets записывает туда "\n"

    return get_student_node_with_id(list, id);
}

void add_student(struct StudentList* list) {
    if (!list) {
        return;
    }

    Student s;

    printf("Введите номер зачетной книжки: ");
    fgets(s.id, 16, stdin);
    // Проставляем нуль-терминант в последний символ строки, т.к. fgets записывает туда "\n"
    s.id[strlen(s.id)-1] = 0;
    if (get_student_node_with_id(list, s.id)) {
        printf("Студент по данной зачетной книжке уже зарегистрирован\n\n");
        return;
    }

    printf("Введите фамилию студента: ");
    fgets(s.f, 128, stdin);
    s.f[strlen(s.f) - 1] = 0;

    printf("Введите имя студента: ");
    fgets(s.i, 128, stdin);
    s.i[strlen(s.i) - 1] = 0;

    printf("Введите отчество студента: ");
    fgets(s.o, 128, stdin);
    s.o[strlen(s.o) - 1] = 0;

    printf("Введите факультет студента: ");
    fgets(s.faculty, 8, stdin);
    s.faculty[strlen(s.faculty) - 1] = 0;

    printf("Введите специальность студента: ");
    fgets(s.specialty, 256, stdin);
    s.specialty[strlen(s.specialty) - 1] = 0;

    push_student_list(list, s);
    printf("\nСтудент успешно зарегистрирован\n\n");
}

void remove_student(struct StudentList* list) {
    if (!list) {
        return;
    }

    StudentNode * node = get_student_node(list);
    if (!node) {
        printf("Студента с таким номером зачетной книжки нет\n\n");
        return;
    }

    remove_student_node(list, node);

    printf("\nСтудент успешно удален\n\n");
}

void read_student_value(char buffer[]) {
    fgets(buffer, 256, stdin);
    buffer[strlen(buffer)-1] = 0;
}

void edit_student(struct StudentList* list) {
    if (!list) {
        return;
    }

    StudentNode* node = get_student_node(list);
    if (!node) {
        printf("Студента с таким номером зачетной книжки нет\n\n");
        return;
    }

    Student* s = &node->val;
    printf("Правила редактирования: введите новое значение поля,"
           " или оставьте его пустым, если хотите оставить старое значение\n");

    char buffer[256];

    printf("Номер зачетной книжки: %s\n", s->id);
    printf("Новое значение: ");
    read_student_value(buffer);
    if (strlen(buffer) != 0) {
        snprintf(s->id, 16, "%s", buffer);
    }

    printf("Фамилия: %s\n", s->f);
    printf("Новое значение: ");
    read_student_value(buffer);
    if (strlen(buffer) != 0) {
        snprintf(s->f, 128, "%s", buffer);
    }

    printf("Имя: %s\n", s->i);
    printf("Новое значение: ");
    read_student_value(buffer);
    if (strlen(buffer) != 0) {
        snprintf(s->i, 128, "%s", buffer);
    }

    printf("Отчество: %s\n", s->o);
    printf("Новое значение: ");
    read_student_value(buffer);
    if (strlen(buffer) != 0) {
        snprintf(s->o, 128, "%s", buffer);
    }

    printf("Факультет: %s\n", s->faculty);
    printf("Новое значение: ");
    read_student_value(buffer);
    if (strlen(buffer) != 0) {
        snprintf(s->faculty, 8, "%s", buffer);
    }

    printf("Специальность: %s\n", s->specialty);
    printf("Новое значение: ");
    read_student_value(buffer);
    if (strlen(buffer) != 0) {
        snprintf(s->specialty, 256, "%s", buffer);
    }

    printf("\nСтудент успешно отредактирован\n\n");
}

void show_student(struct StudentList* list) {
    if (!list) {
        return;
    }

    StudentNode* node = get_student_node(list);
    if (!node) {
        printf("Студента с таким номером зачетной книжки нет\n\n");
        return;
    }

    Student* s = &node->val;
    printf("Студент:\n");
    printf("\tНомер зачетной книжки: %s\n"
           "\tФИО: %s %s %s\n"
           "\tФакультет: %s\n"
           "\tСпециальность: %s\n\n", s->id, s->f, s->i, s->o, s->faculty, s->specialty);
}