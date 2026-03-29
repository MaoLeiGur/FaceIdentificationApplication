#include "utils/ImageUtils.hpp"

bool validateImage(const cv::Mat& image) {
    return !image.empty() && image.channels() >= 1 && image.rows > 0 && image.cols > 0;
}



cv::Rect scaleRect(const cv::Rect& rect, float scale_x, float scale_y) {
    return cv::Rect(static_cast<int>(rect.x * scale_x),
        static_cast<int>(rect.y * scale_y),
        static_cast<int>(rect.width * scale_x),
        static_cast<int>(rect.height * scale_y));
}