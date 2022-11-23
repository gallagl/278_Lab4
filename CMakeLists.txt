cmake_minimum_required(VERSION 3.23)
project(278_Lab4)

set(CMAKE_CXX_STANDARD 14)

add_executable(LAB4_AVL.c LAB4_AVL.c)
add_executable(bst.c bst.c)
add_executable(bintree.c bintree.c)
add_executable(main.c main.c LAB4_AVL.c LAB4_AVL.h bintree.c bintree.h)
add_executable(LAB4_MAINB.c LAB4_MAINB.c LAB4_AVL.c LAB4_AVL.h bintree.c bintree.h)
add_executable(MakeRandom.c MakeRandom.c)
add_executable(deleteAVL.c deleteAVL.c)
add_executable(LAB4_BST.c LAB4_BST.c)

