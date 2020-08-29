cmake_minimum_required(VERSION 3.14)
# SET(CMAKE_C_COMPILER "C:/MinGW/bin/gcc.exe")
SET(CMAKE_C_COMPILER 
    "C:/Program Files/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/bin/gcc.exe"
)
SET(CMAKE_CXX_COMPILER 
    "C:/Program Files/mingw-w64/x86_64-8.1.0-posix-seh-rt_v6-rev0/mingw64/bin/g++.exe"
)
set(CMAKE_CXX_STANDARD 14)

project(noise-filters CXX)

add_executable(main main.cpp)
target_include_directories(main PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_include_directories(main PUBLIC "${CMAKE_SOURCE_DIR}/dependencies/include")


# add_subdirectory(include)
add_subdirectory(src)
# add_subdirectory(test)

# add_executable(nf main)
# target_include_directories(nf PUBLIC "${CMAKE_SOURCE_DIR}/include")
# target_include_directories(nf PUBLIC "${CMAKE_SOURCE_DIR}/dependencies/include")
target_compile_options(main PUBLIC "-DSFML_STATIC")
target_link_directories(main PUBLIC "${CMAKE_SOURCE_DIR}/dependencies/lib")




target_link_libraries(main
    PUBLIC 
    libsfml-graphics-s.a
    libsfml-window-s.a
    libsfml-system-s.a
    pthread
    opengl32
    winmm
    gdi32
    freetype 
)
