#include <iostream>

#include "opencv2/opencv.hpp"
#include "opencv2/core.hpp"

//#include "core/FaceId.hpp"
//#include "api/FaceIdTypes.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;


    //CFaceId faceId = CFaceId();
	//faceId.initialize("config.json");

    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open webcam." << std::endl;
        return -1;
    }

    cv::Mat frame;
    while (true) {
        // Capture a frame from the webcam  
        cap >> frame;
        if (frame.empty()) {
            std::cerr << "Error: Empty frame captured." << std::endl;
            break;
        }

        // Display the frame  
        cv::imshow("Webcam Feed", frame);


		//faceId.Run(frame, Person());


        // Break the loop if 'q' is pressed  
        if (cv::waitKey(30) == 'q') {
            break;
        }
    }

    // Release the webcam and close windows  
    cap.release();
    cv::destroyAllWindows();

    return 0;


    return 0;
}