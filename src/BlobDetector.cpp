//
//  BlobDetector.cpp
//  kinectExample
//
//  Created by jayson on 9/07/14.
//
//

#include "BlobDetector.h"


BlobDetector::BlobDetector()
{
    _initialising = true;
    _blurAmt = 15;
    contourFinder = new ofxCvContourFinder();
    
    _currentRecordFrame = 0;
    
    for(int i = 0; i < NUM_KINECT_PIXELS;i++)
        _numRecordedPixs[i] = 0 ;
    
}

void BlobDetector::addFrame(unsigned char * newPixels)
{
    for(int i = 0; i < NUM_KINECT_PIXELS;i++)
    {
        int val = (int)newPixels[i];
        
        _prevPixels[_currentRecordFrame][i] = val;
        
        if(val > 0)
            _numRecordedPixs[i]++;
        
    }
    _currentRecordFrame++;
    
    if(_currentRecordFrame >= INIT_RECORD_FRAMES)
        createImageFromPrevPixels();
}

void BlobDetector::update(unsigned char * newPixels)
{
    
    if(_currentRecordFrame < INIT_RECORD_FRAMES)
    {
        addFrame(newPixels);
    }else{
        
        _initialising = false;
        // Add different pixels
        addDifferentPixels(newPixels);
        
        ofxCvGrayscaleImage grayScaleCVImg;
        grayScaleCVImg.allocate(KINECT_WIDTH,KINECT_HEIGHT);
        grayScaleCVImg.setFromPixels(blobPixels, KINECT_WIDTH, KINECT_HEIGHT);
        grayScaleCVImg.blur(_blurAmt);
        grayScaleCVImg.threshold(90);
        contourFinder->findContours(grayScaleCVImg, 600, (KINECT_WIDTH * KINECT_HEIGHT)/2, 10, false);	// find holes
        
        
    }
}

void BlobDetector::addDifferentPixels(unsigned char * newPixels)
{
    for(int i = 0; i < NUM_KINECT_PIXELS;i++)
    {
        int diff = abs(_drawPixels[i] - newPixels[i]);
        
        blobPixels[i]=0;
        
        /*if(diff < THRESHOLD && newPixels[i]  > 0 )
        {
            // Move pixels back one
            for(int j = 0; j < INIT_RECORD_FRAMES-1; j++)
            {
                _prevPixels[j][i] = _prevPixels[j+1][i];
            }
            
            _prevPixels[INIT_RECORD_FRAMES-1][i] = newPixels[i];
            
        }else */
        
        if(diff >= THRESHOLD && newPixels[i] > 0)
        {
            blobPixels[i] = newPixels[i];
        }
    }
}

void BlobDetector::createImageFromPrevPixels()
{
    for(int i = 0; i < NUM_KINECT_PIXELS;i++)
    {
        int total = 0;
        int numAboveZero=0;
        for(int j = 0; j < INIT_RECORD_FRAMES;j++)
        {
            total += _prevPixels[j][i];
            if(_prevPixels[j][i]>0)
                numAboveZero++;
        }
        
        if(total > 0 && numAboveZero > 0)
            total /= numAboveZero;
        
        _drawPixels[i] = total;
    }
    
    //_drawImg.setFromPixels(drawPixels, KINECT_WIDTH, KINECT_HEIGHT,OF_IMAGE_GRAYSCALE );
}

void BlobDetector::drawBackgroundImage(float x, float y, float w, float h)
{
    if(_currentRecordFrame >= INIT_RECORD_FRAMES)
    {
        glPushMatrix();
        glTranslatef(x,y,0);
        glScalef(w/640.0f, h/480.0f,1.0f);
        glBegin(GL_POINTS);
        
        for(int x = 0; x < 640; x++)
        {
            for(int y = 0; y < 480;y++)
            {
                int indx = x + y * 640;
                glColor3f((float)_drawPixels[indx] / 255.0f,(float)_drawPixels[indx] / 255.0f,(float)_drawPixels[indx] / 255.0f);
                glVertex2i(x,y);
            }
        }
        glEnd();
        glPopMatrix();
    }else
        drawWaitingMessage(x,y,w,h);
    
}

void BlobDetector::drawBlobImage(float x, float y, float w, float h)
{
    if(_currentRecordFrame >= INIT_RECORD_FRAMES)
    {
        glPushMatrix();
        glTranslatef(x,y,0);
        glScalef(w/640.0f, h/480.0f,1.0f);
        glBegin(GL_POINTS);
        
        for(int x = 0; x < 640; x++)
        {
            for(int y = 0; y < 480;y++)
            {
                int indx = x + y * 640;
                glColor3f((float)blobPixels[indx] / 255.0f,(float)blobPixels[indx] / 255.0f,(float)blobPixels[indx] / 255.0f);
                glVertex2i(x,y);
            }
        }
        glEnd();
        glPopMatrix();
    }else
        drawWaitingMessage(x,y,w,h);
    
}

void BlobDetector::drawOpenCVBlobs(float x, float y, float w, float h)
{
    contourFinder->draw(x,y,w,h);
}

void BlobDetector::drawWaitingMessage(float x, float y, float w, float h)
{
    ofSetColor(0,255,0);
    ofRect(x,y,w,h);
}


ofxCvContourFinder *BlobDetector::getContourFinder()
{
    return contourFinder;
}

void BlobDetector::increaseBlur(int amt)
{
    
    _blurAmt += amt;
    
    if(_blurAmt < 0)
        _blurAmt=0;
    
    printf("Blur is: %i\n",_blurAmt);
}


bool BlobDetector::isInitialising()
{
    return _initialising;
}


void BlobDetector::drawProgress()
{
    
    float percent = (float)_currentRecordFrame / (float)INIT_RECORD_FRAMES;
    
    float width = 500.0;
    
    ofSetColor(125,125,125);
    ofRect(ofGetWidth()/2 - width/2,ofGetHeight() /2, width,30);
    
    ofSetColor(0,0,0);
    ofRect(ofGetWidth()/2 - width/2,ofGetHeight() /2, width*percent,30);
}