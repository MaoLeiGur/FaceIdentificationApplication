#include "preprocessing/ImageProcessor.hpp"


ImageProcessor::ImageProcessor() {
	// Constructor implementation (if needed)
}


ImageProcessor::ImageProcessor(std::shared_ptr<spdlog::logger>& logger):ImageProcessor()
{
	pLogger = logger;
	pLogger->info("ImageProcessor created.");
}
ImageProcessor::~ImageProcessor() {
	// Destructor implementation (if needed)
}



void ImageProcessor::initialize(const ImageProcessingConfig& config)
{
	config_ = config;
}


void ImageProcessor::process(const cv::Mat& image, cv::Mat& processedImage) 
{
	// Process the image using the configuration settings
	// This is a placeholder implementation
	cv::Mat frameGray, frameRezised;
	convertToGrayscale(image, frameGray);
	applyResize(frameGray, config_.resize_width, config_.resize_height, processedImage);

	applyHistogramEqualization(processedImage, processedImage);
}

bool ImageProcessor::resizeImage(const cv::Mat& image, int width, int height, cv::Mat& resizedImage) {
	if (image.empty()) {
		pLogger->error("Input image is empty.");
		return false;
	}
	cv::resize(image, resizedImage, cv::Size(width, height));
	return true;
}


bool ImageProcessor::convertToGrayscale(const cv::Mat& image, cv::Mat& grayscaleImage) {
	if (image.empty()) {
		pLogger->error("Input image is empty.");
		return false;
	}
	cv::cvtColor(image, grayscaleImage, cv::COLOR_BGR2GRAY);
	return true;
}

bool ImageProcessor::normalizeImage(const cv::Mat& image, cv::Mat& normalizedImage) {
	if (image.empty()) {
		pLogger->error("Input image is empty.");
		return false;
	}
	image.convertTo(normalizedImage, CV_32F, 1.0 / 255.0);
	return true;
}


bool ImageProcessor::applyRotation(const cv::Mat& image, double angle, cv::Mat& rotatedImage) {
	if (image.empty()) {
		pLogger->error("Input image is empty.");
		return false;
	}
	cv::Mat rotationMatrix = cv::getRotationMatrix2D(cv::Point2f(image.cols / 2, image.rows / 2), angle, 1.0);
	cv::warpAffine(image, rotatedImage, rotationMatrix, image.size());
	return true;
}

bool ImageProcessor::flipImage(const cv::Mat& image, int flipCode, cv::Mat& flippedImage) {
	if (image.empty()) {
		pLogger->error("Input image is empty.");
		return false;
	}
	cv::flip(image, flippedImage, flipCode);
	return true;
}

bool ImageProcessor::applyGaussianBlur(const cv::Mat & image, int kernelSize, double sigmaX, double sigmaY, cv::Mat & blurredImage){
	if (image.empty()) {
		pLogger->error("Input image is empty.");
		return false;
	}
	if (kernelSize % 2 == 0) {
		pLogger->error("Kernel size must be odd.");
		return false;
	}
	cv::GaussianBlur(image, blurredImage, cv::Size(kernelSize, kernelSize), sigmaX, sigmaY);
	return true;
}

bool ImageProcessor::applyMedianBlur(const cv::Mat& image, int kernelSize, cv::Mat& blurredImage) {
	if (image.empty()) {
		pLogger->error("Input image is empty.");
		return false;
	}
	if (kernelSize % 2 == 0) {
		pLogger->error("Kernel size must be odd.");
		return false;
	}
	cv::medianBlur(image, blurredImage, kernelSize);
	return true;
}


bool ImageProcessor::applyBilateralFilter(const cv::Mat& image, int d, double sigmaColor, double sigmaSpace, cv::Mat& filteredImage) {
	if (image.empty()) {
		pLogger->error("Input image is empty.");
		return false;
	}
	cv::bilateralFilter(image, filteredImage, d, sigmaColor, sigmaSpace);
	return true;
}

bool ImageProcessor::applyCannyEdgeDetection(const cv::Mat& image, int threshold1, int threshold2, cv::Mat& edgeImage) {
	if (image.empty()) {
		pLogger->error("Input image is empty.");
		return false;
	}
	cv::Canny(image, edgeImage, threshold1, threshold2);
	return true;
}


bool ImageProcessor::applyAdaptiveThreshold(const cv::Mat& image, int maxValue, int adaptiveMethod, int thresholdType, int blockSize, double C, cv::Mat& thresholdedImage) {
	if (image.empty()) {
		pLogger->error("Input image is empty.");
		return false;
	}
	cv::adaptiveThreshold(image, thresholdedImage, maxValue, adaptiveMethod, thresholdType, blockSize, C);
	return true;
}


