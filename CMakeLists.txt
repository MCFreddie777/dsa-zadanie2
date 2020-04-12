cmake_minimum_required(VERSION 3.14)
project(DSA-Zadanie2)

add_executable(avl src/bst/avl/avl-test.c)
add_executable(red-black src/bst/red-black/red-black-test.c)
add_executable(quadratic-probing src/hashmap/quadratic-probing/quadratic-probing-test.c)
add_executable(chaining src/hashmap/chaining/chaining-test.c)