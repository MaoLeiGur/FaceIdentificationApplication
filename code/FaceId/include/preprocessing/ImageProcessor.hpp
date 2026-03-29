#pragma once

#include <string>
#include <vector>
#include <memory>
#include <opencv2/opencv.hpp>

#include <utils/Logger.hpp>
#include <api/FaceIdTypes.hpp>

class ImageProcessor
{
public:
	ImageProcessor();
	ImageProcessor(std::shared_ptr<spdlog::logger>& logger);
	~ImageProcessor();

	// Initialize the ImageProcessor with configuration parameters
	void initialize(const ImageProcessingConfig& config);

	void process(const cv::Mat& image, cv::Mat& processedImage);


	// Preprocessing functions  
	bool resizeImage(const cv::Mat& image, int width, int height, cv::Mat& resizedImage);
	bool convertToGrayscale(const cv::Mat& image, cv::Mat& grayscaleImage);
	bool normalizeImage(const cv::Mat& image , cv::Mat& normalizedImage);
	bool applyRotation(const cv::Mat& image, double angle, cv::Mat& rotatedImage);
	bool applyGaussianBlur(const cv::Mat& image, int kernelSize, double sigmaX, double sigmaY, cv::Mat& blurredImage);
	bool applyMedianBlur(const cv::Mat& image, int kernelSize, cv::Mat& blurredImage);
	bool applyBilateralFilter(const cv::Mat& image, int d, double sigmaColor, double sigmaSpace, cv::Mat& filteredImage);
	bool applyCannyEdgeDetection(const cv::Mat& image, int threshold1, int threshold2, cv::Mat& edgeImage);
	bool applyAdaptiveThreshold(const cv::Mat& image, int maxValue, int adaptiveMethod, int thresholdType, int blockSize, double C, cv::Mat& thresholdedImage);
	bool flipImage(const cv::Mat& image, int flipCode, cv::Mat& flippedImage);
	bool applyHistogramEqualization(const cv::Mat& image, cv::Mat& equalizedImage);
	bool applyCLAHE(const cv::Mat& image, double clipLimit, cv::Size tileGridSize, cv::Mat& claheImage);
	bool applyMorphologicalOperations(const cv::Mat& image, int operation, const cv::Mat& kernel, int iterations, cv::Mat& morphedImage);
	bool applyThreshold(const cv::Mat& image, double thresh, double maxVal, int type, cv::Mat& thresholdedImage);
	bool applyDilation(const cv::Mat& image, const cv::Mat& kernel, int iterations, cv::Mat& dilatedImage);
	bool applyErosion(const cv::Mat& image, const cv::Mat& kernel, int iterations, cv::Mat& erodedImage);
	bool applyOpening(const cv::Mat& image, const cv::Mat& kernel, int iterations, cv::Mat& openedImage);
	bool applyClosing(const cv::Mat& image, const cv::Mat& kernel, int iterations, cv::Mat& closedImage);
	bool applyMorphologyEx(const cv::Mat& image, int operation, const cv::Mat& kernel, int iterations, cv::Mat& morphedImage);
	bool applySobelFilter(const cv::Mat& image, int ddepth, int dx, int dy, int ksize, double scale, double delta, cv::Mat& sobelImage);
	bool applyScharrFilter(const cv::Mat& image, int ddepth, int dx, int dy, double scale, double delta, cv::Mat& scharrImage);
	bool applyLaplacianFilter(const cv::Mat& image, int ddepth, int ksize, double scale, double delta, cv::Mat& laplacianImage);
	bool applyResize(const cv::Mat& image, int width, int height, cv::Mat& resizedImage);
	bool applyCrop(const cv::Mat& image, const cv::Rect& roi, cv::Mat& croppedImage);
	bool applyCrop(const cv::Mat& image, int x, int y, int width, int height, cv::Mat& croppedImage);
	bool applyColorConversion(const cv::Mat& image, int code, cv::Mat& convertedImage);
	bool applyPerspectiveTransform(const cv::Mat& image, const std::vector<cv::Point2f>& srcPoints, const std::vector<cv::Point2f>& dstPoints, cv::Mat& transformedImage);
	bool applyAffineTransform(const cv::Mat& image, const cv::Mat& M, const cv::Size& dsize, cv::Mat& transformedImage);
	bool applyBitwiseAnd(const cv::Mat& image1, const cv::Mat& image2, cv::Mat& resultImage);
	bool applyBitwiseOr(const cv::Mat& image1, const cv::Mat& image2, cv::Mat& resultImage);
	bool applyBitwiseXor(const cv::Mat& image1, const cv::Mat& image2, cv::Mat& resultImage);
	bool applyBitwiseNot(const cv::Mat& image, cv::Mat& resultImage);
	bool applyFloodFill(const cv::Mat& image, cv::Point seedPoint, const cv::Scalar& newVal, cv::Rect* rect = nullptr, const cv::Scalar& loDiff = cv::Scalar(), const cv::Scalar& upDiff = cv::Scalar(), int flags = 4);
	bool applyConnectedComponents(const cv::Mat& image, cv::Mat& labels, int connectivity = 8, cv::Mat& stats = cv::Mat(), cv::Mat& centroids = cv::Mat());
	bool applyConnectedComponentsWithStats(const cv::Mat& image, cv::Mat& labels, cv::Mat& stats, cv::Mat& centroids, int connectivity = 8);
	bool applyDistanceTransform(const cv::Mat& image, int distanceType, int maskSize, cv::Mat& distImage);

