//
//  ScreenMask.h
//  kinectExample
//
//  Created by jayson on 10/09/14.
//
//

#ifndef __kinectExample__ScreenMask__
#define __kinectExample__ScreenMask__

#include <iostream>
#include "ofMain.h"

#define MASK_IMAGE_PATH "assets/mask/mask_image.png"

class ScreenMask
{
    
public:
    void init();
    void draw();
private:
    ofImage _maskImage;
    
};
#endif 
