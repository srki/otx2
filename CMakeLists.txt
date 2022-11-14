cmake_minimum_required(VERSION 3.09)

project(otx
        VERSION 0.1
        DESCRIPTION "A Simple Header Library for Parsing Program Options."
        LANGUAGES CXX)

add_library(otx INTERFACE)
target_include_directories(otx INTERFACE include)

add_subdirectory(tests)