/*
 * SaveImages.cpp
 *
 *  Created on: 24/02/2018
 *      Author: alex
 */

#include "SaveImages.hpp"

#include <opencv2/opencv.hpp>

#define SAVE_IMAGES

#ifdef SAVE_IMAGES
#warning "SAVING IMAGES!!!"
#endif // #ifdef SAVE_IMAGES

using namespace cv;

SaveImages :: SaveImages ( void ) : SaveImages ( "" )
{
}

SaveImages :: SaveImages ( String folder )
{
    ChangeFolder ( folder );
}

SaveImages :: ~SaveImages ( void )
{
}

void SaveImages :: ChangeFolder ( String folder )
{
    Folder = folder;
}

void SaveImages :: Save ( Mat &image, String name )
{
#ifdef SAVE_IMAGES
    if ( "" != Folder )
    {
        String full_name = Folder + "/" + name + ".png";
        imwrite ( full_name, image );
    }
#endif // SAVE_IMAGES
}