bool ImageProcessor::applyMorphologicalOperations(const cv::Mat& image, int operation, const cv::Mat& kernel, int iterations, cv::Mat& morphedImage) {
	if (image.empty()) {
		pLogger->error("Input image is empty.");
		return false;
	}
	cv::morphologyEx(image, morphedImage, operation, kernel, cv::Point(-1, -1), iterations);
	return true;
}


bool ImageProcessor::applyHistogramEqualization(const cv::Mat& image, cv::Mat& equalizedImage) {
	if (image.empty()) {
		pLogger->error("Input image is empty.");
		return false;
	}
	if (image.channels() == 3) {
		cv::cvtColor(image, equalizedImage, cv::COLOR_BGR2GRAY);
	}
	else {
		equalizedImage = image.clone();
	}
	cv::equalizeHist(equalizedImage, equalizedImage);
	return true;
}

bool ImageProcessor::applyResize(const cv::Mat& image, int width, int height, cv::Mat& resizedImage) {
	if (image.empty()) {
		pLogger->error("Input image is empty.");
		return false;
	}
	cv::resize(image, resizedImage, cv::Size(width, height));
	return true;
}

bool ImageProcessor::applyCrop(const cv::Mat& image, const cv::Rect& roi, cv::Mat& croppedImage) {
	if (image.empty()) {
		pLogger->error("Input image is empty.");
		return false;
	}
	if (roi.x < 0 || roi.y < 0 || roi.x + roi.width > image.cols || roi.y + roi.height > image.rows) {
		pLogger->error("ROI is out of bounds.");
		return false;
	}
	croppedImage = image(roi);
	return true;
}

bool ImageProcessor::applyCrop(const cv::Mat& image, int x, int y, int width, int height, cv::Mat& croppedImage) {
	if (image.empty()) {
		pLogger->error("Input image is empty.");
		return false;
	}
	croppedImage = image(cv::Rect(x, y, width, height));
	return true;
}

bool ImageProcessor::applyColorConversion(const cv::Mat& image, int code, cv::Mat& convertedImage) {
	if (image.empty()) {
		pLogger->error("Input image is empty.");
		return false;
	}
	cv::cvtColor(image, convertedImage, code);
	return true;
}

bool ImageProcessor::applyPerspectiveTransform(const cv::Mat& image, const std::vector<cv::Point2f>& srcPoints, const std::vector<cv::Point2f>& dstPoints, cv::Mat& transformedImage) {
	if (image.empty()) {
		pLogger->error("Input image is empty.");
		return false;
	}
	if (srcPoints.size() != 4 || dstPoints.size() != 4) {
		pLogger->error("Source and destination points must have exactly 4 points.");
		return false;
	}
	cv::Mat M = cv::getPerspectiveTransform(srcPoints, dstPoints);
	cv::warpPerspective(image, transformedImage, M, image.size());
	return true;
}

bool ImageProcessor::applyAffineTransform(const cv::Mat& image, const cv::Mat& M, const cv::Size& dsize, cv::Mat& transformedImage) {
	if (image.empty()) {
		pLogger->error("Input image is empty.");
		return false;
	}
	if (M.empty() || M.rows != 2 || M.cols != 3) {
		pLogger->error("Invalid affine transformation matrix.");
		return false;
	}
	cv::warpAffine(image, transformedImage, M, dsize);
	return true;
}

bool ImageProcessor::applyBitwiseAnd(const cv::Mat& image1, const cv::Mat& image2, cv::Mat& resultImage) {
	if (image1.empty() || image2.empty()) {
		pLogger->error("Input images are empty.");
		return false;
	}
	if (image1.size() != image2.size() || image1.type() != image2.type()) {
		pLogger->error("Input images must have the same size and type.");
		return false;
	}
	cv::bitwise_and(image1, image2, resultImage);
	return true;
}

bool ImageProcessor::applyBitwiseOr(const cv::Mat& image1, const cv::Mat& image2, cv::Mat& resultImage) {
	if (image1.empty() || image2.empty()) {
		pLogger->error("Input images are empty.");
		return false;
	}
	if (image1.size() != image2.size() || image1.type() != image2.type()) {
		pLogger->error("Input images must have the same size and type.");
		return false;
	}
	cv::bitwise_or(image1, image2, resultImage);
	return true;
}

bool ImageProcessor::applyBitwiseXor(const cv::Mat& image1, const cv::Mat& image2, cv::Mat& resultImage) {
	if (image1.empty() || image2.empty()) {
		pLogger->error("Input images are empty.");
		return false;
	}
	if (image1.size() != image2.size() || image1.type() != image2.type()) {
		pLogger->error("Input images must have the same size and type.");
		return false;
	}
	cv::bitwise_xor(image1, image2, resultImage);
	return true;
}

