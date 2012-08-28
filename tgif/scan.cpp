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

extern "C"
{
    #include </home/root/tridge/cuav/tgif/scanner.h>
}

#define ALLOCATE(p) (p) = malloc(sizeof(*p))


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
    char saveFile[256];

    //const struct rgb_image8 *in = DATA FROM OPENCV
    
    struct rgb_image8 *himage, *jimage;
    struct regions *regions;

    malloc(sizeof(*himage));
    malloc(sizeof(*jimage));
    malloc(sizeof(*regions));

    assign_regions(himage,regions);

    /*ALLOCATE(regions);
    ALLOCATE(himage);
    ALLOCATE(jimage);*/


    dp = opendir("/home/root/tridge/cuav/tgif/captures");

    if (dp != NULL)
    {
        while ((contents=readdir(dp))!=NULL)
        {
            if (strlen(contents->d_name) == 12)
            {
                newNumber = atoi(&(contents->d_name[3]));
                if (newNumber > biggestNumber)
                {
                    biggestNumber = newNumber;
                }
            }
        }
        closedir(dp);
    } else {
        printf("Can't find the folder captain.\n");
    }

    printf("Trying to grab some frames...\n");

    frame = cvQueryFrame(camera);
    frame = cvQueryFrame(camera);
    frame = cvQueryFrame(camera);
 
    do {
        frame = cvQueryFrame(camera);
        biggestNumber += 1;
        if (biggestNumber >= 99999)
        {
            biggestNumber = 1;
        }
        
        if (frame != NULL)
        {
            printf("Frame\n");
            sprintf(saveFile, "/home/root/opencv/blob/captures/raw%05d.jpg", biggestNumber);
            cvSaveImage(saveFile, frame);
        
        } else {
            //printf("Null frame\n\r");
        }
  } while (true);
  cvReleaseCapture(&camera);
  return 0;
}
