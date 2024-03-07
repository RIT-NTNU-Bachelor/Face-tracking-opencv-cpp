#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>  // for cascade classifier 
#include <iostream>
#include <vector>
#include <string>


using namespace cv;
using namespace std;

// Constants that may change over time as the app

int x_size = 0;
int y_size = 0;


int calulate_depth(Mat& img, bool calibrate, cv::Rect &face, bool hide){

    if (calibrate){
        x_size = face.width;
        y_size = face.height;
        calibrate = false;
        return 1;
    }

    string image_text;
    float percentage;

    // If the depth has been calibrated 
    if (x_size != 0 && y_size != 0){
        int box_size = face.width * face.height;
        int org_box_size = x_size * y_size;

        percentage = (static_cast<float>(org_box_size) / box_size) * 100;
        // Round to 2 decimal places
        percentage = roundf(percentage*100)/100;

        if (!hide){
            image_text = "Z = " + to_string(percentage) + " m";

            // Put distance text at the bottom of the box that is around the face
            cv::putText(img, 
                image_text, 
                cv::Point(face.x, face.y + face.width + 25),
                cv::FONT_HERSHEY_DUPLEX,
                0.7,
                CV_RGB(0, 150, 150),
                2);
        }

        return percentage;
    }else {

        if(!hide){
            // Else set unknown z distance 
            image_text = "Z = ?";

            // Put distance text at the bottom of the box that is around the face
            cv::putText(img, 
                image_text, 
                cv::Point(face.x, face.y + face.width + 25),
                cv::FONT_HERSHEY_DUPLEX,
                0.7,
                CV_RGB(0, 150, 150),
                2);

        }
        
        

        return 0;
    }

}