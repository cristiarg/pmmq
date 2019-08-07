
cmake_minimum_required (VERSION 3.8)

project(pmmq_tests)

file(GLOB TEST01_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/test01.cpp")

add_executable (test01 ${TEST01_SOURCES} )

target_include_directories(test01 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(test01 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)

target_link_libraries(test01 PRIVATE catch)
target_link_libraries(test01 PRIVATE libpmmq)

target_compile_features(test01 PRIVATE cxx_std_14)

# compiler options
target_compile_features(test01 PUBLIC cxx_std_14)
if ( CMAKE_COMPILER_IS_GNUCC )
    target_compile_options(test01 PRIVATE -Werror -Wall -Wextra)
endif()
if ( MSVC )
    target_compile_options(test01 PRIVATE /W4)
endif()
