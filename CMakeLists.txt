cmake_minimum_required(VERSION 3.10)  # Минимальная версия CMake

# Укажите имя вашего проекта
project(Untitled)

# Установите стандарт C++
set(CMAKE_CXX_STANDARD 17)            # Используйте нужную версию C++
set(CMAKE_CXX_STANDARD_REQUIRED True)

# задаем имя исполняемого файла основной программы
set(exe_name ${PROJECT_NAME})
# задаем имя исполняемого файла программы для запуска тестов
set(test_name test)

add_library(corelib OBJECT flat_map.cpp)

add_executable(${exe_name} main.cpp)
target_link_libraries(${exe_name} corelib)

# Добавляем Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# описываем исполняемый файл программы для запуска тестов: это cpp-файлы тестов + основная библиотека + библиотека gtest_main
# наш собственный main.cpp здесь не нужен, т.к. функция main реализована в gtest_main
add_executable(${test_name} flat_map_test.cpp)
target_link_libraries(${test_name} gtest_main)
target_link_libraries(${test_name} corelib)