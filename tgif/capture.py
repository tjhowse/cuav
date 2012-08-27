import cv

#capture = cv.CreateCameraCapture(0)
capture = cv.CaptureFromCAM(-1)

if not capture:
    print "Failed to create camera\n"

cv.SetCaptureProperty(capture, cv.CV_CAP_PROP_FRAME_WIDTH, 1280)
cv.SetCaptureProperty(capture, cv.CV_CAP_PROP_FRAME_HEIGHT, 960)

#cv.GrabFrame(capture)
#cv.GrabFrame(capture)
#cv.GrabFrame(capture)

#while 1:
img = cv.QueryFrame(capture)
#cv.RetrieveFrame(capture)
#img = cv.GrabFrame(capture)

if not img:
    print "Null Image\n"

cv.SaveImage("/home/root/opencv/blob/captures/test.jpg",img)
cv.SaveImage("/www/pages/test.jpg",img)

