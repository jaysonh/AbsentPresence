//
//  ShadowDrawer.h
//  kinectExample
//
//  Created by jayson on 9/07/14.
//
//

#ifndef __kinectExample__ShadowDrawer__
#define __kinectExample__ShadowDrawer__

#include <iostream>
#include "ofxOpenCv.h"
#include "ofMain.h"
#include "ofxBlurShader.h"
#include "SmokeEmitter.h"
#include "GLOBALS.H"
#include "UI.h"

class ShadowDrawer
{
public:
    ShadowDrawer();
    void draw(ofxCvContourFinder *contours,float x, float y, float w, float h, UI *ui);
private:
    ofxBlurShader blur;
    SmokeEmitter smokeEmitter;
    
    
};
#endif /* defined(__kinectExample__ShadowDrawer__) */
