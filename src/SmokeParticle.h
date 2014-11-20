//
//  SmokeParticle.h
//  kinectExample
//
//  Created by jayson on 4/08/14.
//
//

#ifndef __kinectExample__SmokeParticle__
#define __kinectExample__SmokeParticle__

#include <iostream>
#include "ofMain.h"
#include "GLOBALS.h"

#define MIN_SMOKE_PARTICLE_SIZE 10.0f
#define MAX_SMOKE_PARTICLE_SIZE 15.0f

#define PARTICLE_LIFE_SPAN 50

class SmokeParticle
{
    
public:
    SmokeParticle(ofPoint p, ofPoint v);
    void draw();
    
    float getAge();
    
private:
    ofPoint _pos;
    ofPoint _vel;
    float _size;
    float _age;
};
#endif /* defined(__kinectExample__SmokeParticle__) */
