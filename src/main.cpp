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





int main(){
    VideoCapture v_cap(0);    // 0: default webcam
    Mat img;
        
    while (true){                 //once v_cap frame read is over
    
        v_cap.read(img);            

        // Detect faces and eyes
        detect_faces(img);
        //detect_eyes(img); 


        imshow("Detected Faces", img);  // display img
        waitKey(10);                    // delay of 10 ms 
    }
    return 0;
}