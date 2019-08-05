cmake_minimum_required (VERSION 3.8)

#set(CMAKE_USER_MAKE_RULES_OVERRIDE "${CMAKE_CURRENT_LIST_DIR}/CompilerOptions.cmake")

project(pmmq)

add_executable(pmmq
    "Message.hpp"
    "IConsumer.hpp"
    "IProducer.hpp"
    "Broker.hpp"

    "IConsumer.cpp"
    "IProducer.cpp"
    "Broker.cpp"

    "pmmq.cpp"
    )

target_include_directories(pmmq PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(pmmq PUBLIC cxx_std_14)

