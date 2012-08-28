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
    //cvSetCaptureProperty( camera, CV_CAP_PROP_FRAME_WIDTH, 640);
    //cvSetCaptureProperty( camera, CV_CAP_PROP_FRAME_HEIGHT, 480);

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
    FILE* fileTest;

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
        while ((fileTest = fopen("imgReady","r")) != NULL)
        {
            fclose(fileTest);
            usleep(100000);
            frame = cvQueryFrame(camera);
        }

        printf("Python done!\n");

        frame = cvQueryFrame(camera);
        
        if (frame != NULL)
        {
            printf("Got frame\n");
            cvSaveImage(saveFile, frame);
            fileTest = fopen("imgReady","w+");
            fclose(fileTest);
        
        } else {
            printf("Null frame\n\r");
        }
        printf("Waiting on python.\n");
    } while (setLoop);
    cvReleaseCapture(&camera);
    return 0;
}
