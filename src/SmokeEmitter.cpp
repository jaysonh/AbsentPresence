//
//  SmokeEmitter.cpp
//  kinectExample
//
//  Created by jayson on 4/08/14.
//
//

#include "SmokeEmitter.h"

void SmokeEmitter::init()
{
    _smokeDirection = ofPoint(ofRandom(-2.5 *SMOKE_SPEED,2.5 *SMOKE_SPEED),ofRandom(-2.5 *SMOKE_SPEED,2.5 *SMOKE_SPEED));
}

void SmokeEmitter::draw(ofxCvContourFinder *contours, UI *ui)
{
    // Add new smoke particles
    for(int i = 0; i < contours->nBlobs;i++)
    {
        for(int j = 0; j < contours->blobs[i].nPts;j+=5)
        {
            // Pick random point to join with
            
            int indx = (int)ofRandom(0,contours->blobs[i].nPts);
            
            ofPoint p1 = contours->blobs[i].pts[j];
            ofPoint p2 = contours->blobs[i].pts[indx];
            
            float distBetween = ofRandom(0.0,1.0);
            
            ofPoint diff = ofPoint(p2.x - p1.x, p2.y - p1.y);
            
            ofPoint p3 = ofPoint(p1.x + diff.x * distBetween,p1.y + diff.y * distBetween);
            
            p1.x *= ui->getGhostScaleX();
            p1.y *= ui->getGhostScaleY();
            
            addSmokeParticle(p1);
        }   
    }
    
    // Draw Smoke Particles
    for(vector<SmokeParticle *>::iterator  it = smokeParticleList.begin(); it != smokeParticleList.end();)
    {
        SmokeParticle *p = *it;
        
        p->draw();
        if(p->getAge() < 0)
        {
            it = smokeParticleList.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void SmokeEmitter::addSmokeParticle(ofPoint p)
{
    ofPoint v;
    v.x = _smokeDirection.x + ofRandom(-1.25 *SMOKE_SPEED,1.25 *SMOKE_SPEED);
    v.y = _smokeDirection.y + ofRandom(-1.25 *SMOKE_SPEED,1.25 *SMOKE_SPEED);
    smokeParticleList.push_back(new SmokeParticle(p, v));
    
}