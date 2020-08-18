add_library(
    src STATIC
    filters.cpp
    rgbToGray.cpp
    grayToMono.cpp
    mean.cpp
    variance.cpp
    )
# target_compile_definitions(src PUBLIC _WIN32_WINNT=0x0501)
target_compile_options(src PUBLIC "-DSFML_STATIC")
# target_compile_options(src PUBLIC "-pthread")
target_include_directories(src PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_include_directories(src PUBLIC "${CMAKE_SOURCE_DIR}/dependencies/include")
target_link_directories(src PUBLIC "${CMAKE_SOURCE_DIR}/dependencies/lib")


target_link_libraries(src 
    PUBLIC 
    libsfml-graphics-s.a
    libsfml-window-s.a
    libsfml-system-s.a
    pthread
    FLAC
    freetype 
    ogg
    openal32
    vorbis
    libvorbisenc.a 
    libvorbisfile.a
    opengl32.lib
    winmm.lib
    gdi32.lib
)
