cmake_minimum_required(VERSION 3.28.0)
project(boolean_simplifier VERSION 0.1.0 LANGUAGES CXX)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(itl_containers)

add_executable(boolean_simplifier main.cpp expression_evaluator/tokenizer.cpp expression_evaluator/parser.cpp)

target_include_directories(boolean_simplifier PRIVATE expression_evaluator)
target_link_libraries(boolean_simplifier PRIVATE i0bz_templatic_library)


include(CTest)
enable_testing()

