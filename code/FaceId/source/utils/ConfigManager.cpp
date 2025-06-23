#include "utils/ConfigManager.hpp"



ConfigManager::ConfigManager() {
	// Constructor implementation (if needed)
}

ConfigManager::ConfigManager(const std::shared_ptr<spdlog::logger>& logger):ConfigManager()
{
	// Initialize the logger if needed
	pLogger = logger;
    pLogger->info("ConfigManager created.");
}


void ConfigManager::loadConfig(const std::string& configFilePath) {
    configFilePath_ = configFilePath;
    try {
        // Open the JSON file  
        std::ifstream file(configFilePath);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open configuration file: " + configFilePath);
        }

        // Parse the JSON file  
        nlohmann::json jsonConfig;
        file >> jsonConfig;

        // Load ImageProcessingConfig  
        if (jsonConfig.contains("ImageProcessingConfig")) {
            auto ipc = jsonConfig["ImageProcessingConfig"];
            imageProcessingConfig_.flip = ipc.value("flip", false);
            imageProcessingConfig_.normalize = ipc.value("normalize", true);
            imageProcessingConfig_.resize = ipc.value("resize", true);
            imageProcessingConfig_.resize_width = ipc.value("resize_width", 640);
            imageProcessingConfig_.resize_height = ipc.value("resize_height", 640);
            imageProcessingConfig_.grayscale = ipc.value("grayscale", false);
            imageProcessingConfig_.equalize = ipc.value("equalize", false);
            imageProcessingConfig_.rotate = ipc.value("rotate", false);
            imageProcessingConfig_.rotate_angle = ipc.value("rotate_angle", 0);
            imageProcessingConfig_.crop = ipc.value("crop", false);
            imageProcessingConfig_.crop_x = ipc.value("crop_x", 0);
            imageProcessingConfig_.crop_y = ipc.value("crop_y", 0);
            imageProcessingConfig_.crop_width = ipc.value("crop_width", 0);
            imageProcessingConfig_.crop_height = ipc.value("crop_height", 0);
            imageProcessingConfig_.detect_faces = ipc.value("detect_faces", false);
        }

        // Load DetectionConfig  
        if (jsonConfig.contains("DetectionConfig")) {
            auto dc = jsonConfig["DetectionConfig"];
            detectionConfig_.confidence_threshold = dc.value("confidence_threshold", 0.7f);
            detectionConfig_.nms_threshold = dc.value("nms_threshold", 0.4f);
            detectionConfig_.input_size = dc.value("input_size", 640);
            detectionConfig_.model_path = dc.value("model_path", "");
            detectionConfig_.backend = dc.value("backend", "opencv");
        }

        // Load RecognitionConfig  
        if (jsonConfig.contains("RecognitionConfig")) {
            auto rc = jsonConfig["RecognitionConfig"];
            recognitionConfig_.similarity_threshold = rc.value("similarity_threshold", 0.6f);
            recognitionConfig_.embedding_size = rc.value("embedding_size", 512);
            recognitionConfig_.normalize_embeddings = rc.value("normalize_embeddings", true);
            recognitionConfig_.model_path = rc.value("model_path", "");
            recognitionConfig_.backend = rc.value("backend", "opencv");
        }

        // Load DatabaseConfig  
        if (jsonConfig.contains("DatabaseConfig")) {
            auto dbc = jsonConfig["DatabaseConfig"];
            databaseConfig_.type = dbc.value("type", "sqlite");
            databaseConfig_.connection_string = dbc.value("connection_string", "");
            databaseConfig_.table_name = dbc.value("table_name", "faces");
            databaseConfig_.auto_create = dbc.value("auto_create", true);
        }

        // Load EncoderConfig  
        if (jsonConfig.contains("EncoderConfig")) {
            auto ec = jsonConfig["EncoderConfig"];
            faceEncoderConfig_.model_path = ec.value("model_path", "");
            faceEncoderConfig_.backend = ec.value("backend", "opencv");
        }

        // Load AlignerConfig  
        if (jsonConfig.contains("AlignerConfig")) {
            auto ac = jsonConfig["AlignerConfig"];
            faceAlignerConfig_.model_path = ac.value("model_path", "");
            faceAlignerConfig_.backend = ac.value("backend", "opencv");
        }

    }
    catch (const std::exception& e) {
        throw std::runtime_error("Error loading configuration: " + std::string(e.what()));
    }
}

void ConfigManager::initialize(const std::string& configFilePath) {
	
	configFilePath_ = configFilePath;
	if (configFilePath_.empty()) { // If no config file is provided, use default values
		imageProcessingConfig_  = ImageProcessingConfig(); // Set default or loaded values
		detectionConfig_        = DetectionConfig(); // Set default or loaded values
		recognitionConfig_      = RecognitionConfig(); // Set default or loaded values
		databaseConfig_         = DatabaseConfig(); // Set default or loaded values
        faceAlignerConfig_      = FaceAlignerConfig();
        faceEncoderConfig_      = FaceEncoderConfig();
        recognitionConfig_      = RecognitionConfig();
	}
	else
	{
		loadConfig(configFilePath);
	}
	// Initialize other configurations if needed
	// For example, you can set default values for image processing, detection, recognition, and database configurations
}

std::string ConfigManager::getConfigFilePath() const {
	return configFilePath_;
}

void ConfigManager::setConfigFilePath(const std::string& path) {
	configFilePath_ = path;
}

// Getters for other configuration parameters
ImageProcessingConfig ConfigManager::get_imageProcessingConfig() const {
	return imageProcessingConfig_;
}

DetectionConfig ConfigManager::get_detectionConfig() const {
	return detectionConfig_;
}

RecognitionConfig ConfigManager::get_recognitionConfig() const {
	return recognitionConfig_;
}

DatabaseConfig ConfigManager::get_databaseConfig() const {
	return databaseConfig_;
}


FaceAlignerConfig ConfigManager::get_alignerConfig() const {
    return faceAlignerConfig_;
}

FaceEncoderConfig ConfigManager::get_encodingConfig() const {
    return faceEncoderConfig_;
}


// Setters for other configuration parameters:
void ConfigManager::setImageProcessingConfig(const ImageProcessingConfig& config) {
	imageProcessingConfig_ = config;
}

void ConfigManager::setDetectionConfig(const DetectionConfig& config) {
	detectionConfig_ = config;
}

void ConfigManager::setRecognitionConfig(const RecognitionConfig& config) {
	recognitionConfig_ = config;
}

void ConfigManager::setDatabaseConfig(const DatabaseConfig& config) {
	databaseConfig_ = config;
}


void ConfigManager::setAlignerConfig(const FaceAlignerConfig& config) {
    faceAlignerConfig_ = config;
}
void ConfigManager::setEncoderConfig(const FaceEncoderConfig& config) {
    faceEncoderConfig_ = config;
}