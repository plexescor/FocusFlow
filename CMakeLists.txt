cmake_minimum_required(VERSION 3.20)
project(FocusFlow)

# Grab all .cpp files in Scripts folder (and subfolders)
file(GLOB_RECURSE SOURCES "Scripts/*.cpp")

add_executable(FocusFlow ${SOURCES})
