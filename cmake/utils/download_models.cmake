# download_models.cmake
# Downloads face detection and recognition models if they don't exist

function(download_model MODEL_NAME MODEL_URL MODEL_PATH)
    if(NOT EXISTS ${MODEL_PATH})
        message(STATUS "Downloading ${MODEL_NAME}...")
        
        file(DOWNLOAD
            ${MODEL_URL}
            ${MODEL_PATH}
            SHOW_PROGRESS
            STATUS download_status
            LOG download_log
        )
        
        # Check if download was successful
        list(GET download_status 0 status_code)
        if(NOT status_code EQUAL 0)
            message(FATAL_ERROR "Failed to download ${MODEL_NAME}: ${download_log}")
        else()
            message(STATUS "Successfully downloaded ${MODEL_NAME}")
        endif()
    else()
        message(STATUS "${MODEL_NAME} already exists, skipping download")
    endif()
endfunction()

# Function to download all required models
function(download_face_models)
    set(MODELS_DIR ${CMAKE_SOURCE_DIR}/models)
    
    # Create models directory
    file(MAKE_DIRECTORY ${MODELS_DIR}/detection)
    file(MAKE_DIRECTORY ${MODELS_DIR}/recognition)
    file(MAKE_DIRECTORY ${MODELS_DIR}/landmarks)
    
    # Download face detection model
    download_model(
        "Face Detection Model"
        "https://github.com/opencv/opencv_zoo/raw/master/models/face_detection_yunet/face_detection_yunet_2022mar.onnx"
        "${MODELS_DIR}/detection/face_detection.onnx"
    )
    
    # Download face recognition model
    download_model(
        "Face Recognition Model"
        "https://github.com/opencv/opencv_zoo/raw/master/models/face_recognition_sface/face_recognition_sface_2021dec.onnx"
        "${MODELS_DIR}/recognition/face_recognition.onnx"
    )
    
    # Download face landmarks model
    download_model(
        "Face Landmarks Model"  
        "https://github.com/davisking/dlib-models/raw/master/shape_predictor_68_face_landmarks.dat.bz2"
        "${MODELS_DIR}/landmarks/shape_predictor_68_face_landmarks.dat.bz2"
    )
    
    # Extract compressed files if needed
    if(EXISTS "${MODELS_DIR}/landmarks/shape_predictor_68_face_landmarks.dat.bz2")
        message(STATUS "Extracting landmarks model...")
        execute_process(
            COMMAND ${CMAKE_COMMAND} -E tar xf shape_predictor_68_face_landmarks.dat.bz2
            WORKING_DIRECTORY ${MODELS_DIR}/landmarks
        )
    endif()
endfunction()