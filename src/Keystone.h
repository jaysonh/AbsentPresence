/*
 *  Keystone.h
 *  humaneffectkinect
 *
 *  Created by Jayson Haebich on 5/07/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef KEYSTONE_H
#define KEYSTONE_H

#define KEYSTONE_SETTINGS_FILE "data/keystone_settings.txt"

class Keystone
{
public:
	
	void init(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) {
        _moving=false;
		selectedCorner_ = 0;
		
        modifying_=false;
		
		corners[0].x = x1;
		corners[0].y = y1;
		
		corners[1].x = x2;
		corners[1].y = y2;
		
		corners[2].x = x3;
		corners[2].y = y3;
		
		corners[3].x = x4;
		corners[3].y = y4;
		
		initialized = true;
		//loadFromFile();
		
	}
    
    void loadFromFile()
    {
        CFURLRef mainRef = CFBundleCopyBundleURL(CFBundleGetMainBundle());
		CFStringRef macPath = CFURLCopyFileSystemPath(mainRef, kCFURLPOSIXPathStyle);
		const char *pathPtr = CFStringGetCStringPtr(macPath,   CFStringGetSystemEncoding());
		string str (pathPtr);
		size_t found;
		found=str.find_last_of("/\\");
		string mainPath = str.substr(0,found+1);
        string filename = mainPath + KEYSTONE_SETTINGS_FILE;
		const char *filenameCh  = filename.c_str();
		ifstream fileIn(filenameCh);
		if(fileIn.is_open())
		{
            for(int i = 0; i < 4;i++)
            {
                string lineX;
                getline(fileIn,lineX);
                float tempX = ::atof(lineX.c_str());
                
                string lineY;
                getline(fileIn,lineY);
                float tempY = ::atof(lineY.c_str());
                
                corners[i].x = tempX;
                corners[i].y = tempY;
            }
        }
        fileIn.close();
    }
    void saveToFile()
    {
        CFURLRef mainRef = CFBundleCopyBundleURL(CFBundleGetMainBundle());
		CFStringRef macPath = CFURLCopyFileSystemPath(mainRef, kCFURLPOSIXPathStyle);
		const char *pathPtr = CFStringGetCStringPtr(macPath,   CFStringGetSystemEncoding());
		string str (pathPtr);
		size_t found;
		found=str.find_last_of("/\\");
		string mainPath = str.substr(0,found+1);
        
        ofstream fileOut;
		string filename = mainPath + KEYSTONE_SETTINGS_FILE;
		const char *filenameCh  = filename.c_str();
		fileOut.open(filenameCh);
        
        for(int i =0; i < 4;i++)
        {
            fileOut << corners[i].x << endl;
            fileOut << corners[i].y << endl;
        }
        
         fileOut.close();

    }
    
    
	void init(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4,float offset,ofPoint moviePos, ofPoint movieSize) {
        
		selectedCorner_ = 0;
		moviePos_ = moviePos;
		movieSize_ = movieSize;
		modifying_=false;
		
		corners[0].x = x1;
		corners[0].y = y1;
		
		corners[1].x = x2;
		corners[1].y = y2;
		
		corners[2].x = x3;
		corners[2].y = y3;
		
		corners[3].x = x4;
		corners[3].y = y4;
		
		initialized = true;
		
		
	}
	void resetCorners()
	{
		corners[0].x = 0;
		corners[0].y = 0;
		
		corners[1].x = 1;
		corners[1].y = 0;
		
		corners[2].x = 1;
		corners[2].y = 1;
		
		corners[3].x = 0;
		corners[3].y = 1;
		
	}
	
	void setPosition(float x, float y)
	{
		moviePos_ = ofPoint(x,y);
	}
	
	void setImageSize(float newX, float newY)
	{
		movieSize_.x = newX;
		movieSize_.y = newY;
	}
	
	void setCorners(ofPoint newCorners[])
	{
		for(int i = 0; i < 4;i++)
			corners[i] = newCorners[i];
		
	}
	
	
	void setModifying(bool status)
	{
		modifying_ = status;
	}
	
	bool isModifying() { return modifying_; }
	
	void update(float w, float h) {
		//we set matrix to the default - 0 translation
		//and 1.0 scale for x y z and w
		for(int i = 0; i < 16; i++){
			if(i % 5 != 0) matrix[i] = 0.0;
			else matrix[i] = 1.0;
		}
		
		//float w = 800;
		//float h = 800;
		//we set the warp coordinates
		//source coordinates as the dimensions of our window
		src[0].x = 0;
		src[0].y = 0;
		src[1].x = w;
		src[1].y = 0;
		src[2].x = w;
		src[2].y = h;
		src[3].x = 0;
		src[3].y = h;
		
		//printf("MovieSize.x: %f MovieSize.y: %f\n",movieSize_.x,movieSize_.y);
		//corners are in 0.0 - 1.0 range
		//so we scale up so that they are at the window's scale
		for(int i = 0; i < 4; i++){
			dst[i].x = corners[i].x  * w;
			dst[i].y = corners[i].y * h;
			
            //	printf("%f %f\n",dst[i].x,dst[i].y);
		}
		//printf("\n");
	}
	
	void set(bool modifying,float w, float h)
	{
        movieSize_ = ofPoint(w,h);
		update(w,h);
        
		findHomography(src, dst, matrix);
		
		glMultMatrixf(matrix);
		
		
	}
    
    void rotate(float amount)
    {
        /*float angle = amount / (float)ofGetWidth();
         
         float xInc = 0.1f*cos(angle);
         float yInc = 0.1f*sin(angle);
         
         printf("Rotating %f deg x: %f y: %f\n",angle,xInc,yInc);
         for(int i = 0; i < 4;i++)
         {
         corners[i].x += xInc;
         corners[i].y += yInc;
         }*/
    }
	
	void cornerMoved(float x, float y, const bool move, const bool resize)
	{
		//if(modifying_)
		//{
        //float scaleX = (float)(x-moviePos_.x) / movieSize_.x;
        //float scaleY = (float)(y-moviePos_.y) / movieSize_.y;
        
        
        float scaleX = (x) / movieSize_.x;
        float scaleY = (y) / movieSize_.y;
        
        
        //printf("mouseX: %f mouseY: %f moviePos.x: %f moviePos.y: %f ScaleX: %f ScaleY: %f\n",x,y,moviePos_.x,moviePos_.y,scaleX,scaleY);
		
        if(selectedCorner_ >= 0 && selectedCorner_ < 4)
        {
            if(move)
            {
                float xDiff = corners[selectedCorner_].x - scaleX;
                float yDiff = corners[selectedCorner_].y - scaleY;
                
                
                for(int i = 0; i < 4;i++)
                {
                    if(i != selectedCorner_)
                    {
                        corners[i].x -= xDiff;
                        corners[i].y -= yDiff;
                    }
                }
            }
            
            if(resize)
            {
                float xDiff = corners[selectedCorner_].x - scaleX;
                float yDiff = corners[selectedCorner_].y - scaleY;
                
                
                if(selectedCorner_ == 0)
                {
                    corners[3].x -= xDiff;
                    corners[1].y -= yDiff;
                }else if(selectedCorner_ == 1)
                {
                    corners[2].x -= xDiff;
                    corners[0].y -= yDiff;
                }else if(selectedCorner_ == 2)
                {
                    corners[1].x -= xDiff;
                    corners[3].y -= yDiff;
                }if(selectedCorner_ == 3)
                {
                    corners[0].x -= xDiff;
                    corners[2].y -= yDiff;
                }
                
            }
            
            corners[selectedCorner_].x = scaleX;
            corners[selectedCorner_].y = scaleY;
        }
        
		
	}
    
    void stopMoving()
    {
        _moving=false;
    }
	
    bool selectMiddle(int x, int y)
    {
        float xDiff = (corners[1].x - corners[0].x);
        float yDiff = (corners[3].y - corners[0].y);
        
        float distx;
        float disty;
        
        if(corners[0].x < corners[1].x)
            distx = (corners[0].x + abs(xDiff)/2) - (float)(x)/movieSize_.x;
        else
            distx = (corners[1].x + abs(xDiff)/2) - (float)(x)/movieSize_.x;
        
        if(corners[0].y < corners[3].y)
            disty = (corners[0].y + abs(yDiff)/2) - (float)(y)/movieSize_.y;
        else
            disty = (corners[3].y + abs(yDiff)/2) - (float)(y)/movieSize_.y;
        
        float dist  = sqrt( distx * distx + disty * disty);
        
        if(dist < 0.25 || _moving)
        {
            _moving=true;
            for(int i = 0; i < 4;i++)
            {
                corners[i].y -= disty;
                corners[i].x -= distx;
            }
            return true;
        }else
        {
            _moving=false;
            return false;
        }
    }
    
    void movePosition(int x, int y)
    {
        
    }
    
	void cornerSelected(int x, int y)
	{
		//if(modifying_)
		//{
        
        printf("Selecting corner at %i %i\n", x , y);
        float smallestDist = 1.0;
        selectedCorner_  = -1;
        
        for(int i = 0; i < 4; i++)
        {
            //float distx = corners[i].x - (float)x/movieSize_.x;
            //float disty = corners[i].y - (float)y/movieSize_.y;
            float distx = corners[i].x - (float)(x)/movieSize_.x;
            float disty = corners[i].y - (float)(y)/movieSize_.y;
            float dist  = sqrt( distx * distx + disty * disty);
            printf("Corner[%i] dist: %f\n",i, dist);
            if(dist < smallestDist ){
                selectedCorner_ = i;
                smallestDist = dist;
            }
        }
		//}
	}
	
	ofPoint * getCorners()
	{
		return corners;
	}
	
	void increaseSelectedCornerX(float amt)
	{
		//corners[selectedCorner_].x -= xAmt;
		//corners[selectedCorner_].y -= yAmt;
		
	}
	
	void decreaseSelectedCorner(float xAmt, float yAmt)
	{
		corners[selectedCorner_].x -= xAmt;
		corners[selectedCorner_].y -= yAmt;
		
		for(int i = 0; i < 4;i++)
			printf("corner[%i] x: %f y: %f\n",i,corners[i].x,corners[i].y);
	}
	
	void nextKeystoneCorner()
	{
		selectedCorner_++;
		if(selectedCorner_ >= 4) selectedCorner_ = 0;
	}
	
    void printInfo()
    {
        for(int i = 0; i < 4;i++)
            printf("%f %f ",corners[i].x,corners[i].y);
        printf("\n");
    }
    

	
	
	void gaussian_elimination(float *input, int n){
		// ported to c from pseudocode in
		// http://en.wikipedia.org/wiki/Gaussian_elimination
		
		float * A = input;
		int i = 0;
		int j = 0;
		int m = n-1;
		while (i < m && j < n){
			// Find pivot in column j, starting in row i:
			int maxi = i;
			for(int k = i+1; k<m; k++){
				if(fabs(A[k*n+j]) > fabs(A[maxi*n+j])){
					maxi = k;
				}
			}
			if (A[maxi*n+j] != 0){
				//swap rows i and maxi, but do not change the value of i
				if(i!=maxi)
					for(int k=0;k<n;k++){
						float aux = A[i*n+k];
						A[i*n+k]=A[maxi*n+k];
						A[maxi*n+k]=aux;
					}
				//Now A[i,j] will contain the old value of A[maxi,j].
				//divide each entry in row i by A[i,j]
				float A_ij=A[i*n+j];
				for(int k=0;k<n;k++){
					A[i*n+k]/=A_ij;
				}
				//Now A[i,j] will have the value 1.
				for(int u = i+1; u< m; u++){
					//subtract A[u,j] * row i from row u
					float A_uj = A[u*n+j];
					for(int k=0;k<n;k++){
						A[u*n+k]-=A_uj*A[i*n+k];
					}
					//Now A[u,j] will be 0, since A[u,j] - A[i,j] * A[u,j] = A[u,j] - 1 * A[u,j] = 0.
				}
				
				i++;
			}
			j++;
		}
		
		//back substitution
		for(int i=m-2;i>=0;i--){
			for(int j=i+1;j<n-1;j++){
				A[i*n+m]-=A[i*n+j]*A[j*n+m];
				//A[i*n+j]=0;
			}
		}
	}
	
	void drawBoundingBox()
	{
		
		ofFill();
		ofSetColor(0,255,0);
		//if(selectedCorner_ == 0)
        
		//if(selectedCorner_ >= 0 && selectedCorner_ <= 4)
        //    ofCircle(corners[selectedCorner_].x*movieSize_.x,corners[selectedCorner_].y*movieSize_.y,4);
        
        ofNoFill();
        ofPushMatrix();
        
        for(int y = 0; y < 801; y+= 40)
        {
            ofLine(0,y,1280,y);
        }
        for(int x = 0; x < 1281; x+= 40)
        {
            ofLine(x,0,x,800);
        }
        ofFill();
	}
	void findHomography(ofPoint src[4], ofPoint dst[4], float homography[16]){
		
		// create the equation system to be solved
		//
		// from: Multiple View Geometry in Computer Vision 2ed
		//       Hartley R. and Zisserman A.
		//
		// x' = xH
		// where H is the homography: a 3 by 3 matrix
		// that transformed to inhomogeneous coordinates for each point
		// gives the following equations for each point:
		//
		// x' * (h31*x + h32*y + h33) = h11*x + h12*y + h13
		// y' * (h31*x + h32*y + h33) = h21*x + h22*y + h23
		//
		// as the homography is scale independent we can let h33 be 1 (indeed any of the terms)
		// so for 4 points we have 8 equations for 8 terms to solve: h11 - h32
		// after ordering the terms it gives the following matrix
		// that can be solved with gaussian elimination:
		
		float P[8][9]={
            {-src[0].x, -src[0].y, -1,   0,   0,  0, src[0].x*dst[0].x, src[0].y*dst[0].x, -dst[0].x }, // h11
            {  0,   0,  0, -src[0].x, -src[0].y, -1, src[0].x*dst[0].y, src[0].y*dst[0].y, -dst[0].y }, // h12
			
            {-src[1].x, -src[1].y, -1,   0,   0,  0, src[1].x*dst[1].x, src[1].y*dst[1].x, -dst[1].x }, // h13
            {  0,   0,  0, -src[1].x, -src[1].y, -1, src[1].x*dst[1].y, src[1].y*dst[1].y, -dst[1].y }, // h21
			
            {-src[2].x, -src[2].y, -1,   0,   0,  0, src[2].x*dst[2].x, src[2].y*dst[2].x, -dst[2].x }, // h22
            {  0,   0,  0, -src[2].x, -src[2].y, -1, src[2].x*dst[2].y, src[2].y*dst[2].y, -dst[2].y }, // h23
			
            {-src[3].x, -src[3].y, -1,   0,   0,  0, src[3].x*dst[3].x, src[3].y*dst[3].x, -dst[3].x }, // h31
            {  0,   0,  0, -src[3].x, -src[3].y, -1, src[3].x*dst[3].y, src[3].y*dst[3].y, -dst[3].y }, // h32
		};
		
		gaussian_elimination(&P[0][0],9);
		
		// gaussian elimination gives the results of the equation system
		// in the last column of the original matrix.
		// opengl needs the transposed 4x4 matrix:
		float aux_H[]={ P[0][8],P[3][8],0,P[6][8], // h11  h21 0 h31
			P[1][8],P[4][8],0,P[7][8], // h12  h22 0 h32
			0      ,      0,0,0,       // 0    0   0 0
			P[2][8],P[5][8],0,1};      // h13  h23 0 h33
		
		for(int i=0;i<16;i++) homography[i] = aux_H[i];
	}
	
    bool _moving;
	int selectedCorner_;
	ofPoint moviePos_,movieSize_;
	bool initialized,modifying_;
	GLfloat matrix[16];
	ofPoint corners[4];
	ofPoint src[4];
	ofPoint dst[4];
	
	//ofPoint moviePos, movieSize;
};
#endif