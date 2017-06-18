cmake_minimum_required(VERSION 3.6)
project(LaneLines)

set(CMAKE_CXX_STANDARD 14)
set(SOURCE_FILES main.cpp src/calibration/Calibrator.cpp src/calibration/Calibrator.h src/seeker/LineSeeker.cpp src/seeker/LineSeeker.h)

if (!$ENV{OpenCV3_DIR})
    find_package(OpenCV REQUIRED)
else ()
    include( $ENV{OpenCV3_DIR}/share/OpenCV/OpenCVConfig.cmake )
endif ()

message( STATUS "OpenCV library status:" )
message( STATUS "    version: ${OpenCV_VERSION}" )
message( STATUS "    libraries: ${OpenCV_LIBS}" )
message( STATUS "    include path: ${OpenCV_INCLUDE_DIRS}" )

include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(LaneLines ${SOURCE_FILES})

target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )