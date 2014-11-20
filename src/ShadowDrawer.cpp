//
//  ShadowDrawer.cpp
//  kinectExample
//
//  Created by jayson on 9/07/14.
//
//

#include "ShadowDrawer.h"

ShadowDrawer::ShadowDrawer()
{
    smokeEmitter.init();
    
}

void ShadowDrawer::draw(ofxCvContourFinder *contours,float x, float y, float w, float h, UI *ui)
{
    //ofFbo fbo;
    //fbo.allocate(CANVAS_WIDTH,CANVAS_HEIGHT,GL_RGBA);
    
    //fbo.begin();
    
      
    ofPushMatrix();
    //ofBackground(255,255,255);
    //ofTranslate(CANVAS_WIDTH/2,CANVAS_HEIGHT/2);
    //ofRotate(ui->getSceneRotation());
    //smokeEmitter.draw(contours,ui);
    ofSetColor(0,0,0);
    for(int i = 0; i < contours->nBlobs;i++)
    {
        
        ofBeginShape();
        
        float cX = contours->blobs[i].centroid.x * X_SCALE;
        float cY = contours->blobs[i].centroid.y * Y_SCALE;
        
        for(int j = 0; j < contours->blobs[i].nPts;j+=CONTOUR_INCREMENT)
        {
            float x = contours->blobs[i].pts[j].x* X_SCALE * ui->getPersonPositionScaleX();
            float y = contours->blobs[i].pts[j].y* Y_SCALE * ui->getPersonPositionScaleY();
            
            float dX = (cX - x) * ui->getPersonScaleX();
            float dY = (cY - y) * ui->getPersonScaleY();
            
            float pX = (cX - dX) + ui->getPersonOffsetX();
            float pY = (cY - dY) + ui->getPersonOffsetY();
            
            if(ui->isFlipX())
            {
                pX = 1024-pX;
            }
            
            if(ui->isFlipY())
            {
                pY = 768-pY;
            }
            ofCurveVertex(pX, pY );
            //ofCurveVertex((contours->blobs[i].pts[j].x * X_SCALE -  CANVAS_WIDTH/2) * ui->getPersonScaleX(), (contours->blobs[i].pts[j].y * Y_SCALE -  CANVAS_HEIGHT/2) * ui->getPersonScaleY());
        }
        
        ofEndShape();
    }
    ofPopMatrix();
}