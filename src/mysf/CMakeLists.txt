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