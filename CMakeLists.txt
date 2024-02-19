cmake_minimum_required(VERSION 3.2)

project(FindDuplicates LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(APP_NAME DuplicatesFileFinder)
set(UTILS_LIB Utils)

add_subdirectory(app)
add_subdirectory(src)
