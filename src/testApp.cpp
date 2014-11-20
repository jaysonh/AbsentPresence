#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup() {
    
    screenMask.init();
    _fullScreen=true;
    ofSetFullscreen(_fullScreen);
    lastScreen.allocate(CANVAS_WIDTH,CANVAS_HEIGHT);
    lastScreen.begin();
    ofClear(255,255,255);
    lastScreen.end();
    
    blur.setup(CANVAS_WIDTH,CANVAS_HEIGHT);
    _mode = MODE_WAITING_TO_START;
    
    _font.loadFont("fonts/verdana.ttf", 32, true, true);
    _blobRecorder.init();
    _startedInitalise=false;
    _ui.init(&kinect, &_blobRecorder, &keystone);
    
	syphonOut.setName("Screen Output");
	ofSetLogLevel(OF_LOG_VERBOSE);
	debugMode=false;
    
	// enable depth->video image calibration
	kinect.setRegistration(true);
    
	kinect.init();
	//kinect.init(true); // shows infrared instead of RGB video image
	//kinect.init(false, false); // disable video image (faster fps)
	
	kinect.open();		// opens first available kinect
	
	if(kinect.isConnected()) {
		ofLogNotice() << "sensor-emitter dist: " << kinect.getSensorEmitterDistance() << "cm";
		ofLogNotice() << "sensor-camera dist:  " << kinect.getSensorCameraDistance() << "cm";
		ofLogNotice() << "zero plane pixel size: " << kinect.getZeroPlanePixelSize() << "mm";
		ofLogNotice() << "zero plane dist: " << kinect.getZeroPlaneDistance() << "mm";
        kinect.setDepthClipping(500,4400);
	}
	
	
	nearThreshold = 430;
	farThreshold = 70;
	bThreshWithOpenCV = true;
	
    kinect.setCameraTiltAngle(_ui.getKinectAngle());
	ofSetFrameRate(25);
    
    keystone.init(0.0,0,1.0,0.0,1.0,1.0,0.0,1.0);
}

//--------------------------------------------------------------
void testApp::update() {
	
	ofBackground(100, 100, 100);
	
    if(kinect.isConnected())
    {
        kinect.update();
	
        // there is a new frame and we are connected
        if(kinect.isFrameNew())
        {
		
            if(_mode != MODE_WAITING_TO_START )
            {
                grayImage.flagImageChanged();
                blobDetector.update(kinect.getDepthPixels());
            }
        
            if(_mode == MODE_PLAYING_BACK_GHOSTS)
            {
                _blobRecorder.addBlobs(blobDetector.getContourFinder());
            }
        }
    }
    
    char title[128];
    sprintf(title, "FPS: %f",ofGetFrameRate());
	ofSetWindowTitle(title);
}

void testApp::displayInitScreen()
{
    glPushMatrix();
    keystone.setModifying(true);
    keystone.set(true,1024,768);
    ofSetColor(255);
    kinect.drawDepth(0,0,CANVAS_WIDTH,CANVAS_HEIGHT);
    _font.drawString("Press Spacebar To Start Initialising\nMake sure no one is in detection area", 30, ofGetHeight()/2);
    glPopMatrix();
}

void testApp::displayRecordingGhostsScreen()
{
    
    blur.begin();
    blur.amount = 1;//ofMap(mouseX,0,ofGetWidth(),0,10,true);
    blur.iterations = _ui.getGhostBlurAmt();//ofMap(mouseY,0,ofGetHeight(),1,10,true);
    
    ofClear(255,255,255,255);
        
    shadowDrawer.draw(blobDetector.getContourFinder(),0,0,1024,768,&_ui);
    blur.end();

    ofSetColor(0 ,0,0);
    _font.drawString("Recording Ghosts\nPress SpaceBar To Finish", 30, ofGetHeight()/2);
}

void testApp::recordInitScene()
{
    
    ofSetColor(255 ,255,255);
    _font.drawString("Scanning Scene\nDo not enter detection area", 30, ofGetHeight()/2-100);

    if(blobDetector.isInitialising())
    {
        blobDetector.drawProgress();
    }else
        _mode = MODE_PLAYING_BACK_GHOSTS;
        //_mode = MODE_RECORDING_GHOSTS;
}

