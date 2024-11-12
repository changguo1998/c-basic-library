cmake_minimum_required(VERSION 3.15)

project(c_basic_library VERSION 0.0.1 LANGUAGES C)

set(CMAKE_C_STANDARD 99)

set(DEBUG False)

#include(D:/Softwares/fftw3/lib/cmake/fftw3/FFTW3Config.cmake)
set(FFTW D:/Softwares/fftw3)
include_directories(${FFTW}/include)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install)

# experiment codes
#add_executable(exp_Macro_template experiment/macro_template.c)

add_executable(exp_FFTW experiment/fftw.c)
target_include_directories(exp_FFTW PRIVATE "${FFTW}/include")
target_link_directories(exp_FFTW PRIVATE "${FFTW}/bin")
target_link_libraries(exp_FFTW PRIVATE fftw3)

# tests
set(BASIC_LIB include/Module_Basic.h src/Module_Basic.c)
set(MATH_BASIC include/Type_Part_math_basic.h src/Type_Part_math_basic.c)

function(add_test_target modulename)
    if (DEBUG)
        message("===========================")
        message("modulename: ${modulename}")
        message("deps: ${ARGN}")
    endif ()

    file(GLOB ${modulename}_C_inc include/*_${modulename}.h)

    if (DEBUG)
        message("INC: ${${modulename}_C_inc}")
    endif ()

    file(GLOB ${modulename}_C_src src/*_${modulename}.c)

    if (DEBUG)
        message("SRC: ${${modulename}_C_src}")
    endif ()

    set(${modulename}_C "${${modulename}_C_inc}" "${${modulename}_C_src}" PARENT_SCOPE)
    list(APPEND ${modulename}_C "${${modulename}_C_inc}" "${${modulename}_C_src}")

    if (DEBUG)
        message("${modulename}_C: ${${modulename}_C}")
    endif ()

    list(APPEND deps ${BASIC_LIB} ${${modulename}_C} ${ARGN})

    if (DEBUG)
        message("sources: ${deps}")
    endif ()

    add_executable(test_${modulename} ${deps} test/${modulename}.c)
    target_include_directories(test_${modulename} PRIVATE include)
    target_link_directories(test_${modulename} PRIVATE ${FFTW}/bin)
    target_link_libraries(test_${modulename} fftw3)
    install(TARGETS test_${modulename} DESTINATION bin)
endfunction()

add_test_target(Complex)
add_test_target(String)
add_test_target(DateTime ${String_C} ${MATH_BASIC})
add_test_target(Log ${DateTime_C} ${String_C})
list(APPEND Log_C ${DateTime_C} ${String_C})
add_test_target(Dict ${String_C})
add_test_target(IntVector ${MATH_BASIC})
add_test_target(FloatVector ${MATH_BASIC} ${IntVector_C})
add_test_target(ComplexVector ${MATH_BASIC} ${IntVector_C} ${FloatVector_C})
add_test_target(FloatMatrix ${MATH_BASIC} ${IntVector_C} ${FloatVector_C})
add_test_target(IntVectorN ${MATH_BASIC} include/Template_VectorN.h)
add_test_target(FloatVectorN ${MATH_BASIC} include/Template_VectorN.h)
# add_test_target(TypeArray)

# CBL
file(GLOB CBL_H "include/*.h")
file(GLOB CBL_C "src/*.c")

add_executable(test_CBL ${CBL_C} ${CBL_H} test/CBL.c)
target_include_directories(test_CBL PRIVATE include)
target_link_directories(test_CBL PRIVATE "${FFTW}/bin")
target_link_libraries(test_CBL PRIVATE fftw3)

add_library(CBL STATIC ${CBL_C} ${CBL_H})
target_include_directories(CBL PUBLIC include)
target_link_directories(CBL PRIVATE "${FFTW}/bin")
target_link_libraries(CBL PRIVATE fftw3)
target_sources(CBL PUBLIC
        FILE_SET headerCBL
        TYPE HEADERS
        BASE_DIRS include
        FILES ${CBL_H})
install(TARGETS CBL
        LIBRARY DESTINATION lib
        FILE_SET headerCBL)
