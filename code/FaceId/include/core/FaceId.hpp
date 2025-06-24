#pragma once

#include <string>
#include <memory>


#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

//#include <nlohmann/json.hpp>
//#include <spdlog/spdlog.h>


#include "api/FaceIdAPI.hpp"
#include "api/FaceIdTypes.hpp"

#include "utils/ConfigManager.hpp"
#include "utils/Logger.hpp"
#include "utils/ImageUtils.hpp"
#include "utils/GeometryUtils.hpp"


#include "preprocessing/ImageProcessor.hpp"
#include "preprocessing/FaceAligner.hpp"
#include "preprocessing/QualityAssessor.hpp"

#include "FaceDatabase.hpp"
#include "FaceDetector.hpp"
#include "FaceEncoder.hpp"
#include "FaceRecognizer.hpp"



class CFaceId {
public:
	CFaceId();
	~CFaceId();

	void initialize(const std::string& config_path);

	ErrorCode Run(const cv::Mat& image,Person& person);
	//ErrorCode Run(const cv::Mat& image, std::vector<Person>& persons);

private:
	std::shared_ptr<spdlog::logger> pLogger;
	std::shared_ptr<ConfigManager> pConfigManager;
	std::unique_ptr<ImageProcessor> pImageProcessor;
	std::unique_ptr<FaceDetector> pDetector;
	std::unique_ptr<FaceRecognizer> pRecognizer;
	std::unique_ptr<FaceEncoder> pEncoder;
	std::unique_ptr<FaceAligner> pAligner;




	cv::Mat							ppFrame_;
	std::vector<FaceDetection>		facesDetections_;

};







