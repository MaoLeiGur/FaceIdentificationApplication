#include <iostream>  
#include <string>
#include <filesystem>

#include "opencv2/opencv.hpp"  
#include "opencv2/core.hpp"  
#include "core/FaceId.hpp"  
#include "api/FaceIdTypes.hpp"  
#ifdef CONFIG_DIR

#endif


int main() {
    std::cout << "Hello, World!" << std::endl;
    try {
        std::cout << "Current Working Directory: " << std::filesystem::current_path() << std::endl;
    }
    catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error retrieving current working directory: " << e.what() << std::endl;
    }

    CFaceId faceId = CFaceId();  
	Person person;
    std::cout << "CONFIG_DIR: " << std::string(CONFIG_DIR) << std::endl;
    std::filesystem::path configFilePath = std::filesystem::current_path()/"config" / "config.json";

    
    faceId.initialize(configFilePath.string());

    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open webcam." << std::endl;
        return -1;
    }
    cv::Mat frame;
    bool keepRunning = true;
    while (keepRunning) {
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "Error: Empty frame captured." << std::endl;
            keepRunning = false;
            continue;
        }

        cv::imshow("Webcam Feed", frame);


        faceId.Run(frame, person);



        if (cv::waitKey(30) == 'q') {
            keepRunning = false;
        }
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}
