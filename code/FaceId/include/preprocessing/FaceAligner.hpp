#pragma once

#include <opencv2/opencv.hpp>
#include <memory>

#include "api/FaceIdTypes.hpp"
#include "utils/Logger.hpp"

class FaceAligner {


public:
	FaceAligner();

	FaceAligner(const std::shared_ptr<spdlog::logger>& logger);

	~FaceAligner();

	void initialize(const FaceAlignerConfig& config);

	// Aligns the face in the given image based on the provided landmarks
	cv::Mat align(const cv::Mat& image, const std::vector<cv::Point2f>& landmarks);
	// Aligns the face in the given image based on the provided landmarks and returns a cropped face image
	cv::Mat alignAndCrop(const cv::Mat& image, const std::vector<cv::Point2f>& landmarks);


private:
	std::shared_ptr<spdlog::logger> pLogger; // Logger for logging messages and errors
	FaceAlignerConfig config_; // Configuration for the face aligner
};