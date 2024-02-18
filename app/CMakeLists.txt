add_executable(${APP_NAME} main.cpp DuplicateFileFinderApp.cpp)
target_include_directories(${APP_NAME} PUBLIC "./")
target_link_libraries(${APP_NAME} ${UTILS_LIB})
