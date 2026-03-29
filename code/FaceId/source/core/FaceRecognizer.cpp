#include "core/FaceRecognizer.hpp"



FaceRecognizer::FaceRecognizer() 
{
}

FaceRecognizer::FaceRecognizer(std::shared_ptr<spdlog::logger>& logger):FaceRecognizer()
{
	pLogger = logger;
	pLogger->info("FaceRecognizer created.");
}

FaceRecognizer::~FaceRecognizer() 
{
}

void FaceRecognizer::initialize(const RecognitionConfig& config)
{
	// Initialize the recognizer with the provided configuration
	// This could include loading models, setting parameters, etc.
	// For now, we will just log the initialization
	// pLogger->info("FaceRecognizer initialized with config: {}", config.toString());
	config_ = config;
}

ErrorCode FaceRecognizer::recognize(const FaceDetection& detection, Person& person)
{
	//if (detection.face_image.empty()) {
	//	return ErrorCode::INVALID_INPUT;
	//}
	//// Extract features from the detected face
	//FaceEmbedding embedding;
	//ErrorCode featureExtractionResult = extractFeatures(detection.face_image, embedding);
	//if (featureExtractionResult != ErrorCode::SUCCESS) {
	//	return featureExtractionResult;
	//}
	//// Match the extracted features against the database
	//FaceMatch bestMatch;
	//ErrorCode matchResult = matchFeatures(embedding, bestMatch);
	//if (matchResult != ErrorCode::SUCCESS) {
	//	return matchResult;
	//}
	//// If a match is found, populate the person object
	//if (bestMatch.is_match) {
	//	person.id = bestMatch.person_id;
	//	person.name = bestMatch.person_name;
	//	person.metadata = "Matched with similarity: " + std::to_string(bestMatch.similarity);
	//	person.embeddings.push_back(embedding);
	//	return ErrorCode::SUCCESS;
	//}
	//else {
	//	return ErrorCode::PERSON_NOT_FOUND;
	//}
	return ErrorCode::SUCCESS;
}