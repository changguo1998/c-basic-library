cmake_minimum_required(VERSION 3.15)

project(c_basic_library VERSION 0.0.1 LANGUAGES C)

set(CMAKE_C_STANDARD 99)

#set(CMAKE_INSTALL_PREFIX ./)

# tests
set(BASIC_LIB include/CBL_Basic.h src/CBL_Basic.c)

function(add_test_target modulename)
#    message("===========================")
#    message("modulename: ${modulename}")
#    message("deps: ${ARGN}")
    set(${modulename}_C include/CBL_${modulename}.h src/CBL_${modulename}.c PARENT_SCOPE)
    list(APPEND deps ${ARGN} ${BASIC_LIB} include/CBL_${modulename}.h src/CBL_${modulename}.c)
    add_executable(test_${modulename} ${deps} test/${modulename}.c)
    target_include_directories(test_${modulename} PRIVATE include)
    install(TARGETS test_${modulename} DESTINATION bin)
endfunction()

add_test_target(String)
add_test_target(DateTime ${String_C})
add_test_target(Log ${DateTime_C} ${String_C})
list(APPEND Log_C ${DateTime_C} ${String_C})
add_test_target(Vector)
add_test_target(Array ${Vector_C})
add_test_target(Dict ${String_C})
add_test_target(IntVector)
add_test_target(FloatVector)
add_test_target(FloatMatrix)
# add_test_target(TypeArray)

# CBL
file(GLOB CBL_H "include/CBL*.h")
file(GLOB CBL_C "src/CBL*.c")

add_executable(test_CBL ${CBL_C} ${CBL_H} test/CBL.c)
target_include_directories(test_CBL PRIVATE include)

add_library(CBL STATIC ${CBL_C} ${CBL_H})
target_include_directories(CBL PUBLIC include)
target_sources(CBL PUBLIC
        FILE_SET headerCBL
        TYPE HEADERS
        BASE_DIRS include
        FILES ${CBL_H})
install(TARGETS CBL
        LIBRARY DESTINATION lib
        FILE_SET headerCBL)
