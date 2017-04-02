set(SystemC_DEFINITIONS "-DSC_INCLUDE_DYNAMIC_PROCESSES")

#------------------------------------------------------------------------------- 
#-- SystemC Settings
#------------------------------------------------------------------------------- 
file(TO_CMAKE_PATH $ENV{SYSTEMC_HOME} SYSTEMC_HOME)
if(NOT SYSTEMC_HOME)
  message(FATAL_ERROR "*** Set SYSTEMC_HOME env. variable.")
endif(NOT SYSTEMC_HOME)

set(_SC_INC ${SYSTEMC_HOME}/include)
set(_SC_LIB ${SYSTEMC_HOME}/lib-linux64)


find_path(SystemC_INCLUDE_DIR systemc.h
          HINTS ${_SC_INC})

find_library(SystemC_LIBRARY NAMES systemc
             HINTS ${_SC_LIB})

set(SystemC_LIBRARIES ${SystemC_LIBRARY} )
set(SystemC_INCLUDE_DIRS ${SystemC_INCLUDE_DIR} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set SystemC_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(SystemC  DEFAULT_MSG
  SystemC_DEFINITIONS SystemC_LIBRARIES SystemC_INCLUDE_DIRS)

mark_as_advanced(SystemC_INCLUDE_DIR SystemC_LIBRARY )
add_definitions(--std=c++11)
