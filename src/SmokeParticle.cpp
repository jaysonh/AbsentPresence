//
//  SmokeParticle.cpp
//  kinectExample
//
//  Created by jayson on 4/08/14.
//
//

#include "SmokeParticle.h"


SmokeParticle::SmokeParticle(ofPoint p, ofPoint v)
{
    _pos = p;
    _vel = v;
    
    _pos.x *= X_SCALE;
    _pos.y *= Y_SCALE;
    
    _size = ofRandom(MIN_SMOKE_PARTICLE_SIZE,MAX_SMOKE_PARTICLE_SIZE);
    _age = 255.0f;
}

void SmokeParticle::draw()
{
   // printf("POS: %f %f\n",_pos.x,_pos.y);
    ofSetColor(255.0 - _age,255.0 - _age,255.0- _age);
    //ofSetColor(0,0,0);
    
    ofEllipse(_pos.x,_pos.y,_size,_size);
    
    _pos.x += _vel.x;
    _pos.y += _vel.y;
    
    _age-=12.5f;
    
}

float SmokeParticle::getAge()
{
    return _age;
}