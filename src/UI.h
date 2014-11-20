//
//  UI.h
//  kinectExample
//
//  Created by jayson on 5/08/14.
//
//

#ifndef __kinectExample__UI__
#define __kinectExample__UI__

#include <iostream>

#include "ofxGui.h"
#include "ofxKinect.h"
#include "AppParams.h"
#include "BlobRecorder.h"
#include "Keystone.h"

class BlobRecorder;

class UI
{
public:
    
    void draw();
    void init(ofxKinect *kinect, BlobRecorder *recorder, Keystone *keystone);
    
    float getKinectAngle();
    
    float getGhostScaleX();
    float getGhostScaleY();
    
    float getPersonScaleX();
    float getPersonScaleY();
    
    float getPersonPositionScaleX();
    float getPersonPositionScaleY();
    
    float getPersonOffsetX();
    float getPersonOffsetY();
    
    float getGhostOffsetX();
    float getGhostOffsetY();
    
    float getGhostPositionScaleX();
    float getGhostPositionScaleY();
    
    int getGhostBlurAmt();
    int getPersonBlurAmt();
    float getSceneRotation();
    
    int getGhostFadeSpeed();
    bool isShowDebug();
    bool isFlipX();
    bool isFlipY();
    
    bool isDisableGhosts();
	void kinectAngleChanged(int &angle);
    void toggleDebug(bool &status);
    void toggleDisplay();

    AppParams getParameters();
    void saveKeystone();
    void loadKeystone();
    void resetKeystone();
    
    bool isEnabled();
    float getCorner1X();
    float getCorner1Y();
    float getCorner2X();
    float getCorner2Y();
    float getCorner3X();
    float getCorner3Y();
    float getCorner4X();
    float getCorner4Y();
private:
    
    BlobRecorder * _blobRecorder;
    bool _displayed;
    
    ofxKinect *_kinect;
	ofxPanel _gui;
    ofxFloatSlider _rotateAngle;
	ofxFloatSlider _ghostScaleX;
	ofxFloatSlider _ghostScaleY;
    ofxFloatSlider _ghostPositionScaleX;
    ofxFloatSlider _ghostPositionScaleY;
	
    ofxFloatSlider _personPositionScaleX;
    ofxFloatSlider _personPositionScaleY;
    ofxFloatSlider _personScaleX;
	ofxFloatSlider _personScaleY;
    ofxFloatSlider _personOffX;
    ofxFloatSlider _personOffY;
    
    
    ofxFloatSlider _corner1XSlider;
    ofxFloatSlider _corner1YSlider;
    
    ofxFloatSlider _corner2XSlider;
    ofxFloatSlider _corner2YSlider;
    
    ofxFloatSlider _corner3XSlider;
    ofxFloatSlider _corner3YSlider;
    
    ofxFloatSlider _corner4XSlider;
    ofxFloatSlider _corner4YSlider;
    
    ofxFloatSlider _ghostOffX;
    ofxFloatSlider _ghostOffY;
    ofxIntSlider   _kinectAngleSlider;
    ofxIntSlider   _ghostBlurSlider;
    ofxIntSlider   _personBlurSlider;
    
    
    ofxButton _increaseKinectAngleButton;
    ofxButton _decreaseKinectAngleButton;
    
    ofxButton _saveKeystoneButton;
    ofxButton _loadKeystoneButton;
    ofxButton _resetKeystoneButton;
    
    
    ofxToggle _showDebug;
    ofxToggle _flipXToggle, _flipYToggle;
    
    ofxToggle _disableGhosts;
    
    ofxIntSlider _ghostFadeSlider;
    Keystone *_keystone;
    AppParams _parameters;
    
    
    
    void decreaseKinectAngle();
    void increaseKinectAngle();

};
#endif /* defined(__kinectExample__UI__) */
