enable_testing()

set(GTest_DIR ${CMAKE_SOURCE_DIR}/3rdparty/googletest)
set(GTest_INCLUDE_DIR ${GTest_DIR}/googletest/include)
set(GTest_ADD_TO_SRC  ${GTest_DIR}/googletest/src/gtest-all.cc)

include_directories(
	${GTest_INCLUDE_DIR}
	${GTest_INCLUDE_DIR}/..
	../Helpers/
	)

#set(GTEST_ROOT ${GTest_DIR}/googletest)

find_package(GTest)

macro(DLL_HELPERS_TEST testName)
	add_executable(${testName} ${ARGN} main.h ${GTest_ADD_TO_SRC})
	GTEST_ADD_TESTS(${testName} "" ${ARGN})
	set_property(TARGET ${testName} PROPERTY FOLDER "DllHelpers/Tests")
endmacro()

add_definitions(-DGTEST_LANG_CXX11 -DBRAND_NAME=\"Tests\")


DLL_HELPERS_TEST(DllTest Test/Test.cpp ../Helpers/DllHelpers.h)
