cmake_minimum_required(VERSION 3.10)

project(reduce_fraction VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

add_executable(${PROJECT_NAME} main.c)

# Enable sanitizers or runtime checks based on compiler
if(CMAKE_C_COMPILER_ID MATCHES "Clang|GNU")
    message(STATUS "Clang/GCC detected — enabling AddressSanitizer")
    target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=address -g)
    target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=address)
elseif(MSVC)
    message(STATUS "MSVC detected — enabling runtime checks")
    target_compile_options(${PROJECT_NAME} PRIVATE /Zi /Od /RTC1)
    target_link_options(${PROJECT_NAME} PRIVATE /DEBUG)
endif()
