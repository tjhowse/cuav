#include <stdio.h>
#include "opencv/cv.h"
#include "opencv/cvaux.h"
#include "opencv/highgui.h"
#include "opencv/cxcore.h"
#include <fstream>
#include <iostream>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>


int main(int argc, char* argv[])
{
    CvCapture* camera = cvCreateCameraCapture(-1); // Use the default camera
    cvSetCaptureProperty( camera, CV_CAP_PROP_FRAME_WIDTH, 1280);
    cvSetCaptureProperty( camera, CV_CAP_PROP_FRAME_HEIGHT, 960);

    IplImage* frame = 0;
 
    // capturing some extra frames seems to help stability
    cvGrabFrame(camera);

    // Grab the highest numbered file
    //
    DIR *dp;
    struct dirent *contents;
    int newNumber = 0;
    int biggestNumber = 0;
    char *split;
    char *saveFile;

    if (argc > 1)
    {
        saveFile = new char[strlen(argv[1])*sizeof(char)];
        strcpy(saveFile, argv[1]);
    } else {
        saveFile = new char[13];
        strcpy(saveFile, "default.jpg");
    }

    printf("Trying to grab some frames...\n");

    frame = cvQueryFrame(camera);
    frame = cvQueryFrame(camera);
    frame = cvQueryFrame(camera);
 
    frame = cvQueryFrame(camera);
    
    if (frame != NULL)
    {
        printf("Got frame\n");
        cvSaveImage(saveFile, frame);
    
    } else {
        printf("Null frame\n\r");
        cvReleaseCapture(&camera);
        return 1;
    }
    cvReleaseCapture(&camera);
    return 0;
}
