set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")
cmake_minimum_required(VERSION 2.6)
project(b_transport_1)

find_package(SystemC REQUIRED)
set(LIBS ${LIBS} ${SystemC_LIBRARY})
include_directories(${CMAKE_SOURCE_DIR} ${SystemC_INCLUDE_DIRS})
add_definitions(${SystemC_DEFINITIONS})
#set(HEADER_FILES Initiator.h Interconnect_1.h Target.h)
#add_library(mylib ${HEADER_FILES})
add_executable(b_transport_1 Top.cpp Target.h Interconnect_1.h Initiator.h)
target_link_libraries(b_transport_1 ${LIBS})
#install(FILES Initiator.h Interconnect_1.h Target.h DESTINATION include/pvt)


