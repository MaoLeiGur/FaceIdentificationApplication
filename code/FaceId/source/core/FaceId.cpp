#include "core/FaceId.hpp"




CFaceId::CFaceId() 
{
	// Initialize components
	LoggerConfig LoggerConfig;


	Logger::getInstance().init(LoggerConfig);
	pLogger = Logger::getInstance().getLogger();

	pConfigManager = std::make_shared<ConfigManager>(pLogger);
	pImageProcessor = std::make_unique<ImageProcessor>(pLogger);
	pDetector = std::make_unique<FaceDetector>(pLogger);
	pRecognizer = std::make_unique<FaceRecognizer>(pLogger);
	
	// pEncoder = std::make_unique<FaceEncoder>();
	// pAligner = std::make_unique<FaceAligner>();

}

CFaceId::~CFaceId()
{
	// Destructor implementation (if needed)
}


void CFaceId::initialize(const std::string& config_path)
{
	// Load configuration and initialize components
	pConfigManager->initialize(config_path);
	pImageProcessor->initialize(pConfigManager->get_imageProcessingConfig());
	pDetector->initialize(pConfigManager->get_detectionConfig());
	pRecognizer->initialize(pConfigManager->get_recognitionConfig());
	pEncoder->initialize(pConfigManager->get_encodingConfig());
	pAligner->initialize(pConfigManager->get_alignerConfig());
}


ErrorCode CFaceId::Run(const cv::Mat& image, Person& person)
{
	if (image.empty()) {
		pLogger->error("Input image is empty.");
		return ErrorCode::INVALID_INPUT;
	}

	cv::Mat frameGray,frameRezised;
	
	//(1) PreProcessing:
	pImageProcessor->convertToGrayscale(image, frameGray);
	ImageProcessingConfig imageProcessingConfig = pConfigManager->get_imageProcessingConfig();
	uint16_t width = imageProcessingConfig.resize_width;
	uint16_t height = imageProcessingConfig.resize_height;
	if (width == 0 || height == 0) {
		pLogger->error("Resize dimensions are not set in the configuration.");
		return ErrorCode::INVALID_CONFIG;
	}
	pImageProcessor->applyResize(frameGray, width,height, frameRezised);

	
	//(2) Detect faces in the image
	std::vector<FaceDetection> facesDetections;
	ErrorCode detectionResult = pDetector->detect(frameRezised, facesDetections);
	if (detectionResult != ErrorCode::SUCCESS || facesDetections.empty()) {
		return detectionResult;
	}

	//for each face detected in the image:
	if (facesDetections.size() > 1) {
		pLogger->warn("Multiple faces detected, recognizing the first one.");
	}


	//(4) Encode Faces:
	std::vector<FaceLandmarks> landmarks;
	ErrorCode encodingResult = pEncoder->encodeBatch(facesDetections, landmarks);
	if (encodingResult != ErrorCode::SUCCESS) {
		return encodingResult;
	}

	//(3) Detect faces in the image:
	//pAligner->align(facesDetections[0].face_image, facesDetections[0].face_image_aligned);
	// Recognize the first detected face
	ErrorCode recognitionResult = pRecognizer->recognize(facesDetections[0], person);
	return recognitionResult;
}