bool ImageProcessor::applyBitwiseNot(const cv::Mat& image, cv::Mat& resultImage) {
	if (image.empty()) {
		pLogger->error("Input image is empty.");
		return false;
	}
	cv::bitwise_not(image, resultImage);
	return true;
}

bool ImageProcessor::applyFloodFill(const cv::Mat& image, cv::Point seedPoint, const cv::Scalar& newVal, cv::Rect* rect, const cv::Scalar& loDiff, const cv::Scalar& upDiff, int flags) {
	if (image.empty()) {
		pLogger->error("Input image is empty.");
		return false;
	}
	cv::Mat tempImage = image.clone();
	cv::floodFill(tempImage, seedPoint, newVal, rect, loDiff, upDiff, flags);
	return true;
}

bool ImageProcessor::applyConnectedComponents(const cv::Mat& image, cv::Mat& labels, int connectivity, cv::Mat& stats, cv::Mat& centroids) {
	if (image.empty()) {
		pLogger->error("Input image is empty.");
		return false;
	}
	int numLabels = cv::connectedComponentsWithStats(image, labels, stats, centroids, connectivity);
	return numLabels > 0;
}

bool ImageProcessor::applyConnectedComponentsWithStats(const cv::Mat& image, cv::Mat& labels, cv::Mat& stats, cv::Mat& centroids, int connectivity) {
	if (image.empty()) {
		pLogger->error("Input image is empty.");
		return false;
	}
	int numLabels = cv::connectedComponentsWithStats(image, labels, stats, centroids, connectivity);
	return numLabels > 0;
}

bool ImageProcessor::applyDistanceTransform(const cv::Mat& image, int distanceType, int maskSize, cv::Mat& distImage) {
	if (image.empty()) {
		pLogger->error("Input image is empty.");
		return false;
	}
	cv::distanceTransform(image, distImage, distanceType, maskSize);
	return true;
}

bool ImageProcessor::applyFindContours(const cv::Mat& image, std::vector<std::vector<cv::Point>>& contours, int mode, int method) {
	if (image.empty()) {
		pLogger->error("Input image is empty.");
		return false;
	}
	cv::findContours(image, contours, mode, method);
	return true;
}

bool ImageProcessor::applyWatershed(const cv::Mat& image, const cv::Mat& markers, cv::Mat& watershedImage) {
	if (image.empty() || markers.empty()) {
		pLogger->error("Input image or markers are empty.");
		return false;
	}
	if (image.size() != markers.size()) {
		pLogger->error("Image and markers must have the same size.");
		return false;
	}
	watershedImage = image.clone();
	cv::watershed(watershedImage, markers);
	return true;
}

bool ImageProcessor::applyTemplateMatching(const cv::Mat& image, const cv::Mat& templ, int method, cv::Mat& resultImage) {
	if (image.empty() || templ.empty()) {
		pLogger->error("Input image or template is empty.");
		return false;
	}
	cv::matchTemplate(image, templ, resultImage, method);
	return true;
}

bool ImageProcessor::applyHoughLines(const cv::Mat& image, std::vector<cv::Vec2f>& lines, double rho, double theta, int threshold) {
	if (image.empty()) {
		pLogger->error("Input image is empty.");
		return false;
	}
	cv::HoughLines(image, lines, rho, theta, threshold);
	return true;
}
bool ImageProcessor::applyHoughCircles(const cv::Mat& image, std::vector<cv::Vec3f>& circles, double dp, double minDist, double param1, double param2, int minRadius, int maxRadius) {
	if (image.empty()) {
		pLogger->error("Input image is empty.");
		return false;
	}
	cv::HoughCircles(image, circles, cv::HOUGH_GRADIENT, dp, minDist, param1, param2, minRadius, maxRadius);
	return true;
}

bool ImageProcessor::applyHoughLinesP(const cv::Mat& image, std::vector<cv::Vec4i>& lines, double rho, double theta, int threshold, double minLineLength, double maxLineGap) {
	if (image.empty()) {
		pLogger->error("Input image is empty.");
		return false;
	}
	cv::HoughLinesP(image, lines, rho, theta, threshold, minLineLength, maxLineGap);
	return true;
}

bool ImageProcessor::applyCvtColor(const cv::Mat& image, int code, cv::Mat& convertedImage) {
	if (image.empty()) {
		pLogger->error("Input image is empty.");
		return false;
	}
	cv::cvtColor(image, convertedImage, code);
	return true;
}


bool ImageProcessor::applyFlip(const cv::Mat& image, int flipCode, cv::Mat& flippedImage) {
	if (image.empty()) {
		pLogger->error("Input image is empty.");
		return false;
	}

	try {
		cv::flip(image, flippedImage, flipCode);
		pLogger->info("Image flipped successfully.");
		return true;
	}
	catch (const cv::Exception& e) {
		pLogger->error("Error during image flipping: " + std::string(e.what()));
		return false;
	}
}


