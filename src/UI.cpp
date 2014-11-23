//
//  UI.cpp
//  kinectExample
//
//  Created by jayson on 5/08/14.
//
//

#include "UI.h"


void UI::init(ofxKinect *kinect, BlobRecorder *recorder, Keystone *keystone)
{
    _blobRecorder = recorder;
    _displayed = false;
    _keystone = keystone;
    _kinect = kinect;
    _gui.setup();
    
    _kinectAngleSlider.addListener(this,&UI::kinectAngleChanged);
    _gui.add(_kinectAngleSlider.setup("Kinect Angle",0.0,-30.0,30.0));
    
    _gui.add(_flipXToggle.setup("Flip X", false));
    _gui.add(_flipYToggle.setup("Flip Y", false));
    
    
    _gui.add(_showDebug.setup("Show Debug", false));
    
    _gui.add(_personScaleX.setup( "Person Scale X", 1.0, 0.0, 5.0 ));
    _gui.add(_personScaleY.setup( "Person Scale Y", 1.0, 0.0, 5.0 ));
    
    _gui.add(_personOffX.setup("Person Offset X", 0.0, -800.0, 800.0));
    _gui.add(_personOffY.setup("Person Offset Y", 0.0, -800.0, 800.0));
    
    _gui.add(_personPositionScaleX.setup("Person Pos Scale X", 1.0, 0.0, 4.0));
    _gui.add(_personPositionScaleY.setup("Person Pos Scale Y", 1.0, 0.0, 4.0));
    
    _gui.add(_ghostScaleX.setup("Ghost Scale X", 1.0, 0.0, 5.0 ));
    _gui.add(_ghostScaleY.setup("Ghost Scale Y", 1.0, 0.0, 5.0 ));
    
    _gui.add(_ghostOffX.setup("Ghost Offset X", 0.0, -800.0, 800.0));
    _gui.add(_ghostOffY.setup("Ghost Offset Y", 0.0, -800.0, 800.0));
    
    _gui.add(_ghostPositionScaleX.setup("Ghost Pos Scale X", 1.0, 0.0, 4.0));
    _gui.add(_ghostPositionScaleY.setup("Ghost Pos Scale Y", 1.0, 0.0, 4.0));
    
    _gui.add(_ghostBlurSlider.setup("Ghost Blur",4,0,20));
	
    _showDebug.addListener(this,&UI::toggleDebug);
    
    //_gui.add(_rotateAngle.setup("Scene Rotation",0,-180,180));
	
    _gui.add(_disableGhosts.setup("Disable Ghosts", false));
    
    _gui.add(_ghostFadeSlider.setup("Ghost Fade Speed", 25, 0,255));
    //_gui.add(_saveKeystoneButton.setup("Save Keystone"));
	//_saveKeystoneButton.addListener(this,&UI::saveKeystone);
    //_gui.add(_loadKeystoneButton.setup("Load Keystone"));
	//_loadKeystoneButton.addListener(this,&UI::loadKeystone);
    _gui.add(_resetKeystoneButton.setup("Reset Keystone"));
	_resetKeystoneButton.addListener(this,&UI::resetKeystone);
    
    
    
    //_gui.add(_increaseKinectAngleButton.setup("+ Kinect Angle"));
	//_increaseKinectAngleButton.addListener(this,&UI::increaseKinectAngle);
    //_gui.add(_decreaseKinectAngleButton.setup("- Kinect Angle"));
	//_decreaseKinectAngleButton.addListener(this,&UI::decreaseKinectAngle);
    _gui.loadFromFile("settings.xml");
    
	kinect->setCameraTiltAngle(_kinectAngleSlider);
}

void UI::increaseKinectAngle()
{
    float currentAngle =_kinect->getCurrentCameraTiltAngle();
    _kinect->setCameraTiltAngle(currentAngle+1.0);
    
}
void UI::decreaseKinectAngle()
{
    float currentAngle =_kinect->getCurrentCameraTiltAngle();
    _kinect->setCameraTiltAngle(currentAngle-1.0);
}


