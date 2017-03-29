cmake_minimum_required(VERSION 3.6)
project(LaneLines)

set(CMAKE_CXX_STANDARD 11)
set(SOURCE_FILES main.cpp)

include( $ENV{OpenCV2_DIR}/share/OpenCV/OpenCVConfig.cmake )
#find_package(OpenCV REQUIRED)
message( STATUS "OpenCV library status:" )
message( STATUS "    version: ${OpenCV_VERSION}" )
message( STATUS "    libraries: ${OpenCV_LIBS}" )
message( STATUS "    include path: ${OpenCV_INCLUDE_DIRS}" )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(LaneLines ${SOURCE_FILES})

target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )