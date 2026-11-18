cmake_minimum_required(VERSION 3.20)

project(Lab5Variant30 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

add_library(AlgorithmLibrary1 SHARED src/pi_sort_library1.c)
add_library(AlgorithmLibrary2 SHARED src/pi_sort_library2.c)

target_include_directories(AlgorithmLibrary1 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_include_directories(AlgorithmLibrary2 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_compile_definitions(AlgorithmLibrary1 PRIVATE BUILDING_LIBRARY)
target_compile_definitions(AlgorithmLibrary2 PRIVATE BUILDING_LIBRARY)

add_executable(LinkTest src/static_main.c)
target_include_directories(LinkTest PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_compile_definitions(LinkTest PRIVATE USING_LIBRARY)
target_link_libraries(LinkTest PRIVATE AlgorithmLibrary1)

add_executable(DynamicTest src/dynamic_main.c)
target_include_directories(DynamicTest PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries(DynamicTest PRIVATE kernel32)
add_dependencies(DynamicTest AlgorithmLibrary1 AlgorithmLibrary2)

if(MSVC)
    target_compile_options(AlgorithmLibrary1 PRIVATE /W4)
    target_compile_options(AlgorithmLibrary2 PRIVATE /W4)
    target_compile_options(LinkTest PRIVATE /W4)
    target_compile_options(DynamicTest PRIVATE /W4)
endif()

set_property(TARGET LinkTest PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:LinkTest>")
set_property(TARGET DynamicTest PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:DynamicTest>")
