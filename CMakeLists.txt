cmake_minimum_required(VERSION 3.16)
project(University C)

set(CMAKE_C_STANDARD 99)

# Semester 1
add_executable(S1Optional1 semester1/optionals/optional1.c)
add_executable(S1Optional2 semester1/optionals/optional2.c)
add_executable(S1Optional3 semester1/optionals/optional3.c)
add_executable(S1Optional4 semester1/optionals/optional4.c)

add_executable(S1Final1 semester1/finals/final1.c)
add_executable(S1Final2 semester1/finals/final2.c)
add_executable(S1Final3 semester1/finals/final3.c)

add_executable(S1Frog semester1/projects/frog.c)

# Semester 2
add_executable(S2Matrices semester2/exercises/matrices.c)

add_executable(S2CinemaProject semester2/projects/cinema.c)
add_executable(S2WordSearch semester2/projects/word_search.c)

add_executable(S2Test1 semester2/tests/test1.c)

# Semester 3
add_executable(S3Diagnosis semester3/diagnosis/diagnosis.c)
