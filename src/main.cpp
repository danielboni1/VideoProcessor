#include <opencv2/opencv.hpp>
#include <gst/gst.h>
#include <iostream>

// Function to convert video format and save it with a different codec
void convertFormat(const std::string& inputFile, const std::string& outputFile) {
    cv::VideoCapture cap(inputFile);  // Open input video file
    cv::VideoWriter writer(outputFile, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30,
        cv::Size((int)cap.get(cv::CAP_PROP_FRAME_WIDTH), (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT)));  // Create video writer for output file

    cv::Mat frame;
    while (cap.read(frame)) {  // Read each frame from the input video
        writer.write(frame);   // Write the frame to the output video
    }
}

// Function to trim a portion of the video based on start and end times
void trimVideo(const std::string& inputFile, const std::string& outputFile, int startSec, int endSec) {
    cv::VideoCapture cap(inputFile);  // Open input video file
    int fps = cap.get(cv::CAP_PROP_FPS);  // Get the frames per second (FPS) of the input video
    int startFrame = startSec * fps;      // Calculate the starting frame number
    int endFrame = endSec * fps;          // Calculate the ending frame number

    // Create video writer for output file
    cv::VideoWriter writer(outputFile, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps,
        cv::Size((int)cap.get(cv::CAP_PROP_FRAME_WIDTH), (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT)));

    cv::Mat frame;
    int frameCount = 0;  // Frame counter
    while (cap.read(frame)) {  // Read each frame from the input video
        if (frameCount >= startFrame && frameCount <= endFrame) {  // Write frames in the specified range
            writer.write(frame);
        }
        frameCount++;
    }
}

// Function to resize the video to new dimensions
void resizeVideo(const std::string& inputFile, const std::string& outputFile, int newWidth, int newHeight) {
    cv::VideoCapture cap(inputFile);  // Open input video file
    // Create video writer for output file with new dimensions
    cv::VideoWriter writer(outputFile, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, cv::Size(newWidth, newHeight));

    cv::Mat frame;
    while (cap.read(frame)) {  // Read each frame
        cv::resize(frame, frame, cv::Size(newWidth, newHeight));  // Resize the frame
        writer.write(frame);  // Write the resized frame to the output video
    }
}

// Function to rotate the video by a specified angle
void rotateVideo(const std::string& inputFile, const std::string& outputFile, double angle) {
    cv::VideoCapture cap(inputFile);  // Open input video file
    // Create video writer for output file with the same size as the original
    cv::VideoWriter writer(outputFile, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30,
        cv::Size((int)cap.get(cv::CAP_PROP_FRAME_WIDTH), (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT)));

    cv::Mat frame, rotatedFrame;
    while (cap.read(frame)) {  // Read each frame
        // Get the center point of the frame for rotation
        cv::Point2f center(frame.cols / 2.0, frame.rows / 2.0);
        // Create the rotation matrix
        cv::Mat rotMatrix = cv::getRotationMatrix2D(center, angle, 1.0);
        // Apply rotation to the frame
        cv::warpAffine(frame, rotatedFrame, rotMatrix, frame.size());
        // Write the rotated frame to the output video
        writer.write(rotatedFrame);
    }
}

// Function to add text overlay to the video
void addTextOverlay(const std::string& inputFile, const std::string& outputFile, const std::string& text) {
    cv::VideoCapture cap(inputFile);  // Open input video file
    // Create video writer for output file
    cv::VideoWriter writer(outputFile, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30,
        cv::Size((int)cap.get(cv::CAP_PROP_FRAME_WIDTH), (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT)));

    cv::Mat frame;
    while (cap.read(frame)) {  // Read each frame
        // Add the specified text to the frame at position (50, 50)
        cv::putText(frame, text, cv::Point(50, 50), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(255, 255, 255), 2);
        writer.write(frame);  // Write the frame with text overlay to the output video
    }
}

// Function to apply a grayscale filter to the video
void applyGrayscaleFilter(const std::string& inputFile, const std::string& outputFile) {
    cv::VideoCapture cap(inputFile);  // Open input video file
    // Create video writer for output file
    cv::VideoWriter writer(outputFile, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30,
        cv::Size((int)cap.get(cv::CAP_PROP_FRAME_WIDTH), (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT)));

    cv::Mat frame, grayFrame;
    while (cap.read(frame)) {  // Read each frame
        // Convert the frame to grayscale
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
        // Convert grayscale back to 3 channels for writing to the video (as most codecs expect 3 channels)
        cv::cvtColor(grayFrame, frame, cv::COLOR_GRAY2BGR);
        writer.write(frame);  // Write the frame to the output video
    }
}

int main(int argc, char** argv) {
    // Check if the input video file is provided as an argument
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input video>" << std::endl;
        return -1;
    }

    std::string inputFile = argv[1];  // Input video file from the command line argument
    std::string outputFile = "output.avi";  // Default output video file

    // Example processing functions
    convertFormat(inputFile, outputFile);  // Convert video format
    trimVideo(inputFile, "trimmed.avi", 5, 10);  // Trim from 5 to 10 seconds
    resizeVideo(inputFile, "resized.avi", 640, 480);  // Resize video to 640x480
    rotateVideo(inputFile, "rotated.avi", 90);  // Rotate video by 90 degrees
    addTextOverlay(inputFile, "text_overlay.avi", "Sample Text");  // Add text overlay
    applyGrayscaleFilter(inputFile, "grayscale.avi");  // Apply grayscale filter

    return 0;  // Exit the program
}
