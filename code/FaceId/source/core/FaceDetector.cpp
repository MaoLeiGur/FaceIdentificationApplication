#include "core/FaceDetector.hpp"
#include "utils/Logger.hpp"
#include <chrono>
#include <algorithm>


FaceDetector::FaceDetector() 
{

}


FaceDetector::FaceDetector(std::shared_ptr<spdlog::logger>& logger):FaceDetector()
{
	pLogger = logger;
    pLogger->info("FaceDetector Created.");
}

FaceDetector::FaceDetector(const DetectionConfig& config)
{

}

FaceDetector::~FaceDetector() = default;

ErrorCode FaceDetector::initialize(const std::string& model_path) {
	
	return ErrorCode::SUCCESS;
}

ErrorCode FaceDetector::initialize(const DetectionConfig& config) {
    
    return initialize(config.model_path);
}

ErrorCode FaceDetector::detect(const cv::Mat& image, std::vector<FaceDetection>& detections)
{    
    ErrorCode results = ErrorCode::SUCCESS;
    try {
        auto start_time = std::chrono::high_resolution_clock::now();

        // Preprocess image
       
        // Set input to the network
       
        // Run forward pass
        
        std::vector<FaceDetection> detections_t;
        
        // Filter by confidence threshold
        std::vector<FaceDetection> filtered_detections;
        for (const auto& detection : detections) {
            if (detection.confidence >= confidence_threshold) {
                filtered_detections.push_back(detection);
            }
        }

        if(detections.empty())
        { 
            results = ErrorCode::NO_FACE_DETECTED;
        }
        return results;

    }
    catch (const cv::Exception& e) {
        throw std::runtime_error(std::string(e.what()));
    }
    return results;
}







