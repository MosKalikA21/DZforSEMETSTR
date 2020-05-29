cmake_minimum_required(VERSION 3.12)
project(difficulty1 C)

set(CMAKE_C_STANDARD 99)

add_executable(difficulty1 main.c book.c book_list.c auth.c menu.c student.c student_list.c utils.h)