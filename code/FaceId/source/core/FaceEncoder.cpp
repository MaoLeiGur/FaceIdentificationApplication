#include "core/FaceEncoder.hpp"



FaceEncoder::FaceEncoder()
{

}
FaceEncoder::FaceEncoder(std::shared_ptr<spdlog::logger>& logger):FaceEncoder()
{
	pLogger = logger;
	pLogger->info("FaceEncoder created.");
}

FaceEncoder::~FaceEncoder()
{
}



ErrorCode FaceEncoder::initialize(const FaceEncoderConfig& config)
{
	// Initialize the encoder with the provided configuration
	// This could include loading models, setting parameters, etc.
	// For now, we will just log the initialization
	pLogger->info("Initializing FaceEncoder with model path: {}", config.model_path);
	

	return ErrorCode::SUCCESS;
}
ErrorCode FaceEncoder::encode(const FaceDetection& faceDetection, FaceLandmarks& landmarks)
{
	return ErrorCode::SUCCESS;
}
ErrorCode FaceEncoder::encodeBatch(const std::vector<FaceDetection>& faceDetections, std::vector<FaceLandmarks>& landmarks)
{
	return ErrorCode::SUCCESS;
}

void FaceEncoder::setBatchSize(int batch_size)
{

}
int FaceEncoder::getBatchSize() const
{
	return 0;
}