set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")
cmake_minimum_required(VERSION 2.6)
project(quantum)

find_package(SystemC REQUIRED)
set(LIBS ${LIBS} ${SystemC_LIBRARY})
include_directories(${CMAKE_SOURCE_DIR} ${SystemC_INCLUDE_DIRS})
add_definitions(${SystemC_DEFINITIONS})
#set(HEADER_FILES Initiator.h Interconnect_1.h Target.h)
#add_library(mylib ${HEADER_FILES})
add_executable(quantum Top.cpp Initiator.cpp Initiator_R.cpp Target.cpp Target.h Initiator_R.h Initiator.h)
target_link_libraries(quantum ${LIBS})
#install(FILES Initiator.h Interconnect_1.h Target.h DESTINATION include/pvt)


