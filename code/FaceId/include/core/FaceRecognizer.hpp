#pragma once
#include <memory>
#include <vector>

#include <opencv2/opencv.hpp>

#include "api/FaceIdTypes.hpp"
#include "utils/Logger.hpp"

class FaceRecognizer {
public:
	FaceRecognizer();
	FaceRecognizer(std::shared_ptr<spdlog::logger>& logger);
	~FaceRecognizer();

	void initialize(const RecognitionConfig& config);
	ErrorCode recognize(const FaceDetection& detection,Person& person);


private:
	std::shared_ptr<spdlog::logger> pLogger;
	RecognitionConfig config_;
};
