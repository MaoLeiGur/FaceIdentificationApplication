# FindDlib.cmake
find_path(DLIB_INCLUDE_DIRS
    NAMES dlib/image_processing.h
    PATHS
        /usr/include
        /usr/local/include
        ${CMAKE_SOURCE_DIR}/external/dlib
)

find_library(DLIB_LIBRARIES
    NAMES dlib
    PATHS
        /usr/lib
        /usr/local/lib
        ${CMAKE_SOURCE_DIR}/external/dlib/build
)

if(DLIB_INCLUDE_DIRS AND DLIB_LIBRARIES)
    set(DLIB_FOUND TRUE)
    # Create imported target
    add_library(dlib::dlib INTERFACE IMPORTED)
    target_include_directories(dlib::dlib INTERFACE ${DLIB_INCLUDE_DIRS})
    target_link_libraries(dlib::dlib INTERFACE ${DLIB_LIBRARIES})
endif()