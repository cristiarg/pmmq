cmake_minimum_required (VERSION 3.8)

project(pmmq)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/catch)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tsT)

# set (PMMQ_SOURCES
#       inc/pmmp.h
#       src/pmmp.cpp)

# Add source to this project's executable.
#add_executable (pmmq 
#    "inc/Broker.hpp"
#    "inc/IConsumer.hpp"
#    "inc/IProducer.hpp"
#    "inc/Message.hpp"
#    "src/Broker.cpp"
#    "src/Message.cpp"
#    "src/pmmq.cpp" )
#target_include_directories(pmmq PRIVATE inc)

# add_executable (pmmq ${PMMQ_SOURCES})
# target_include_directories(pmmq PRIVATE inc)

# TODO: Add tests and install targets if needed.
#add_executable (test01 "tst/test01.cpp")
#target_include_directories(test01 PRIVATE inc)
#target_link_libraries(test01 PRIVATE catch)
