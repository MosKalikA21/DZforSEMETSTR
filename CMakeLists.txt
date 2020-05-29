cmake_minimum_required(VERSION 3.12)
project(difficulty1 C)

set(CMAKE_C_STANDARD 99)

include_directories(. book student menu auth)
add_executable(difficulty1
        main.c
        book/book.c book/book_list.c
        auth/auth.c
        menu/menu.c
        student/student.c student/student_list.c
)