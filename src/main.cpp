 #include <opencv2/opencv.hpp>
#include <gst/gst.h>
#include <iostream>
using namespace cv;

void convertFormat(const std::string& inputFile, const std::string& outputFile) {
    cv::VideoCapture cap(inputFile);
    cv::VideoWriter writer(outputFile, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, cv::Size((int)cap.get(cv::CAP_PROP_FRAME_WIDTH), (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT)));
    cv::Mat frame;
    while (cap.read(frame)) {
        writer.write(frame);
    }
}

void trimVideo(const std::string& inputFile, const std::string& outputFile, int startSec, int endSec) {
    cv::VideoCapture cap(inputFile);
    int fps = cap.get(cv::CAP_PROP_FPS);
    int startFrame = startSec * fps;
    int endFrame = endSec * fps;
    cv::VideoWriter writer(outputFile, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, cv::Size((int)cap.get(cv::CAP_PROP_FRAME_WIDTH), (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT)));

    cv::Mat frame;
    int frameCount = 0;
    while (cap.read(frame)) {
        if (frameCount >= startFrame && frameCount <= endFrame) {
            writer.write(frame);
        }
        frameCount++;
    }
}

void resizeVideo(const std::string& inputFile, const std::string& outputFile, int newWidth, int newHeight) {
    cv::VideoCapture cap(inputFile);
    cv::VideoWriter writer(outputFile, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, cv::Size(newWidth, newHeight));

    cv::Mat frame;
    while (cap.read(frame)) {
        cv::resize(frame, frame, cv::Size(newWidth, newHeight));
        writer.write(frame);
    }
}

void rotateVideo(const std::string& inputFile, const std::string& outputFile, double angle) {
    cv::VideoCapture cap(inputFile);
    cv::VideoWriter writer(outputFile, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, cv::Size((int)cap.get(cv::CAP_PROP_FRAME_WIDTH), (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT)));

    cv::Mat frame, rotatedFrame;
    while (cap.read(frame)) {
        cv::Point2f center(frame.cols / 2.0, frame.rows / 2.0);
        cv::Mat rotMatrix = cv::getRotationMatrix2D(center, angle, 1.0);
        cv::warpAffine(frame, rotatedFrame, rotMatrix, frame.size());
        writer.write(rotatedFrame);
    }
}

void addTextOverlay(const std::string& inputFile, const std::string& outputFile, const std::string& text) {
    cv::VideoCapture cap(inputFile);
    cv::VideoWriter writer(outputFile, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, cv::Size((int)cap.get(cv::CAP_PROP_FRAME_WIDTH), (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT)));

    cv::Mat frame;
    while (cap.read(frame)) {
        cv::putText(frame, text, cv::Point(50, 50), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(255, 255, 255), 2);
        writer.write(frame);
    }
}

void applyGrayscaleFilter(const std::string& inputFile, const std::string& outputFile) {
    cv::VideoCapture cap(inputFile);
    cv::VideoWriter writer(outputFile, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, cv::Size((int)cap.get(cv::CAP_PROP_FRAME_WIDTH), (int)cap.get(cv::CAP_PROP_FRAME_HEIGHT)));

    cv::Mat frame, grayFrame;
    while (cap.read(frame)) {
        cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
        cv::cvtColor(grayFrame, frame, cv::COLOR_GRAY2BGR);  // Convert back to 3 channels
        writer.write(frame);
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input video>" << std::endl;
        return -1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = "output.avi";

    // Example processing functions
    convertFormat(inputFile, outputFile);
    trimVideo(inputFile, "trimmed.avi", 5, 10);  // Trim from 5 to 10 seconds
    resizeVideo(inputFile, "resized.avi", 640, 480);
    rotateVideo(inputFile, "rotated.avi", 90);
    addTextOverlay(inputFile, "text_overlay.avi", "Sample Text");
    applyGrayscaleFilter(inputFile, "grayscale.avi");
    
    return 0;
}
