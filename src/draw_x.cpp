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


int draw_x(Mat& img, cv::Rect &face, bool hide){

    // Calculate the vertical center of the face
    int y = face.y + face.height / 2;

    // Calculate the center of the face 
    int x = face.x + face.width/2;


    // Draw only if asked 
    if (!hide){
        // Draw a line from the left border (x=0) to the right border (x=img.cols)
        line(img, Point(0, y), Point(x, y), Scalar(0, 0, 255), 3);

        // Add the infomation of the length of x
        string image_text = "X-distance: " + to_string(x) + " unit";

        cv::putText(img, //target image
                image_text, //text
                cv::Point(0, y-20), //top-left position
                cv::FONT_HERSHEY_DUPLEX,
                1,
                CV_RGB(0, 0, 0), //font color
                2);

    }
    

    return x;
}