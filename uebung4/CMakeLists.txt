cmake_minimum_required(VERSION 2.8)

project(trie)

if (MSVC)
	list(APPEND CMAKE_C_FLAGS " /wd4996 ")
endif()

add_executable(trie trie_test.c)
