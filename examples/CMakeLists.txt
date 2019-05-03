cmake_minimum_required(VERSION 3.10)
project(examples)

add_executable(list list.c)
target_link_libraries(list decklink_c)

