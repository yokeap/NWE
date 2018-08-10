//
//  pylonTest.cpp
//  Test
//
//  Created by Siwakorn Sukprasertchai on 31/7/2561 BE.
//  Copyright © 2561 Siwakorn Sukprasertchai. All rights reserved.
#include <pylon/PylonIncludes.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
using namespace std;
using namespace cv;

using namespace Pylon;

#include <pylon/gige/BaslerGigEInstantCamera.h>
typedef Pylon::CBaslerGigEInstantCamera Camera_t;
using namespace Basler_GigECameraParams;
using namespace Basler_GigEStreamParams;

// Number of images to be grabbed.
static const uint32_t c_countOfImagesToGrab = 10000;

int main( int argc, const char** argv )
{
    // The exit code of the sample application.
    int exitCode = 0;
    
    // Before using any pylon methods, the pylon runtime must be initialized.
    PylonInitialize();
    
    try {
        // Create an instant camera object with the camera device found first.
        cout << "Creating Camera..." << endl;
        CInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice());
        
        cout << "Camera Created." << endl;
        
        // Print the model name of the camera.
        cout << "Using device " << camera.GetDeviceInfo().GetModelName() << endl;
        
        // The parameter MaxNumBuffer can be used to control the count of buffers
        // allocated for grabbing. The default value of this parameter is 10.
        camera.MaxNumBuffer = 10;
        
        // create pylon image format converter and pylon image
        CImageFormatConverter formatConverter;
        formatConverter.OutputPixelFormat= PixelType_Mono8;
        CPylonImage pylonImage;
        
        // Create an OpenCV image
        Mat openCvImage, resizeImage;
        Size size(1280, 720);
        
        // Start the grabbing of c_countOfImagesToGrab images.
        // The camera device is parameterized with a default configuration which
        // sets up free-running continuous acquisition.
        camera.StartGrabbing( c_countOfImagesToGrab);
        
        // This smart pointer will receive the grab result data.
        CGrabResultPtr ptrGrabResult;
        
        // Camera.StopGrabbing() is called automatically by the RetrieveResult() method
        // when c_countOfImagesToGrab images have been retrieved.
        while ( camera.IsGrabbing())
        {
            // Wait for an image and then retrieve it. A timeout of 5000 ms is used.
            camera.RetrieveResult( 5000, ptrGrabResult, TimeoutHandling_ThrowException);
            
            // Image grabbed successfully?
            if (ptrGrabResult->GrabSucceeded())
            {
                // Access the image data.
                cout << "SizeX: " << ptrGrabResult->GetWidth() << endl;
                cout << "SizeY: " << ptrGrabResult->GetHeight() << endl;
                const uint8_t *pImageBuffer = (uint8_t *) ptrGrabResult->GetBuffer();
                cout << "Gray value of first pixel: " << (uint32_t) pImageBuffer[0] << endl << endl;
                
                // Convert the grabbed buffer to pylon imag
                formatConverter.Convert(pylonImage, ptrGrabResult);
                // Create an OpenCV image out of pylon image
                openCvImage= cv::Mat(ptrGrabResult->GetHeight(), ptrGrabResult->GetWidth(), CV_8U, pylonImage.GetBuffer(),cv::Mat::AUTO_STEP);
                
                // Create a display window
                namedWindow( "OpenCV Display Window", CV_WINDOW_AUTOSIZE);//AUTOSIZE //FREERATIO
                cv::resize(openCvImage, resizeImage, size);
                // Display the current image with opencv
                imshow( "OpenCV Display Window", resizeImage);
                // Define a timeout for customer's input in ms.
                // '0' means indefinite, i.e. the next image will be displayed after closing the window
                // '1' means live stream
                waitKey(1);
                
            }
            else
            {
                cout << "Error: " << ptrGrabResult->GetErrorCode() << " " << ptrGrabResult->GetErrorDescription() << endl;
            }
        }
        
    } catch (const GenericException &e) {
        // Error handling.
        cerr << "An exception occurred." << endl
        << e.GetDescription() << endl;
        exitCode = 1;
    }
    
    // Releases all pylon resources.
    PylonTerminate();
    
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}

