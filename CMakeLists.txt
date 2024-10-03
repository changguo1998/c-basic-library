cmake_minimum_required(VERSION 3.15)

project(c_basic_library VERSION 0.0.1 LANGUAGES C)

#set(CMAKE_C_STANDARD 89)
set(CMAKE_INSTALL_PREFIX ./bin)

# CBL
file(GLOB CBL_H "include/CBL*.h")
file(GLOB CBL_C "src/CBL*.c")
add_library(CBL STATIC ${CBL_H} ${CBL_C} include/config.h)
target_include_directories(CBL PRIVATE include)

set(CBL_SRC_FILES DateTime.c Log.c String.c)
set(CBL_INC_FILES CBL.h config.h Basic.h DateTime.h Log.h String.h Vector.h Array.h)
set(BASIC_LIB include/config.h include/CBL_Basic.h)

list(TRANSFORM CBL_SRC_FILES PREPEND "./src/")
list(TRANSFORM CBL_INC_FILES PREPEND "./include/")

#add_library(CBL ${CBL_SRC_FILES} ${CBL_INC_FILES})
set(DateTime_C include/CBL_DateTime.h src/CBL_DateTime.c)
add_executable(test_DateTime ${BASIC_LIB} ${DateTime_C} test/DateTime.c)
target_include_directories(test_DateTime PRIVATE include)

set(String_C include/CBL_String.h src/CBL_String.c)
add_executable(test_String ${BASIC_LIB} ${String_C} test/String.c)
target_include_directories(test_String PRIVATE include)

set(Log_C include/CBL_Log.h src/CBL_Log.c ${DateTime_C} ${String_C})
add_executable(test_Log ${BASIC_LIB} ${Log_C} test/Log.c)
target_include_directories(test_Log PRIVATE include)

set(Vector_C include/CBL_Vector.h src/CBL_Vector.c)
add_executable(test_Vector ${BASIC_LIB} ${Vector_C} ${Log_C} test/Vector.c)
target_include_directories(test_Vector PRIVATE include)

set(Array_C include/CBL_Array.h src/CBL_Array.c)
add_executable(test_Array ${BASIC_LIB} ${Vector_C} ${Log_C} ${Array_C} test/Array.c)
target_include_directories(test_Array PRIVATE include)

set(Dict_C include/CBL_Dict.h src/CBL_Dict.c)
add_executable(test_Dict ${BASIC_LIB} ${String_C} ${Dict_C} ${Log_C} test/Dict.c)
target_include_directories(test_Dict PRIVATE include)

add_executable(test_CBL include/CBL.h test/CBL.c)
target_include_directories(test_CBL PRIVATE include)
target_link_libraries(test_CBL CBL)