	bool applyFindContours(const cv::Mat& image, std::vector<std::vector<cv::Point>>& contours, int mode, int method);
	bool applyWatershed(const cv::Mat& image, const cv::Mat& markers, cv::Mat& watershedImage);
	bool applyTemplateMatching(const cv::Mat& image, const cv::Mat& templ, int method, cv::Mat& resultImage);
	bool applyHoughLines(const cv::Mat& image, std::vector<cv::Vec2f>& lines, double rho = 1, double theta = CV_PI / 180, int threshold = 100);
	bool applyHoughCircles(const cv::Mat& image, std::vector<cv::Vec3f>& circles, double dp = 1, double minDist = 20, double param1 = 100, double param2 = 30, int minRadius = 0, int maxRadius = 0);
	bool applyHoughLinesP(const cv::Mat& image, std::vector<cv::Vec4i>& lines, double rho = 1, double theta = CV_PI / 180, int threshold = 100, double minLineLength = 0, double maxLineGap = 0);
	bool applyCvtColor(const cv::Mat& image, int code, cv::Mat& convertedImage);
	bool applyResize(const cv::Mat& image, const cv::Size& size, cv::Mat& resizedImage);
	bool applyFlip(const cv::Mat& image, int flipCode, cv::Mat& flippedImage);
	bool applySaturation(const cv::Mat& image, double alpha, double beta, cv::Mat& saturatedImage);
	bool applyBrightness(const cv::Mat& image, double alpha, double beta, cv::Mat& brightenedImage);
	bool applyContrast(const cv::Mat& image, double alpha, double beta, cv::Mat& contrastedImage);
	bool applySharpening(const cv::Mat& image, cv::Mat& sharpenedImage);
	bool applyColorSpaceConversion(const cv::Mat& image, int code, cv::Mat& convertedImage);
	bool applyImageBlending(const cv::Mat& image1, const cv::Mat& image2, double alpha, double beta, double gamma, cv::Mat& blendedImage);
	bool applyImageAddition(const cv::Mat& image1, const cv::Mat& image2, cv::Mat& addedImage);
	bool applyImageSubtraction(const cv::Mat& image1, const cv::Mat& image2, cv::Mat& subtractedImage);
	bool applyImageMultiplication(const cv::Mat& image1, const cv::Mat& image2, cv::Mat& multipliedImage);
	bool applyImageDivision(const cv::Mat& image1, const cv::Mat& image2, cv::Mat& dividedImage);
	bool applyImageMasking(const cv::Mat& image, const cv::Mat& mask, cv::Mat& maskedImage);
	bool applyImageThresholding(const cv::Mat& image, double thresh, double maxVal, int type, cv::Mat& thresholdedImage);
	bool applyImageMorphology(const cv::Mat& image, int operation, const cv::Mat& kernel, int iterations, cv::Mat& morphedImage);

private:

	std::shared_ptr<spdlog::logger> pLogger;


	ImageProcessingConfig config_;
};

