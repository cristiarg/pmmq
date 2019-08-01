cmake_minimum_required (VERSION 3.8)

project(pmmq)

add_executable(pmmq
    "Broker.hpp"
    "IConsumer.hpp"
    "IProducer.hpp"
    "Message.hpp"
    "Broker.cpp"
    "Message.cpp"
    "pmmq.cpp" )

target_include_directories(pmmq PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

