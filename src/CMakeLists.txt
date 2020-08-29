
add_subdirectory(mysf)
add_subdirectory(noisefilters)
add_subdirectory(noisemodels)
add_subdirectory(misc)
# target_compile_definitions(src PUBLIC _WIN32_WINNT=0x0501)

# add_library(
#     src
#     mysf 
#     noisemodels
#     noisefilters
#     misc
# )
# target_compile_options(src PUBLIC "-DSFML_STATIC")
# # target_compile_options(src PUBLIC "-pthread")
# target_include_directories(src PUBLIC "${CMAKE_SOURCE_DIR}/include")
# target_include_directories(src PUBLIC "${CMAKE_SOURCE_DIR}/dependencies/include")
# target_link_directories(src PUBLIC "${CMAKE_SOURCE_DIR}/dependencies/lib")

# target_link_libraries(src 
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
    
    # vorbis
    # vorbisenc 
    # vorbisfile
    # FLAC
    # ogg
    # openal32