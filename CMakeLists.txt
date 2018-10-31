cmake_minimum_required(VERSION 3.7)
project(Dll_Helpers)

set(CMAKE_INSTALL_PREFIX bin)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# For all projects to be built at the same folder
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_definitions(-DBRAND_COMPANYNAME=\"Dll_Helpers\" -DBRAND_NAME=\"Dll_Helpers\")

add_subdirectory(src/TestDll)

enable_testing()
add_subdirectory(src/tests)