float UI::getGhostPositionScaleX()
{
    return _ghostPositionScaleX;
}

float UI::getGhostPositionScaleY()
{
    return _ghostPositionScaleY;
}


float UI::getCorner1X()
{
    
    return _corner1XSlider;
}

float UI::getCorner2X()
{
    
    return _corner2XSlider;
}

float UI::getCorner3X()
{
    
    return _corner3XSlider;
}

float UI::getCorner4X()
{
    
    return _corner4XSlider;
}


float UI::getCorner1Y()
{
    
    return _corner1YSlider;
}

float UI::getCorner2Y()
{
    
    return _corner2YSlider;
}

float UI::getCorner3Y()
{
    
    return _corner3YSlider;
}

float UI::getCorner4Y()
{
    
    return _corner4YSlider;
}
bool UI::isEnabled()
{
    return _displayed;
}

void UI::resetKeystone()
{
    _keystone->resetCorners();
    
    
    /*_gui.add(_corner1XSlider.setup("Top Left Corner X",0.0,-2.0,2.0));
    _gui.add(_corner1YSlider.setup("Top Left Corner Y",0.0,-2.0,2.0));
    
    _gui.add(_corner2XSlider.setup("Top Right Corner X",1.0,-2.0,2.0));
    _gui.add(_corner2YSlider.setup("Top Right Corner Y",0.0,-2.0,2.0));
    
    _gui.add(_corner3XSlider.setup("Bottom Right Corner X",1.0,-2.0,2.0));
    _gui.add(_corner3YSlider.setup("Bottom Right Corner Y",1.0,-2.0,2.0));
    
    _gui.add(_corner4XSlider.setup("Bottom Left Corner X",0.0,-2.0,2.0));
    _gui.add(_corner4YSlider.setup("Bottom Left Corner Y",1.0,-2.0,2.0));*/

    
    //_keystone->resetCorners();
}

float UI::getSceneRotation()
{
    return _rotateAngle;
}

void UI::toggleDebug(bool &status)
{
  
    
}

int UI::getGhostFadeSpeed()
{
    return _ghostFadeSlider;
}

bool UI::isFlipY()
{
    
    return _flipYToggle;
}

bool UI::isDisableGhosts()
{
    return _disableGhosts;
}

bool UI::isFlipX()
{
    
    return _flipXToggle;
}
bool UI::isShowDebug()
{
    return _showDebug;
}

float UI::getKinectAngle()
{
    return _parameters.kinectAngle;
}

void UI::kinectAngleChanged(int &angle)
{
    _parameters.kinectAngle = angle;
    _kinect->setCameraTiltAngle((float)angle);
    
}

AppParams UI::getParameters()
{
    return _parameters;    
}

void UI::saveKeystone()
{
   
    _keystone->saveToFile();
    
}

void UI::loadKeystone()
{
    
    _keystone->loadFromFile();
    
}
void UI::toggleDisplay()
{
    _displayed = !_displayed;
}

void UI::draw()
{
    if(_displayed)
        _gui.draw();
}

float UI::getGhostScaleX()
{
    return _ghostScaleX;
}

float UI::getGhostScaleY()
{
    return _ghostScaleY;
}

float UI::getPersonScaleX()
{
    return _personScaleX;
}

float UI::getPersonScaleY()
{
    return _personScaleY;
}

int UI::getGhostBlurAmt()
{
    return _ghostBlurSlider;
}
int UI::getPersonBlurAmt()
{
    
    return _personBlurSlider;
}


float UI::getPersonOffsetX()
{
    return _personOffX;
}

float UI::getPersonOffsetY()
{
 return _personOffY;
 }



float UI::getPersonPositionScaleX()
{
    return _personPositionScaleX;
}

float UI::getPersonPositionScaleY()
{
    return _personPositionScaleY;
}

float UI::getGhostOffsetX()
{
    return _ghostOffX;
}

float UI::getGhostOffsetY()
{
    return _ghostOffY;
}
