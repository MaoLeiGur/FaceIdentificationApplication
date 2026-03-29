#pragma once
#include <memory>
#include <vector>

#include <opencv2/opencv.hpp>

#include "api/FaceIdTypes.hpp"
#include "utils/Logger.hpp"




class FaceEncoder {
public:
	FaceEncoder();

	FaceEncoder(std::shared_ptr<spdlog::logger>& logger);
	~FaceEncoder();
	ErrorCode initialize(const FaceEncoderConfig& config);


	ErrorCode encode(const FaceDetection& faceDetection, FaceLandmarks& landmarks);
	ErrorCode encodeBatch(const std::vector<FaceDetection>& faceDetections, std::vector<FaceLandmarks>& landmarks);
	void setBatchSize(int batch_size);
	int getBatchSize() const;

private:
	std::shared_ptr<spdlog::logger> pLogger;
	FaceEncoderConfig config_; // Configuration for the face encoder
};