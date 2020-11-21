cmake_minimum_required(VERSION 3.17)
project(Assignment10)

set(CMAKE_CXX_STANDARD 17)
set(doxy_main_page ${PROJECT_SOURCE_DIR}/README.md)

add_subdirectory(src)
add_subdirectory(docs)
add_subdirectory(tests)