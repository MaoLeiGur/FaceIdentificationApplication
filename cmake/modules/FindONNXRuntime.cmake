# FindONNXRuntime.cmake
# ONNX Runtime is crucial for running your face recognition models

set(ONNXRUNTIME_ROOT_PATH "" CACHE PATH "Path to ONNX Runtime installation")

# Try to find ONNX Runtime headers
find_path(ONNXRUNTIME_INCLUDE_DIRS
    NAMES onnxruntime_cxx_api.h
    PATHS
        ${ONNXRUNTIME_ROOT_PATH}/include
        /usr/local/include/onnxruntime
        "C:/Program Files/onnxruntime/include"
        $ENV{ONNXRUNTIME_DIR}/include
)

# Try to find ONNX Runtime library
find_library(ONNXRUNTIME_LIBRARIES
    NAMES onnxruntime
    PATHS
        ${ONNXRUNTIME_ROOT_PATH}/lib
        /usr/local/lib
        "C:/Program Files/onnxruntime/lib"
        $ENV{ONNXRUNTIME_DIR}/lib
)

if(ONNXRUNTIME_INCLUDE_DIRS AND ONNXRUNTIME_LIBRARIES)
    set(ONNXRUNTIME_FOUND TRUE)
    
    # Create imported target
    add_library(onnxruntime::onnxruntime INTERFACE IMPORTED)
    target_include_directories(onnxruntime::onnxruntime INTERFACE ${ONNXRUNTIME_INCLUDE_DIRS})
    target_link_libraries(onnxruntime::onnxruntime INTERFACE ${ONNXRUNTIME_LIBRARIES})
    
    message(STATUS "Found ONNX Runtime: ${ONNXRUNTIME_LIBRARIES}")
else()
    message(WARNING "ONNX Runtime not found. Face recognition models may not work.")
endif()