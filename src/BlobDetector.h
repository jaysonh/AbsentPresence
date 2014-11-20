//
//  BlobDetector.h
//  kinectExample
//
//  Created by jayson on 9/07/14.
//
//

#ifndef __kinectExample__BlobDetector__
#define __kinectExample__BlobDetector__

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "GLOBALS.h"
#include <iostream>

#define THRESHOLD 5
#define INIT_RECORD_FRAMES 120

class BlobDetector
{
public:
    BlobDetector();
    void update(unsigned char * newPixels);
    void drawBackgroundImage(float x, float y, float w, float h);
    void drawBlobImage(float x, float y, float w, float h);
    void drawOpenCVBlobs(float x, float y, float w, float h);
    
    ofxCvContourFinder *getContourFinder();
    
    
    void increaseBlur(int amt);
    bool isInitialising();
    void drawProgress();
    
private:
    
    void addFrame(unsigned char * newPixels);
    void createImageFromPrevPixels();
    void drawWaitingMessage(float x, float y, float w, float h);
    
    void addDifferentPixels(unsigned char * newPixels);
    
    int _currentRecordFrame;
    
    int  _prevPixels[INIT_RECORD_FRAMES][NUM_KINECT_PIXELS];
    int  _numRecordedPixs[NUM_KINECT_PIXELS];
    unsigned char _drawPixels[NUM_KINECT_PIXELS];
    ofImage _drawImg;
    unsigned char drawPixels[NUM_KINECT_PIXELS];
    unsigned char blobPixels[NUM_KINECT_PIXELS];
    
    int _blurAmt;
	ofxCvContourFinder *contourFinder;
    
    bool _initialising;
    
};

#endif /* defined(__kinectExample__BlobDetector__) */
