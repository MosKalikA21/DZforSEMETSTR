#ifndef DIFFICULTY1_STUDENT_H
#define DIFFICULTY1_STUDENT_H

// Forward declaration
// Нельзя заинклюдить student_list.h, т.к. student_list.h инклюдит этот файл
struct StudentNode;
struct StudentList;

typedef struct Student {
    char id[16];
    char f[128];
    char i[128];
    char o[128];
    char faculty[8];
    char specialty[256];
} Student;

// Восстанавливает состояние студентов из файла
struct StudentList* read_students_from_file(const char* filename);
// Сохраняет состояние студентов в файл
void write_students_to_file(struct StudentList* list, const char* filename);
// Парсит студента из строки в структуру
Student parse_student(char* string);
// Читает с консоли ID и получает из листа студентов узел со студентом с таким ID, иначе NULL
struct StudentNode* get_student_node(struct StudentList*);
// Читает с консоли данные студента и добавляет в лист студентов
void add_student(struct StudentList*);
// Использует get_student_node, чтобы получить узел, который нужно удалить и удаляет его
void remove_student(struct StudentList*);
// Использует get_student_node, чтобы получить узел, который нужно отредактировать
void edit_student(struct StudentList*);
// Использует get_student_node, чтобы получить узел, и выводит в консоль данные студента
void show_student(struct StudentList*);

#endif //DIFFICULTY1_STUDENT_H