bool ImageProcessor::applySaturation(const cv::Mat& image, double alpha, double beta, cv::Mat& saturatedImage) {
	if (image.empty()) return false;
	image.convertTo(saturatedImage, -1, alpha, beta);
	return true;
}

bool ImageProcessor::applyBrightness(const cv::Mat& image, double alpha, double beta, cv::Mat& brightenedImage) {
	if (image.empty()) return false;
	image.convertTo(brightenedImage, -1, alpha, beta);
	return true;
}

bool ImageProcessor::applyContrast(const cv::Mat& image, double alpha, double beta, cv::Mat& contrastedImage) {
	if (image.empty()) return false;
	image.convertTo(contrastedImage, -1, alpha, beta);
	return true;
}

bool ImageProcessor::applySharpening(const cv::Mat& image, cv::Mat& sharpenedImage) {
	if (image.empty()) return false;
	cv::Mat kernel = (cv::Mat_<float>(3, 3) <<
		0, -1, 0,
		-1, 5, -1,
		0, -1, 0);
	cv::filter2D(image, sharpenedImage, image.depth(), kernel);
	return true;
}

bool ImageProcessor::applyColorSpaceConversion(const cv::Mat& image, int code, cv::Mat& convertedImage) {
	if (image.empty())
	{
		pLogger->error("Input image is empty.");
		return false;
	}
	
	cv::cvtColor(image, convertedImage, code);
	return true;
}

bool ImageProcessor::applyImageBlending(const cv::Mat& image1, const cv::Mat& image2, double alpha, double beta, double gamma, cv::Mat& blendedImage) 
{
	if (image1.empty())
	{
		pLogger->error("Input image1 is empty.");
		return false;
	}
	if (image2.empty())
	{
		pLogger->error("Input image2 is empty.");
		return false;
	}
	cv::addWeighted(image1, alpha, image2, beta, gamma, blendedImage);
	return true;
}

bool ImageProcessor::applyImageAddition(const cv::Mat& image1, const cv::Mat& image2, cv::Mat& addedImage) {
	if (image1.empty())
	{
		pLogger->error("Input image1 is empty.");
		return false;
	}
	if (image2.empty())
	{
		pLogger->error("Input image2 is empty.");
		return false;
	}
	cv::add(image1, image2, addedImage);
	return true;
}

bool ImageProcessor::applyImageSubtraction(const cv::Mat& image1, const cv::Mat& image2, cv::Mat& subtractedImage) {
	if (image1.empty())
	{
		pLogger->error("Input image1 is empty.");
		return false;
	}
	if (image2.empty())
	{
		pLogger->error("Input image2 is empty.");
		return false;
	}
	cv::subtract(image1, image2, subtractedImage);
	return true;
}

bool ImageProcessor::applyImageMultiplication(const cv::Mat& image1, const cv::Mat& image2, cv::Mat& multipliedImage) {
	if (image1.empty())
	{
		pLogger->error("Input image1 is empty.");
		return false;
	}
	if (image2.empty())
	{
		pLogger->error("Input image2 is empty.");
		return false;
	}
	cv::multiply(image1, image2, multipliedImage);
	return true;
}

bool ImageProcessor::applyImageDivision(const cv::Mat& image1, const cv::Mat& image2, cv::Mat& dividedImage) {
	if (image1.empty())
	{
		pLogger->error("Input image1 is empty.");
		return false;
	}
	if (image2.empty())
	{
		pLogger->error("Input image2 is empty.");
		return false;
	}
	cv::divide(image1, image2, dividedImage);
	return true;
}

bool ImageProcessor::applyImageMasking(const cv::Mat& image, const cv::Mat& mask, cv::Mat& maskedImage) {
	if (image.empty())
	{
		pLogger->error("Input image is empty.");
		return false;
	}
	if (mask.empty())
	{
		pLogger->error("Input mask is empty.");
		return false;
	}
	image.copyTo(maskedImage, mask);
	return true;
}

bool ImageProcessor::applyImageThresholding(const cv::Mat& image, double thresh, double maxVal, int type, cv::Mat& thresholdedImage) {
	if (image.empty())
	{
		pLogger->error("Input image is empty.");
		return false;
	}
	cv::threshold(image, thresholdedImage, thresh, maxVal, type);
	return true;
}

bool ImageProcessor::applyImageMorphology(const cv::Mat& image, int operation, const cv::Mat& kernel, int iterations, cv::Mat& morphedImage) {
	if (image.empty())
	{
		pLogger->error("Input image is empty.");
		return false;
	}
	if (kernel.empty())
	{
		pLogger->error("Input kernel is empty.");
		return false;
	}

	cv::morphologyEx(image, morphedImage, operation, kernel, cv::Point(-1, -1), iterations);
	return true;
}
