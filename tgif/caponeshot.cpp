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
    int setLoop = 0;
    fstream fileTest;

    if (argc > 1)
    {
        if (argc == 3)
        {
            setLoop = 1;
        }
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
 
    do
    {
        do
        {
            fileTest.open("imgReady");
            if (fileTest.is_open())
            {
                // Python is still busy
                fileTest.close();
                usleep(10);
            } else {
                break;
            }
        } while (1);

        frame = cvQueryFrame(camera);
        
        if (frame != NULL)
        {
            printf("Got frame\n");
            cvSaveImage(saveFile, frame);
            cvSaveImage("imgReady",NULL);
        
        } else {
            printf("Null frame\n\r");
        }
    } while (setLoop);
    cvReleaseCapture(&camera);
    return 0;
}
