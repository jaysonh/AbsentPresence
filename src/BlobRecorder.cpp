//
//  BlobRecorder.cpp
//  kinectExample
//
//  Created by jayson on 7/08/14.
//
//

#include "BlobRecorder.h"

BlobRecorder::BlobRecorder()
{
}

void BlobRecorder::init()
{
    _ghostFade=0.0f;
    blur.setup(CANVAS_WIDTH,CANVAS_HEIGHT);
    randomIndx =0;
    _currentPlayScene = 0;
    _currentRecordScene = 0;
    playList=NULL;
}

void BlobRecorder::addBlobs(ofxCvContourFinder *contourFinder)
{
    if(contourFinder->blobs.size() > 0 && recordingList.size() < MAX_RECORDING_SCENES)
    {
        for(int i = 0; i <contourFinder->blobs.size();i++ )
        {
            printf("area: %f\n", contourFinder->blobs[i].area);
        }
        recordingList.push_back(new BlobScene(contourFinder->blobs,_currentRecordScene));
        
        

        _lastSceneAdded = true;
    }else
    {
        if(_lastSceneAdded)
        {
            _lastSceneAdded = false;
            
            // Now put recording list into saved scenes;
            // Create new vector
            vector <BlobScene*> newList;
            
            for(int i = 0; i < recordingList.size();i++)
            {
                newList.push_back(new BlobScene(recordingList[i]));
            }
            
            if(newList.size() > 3)
            {
                savedSilhouettes.insert(savedSilhouettes.begin(),newList);
                //savedSilhouettes.push_back(newList);
            }
            recordingList.clear();
            
            if(savedSilhouettes.size() >20)
                savedSilhouettes.erase(savedSilhouettes.end());
            
            // Check if saved silhouettes list is greater than 20 if so then remove first
            //recordingList = new vector
            
        }
    }
    
    printf("Num saved silhs: %i\n",savedSilhouettes.size());
    for(int i = 0;i < savedSilhouettes.size();i++)
    {
        printf("SilhoutedList[%i] size: %i\n",i,savedSilhouettes[i].size());
    }
    
    /*
    if(contourFinder->blobs.size() > 0)
    {
        _blobSceneList.push_back(new BlobScene(contourFinder->blobs,_currentRecordScene));
        _lastSceneAdded = true;
    }else
    {
        if(_lastSceneAdded)
        {
            _lastSceneAdded=false;
            _currentRecordScene++;
        }
    }*/
}

void BlobRecorder::playBack(UI *ui,float x, float y, float w, float h)
{
    ofEnableAlphaBlending();
       if(savedSilhouettes.size()> 0 && !ui->isDisableGhosts())
       {   
            vector <BlobScene *> play= savedSilhouettes[randomIndx];
           
            if(_currentPlayScene < play.size())
            {
                
               
            BlobScene *b = play[_currentPlayScene];
            ofPushMatrix();
            //ofTranslate(CANVAS_WIDTH/2,CANVAS_HEIGHT/2);
            ofRotate(ui->getSceneRotation());
            //smokeEmitter.draw(contours,ui);
                ofSetColor(0,0,0);
            //ofSetColor(0,0,0,_ghostFade);
                
            //    if(_ghostFade < 255.0f)
             //       _ghostFade += GHOST_FADE_IN_SPEED;
                
           //printf("Playing back blob %i blob scene %i total blobs: %i total blobs in scene: %i\n", randomIndx, _currentPlayScene,savedSilhouettes.size(), play.size());
            for(int i = 0; i < b->_blobs.size();i++)
            {
               ofBeginShape();
               
               float cX = b->_blobs[i].centroid.x * X_SCALE;
               float cY = b->_blobs[i].centroid.y * Y_SCALE;
                
               for(int j = 0; j < b->_blobs[i].nPts;j++)
               {
                   float x = b->_blobs[i].pts[j].x * X_SCALE * ui->getGhostPositionScaleX();
                   float y = b->_blobs[i].pts[j].y * Y_SCALE * ui->getGhostPositionScaleY();
                   
                   float dX = (cX - x) * ui->getGhostScaleX();
                   float dY = (cY - y) * ui->getGhostScaleY();
                   
                   float pX = (cX - dX) + ui->getGhostOffsetX();
                   float pY = (cY - dY) + ui->getGhostOffsetY();
                   
                   if(ui->isFlipX())
                   {
                       pX = 1280-pX;
                   }
                   
                   if(ui->isFlipY())
                   {
                       pY = 800-pY;
                   }
                   
                   ofCurveVertex(pX, pY );
                   
                   //ofCurveVertex((b->_blobs[i].pts[j].x * X_SCALE -  CANVAS_WIDTH/2) * ui->getGhostScaleX(), (b->_blobs[i].pts[j].y * Y_SCALE  -  CANVAS_HEIGHT/2)* ui->getGhostScaleY());
               }
               
                ofEndShape();
                printf("endshape\n");
            }
           
            ofPopMatrix();
           if(ofGetFrameNum() %2 ==0)
               _currentPlayScene++;
            }
           if(_currentPlayScene >= play.size())
           {
               _ghostFade=0.0f;
               
               randomIndx = (int)ofRandom(0,savedSilhouettes.size());
               _currentPlayScene=0;
           }
      }
}

