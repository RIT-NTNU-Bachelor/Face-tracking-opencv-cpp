#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>  // for cascade classifier 
#include <iostream>
#include <vector>
#include <string>

#include "draw_x.cpp"
#include "draw_percentage.cpp"
#include "depth.cpp"


using namespace cv;
using namespace std;


// Function to draw bounding box abound detected frontal face
// Input: image
// Output: void

void detect_faces(Mat& img)
{

  CascadeClassifier face_cascade;

  face_cascade.load("models/haarcascade_frontalface_default.xml");
  

  if(face_cascade.empty())
    cout << "Classifier has not been loaded!\n";

  // creating rect for printing bounding box around detected faces
  vector<Rect> faces;
  
  // Detects objects of different sizes in the input image.   
  // The detected objects are returned as a list of rectangles.
  face_cascade.detectMultiScale(img, faces, 1.1,10); 
 
  // drawing bounding box around detected faces
  for(auto& face : faces)
     rectangle(img, face.tl(), face.br(), Scalar(255, 0, 255), 3);
}

void draw_coord(Mat& img, bool calibrate)
{

  CascadeClassifier face_cascade;

  face_cascade.load("models/haarcascade_frontalface_default.xml");
  

  if(face_cascade.empty())
    cout << "Classifier has not been loaded!\n";

  // creating rect for printing bounding box around detected faces
  vector<Rect> faces;
  
  // Detects objects of different sizes in the input image.   
  // The detected objects are returned as a list of rectangles.
  face_cascade.detectMultiScale(img, faces, 1.1,10); 
 
  // drawing bounding box around detected faces
  for(auto& face : faces){
    // Drawing a line from the left border to the right border for each detected face

    int x = draw_x(img, face);

    float percentage = draw_percentage(img, x);

    int depth = calulate_depth(img, calibrate, face);
  }

}

void detect_eyes(Mat& img){
    CascadeClassifier eye_cascade;
    eye_cascade.load("models/haarcascade_eye.xml");
  

    if(eye_cascade.empty())
        cout << "Classifier has not been loaded!\n";

    // creating rect for printing bounding box around detected eyes
    vector<Rect> eyes;
    
    // Detects objects of different sizes in the input image.   
    // The detected objects are returned as a list of rectangles.
    eye_cascade.detectMultiScale(img, eyes, 1.1, 5, 3); 
    
    // drawing bounding box around detected faces
    for(auto& eyes : eyes)
        rectangle(img, eyes.tl(), eyes.br(), Scalar(255, 0, 0), 3);
}


void add_text_data(Mat& img){
    const string image_text = to_string(img.cols) + "x" + to_string(img.rows);

    cv::putText(img, //target image
            image_text, //text
            cv::Point(img.cols*0.80, img.rows*0.95), //top-left position
            cv::FONT_HERSHEY_DUPLEX,
            1.0,
            CV_RGB(255, 0, 0), //font color
            2);
}





int main(){
    VideoCapture v_cap(0);    // 0: default webcam
    Mat img;
    
    bool calibrate = false;
    while (true){                 //once v_cap frame read is over
    
        v_cap.read(img);            

        // Detect faces and eyes
        draw_coord(img, calibrate);
        add_text_data(img);


        imshow("Detected Faces", img);  // display img

        int key = cv::waitKey(30);
        if (key == 32) { // ASCII value for spacebar is 32
            calibrate = true;
        } else {
            calibrate = false;
        }


        waitKey(10);                    // delay of 10 ms 
    }
    return 0;
}