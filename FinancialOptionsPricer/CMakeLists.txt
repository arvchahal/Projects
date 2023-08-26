cmake_minimum_required(VERSION 3.24)
project(optionsTracker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_ ${CMAKE_CURRENT_SOURCE_DIR})
set(Boost_INCLUDE_DIR C:/Users/chaha/OneDrive/Desktop/boost/boost_1_82_0)
set(Boost_LIBRARY_DIR C:/Users/chaha/OneDrive/Desktop/boost/boost_1_82_0/stage)
FIND_PACKAGE(Boost 1.82.0 COMPONENTS program_options REQUIRED HINTS ${Boost_LIBRARY_DIR})
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

add_executable(optionsTracker Binomial.cpp Binomial.h BlackScholes.cpp BlackScholes.h
        MonteCarlo.cpp MonteCarlo.h optionsDriver.cpp Option.h)
link_directories(${Boost_LIBRARY_DIRS})
target_link_libraries(optionsTracker Boost::program_options)


