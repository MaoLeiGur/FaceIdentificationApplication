#include "core/FaceDetector.hpp"
#include "utils/Logger.hpp"
#include <chrono>
#include <algorithm>


FaceDetector::FaceDetector() 
{
	faces_.reserve(5);
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
    
    config_ = config;

	if (config_.backend == "opencv") {
		// Load OpenCV DNN model
		try {
			model = cv::dnn::readNetFromONNX(config_.model_path);
			pLogger->info("Face detection model loaded successfully from: {}", config_.model_path);
		}
		catch (const cv::Exception& e) {
			pLogger->error("Failed to load face detection model: {}", e.what());
			return ErrorCode::MODEL_LOAD_FAILED;
		}
	}
	else if (config_.backend == "haarcascade") {
		// Load Haar Cascade model
		if (!face_cascade.load(config_.model_path)) {
			pLogger->error("Failed to load Haar Cascade model from: {}", config_.model_path);
			return ErrorCode::MODEL_LOAD_FAILED;
		}
	}
	else if (config_.backend == "dlib")
	{
		// Load Dlib model
		try {
			face_cascade.load(config_.model_path);
			pLogger->info("Face detection model loaded successfully from: {}", config_.model_path);
		}
		catch (const std::exception& e) {
			pLogger->error("Failed to load Dlib face detection model: {}", e.what());
			return ErrorCode::MODEL_LOAD_FAILED;
		}
	}
	else if (config_.backend == "tensorrt") {
		// Load TensorRT model
		try {
			model = cv::dnn::readNetFromTensorflow(config_.model_path);
			pLogger->info("Face detection model loaded successfully from: {}", config_.model_path);
		}
		catch (const cv::Exception& e) {
			pLogger->error("Failed to load TensorRT face detection model: {}", e.what());
			return ErrorCode::MODEL_LOAD_FAILED;
		}
	}
	else if (config_.backend == "onnxruntime") {
		// Load ONNX Runtime model
		try {
			model = cv::dnn::readNetFromONNX(config_.model_path);
			pLogger->info("Face detection model loaded successfully from: {}", config_.model_path);
		}
		catch (const cv::Exception& e) {
			pLogger->error("Failed to load ONNX Runtime face detection model: {}", e.what());
			return ErrorCode::MODEL_LOAD_FAILED;
		}
	}
	else if (config_.backend == "tflite") {
		// Load TensorFlow Lite model
		try {
			model = cv::dnn::readNetFromTensorflow(config_.model_path);
			pLogger->info("Face detection model loaded successfully from: {}", config_.model_path);
		}
		catch (const cv::Exception& e) {
			pLogger->error("Failed to load TensorFlow Lite face detection model: {}", e.what());
			return ErrorCode::MODEL_LOAD_FAILED;
		}
	}
	else {
		pLogger->error("Unsupported backend: {}", config_.backend);
		return ErrorCode::INVALID_CONFIG;
	}

    return ErrorCode::SUCCESS;
}

ErrorCode FaceDetector::detect(const cv::Mat& image, std::vector<FaceDetection>& detections)
{    
    ErrorCode results = ErrorCode::SUCCESS;

	faces_.clear();
	detections.clear();

    try {
        auto start_time = std::chrono::high_resolution_clock::now();

        // Preprocess image
       
        // Set input to the network
       
        // Run forward pass
		
		face_cascade.detectMultiScale(image, faces_, 1.1, 3, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));


         
        // Filter by confidence threshold
        std::vector<FaceDetection> filtered_detections;
        for (const auto& faceRect : faces_) 
		{
			FaceDetection detection;
			detection.bbox = faceRect;
			detection.face_image = image(detection.bbox);
			detection.confidence = 1.0;
			detections.push_back(detection);
        }

        if(detections.empty())
        { 
            results = ErrorCode::NO_FACE_DETECTED;
        }

		else // Face found:
		{
			cv::namedWindow("Face Detection", cv::WINDOW_AUTOSIZE);
			cv::rectangle(image, detections[0].bbox, cv::Scalar(0, 255, 0), 2);
			cv::imshow("Face Detection", image);
			cv::waitKey(1);
		}


    }
    catch (const cv::Exception& e) {
        throw std::runtime_error(std::string(e.what()));
    }
    return results;
}