void BlobRecorder::saveSilhouettesToFile()
{
    ofstream myfile;
    string filename = ofToDataPath("backup.xml");
    myfile.open (filename.c_str());
    
    
    for(int i = 0; i < _blobSceneList.size();i++)
    {
        BlobScene *b = _blobSceneList[i];
        myfile << "<blobscene>" << endl;
        for(int j = 0; j < b->_blobs.size();j++)
        {
            myfile << "<blob>" << endl;
            
            for(int k = 0; k < b->_blobs[j].nPts;k++)
            {
                myfile << "<vertex>" << endl;
                myfile << "<vertex_x>" << b->_blobs[j].pts[k].x << "</vertex_x>"<<endl;
                myfile << "<vertex_y>" << b->_blobs[j].pts[k].y << "</vertex_x>"<<endl;
                myfile << "</vertex>" << endl;
            }
            
            myfile << "</blob>"<<endl;
    
        }
        myfile << "</blobscene>" <<endl;
    }
    
    myfile << "<indexs>" << endl;
    for(int i = 0; i < _sceneIndxs.size();i++)
    {
        myfile << "<index>" << _sceneIndxs[i] << "</index>"<< endl;
    }
    myfile << "</indexs>"<<endl;
    
    myfile.close();
    
    
    
    /*ofxXmlSettings xml;
    
    xml.addTag("Silhouettes");
    xml.pushTag("Silhouettes");
    
    for(int i = 0; i < _blobSceneList.size();i++)
    {
        BlobScene *b = _blobSceneList[i];
        
        xml.addTag("BlobScene");
        xml.pushTag("BlobScene",i);
        printf("Blob scene %i\n",i);
        for(int j = 0; j < b->_blobs.size();j++)
        {
            xml.addTag("Blob");
            xml.pushTag("Blob",j);
            printf("Blob %i\n",j);
            for(int k = 0; k < b->_blobs[j].nPts;k++)
            {
                printf("Adding %f %f %f\n",b->_blobs[j].pts[k].x,b->_blobs[j].pts[k].y,b->_blobs[j].pts[k].z);
                
                xml.addTag("vertex");
                xml.pushTag("vertex");
                xml.setAttribute("vertex", "x", b->_blobs[j].pts[k].x,k);
                xml.setAttribute("vertex", "y", b->_blobs[j].pts[k].x,k);
                //xml.addValue("x",b->_blobs[j].pts[k].x);
                //xml.addValue("y",b->_blobs[j].pts[k].y);
                
                xml.popTag();
                
            }
            
            xml.popTag();
            
        }
        xml.popTag();
    }
    xml.popTag();
    xml.saveFile("BackupSilhouettes.xml");
    */
    /*
    ofXml xml;
    
    for(int i = 0; i < _blobSceneList.size();i++)
    {
        BlobScene *b = _blobSceneList[i];
        
        xml.addChild("BlobScene");
        xml.setTo("//BlobScene");
        for(int j = 0; j < b->_blobs.size();j++)
        {
            
            xml.addChild("Blob");
            xml.setTo("//Blob");
            for(int k = 0; k < b->_blobs[j].nPts;k++)
            {
                printf("Adding %f %f %f\n",b->_blobs[j].pts[k].x,b->_blobs[j].pts[k].y,b->_blobs[j].pts[k].z);
                
                ofXml xmlChild;
                xmlChild.addChild("vertex");
                xmlChild.setTo("vertex");
                xmlChild.addValue("x",b->_blobs[j].pts[k].x);
                xmlChild.addValue("y",b->_blobs[j].pts[k].y);
                
                xml.addXml(xmlChild);
            }
            
            
        }
    }
    xml.save("BackupSilhouettes.xml");*/
    
}
