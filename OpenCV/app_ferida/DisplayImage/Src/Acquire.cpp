/*
 * Acquire.cpp
 *
 *  Created on: 25/10/2017
 *      Author: alex
 */

#include "Acquire.hpp"

#include <opencv2/opencv.hpp>

#include <opencv2/highgui/highgui_c.h>
#include <opencv2/videoio.hpp>
#include <opencv2/core/types_c.h>

#include "Image.hpp"

using namespace cv;

Image Acquire :: ImageProcessing = Image ( );
Point Acquire :: Origin          = Point ( -1, -1 );
Point Acquire :: Destiny         = Point ( -1, -1 );
bool  Acquire :: Drag            = false;
Mat   Acquire :: Frame           = Mat ( );
Mat   Acquire :: ROI             = Mat ( );
int   Acquire :: Width           = 0;
int   Acquire :: Height          = 0;

Acquire :: Acquire ( void ) : FromWebcam ( false ), ImagePath ( "" )
{
}

Acquire :: ~Acquire ( void )
{
    /* Sanity check */
    if ( FromWebcam )
    {
        if ( Webcam.isOpened ( ) )
        {
            Webcam.release ( );
        }
    }
}

void Acquire :: OpenFile  ( String image_path )
{
    ImagePath = image_path;

    namedWindow  ( "Image", WINDOW_NORMAL );
    resizeWindow ( "Image", 800, 600 );
}

void Acquire :: OpenFile  ( char * image_path )
{
    ImagePath = image_path;

    namedWindow  ( "Image", WINDOW_NORMAL );
    resizeWindow ( "Image", 800, 600 );
}

bool Acquire :: OpenWebcam ( int deviceID )
{
    FromWebcam = true;

    namedWindow  ( "Image", WINDOW_NORMAL );
    resizeWindow ( "Image", 800, 600 );

    return Webcam.open ( deviceID, cv::CAP_ANY );
}

Mat Acquire :: Capture ( bool show_image )
{
    /* Sanity check */
    if ( FromWebcam )
    {
        if ( Webcam.isOpened ( ) )
        {
            if ( !Webcam.read ( Frame ) )
            {
                cerr << "ERROR! blank frame grabbed\n";
            }
            //Webcam >> Frame;

            if (Frame.empty()) {
                cerr << "ERROR! blank frame grabbed\n";
            }
        }

        else
        {
            return ( Mat ( ) );
        }
    }

    else
    {
        Frame = imread ( ImagePath, IMREAD_COLOR );
    }

    if ( !( ( Frame.empty ( ) ) ) && show_image )
    {
        if ( Drag )
        {
            rectangle ( Frame, Origin, Destiny, Scalar ( 0, 0, 255 ), 2 );
        }

        imshow ( "Image", Frame );
    }

    return ( Frame.clone ( ) );
}

void Acquire :: MouseHandler ( int event, int x, int y, int flags, void * userdata )
{
    x = ( ( x < Frame.cols ) ? ( ( x < 0 ) ? 0 : x ) : ( Frame.cols - 1 ) );
    y = ( ( y < Frame.rows ) ? ( ( y < 0 ) ? 0 : y ) : ( Frame.rows - 1 ) );

    Destiny = Point ( x, y );

    switch ( event )
    {
        case CV_EVENT_LBUTTONDOWN:
            if ( !Drag )
            {
                Origin  = Point ( x, y );

                Width   = 0;
                Height  = 0;

                Drag    = true;
            }

            break;

        case CV_EVENT_LBUTTONUP:
            if ( Drag )
            {
                if ( Origin.x > x )
                {
                    Destiny.x = Origin.x;
                    Origin.x  = x;
                }

                if ( Origin.y > y )
                {
                    Destiny.y = Origin.y;
                    Origin.y  = y;
                }

                Width  = ( Destiny.x - Origin.x );
                Height = ( Destiny.y - Origin.y );

                Drag   = false;
            }

            break;

        case CV_EVENT_RBUTTONUP:
            Origin  = Point ( -1, -1 );

            Width   = 0;
            Height  = 0;

            Drag    = false;
            break;

        default:
            return;
    }
}

Mat Acquire :: GetROI ( bool show_image )
{
    if ( ( Width ) && ( Height ) )
    {
        ROI = Frame ( Rect ( Origin.x, Origin.y, Width, Height ) ).clone ( );

        // White Balance
        ImageProcessing.WhiteBalance ( ROI, ROI );

        // Correct the perspective
        //ImageProcessing.PerspectiveCorrection ( ROI, ROI );

        if ( show_image )
        {
            imshow ( "ROI", ROI );
        }
    }

    return ( ROI.clone ( ) );
}
