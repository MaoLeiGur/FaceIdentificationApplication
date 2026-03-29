# FindOpenCV.cmake
# This script helps CMake find OpenCV in various installation locations

# Try different common paths where OpenCV might be installed
find_path(OpenCV_INCLUDE_DIRS
    NAMES opencv2/opencv.hpp
    PATHS
        /usr/include
        /usr/local/include
        /opt/opencv/include
        "C:/opencv/opencv4100/build/include"
        $ENV{OPENCV_DIR}/include
)

find_library(OpenCV_LIBS
    NAMES opencv_core opencv_imgproc opencv_imgcodecs opencv_objdetect
    PATHS
        /usr/lib
        /usr/local/lib
        /opt/opencv/lib
        "C:/opencv/opencv4100/build/x64/vc17/lib"
        $ENV{OPENCV_DIR}/lib
)

# Define what constitutes a "successful" find
if(OpenCV_INCLUDE_DIRS AND OpenCV_LIBS)
    set(OpenCV_FOUND TRUE)
    message(STATUS "Found OpenCV: ${OpenCV_LIBS}")
else()
    set(OpenCV_FOUND FALSE)
    message(FATAL_ERROR "OpenCV not found! Please install OpenCV or set OPENCV_DIR")
endif()

# Create an "imported target" for easy use
if(OpenCV_FOUND AND NOT TARGET opencv::opencv)
    add_library(opencv::opencv INTERFACE IMPORTED)
    target_include_directories(opencv::opencv INTERFACE ${OpenCV_INCLUDE_DIRS})
    target_link_libraries(opencv::opencv INTERFACE ${OpenCV_LIBS})
endif()