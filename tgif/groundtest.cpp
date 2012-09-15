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

    CvSize size;
    size.width = 800;
    size.height = 600;
    IplImage* frame = cvCreateImage(size,IPL_DEPTH_8U,3);
    IplImage* outputFrame = cvCreateImage(size,IPL_DEPTH_8U,3);
 
    // capturing some extra frames seems to help stability

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
    struct stat junk;
    
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

    frame = cvLoadImage("sample.jpg");
    do
    {
        //while ((fileTest = fopen("imgReady","r")) != NULL)
        while (!stat("/tmp/imgReady",&junk))
        {
            //fclose(fileTest);
            usleep(1000);
            //cvResize(frame,outputFrame);
            //cvGrabFrame(camera);
        }

        //printf("Python done!\n");

        //frame = cvQueryFrame(camera);
        
        if (frame != NULL)
        {
            //cvResize(frame,outputFrame);
            cvSaveImage(saveFile, frame);
            //sync();
            fileTest = fopen("/tmp/imgReady","w+");
            fclose(fileTest);
            printf("Got frame\n");
        
        } else {
            printf("Null frame\n\r");
        }
        printf("Waiting on python.\n");
    } while (setLoop);
    return 0;
}
