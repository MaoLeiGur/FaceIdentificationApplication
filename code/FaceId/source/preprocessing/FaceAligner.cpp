#include "preprocessing/FaceAligner.hpp"



FaceAligner::FaceAligner() {

}

FaceAligner::FaceAligner(const std::shared_ptr<spdlog::logger>& logger):FaceAligner()
{
	pLogger = logger;
	
	pLogger->info("FaceAligner created.");
}
FaceAligner::~FaceAligner() {
	// Destructor implementation (if needed)
}

void FaceAligner::initialize(const FaceAlignerConfig& config) {
	// Initialize the aligner with the provided configuration
	// This is a placeholder implementation
	// You can set parameters like alignment method, reference points, etc.

	config_ = config;
}


cv::Mat FaceAligner::align(const cv::Mat& image, const std::vector<cv::Point2f>& landmarks) {
	// Implement the alignment logic here
	// This is a placeholder implementation
	cv::Mat alignedImage = image.clone();
	// Perform alignment based on landmarks
	return alignedImage;
}


cv::Mat FaceAligner::alignAndCrop(const cv::Mat& image, const std::vector<cv::Point2f>& landmarks) {
	// Implement the alignment and cropping logic here
	// This is a placeholder implementation
	cv::Mat alignedImage = align(image, landmarks);
	// Crop the aligned image based on landmarks
	// For example, you might want to crop around the eyes or mouth
	return alignedImage;
}



