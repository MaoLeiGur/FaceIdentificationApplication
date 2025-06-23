#pragma once
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <memory>

#include <fstream>
#include <nlohmann/json.hpp>
#include <stdexcept>  

#include "api/FaceIdTypes.hpp"
#include "utils/Logger.hpp"

class ConfigManager {
public:
	ConfigManager();

	ConfigManager(const std::shared_ptr<spdlog::logger>& logger);
	void initialize(const std::string& configFilePath);
	void loadConfig(const std::string& configFilePath);
	std::string getConfigFilePath() const;

	void setConfigFilePath(const std::string& path);
	
	ImageProcessingConfig get_imageProcessingConfig() const;
	DetectionConfig get_detectionConfig() const;
	RecognitionConfig get_recognitionConfig() const;
	DatabaseConfig get_databaseConfig() const;

	FaceAlignerConfig get_alignerConfig() const;
	FaceEncoderConfig get_encodingConfig() const;
	void setImageProcessingConfig(const ImageProcessingConfig& config);
	void setDetectionConfig(const DetectionConfig& config);
	void setRecognitionConfig(const RecognitionConfig& config);
	void setDatabaseConfig(const DatabaseConfig& config);

	void setAlignerConfig(const FaceAlignerConfig& config);
	void setEncoderConfig(const FaceEncoderConfig& config);

private:
	std::shared_ptr<spdlog::logger> pLogger;
	std::string configFilePath_;
	ImageProcessingConfig imageProcessingConfig_;
	DetectionConfig detectionConfig_;
	FaceAlignerConfig faceAlignerConfig_;
	FaceEncoderConfig faceEncoderConfig_;
	RecognitionConfig recognitionConfig_;
	DatabaseConfig databaseConfig_;
};