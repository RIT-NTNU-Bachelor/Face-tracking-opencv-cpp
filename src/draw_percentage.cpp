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


float draw_percentage(Mat& img, int x){
    // Add percentage text
    int width = img.cols; 
    float percentage = (static_cast<float>(x) / width) * 100;

    // Round to 2 decimal places
    percentage = roundf(percentage*100)/100;
    string image_text = to_string(percentage) + "%";


    cv::putText(img, //target image
            image_text, //text
            cv::Point(0, img.rows - 20), //top-left position
            cv::FONT_HERSHEY_DUPLEX,
            1,
            CV_RGB(0, 0, 0), //font color
            2);

    return percentage;
}