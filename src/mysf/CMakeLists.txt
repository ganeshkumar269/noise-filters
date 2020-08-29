target_sources(
    main PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/grayToMono.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/mean.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/rgbToGray.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/variance.cpp"
)

target_include_directories(main PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_include_directories(main PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_include_directories(main PUBLIC "${CMAKE_SOURCE_DIR}/dependencies/include")

# add_library(
#     mysf
#     grayToMono.cpp
#     mean.cpp
#     rgbToGray.cpp
#     variance.cpp
# )
# target_compile_options(mysf PUBLIC "-DSFML_STATIC")
# # target_compile_options(src PUBLIC "-pthread")
# target_include_directories(mysf PUBLIC "${CMAKE_SOURCE_DIR}/include")
# target_include_directories(mysf PUBLIC "${CMAKE_SOURCE_DIR}/dependencies/include")
# target_link_directories(mysf PUBLIC "${CMAKE_SOURCE_DIR}/dependencies/lib")

# target_link_libraries(mysf
#     PUBLIC 
#     libsfml-graphics-s.a
#     libsfml-window-s.a
#     libsfml-system-s.a
#     pthread
#     libopengl32.a
#     libwinmm.a
#     libgdi32.a
#     libfreetype.a 
# )