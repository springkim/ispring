cmake_minimum_required(VERSION 3.8)
project(ISpring)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp unit_test.h)

set(HEADER_FILES ispring/All.h ispring/Basic.h ispring/Compression.h
		ispring/Console.h ispring/CV.h ispring/File.h ispring/System.h ispring/Time.h ispring/Verify.h
		ispring/modules)

link_libraries(opencv_world pthread)
add_executable(ISpring ${SOURCE_FILES} ${HEADER_FILES})