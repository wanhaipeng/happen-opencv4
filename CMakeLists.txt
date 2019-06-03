project(learn-opencv4[CXX])
cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD          11)
set(CMAKE_CXX_FLAGS             ${CMAKE_CXX_FLAGS} -g)
set(EXECUTABLE_OUTPUT_PATH      ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH         ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_MODULE_PATH           ${CMAKE_SOURCE_DIR}/cmake)
# add pybind11 && OpenCV4 Third-party libraries
add_subdirectory(include/pybind11)
find_package(OpenCV 4 REQUIRED)
if(OpenCV_FOUND)
    message(STATUS "OpenCV4_INCLUDE_DIRS = ${OpenCV_INCLUDE_DIRS}")
    message(STATUS "OpenCV4_LIBRARIES    = ${OpenCV_LIBRARIES}")
endif()
include_directories(${CMAKE_SOURCE_DIR}/include
                    ${OpenCV_INCLUDE_DIRS}
                    ${PYBIND11_INCLUDE_DIR}
                    ${PYTHON_INCLUDE_DIRS})
add_subdirectory(src)
link_libraries(${OpenCV_LIBRARIES})
add_executable(run_img tools/run_open.cpp)