#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "BlobDetector.h"
#include "BlobRecorder.h"
#include "ShadowDrawer.h"
#include "ofxSyphon.h"
#include "ofxGui.h"
#include "UI.h"
#include "ofxBlurShader.h"
#include "ScreenMask.h"
#include "Keystone.h"

// uncomment this to read from two kinects simultaneously
//#define USE_TWO_KINECTS

#define MODE_WAITING_TO_START 0
#define MODE_RECORDING_INIT_SCENE 1
#define MODE_RECORDING_GHOSTS 2
#define MODE_PLAYING_BACK_GHOSTS 3

class testApp : public ofBaseApp {
public:
	
	void setup();
	void update();
	void draw();
	void exit();
	
	void drawPointCloud();
	
	void keyPressed(int key);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
    
    
    void displayInitScreen();
    void recordInitScene();
    void displayRecordingGhostsScreen();
    void drawScene();
    
    void displayKinectErrorMsg();
    
	ofxKinect kinect;
	
#ifdef USE_TWO_KINECTS
	ofxKinect kinect2;
#endif
	
	ofxCvColorImage colorImg;
	
	ofxCvGrayscaleImage grayImage; // grayscale depth image
	ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
	ofxCvGrayscaleImage grayThreshFar; // the far thresholded image
	
	ofxCvContourFinder contourFinder;
	
	bool bThreshWithOpenCV;
	bool bDrawPointCloud;
	
	int nearThreshold;
	int farThreshold;
	
	int angle;
	
	// used for viewing the point cloud
	ofEasyCam easyCam;
    BlobDetector blobDetector;
    BlobRecorder _blobRecorder;
    ShadowDrawer shadowDrawer;
    
    bool debugMode;
	ofxSyphonServer syphonOut;
    
    UI _ui;
    
    bool _startedInitalise;
    bool _fullScreen;
    
    ofTrueTypeFont	_font;

    int _mode;
    ofxBlurShader blur;
    
    ofFbo lastScreen;
    
    ScreenMask screenMask;
    
    Keystone keystone;
};
