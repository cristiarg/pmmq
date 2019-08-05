
cmake_minimum_required (VERSION 3.8)

project(pmmq_tests)

add_executable (test01 "test01.cpp"
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/IConsumer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/IProducer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/Broker.cpp
    )
target_include_directories(test01 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)

#target_link_libraries(test01 PRIVATE pmmq)
target_link_libraries(test01 PRIVATE catch)

target_compile_features(test01 PUBLIC cxx_std_14)
