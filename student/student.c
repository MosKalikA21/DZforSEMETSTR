#include "student.h"
#include <stdio.h>
#include <string.h>
#include "student_list.h"
#include "utils.h"

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
        buffer[strlen(buffer)-1] = 0;
        push_student_list(list, parse_student(buffer)); // Парсим студента и добавляем в конец листа
    }

    fclose(file);

    return list;
}

// Парсит студента из строки в структуру
Student parse_student(char* string) {
    Student s;

    // Считываем строковые данные книги
    string = read_csv_value(s.id, string);
    string = read_csv_value(s.f, string);
    string = read_csv_value(s.i, string);
    string = read_csv_value(s.o, string);
    string = read_csv_value(s.faculty, string);
    read_csv_value(s.specialty, string);

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
    read_value(id, 16);

    return get_student_node_with_id(list, id);
}

void add_student(struct StudentList* list) {
    if (!list) {
        return;
    }

    Student s;

    printf("Введите номер зачетной книжки: ");
    read_value(s.id, 16);
    if (get_student_node_with_id(list, s.id)) {
        printf("Студент по данной зачетной книжке уже зарегистрирован\n\n");
        return;
    }

    printf("Введите фамилию студента: ");
    read_value(s.f, 128);

    printf("Введите имя студента: ");
    read_value(s.i, 128);

    printf("Введите отчество студента: ");
    read_value(s.o, 128);

    printf("Введите факультет студента: ");
    read_value(s.faculty, 8);

    printf("Введите специальность студента: ");
    read_value(s.specialty, 256);

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
    read_value(buffer, 16);
    if (strlen(buffer) != 0) {
        snprintf(s->id, 16, "%s", buffer);
    }

    printf("Фамилия: %s\n", s->f);
    printf("Новое значение: ");
    read_value(buffer, 128);
    if (strlen(buffer) != 0) {
        snprintf(s->f, 128, "%s", buffer);
    }

    printf("Имя: %s\n", s->i);
    printf("Новое значение: ");
    read_value(buffer, 128);
    if (strlen(buffer) != 0) {
        snprintf(s->i, 128, "%s", buffer);
    }

    printf("Отчество: %s\n", s->o);
    printf("Новое значение: ");
    read_value(buffer, 128);
    if (strlen(buffer) != 0) {
        snprintf(s->o, 128, "%s", buffer);
    }

    printf("Факультет: %s\n", s->faculty);
    printf("Новое значение: ");
    read_value(buffer, 8);
    if (strlen(buffer) != 0) {
        snprintf(s->faculty, 8, "%s", buffer);
    }

    printf("Специальность: %s\n", s->specialty);
    printf("Новое значение: ");
    read_value(buffer, 256);
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