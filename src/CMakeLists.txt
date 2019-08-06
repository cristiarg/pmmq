cmake_minimum_required (VERSION 3.8)

project(pmmq)

add_executable(pmmq
    "Message.hpp"
    "IConsumer.hpp"
    "Broker.hpp"

    "IConsumer.cpp"
    "Broker.cpp"

    "pmmq.cpp"
    )

target_include_directories(pmmq PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(pmmq PUBLIC cxx_std_14)