void testApp::drawScene()
{
    if(_ui.isShowDebug())
    {
        ofSetColor(255,255,255);
        blobDetector.drawBackgroundImage(10, 10, 400, 300);
        blobDetector.drawBlobImage(410, 10, 400, 300);
        blobDetector.drawOpenCVBlobs(10,310,400,300);
        shadowDrawer.draw(blobDetector.getContourFinder(),410,310,400,300,&_ui);
        
        
    }else if(kinect.isConnected())
    {
        ofFbo ghostImages;
        ghostImages.allocate(CANVAS_WIDTH,CANVAS_HEIGHT);
        ghostImages.begin();
        ofClear(255,255,255,255);
        ofSetColor(255,255,255);
        ofRect(0,0,CANVAS_WIDTH,CANVAS_HEIGHT);
        ofSetColor(255,255,255);
        lastScreen.draw(0,0,CANVAS_WIDTH,CANVAS_HEIGHT);
        ofSetColor(255,255,255, _ui.getGhostFadeSpeed() );
        ofRect(0,0,CANVAS_WIDTH,CANVAS_HEIGHT);
        _blobRecorder.playBack(&_ui,0,0,1024,768);
        ghostImages.end();
        
        lastScreen = ghostImages;
        
        ofFbo fbo;
        fbo.allocate(CANVAS_WIDTH, CANVAS_HEIGHT);
        fbo.begin();
        blur.begin();
        blur.amount = 1;//ofMap(mouseX,0,ofGetWidth(),0,10,true);
        blur.iterations = _ui.getGhostBlurAmt();//ofMap(mouseY,0,ofGetHeight(),1,10,true);
        
        ofClear(255,255,255,255);
        
        
        ofSetColor(255,255,255);
        ghostImages.draw(0,0,CANVAS_WIDTH,CANVAS_HEIGHT);
        shadowDrawer.draw(blobDetector.getContourFinder(),0,0,1024,768,&_ui);
        
        blur.end();
        fbo.end();
        
        glPushMatrix();
        keystone.init(_ui.getCorner1X(),_ui.getCorner1Y(),
                      _ui.getCorner2X(),_ui.getCorner2Y(),
                      _ui.getCorner3X(),_ui.getCorner3Y(),
                      _ui.getCorner4X(),_ui.getCorner4Y());
        
		keystone.setModifying(_ui.isEnabled());
        keystone.set(true,1024,768);
        ofSetColor(255,255,255);
        fbo.draw(0,0,CANVAS_WIDTH,CANVAS_HEIGHT);
        if(keystone.isModifying())
            keystone.drawBoundingBox();
        glPopMatrix();
        screenMask.draw();
        
    }
}

void testApp::displayKinectErrorMsg()
{
    ofSetColor(0,0,0);
    ofRect(0,0,1024,768);
    ofSetColor(255,255,255);
    _font.drawString("Error! No Kinect",50,50);
}

//--------------------------------------------------------------
void testApp::draw() {
	
	//printf("MODE: %i\n",_mode);
    printf("angle: %f\n",kinect.getCurrentCameraTiltAngle());
    if(kinect.isConnected())
    {
        switch(_mode)
        {
            case MODE_WAITING_TO_START:
                displayInitScreen();
                break;
            
            case MODE_RECORDING_INIT_SCENE:
                recordInitScene();
                break;
            
            case MODE_RECORDING_GHOSTS:
                displayRecordingGhostsScreen();
                break;
            
            case MODE_PLAYING_BACK_GHOSTS:
                drawScene();
                break; 
            
        }
    }else{
            displayKinectErrorMsg();
    }
    
	syphonOut.publishScreen();
    
    _ui.draw();
}

void testApp::drawPointCloud() {
	int w = 640;
	int h = 480;
	ofMesh mesh;
	mesh.setMode(OF_PRIMITIVE_POINTS);
	int step = 2;
	for(int y = 0; y < h; y += step) {
		for(int x = 0; x < w; x += step) {
			if(kinect.getDistanceAt(x, y) > 0) {
				mesh.addColor(kinect.getColorAt(x,y));
				mesh.addVertex(kinect.getWorldCoordinateAt(x, y));
			}
		}
	}
	glPointSize(3);
	ofPushMatrix();
	// the projected points are 'upside down' and 'backwards' 
	ofScale(1, -1, -1);
	ofTranslate(0, 0, -1000); // center the points a bit
	ofEnableDepthTest();
	mesh.drawVertices();
	ofDisableDepthTest();
	ofPopMatrix();
}

//--------------------------------------------------------------
void testApp::exit() {
	//kinect.setCameraTiltAngle(0); // zero the tilt on exit
	kinect.close();
	
#ifdef USE_TWO_KINECTS
	kinect2.close();
#endif
}

//--------------------------------------------------------------
void testApp::keyPressed (int key) {
	switch (key) {
        case 'f':
        case 'F':
            _fullScreen = !_fullScreen;
            ofSetFullscreen(_fullScreen);
            break;
		case 'a':
            blobDetector.increaseBlur(1);
            break;
		case 's':
            blobDetector.increaseBlur(-1);
            break;
        case '\t':
            _ui.toggleDisplay();
            //debugMode = !debugMode;
            break;
        case ' ':
            if(_mode == MODE_WAITING_TO_START)
                _mode = MODE_RECORDING_INIT_SCENE;
            else if(_mode == MODE_RECORDING_GHOSTS)
            {
                //_blobRecorder.processScenes();
                //_blobRecorder.saveSilhouettesToFile();
                _mode = MODE_PLAYING_BACK_GHOSTS;
            }
            break;
	}
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
    
    keystone.cornerMoved(x, y, false, false);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
    keystone.cornerSelected(x,y);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{}
