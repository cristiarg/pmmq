cmake_minimum_required (VERSION 3.8)

project(pmmq)

file(GLOB LIBPMMQ_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(libpmmq STATIC ${LIBPMMQ_SOURCES} )

target_include_directories(libpmmq PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# compiler options
target_compile_features(libpmmq PUBLIC cxx_std_14)
if ( CMAKE_COMPILER_IS_GNUCC )
    target_compile_options(libpmmq PRIVATE -Werror -Wall -Wextra)
endif()
if ( MSVC )
    target_compile_options(libpmmq PRIVATE /W4)
endif()
