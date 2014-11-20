//
//  SmokeEmitter.h
//  kinectExample
//
//  Created by jayson on 4/08/14.
//
//

#ifndef __kinectExample__SmokeEmitter__
#define __kinectExample__SmokeEmitter__

#include <iostream>
#include "ofxOpenCv.h"
#include "ofMain.h"
#include "SmokeParticle.h"
#include "UI.h"

class SmokeEmitter
{
    
public:
    
    void init();
    void draw(ofxCvContourFinder *contours, UI *ui);

private:
    
    void addSmokeParticle(ofPoint p);
    
    vector <SmokeParticle*> smokeParticleList;
    
    ofPoint _smokeDirection;
    
};

#endif /* defined(__kinectExample__SmokeEmitter__) */
