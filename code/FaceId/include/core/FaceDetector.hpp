#pragma once


#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <memory>
#include <vector>

#include "api/FaceIdTypes.hpp"
#include "utils/Logger.hpp"

class FaceDetector {
public:
    FaceDetector();
    explicit FaceDetector(const DetectionConfig& config);
    FaceDetector(std::shared_ptr<spdlog::logger>& logger);
    ~FaceDetector();

    // Initialize the detector with model
    ErrorCode initialize(const std::string& model_path);
    ErrorCode initialize(const DetectionConfig& config);
    
    // Detect faces in image
    ErrorCode detect(const cv::Mat& image,std::vector<FaceDetection>& detections);
   
private: 
	std::shared_ptr<spdlog::logger> pLogger;
	//cv::dnn::Net model;
    bool        profiling_enabled;
    float       confidence_threshold;

    // Preprocessing
    cv::Mat preprocessImage(const cv::Mat& image);
    
    // Postprocessing
    std::vector<FaceDetection> postprocessDetections(const cv::Mat& output, const cv::Mat& original_image);
};



// Factory function for creating detectors
std::unique_ptr<FaceDetector> createFaceDetector(const std::string& detector_type,
                                                const DetectionConfig& config);