#include <opencv2/highgui.hpp>

int main(){
    cv::Mat image;

    image = cv::imread("./image/students.jpeg");

    cv::imshow("TEST", image);
    cv::waitKey(0);

    return 0; 
}