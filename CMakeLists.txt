cmake_minimum_required(VERSION 3.15)

project(c_basic_library VERSION 0.0.1 LANGUAGES C)


#set(CMAKE_C_STANDARD 89)
set(CMAKE_INSTALL_PREFIX ./bin)

include_directories("./include")

set(CBL_SRC_FILES DateTime.c Log.c String.c)
set(CBL_INC_FILES CBL.h config.h Basic.h DateTime.h Log.h String.h Vector.h Array.h)
set(BASIC_LIB include/config.h include/CBL_Basic.h)

list(TRANSFORM CBL_SRC_FILES PREPEND "./src/")
list(TRANSFORM CBL_INC_FILES PREPEND "./include/")

#add_library(CBL ${CBL_SRC_FILES} ${CBL_INC_FILES})
set(DateTime_COLLECTION include/CBL_DateTime.h src/CBL_DateTime.c)
add_executable(test_DateTime ${BASIC_LIB} ${DateTime_COLLECTION} test/DateTime.c)
target_include_directories(test_DateTime PRIVATE include)

set(String_COLLECTION include/CBL_String.h src/CBL_String.c)
add_executable(test_String ${BASIC_LIB} ${String_COLLECTION} test/String.c )
target_include_directories(test_String PRIVATE include)

set(Log_COLLECTION include/CBL_Log.h src/CBL_Log.c ${DateTime_COLLECTION} ${String_COLLECTION})
add_executable(test_Log ${BASIC_LIB} ${Log_COLLECTION} test/Log.c)
target_include_directories(test_Log PRIVATE include)

set(Vector_COLLECTION include/CBL_Vector.h src/CBL_Vector.c)
add_executable(test_Vector ${BASIC_LIB}  ${Vector_COLLECTION} ${Log_COLLECTION} test/Vector.c)