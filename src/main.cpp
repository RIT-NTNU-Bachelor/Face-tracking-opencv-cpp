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

void draw_x_distance(Mat& img)
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

    // Calculate the vertical center of the face
    int y = face.y + face.height / 2;

    // Calculate the center of the face 
    int x = face.x + face.width/2;

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


    // Add percentage text
    int width = img.cols; 
    float percentage = (static_cast<float>(x) / width) * 100;

    // Round to 2 decimal places
    percentage = roundf(percentage*100)/100;
    image_text = to_string(percentage) + "%";
    cv::putText(img, //target image
            image_text, //text
            cv::Point(0, img.rows - 20), //top-left position
            cv::FONT_HERSHEY_DUPLEX,
            1,
            CV_RGB(0, 0, 0), //font color
            2);
  }

}

// Function to draw bounding box abound detected frontal face
// Input: image
// Output: void
void detect_depth(Mat& img, bool calibrate)
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
    rectangle(img, face.tl(), face.br(), Scalar(255, 0, 255), 3);

    if (calibrate){
        x_size = face.width;
        y_size = face.height;
        calibrate = false;
    }

    string image_text;

    // If the depth has been calibrated 
    if (x_size != 0 && y_size != 0){
        int box_size = face.width * face.height;
        int org_box_size = x_size * y_size;

        float percentage = (static_cast<float>(org_box_size) / box_size) * 100;
        // Round to 2 decimal places
        percentage = roundf(percentage*100)/100;

        image_text = "Z = " + to_string(percentage) + " m";
    }else {
        // Else set unknown z distance 
        image_text = "Z = ?";
    }

    // Put distance text at the bottom of the box that is around the face
    cv::putText(img, 
        image_text, 
        cv::Point(face.x, face.y + face.width + 25),
        cv::FONT_HERSHEY_DUPLEX,
        0.7,
        CV_RGB(0, 150, 150),
        2);

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
        detect_depth(img, calibrate);
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