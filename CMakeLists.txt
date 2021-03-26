cmake_minimum_required(VERSION 3.16)
project(University C)

set(CMAKE_C_STANDARD 99)

# Semester 1
add_executable(S1Optional1 s1/optional/optional1.c)
add_executable(S1Optional2 s1/optional/optional2.c)
add_executable(S1Optional3 s1/optional/optional3.c)
add_executable(S1Optional4 s1/optional/optional4.c)

add_executable(S1Final1 s1/final/final1.c)
add_executable(S1Final2 s1/final/final2.c)
add_executable(S1Final3 s1/final/final3.c)

add_executable(Frog s1/frog.c)

# Semester 2
add_executable(S2Matrices s2/exercises/matrices.c)

add_executable(S2CinemaProject s2/projects/cinema.c)
add_executable(S2WordSearch s2/projects/word_search.c)

add_executable(S2Test1 s2/tests/test1.c)

# Semester 3
add_executable(S3Diagnosis s3/diagnosis/diagnosis1.c)
