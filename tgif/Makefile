CC=gcc
CXX=g++
AR=ar
INCLUDES=$(shell python-config --includes) -I/opt/libjpeg-turbo/include -I/home/root/tridge/cuav/image
LIBJPEG=-L/opt/libjpeg-turbo/lib -ljpeg -lturbojpeg
LIBOPENCV=-lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_flann -lstdc++ -lblob
#CC=arm-linux-gnueabi-gcc
#CXX=arm-linux-gnueabi-g++
#AR=arm-linux-gnueabi-ar

CXXFLAGS=-Wall -O3
LISTOPTS=-adhlns=$(@:.o=.lst)
#CFLAGS=-Wall -std=gnu99 -fPIC -O3 -mfpu=neon -ftree-vectorize -Wa,$(LISTOPTS) $(INCLUDES)
ARCH:=$(shell arch)
ifeq ($(ARCH),armv71)
CFLAGS=-Wall -std=gnu99 -fPIC -O3 -mfpu=neon -ftree-vectorize -Wa,$(LISTOPTS) $(INCLUDES)
else
CFLAGS=-Wall -std=gnu99 -fPIC -O3 -Wa,$(LISTOPTS) $(INCLUDES)
endif

objects = pgm_io.o debayer.o histogram.o image_utils.o BlobExtractor.o

all: scan image.lib blobtest histtest hgram_scanner hgram_scanner8 scanner.so

image.lib: $(objects)
	$(AR) -r image.lib $(objects)

blobtest: image.lib blobtest.o
	$(CXX) -o blobtest blobtest.o image.lib

histtest: image.lib histtest.o
	$(CXX) -o histtest histtest.o image.lib

hgram_scanner: hgram_scanner.o
	$(CC) -o hgram_scanner hgram_scanner.o

hgram_scanner8: hgram_scanner8.o
	$(CC) -o hgram_scanner8 hgram_scanner8.o

scanner.so: scanner.o debayer.o pgm_io.o
	$(CC) -shared -o scanner.so scanner.o debayer.o pgm_io.o $(LIBS) $(shell python-config --libs) $(LIBJPEG)

caponeshot: caponeshot.cpp
	$(CC) -o caponeshot caponeshot.cpp $(LIBOPENCV) $(LIBJPEG)

groundtest: groundtest.cpp
	$(CC) -o groundtest groundtest.cpp $(LIBOPENCV) $(LIBJPEG)

scan: scan.cpp
	echo $(ARCH)
	$(CC) -o scan scan.cpp $(CFLAGS) $(LIBS) $(shell python-config --libs) $(LIBJPEG) $(LIBOPENCV)

camvartest: camvartest.cpp
	$(CC) -o camvartest camvartest.cpp $(LIBOPENCV) $(LIBJPEG)

clean:
	rm -f *.o *.so *~ *.bak hgram_scanner hgram_scanner8 blobtest histtest image.lib

depend:
	makedepend -Y. *.cc *.c 2> /dev/null
# DO NOT DELETE

#BlobExtractor.o: BlobExtractor.h image_utils.h image_inlines.h
#blobtest.o: pgm_io.h BlobExtractor.h image_utils.h
#histtest.o: pgm_io.h debayer.h histogram.h BlobExtractor.h image_utils.h
#debayer.o: debayer.h
#histogram.o: histogram.h
#image_utils.o: image_utils.h
