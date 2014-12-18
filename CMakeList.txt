cmake_minimum_required(VERSION 2.8.4)
project(DrowPoker)

set(SOURCE_FILES card.h
                 card.cpp
                 game.cpp
                 game.h
                 player.h
                 player.cpp
				 human_player.h
                 human_player.cpp
				 open_card.h
                 open_card.cpp
                 closed_card.h
                 closed_card.cpp
                 main.cpp)
add_executable(DrowPoker ${SOURCE_FILES})

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -g -std=c++0x")
endif()

