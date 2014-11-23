//
//  ScreenMask.cpp
//  kinectExample
//
//  Created by jayson on 10/09/14.
//
//

#include "ScreenMask.h"


void ScreenMask::init()
{
    
    _maskImage.loadImage(MASK_IMAGE_PATH);
}

void ScreenMask::draw()
{
    _maskImage.draw(0,0,1280,800);
}
