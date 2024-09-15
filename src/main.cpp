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

int main() {
    std::string inputFile = "C:/Users/danie/Downloads/ואת אינך.mp4";  // שם הסרטון המקורי
    std::string outputFile;
    std::string text;
    int choice;
    

    // הצגת אפשרויות לבחירה
    std::cout << "Choose a function to apply to the video:\n";
    std::cout << "1 - Convert Format\n";
    std::cout << "2 - Trim Video\n";
    std::cout << "3 - Resize Video\n";
    std::cout << "4 - Rotate Video\n";
    std::cout << "5 - Add Text Overlay\n";
    std::cout << "6 - Apply Grayscale Filter\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    switch (choice) {
    case 1:
        // 1. המרת פורמט הווידאו
        outputFile = "format_conversion.avi";
        convertFormat(inputFile, outputFile);
        std::cout << "Format conversion done: " << outputFile << std::endl;
        break;

    case 2:
        // 2. חיתוך הווידאו בין שנייה 5 ל-10
        outputFile = "trimmed.avi";
        int startSec, endSec;
        std::cout << "Enter start second: ";
        std::cin >> startSec;
        std::cout << "Enter end second: ";
        std::cin >> endSec;
        trimVideo(inputFile, outputFile, startSec, endSec);
        std::cout << "Video trimming done: " << outputFile << std::endl;
        break;

    case 3:
        // 3. שינוי גודל הווידאו ל-640x480
        outputFile = "resized.avi";
        int newWidth, newHeight;
        std::cout << "Enter new width: ";
        std::cin >> newWidth;
        std::cout << "Enter new height: ";
        std::cin >> newHeight;
        resizeVideo(inputFile, outputFile, newWidth, newHeight);
        std::cout << "Video resizing done: " << outputFile << std::endl;
        break;

    case 4:
        // 4. סיבוב הווידאו ב-90 מעלות
        outputFile = "rotated.avi";
        double angle;
        std::cout << "Enter rotation angle (in degrees): ";
        std::cin >> angle;
        rotateVideo(inputFile, outputFile, angle);
        std::cout << "Video rotation done: " << outputFile << std::endl;
        break;

    case 5:
        // 5. הוספת טקסט על הווידאו
        outputFile = "text_overlay.avi";
        std::cout << "Enter text to overlay: ";
        std::cin.ignore();  // לנקות את ה-buffer של הקלט
        std::getline(std::cin, text);
        addTextOverlay(inputFile, outputFile, text);
        std::cout << "Text overlay added: " << outputFile << std::endl;
        break;

    case 6:
        // 6. יישום מסנן גווני אפור
        outputFile = "grayscale.avi";
        applyGrayscaleFilter(inputFile, outputFile);
        std::cout << "Grayscale filter applied: " << outputFile << std::endl;
        break;

    default:
        std::cout << "Invalid choice!" << std::endl;
        break;
    }

    return 0;
}
