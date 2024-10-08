cmake_minimum_required(VERSION 3.15)

project(c_basic_library VERSION 0.0.1 LANGUAGES C)

#set(CMAKE_C_STANDARD 89)
set(CMAKE_INSTALL_PREFIX ./bin)

# CBL
file(GLOB CBL_H "include/CBL*.h")
file(GLOB CBL_C "src/CBL*.c")
add_library(CBL STATIC ${CBL_H} ${CBL_C} include/config.h)
target_include_directories(CBL PUBLIC include)

# tests
set(BASIC_LIB include/config.h include/CBL_Basic.h)

function(addexe modulename)
#    message("===========================")
#    message("modulename: ${modulename}")
#    message("deps: ${ARGN}")
    set(${modulename}_C include/CBL_${modulename}.h src/CBL_${modulename}.c PARENT_SCOPE)
    list(APPEND deps ${ARGN} ${BASIC_LIB} include/CBL_${modulename}.h src/CBL_${modulename}.c)
    add_executable(test_${modulename} ${deps} test/${modulename}.c)
    target_include_directories(test_${modulename} PRIVATE include)
endfunction()

addexe(DateTime)
addexe(String)
addexe(Log ${DateTime_C} ${String_C})
list(APPEND Log_C ${DateTime_C} ${String_C})
addexe(Vector)
addexe(Array ${Vector_C})
addexe(Dict ${String_C})
addexe(IntVector)
addexe(FloatVector)
addexe(FloatMatrix)
addexe(TypeArray)

add_executable(test_CBL include/CBL.h test/CBL.c)
target_link_libraries(test_CBL CBL)
