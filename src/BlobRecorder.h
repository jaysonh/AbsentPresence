//
//  BlobRecorder.h
//  kinectExample
//
//  Created by jayson on 7/08/14.
//
//

#ifndef __kinectExample__BlobRecorder__
#define __kinectExample__BlobRecorder__

#include <iostream>
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "BlobScene.h"
#include "GLOBALS.h"
#include "ofxBlurShader.h"
#include "UI.h"
#include "ofxXmlSettings.h"

#include <fstream>
#define BLOB_MATCH_CENTRE_DIFF_THRESH 2.0f
#define BLOB_MATCH_AREA_THRESH 10.0f

#define MAX_RECORDING_SCENES 750

#define GHOST_FADE_IN_SPEED 10.0f
class UI;

class BlobRecorder
{
public:
    
    BlobRecorder();
    void init();
    void addBlobs(ofxCvContourFinder *contourFinder);
    void playBack(UI *ui,float x, float y, float w, float h);
    //void processScenes();
    void saveSilhouettesToFile();
    
private:
    
    float _ghostFade;
    int _currentRecordScene;
    bool _lastSceneAdded;
    vector <BlobScene *> _blobSceneList;
    
    vector <int> _sceneIndxs;
    
    int _currentPlayScene;
    
    int _currentPlayEnd;
    ofxBlurShader blur;
    
    // Vector of vectors that contain BlobScene objects
    vector <BlobScene *> *playList;
    int randomIndx;
    vector <vector <BlobScene * > > savedSilhouettes;
    vector <BlobScene *> recordingList;
};

#endif /* defined(__kinectExample__BlobRecorder__) */
