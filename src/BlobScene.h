//
//  BlobScene.h
//  kinectExample
//
//  Created by jayson on 7/08/14.
//
//

#ifndef __kinectExample__BlobScene__
#define __kinectExample__BlobScene__

#include <iostream>
#include "ofxOpenCv.h"
#include "GLOBALS.h"

class BlobScene
{
public:
    
    BlobScene(vector <ofxCvBlob>  blobs, int sceneNum);
    BlobScene(BlobScene *copyBlob);
    int getNumBlobs();
    vector <ofxCvBlob>  _blobs;
    int getSceneIndx();
    int _sceneNum;
};

#endif /* defined(__kinectExample__BlobScene__) */
