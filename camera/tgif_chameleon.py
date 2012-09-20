#!/usr/bin/env
'''
emulate a chameleon camera, getting images from a playback tool

The API is the same as the chameleon module, but takes images from fake_chameleon.pgm
'''

import time, os, sys, cv, numpy

sys.path.insert(0, os.path.join(os.path.dirname(os.path.realpath(__file__)), '..', 'lib'))
sys.path.insert(0, os.path.join(os.path.dirname(os.path.realpath(__file__)), '..', 'image'))
import cuav_util, scanner

continuous_mode = False
fake = 'fake_chameleon.pgm'
frame_counter = 0
trigger_time = 0
frame_rate = 7.5
chameleon_gamma = 950
last_frame_time = 0

imgPath = "/tmp/"

def open(colour, depth, brightness):
    return 0

def trigger(h, continuous):
    global continuous_mode, trigger_time
    continuous_mode = continuous
    trigger_time = time.time()


def load_image(filename):
    os.rename(filename, imgPath+"processme.jpg")
    os.remove(imgPath+"imgReady")
    img = cv.LoadImage(imgPath+"processme.jpg", cv.CV_LOAD_IMAGE_UNCHANGED)
    #img = cv.LoadImage(imgPath+"loop.jpg", cv.CV_LOAD_IMAGE_UNCHANGED)

    img = numpy.ascontiguousarray(cv.GetMat(img))

    return img

def capture(h, timeout, img):
    global continuous_mode, trigger_time, frame_rate, frame_counter, fake, last_frame_time
    
    while timeout > 0 and not os.path.exists(imgPath+"imgReady"):
        timeout -= 10
    
    if timeout <= 0:
        print "Gave up waiting for a frame\n"
        return trigger_time, frame_counter, 0

    frame_counter += 1

    trigger_time = time.time()
    try:
        img = load_image(imgPath+"loop.jpg")
    except Exception, msg:
        print "Failed to grab image"
    return trigger_time, frame_counter, 0

    tnow = time.time()
    due = trigger_time + (1.0/frame_rate)
    if tnow < due:
        time.sleep(due - tnow)
        timeout -= int(due*1000)
    # wait for a new image to appear
    filename = os.path.realpath(fake)
    frame_time = cuav_util.parse_frame_time(filename)
    while frame_time == last_frame_time and timeout > 0:
        timeout -= 10
        time.sleep(0.01)
        filename = os.path.realpath(fake)
        frame_time = cuav_util.parse_frame_time(filename)

    if last_frame_time == frame_time:
        raise chameleon.error("timeout waiting for fake image")
    last_frame_time = frame_time
    try:
        fake_img = load_image(filename)
    except Exception, msg:
        raise chameleon.error('missing %s' % fake)
    frame_counter += 1
    img.data = fake_img.data
    if continuous_mode:
        trigger_time = time.time()
    return trigger_time, frame_counter, 0

def close(h):
    return

def set_gamma(h, gamma):
    global chameleon_gamma
    chameleon_gamma = gamma

def save_pgm(filename, img):
    return 0
    #return chameleon.save_pgm(filename, img)

def save_file(filename, bytes):
    return cv.SaveImage(filename,bytes)
    #return 0
    #return chameleon.save_file(filename, bytes)
