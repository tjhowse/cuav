#!/usr/bin/env python
#from opencv.cv import *
#from opencv.highgui import *
import cv
from subprocess import call
import scanner
import numpy
import os
import time
i = 0

sumFPS = 0;
avgFPS = 0;

#call(["/home/root/tridge/cuav/tgif/caponeshot", "slow.jpg"])

#while 1:
#img = cv.LoadImage("slow.jpg", cv.CV_LOAD_IMAGE_UNCHANGED)
tImageWritten = int(round(time.time()*1000))
imgdir='/home/root/tridge/cuav/tgif/captures'
for subdir,dirs,files in os.walk(imgdir):
    for file in files:
        fileName,fileExtension = os.path.splitext(file)
        if fileExtension != ".jpg":
            continue
        print "New image ready!"
        tNewImage = int(round(time.time()*1000))
        #img = cv.LoadImage("loop.bmp", cv.CV_LOAD_IMAGE_UNCHANGED)
        img = cv.LoadImage("./captures/"+file, cv.CV_LOAD_IMAGE_UNCHANGED)
        #img_small = cv.LoadImage("loop.bmp", cv.CV_LOAD_IMAGE_UNCHANGED)
        if not img:
            print "Null Image"

        img_small = cv.CreateImage((640,480),8,3)
        cv.Resize(img, img_small);
        #img_small = numpy.ascontiguousarray(cv.GetMat(img_small))
        img_small = numpy.ascontiguousarray(cv.GetMat(img_small))


        tImageLoaded = int(round(time.time()*1000))
        regions = scanner.scan(img_small)
        tImageScanned = int(round(time.time()*1000))
        img_small = cv.fromarray(img_small)
        img_ipl = cv.CreateImage((640,480),8,3)
        cv.Copy(img_small,img_ipl)
        if len(regions) == 0:
            print "Nothing found :("
        else:
            print str(len(regions))+" interesting things found."
            i = 0
            for (minx, miny, maxx, maxy) in regions:
                thumbnail = cv.CreateImage((maxx-minx,maxy-miny),8,3)
                cv.SetImageROI(img_ipl,(minx,miny,maxx-minx,maxy-miny))
                cv.Copy(img_ipl,thumbnail)
                #print minx, miny, maxx, maxy
                cv.Rectangle(img_small,(minx,miny), (maxx,maxy),cv.RGB(255,0,0),1,0,0);
                cv.SaveImage("./captures/"+fileName+"-t"+str(i)+".jpg",thumbnail)
                i = i + 1
            
            cv.SaveImage("./captures/"+fileName+"-p.jpg",img_small)
            

        tCalc = int(round(time.time()*1000))
        tTotal = tCalc-tImageWritten
        fps = round(1.0000/(tTotal/1000.00),2)
        sumFPS = sumFPS + fps;
        i = i+1
        avgFPS = round(sumFPS / i,2)
        print ( "Capture: " + str(tNewImage-tImageWritten)+
                " Load: " + str(tImageLoaded-tNewImage)+
                " Process: " + str(tImageScanned-tImageLoaded)+
                " Written: " + str(tCalc-tImageScanned)+
                " Total: " + str(tCalc-tImageWritten)+ " "+
                str(fps)+ " (" + str(avgFPS) + ") FPS")
        tImageWritten = int(round(time.time()*1000))

