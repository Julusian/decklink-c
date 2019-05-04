cmake_minimum_required(VERSION 3.10)
project(examples)

add_executable(list list.c)
target_link_libraries(list decklink_c)

add_executable(output_colour output_colour.c)
target_link_libraries(output_colour decklink_c)

add_executable(output_fading_colour output_fading_colour.c)
target_link_libraries(output_fading_colour decklink_c)

