cmake_minimum_required(VERSION 3.5)
project(tp1)

set(CMAKE_CXX_STANDARD 11)

# Algunos flags para pasar al compilador (gnu++11 en vez de c++11 para que sea cross-plat)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -ggdb3")

# Leemos todos los archivos fuentes en ./src
file(GLOB SOURCE_FILES src/*.cpp src/*.h)

# Leemos todos los archivos de test en ./tests
file(GLOB TEST_SOURCES tests/*.cpp)

add_subdirectory(tests/google-test)


# Creamos el ejecutable para correr los tests
add_executable(correrTests ${TEST_SOURCES} ${SOURCE_FILES} src/BaseDatos.cpp src/BaseDatos.h src/Restriccion.cpp src/Restriccion.h tests/custom_test.cpp tests/restriccion_test.cpp tests/baseDatos_test.cpp)

# Necesitamos asociar los archivos del framework de testing
target_link_libraries(correrTests gtest gtest_main)

add_test(correrTests correrTests)

# Target para correr Valgrind
add_custom_target(correrValgrind valgrind --leak-check=full -v ./correrTests 2>&1 DEPENDS correrTests)
