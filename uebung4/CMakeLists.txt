cmake_minimum_required(VERSION 2.8)

project(trie)

list(APPEND CMAKE_C_FLAGS " /wd4996 ")

add_executable(trie trie_test.c)
