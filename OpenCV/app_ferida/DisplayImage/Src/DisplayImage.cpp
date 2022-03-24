/*
 * DisplayImage.cpp
 *
 *  Created on: 16/10/2017
 *      Author: alex
 */

/*
 * TUTORIAL:
 *
 * https://docs.opencv.org/2.4/doc/tutorials/introduction/linux_eclipse/linux_eclipse.html
 */

#include <unistd.h>
#include <opencv2/opencv.hpp>

#include "ExtractFeatures.hpp"
#include "Acquire.hpp"

using namespace cv;

bool ParametersSanity ( int argc, char * argv [ ] );

int main ( int argc, char * argv [ ] )
{
    ExtractFeatures Features;
    Acquire         Image;

    if ( !ParametersSanity ( argc, argv ) )
    {
        int deviceID = 0;

        if ( !Image.OpenWebcam ( deviceID ) )
        {
            cerr << "Couldn't open webcam - " << deviceID << endl;
        }
    }

    else
    {
        String folder = argv [ 1 ];
        folder = folder.substr ( 0, folder.find_last_of ( "/\\" ) );

        Image.OpenFile ( argv [ 1 ] );

        Features.SetImageFolder ( folder );
    }

    setMouseCallback ( "Image", Image.MouseHandler, 0 );

    while ( 1 )
    {
        Image.Capture ( true );

        Features.EvaluateFeatures ( Image.GetROI ( false ) );

        /* Stop capturing by pressing ESC */
        if ( 27 == waitKey ( 10 ) )
        {
            break;
        }
    };

    return 0;
}

bool ParametersSanity ( int argc, char * argv [ ] )
{
    FILE * file;

    if ( 2 > argc )
    {
        return false;
    }

    if ( 2 < argc )
    {
        cerr << "Invalid parameter number!" << endl;
        exit ( -1 );
    }

    if ( !argv [ 1 ] )
    {
        cerr << "Path cannot be null" << endl;
        exit ( -1 );
    }

    file = fopen ( argv [ 1 ], "r" );

    if ( !file )
    {
        cerr << "File does not exist" << endl;
        exit ( -1 );
    }

    fclose ( file );

    return true;
}
