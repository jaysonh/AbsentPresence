//
//  BlobScene.cpp
//  kinectExample
//
//  Created by jayson on 7/08/14.
//
//

#include "BlobScene.h"

BlobScene::BlobScene(BlobScene *copyBlob)
{
    _sceneNum = copyBlob->_sceneNum;
    
    for(int i = 0; i < copyBlob->_blobs.size();i++)
    {
        _blobs.push_back( copyBlob->_blobs[i]);
    }
}

BlobScene::BlobScene(vector <ofxCvBlob> blobs, int sceneNum)
{
    _sceneNum = sceneNum;
    _blobs=blobs;
    
    
    for(int i = 0; i < _blobs.size();i++)
    {
        ofxCvBlob b = _blobs[i];
        
        vector <ofPoint> pointsHalved;
        int initPts = _blobs[i].nPts;
        
        for(int j = 0; j < _blobs[i].nPts;j+=CONTOUR_INCREMENT )
        {   
            pointsHalved.push_back( _blobs[i].pts[j]);
        }
        
        _blobs[i].pts = pointsHalved;
        _blobs[i].nPts = pointsHalved.size();
        
    }
}

int BlobScene::getSceneIndx()
{
    return _sceneNum;
}

int BlobScene:: getNumBlobs()
{
    return _blobs.size();
}