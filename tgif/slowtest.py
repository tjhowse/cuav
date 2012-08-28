#!/usr/bin/env python
#from opencv.cv import *
#from opencv.highgui import *
import cv
from subprocess import call
import scanner
import numpy

i = 0

call(["/home/root/tridge/cuav/tgif/caponeshot", "slow.jpg"])

#while 1:
img = cv.LoadImage("slow.jpg", cv.CV_LOAD_IMAGE_UNCHANGED)
img_small = cv.CreateImage((640,480),8,3)

cv.Resize(img, img_small);
img_small = numpy.ascontiguousarray(cv.GetMat(img_small))

#cv.RetrieveFrame(capture)
#img = cv.GrabFrame(capture)

if not img:
    print "Null Image"

regions = scanner.scan(img_small)
img_small = cv.fromarray(img_small)

for (minx, miny, maxx, maxy) in regions:
    print minx, miny, maxx, maxy
    '''cv.SetImageROI(img,cv.Rect(minx,miny,max,maxy))
    
    cv.Copy(img,img_output);
    cv.SaveImage("square"+i+".jpg",img_output)'''
    #img_output = cv.GetSubRect(img_small,(minx,miny,maxx,maxy))
    #cv.SaveImage("square"+str(i)+".jpg",img_output)
    #i = i + 1
    cv.Rectangle(img_small,(minx,miny), (maxx,maxy),cv.RGB(255,0,0),1,0,0);
    

print regions

cv.SaveImage("/home/root/opencv/blob/captures/test.jpg",img_small)
cv.SaveImage("/www/pages/test.jpg",img_small)

