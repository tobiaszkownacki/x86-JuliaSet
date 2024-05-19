cmake_minimum_required(VERSION 3.20)
project(julia)

# assemble
enable_language(ASM_NASM)
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> <FLAGS> -f elf64 -o <OBJECT> <SOURCE>")

# executable
add_executable(julia julia_set.asm main.c)

# allegro
TARGET_LINK_LIBRARIES(julia allegro)