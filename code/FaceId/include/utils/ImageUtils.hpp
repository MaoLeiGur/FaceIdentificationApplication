
#pragma once

#include <opencv2/opencv.hpp>
#include <vector>


bool validateImage(const cv::Mat& image);


cv::Rect scaleRect(const cv::Rect& rect, float scale_x, float scale_y);

