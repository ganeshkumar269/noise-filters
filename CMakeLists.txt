cmake_minimum_required(VERSION 3.14)
project(noise-filters VERSION 0.0.1 LANGUAGES CXX)

add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(test)

add_executable(main main.cpp)

target_link_libraries(main PUBLIC src)