/*
 * Image.cpp
 *
 *  Created on: 07/11/2017
 *      Author: alex
 */

#include "Image.hpp"

#include <iostream>
#include <algorithm>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/xphoto.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>

//#define DEBUG_MODE

#ifdef DEBUG_MODE
#warning "DEBUG MODE ENABLED!!!"
#endif // #ifdef DEBUG_MODE

using namespace cv;
using namespace cv :: xphoto;
using namespace std;

#define SAVE( image, name )  SaveImage.Save ( image, name )

char text [ 255 ];

Image :: Image ( void )
{
    WB = xphoto :: createSimpleWB ( );
}

Image :: ~Image ( void )
{
}

bool Image :: SetImage ( Mat input )
{
    bool success = false;

    /* Sanity check */
    if ( !input.empty ( ) )
    {
        Area = input.clone ( );

        success = Morph.Contour ( Area, Perimeter );
    }

    return success;
}

Mat Image :: GetImage ( void )
{
    return Area.clone ( );
}

bool Image :: WhiteBalance ( Mat input, Mat & output )
{
    bool success = false;

    output = input.clone ( );

    /* Sanity check */
    if ( !input.empty ( ) )
    {
        WB -> balanceWhite ( input, output );

#ifdef DEBUG_MODE
        imshow ( "White Balance", output );
#endif

        success = true;
    }

    return success;
}

bool Image :: PerspectiveCorrection ( Mat input, Mat & output, Mat & transform )
{
    bool success = false;

    output    = input.clone ( );
    transform = Mat ( );

    /* Sanity check */
    if ( !input.empty ( ) )
    {
        Mat cross = output.clone ( );
        Mat mask  = output.clone ( );

        /* Creates a mask of the wound */
        Morph.Negative ( output, mask );
        SAVE ( mask, "Figure 05 - Mask" );

        /* Isolate the wound image and the cross sections */
        Morph.FloodFill ( output, output );
        bitwise_and ( mask, output, output );
        Morph.Close ( output, output, 2 );
        Morph.FloodFill ( output, output );
        SetImage ( output );
        SAVE ( output, "Figure 06 - Isolated" );

        success = true;
    #if 0
        vector < vector < Point > > Label;
        vector < Point > Center;

        findContours ( cross, Label, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE );

        if ( Label.size ( ) )
        {
            /* Determine the mass center for each object */
            for ( size_t i = 0; i < Label.size ( ); i++ )
            {
                Center.push_back ( MassCenter ( Label [ i ] ) );
            }

            /* Clears the cross image */
            cross = Scalar :: all ( 0 );

            /* Draws lines between each two objects */
            for ( size_t i = 0; i < Center.size ( ); i++ )
            {
                for ( size_t j = i; j < Center.size ( ); j++ )
                {
                    if ( i != j )
                    {
                        line ( cross, Center [ i ], Center [ j ], Scalar :: all ( 255 ) );
                    }
                }
            }

            SAVE ( cross, "Figure 07 - Perspective Polygon" );

            /* Isolate the biggest polygon possible */
            Morph.FloodFill ( cross, cross );
            findContours ( cross, Label, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE );

            Point2f     RectPoints [ 4 ];
            RotatedRect minRect   = minAreaRect  ( Label [ 0 ] );
            Rect        boundRect = boundingRect ( Label [ 0 ] );

            minRect.points ( RectPoints );

            output = GetImage ( );
            vector < Point2f > quad_pts;
            vector < Point2f > squre_pts;

            quad_pts.push_back ( RectPoints [ 2 ] );
            quad_pts.push_back ( RectPoints [ 1 ] );
            quad_pts.push_back ( RectPoints [ 3 ] );
            quad_pts.push_back ( RectPoints [ 0 ] );

            Point2f p1 = Point2f ( boundRect.x,                   boundRect.y );
            Point2f p2 = Point2f ( boundRect.x,                   boundRect.y + boundRect.height );
            Point2f p3 = Point2f ( boundRect.x + boundRect.width, boundRect.y );
            Point2f p4 = Point2f ( boundRect.x + boundRect.width, boundRect.y + boundRect.height );

            squre_pts.push_back ( p1 );
            squre_pts.push_back ( p2 );
            squre_pts.push_back ( p3 );
            squre_pts.push_back ( p4 );

            Mat dummy ( cross.rows, cross.cols, cross.type ( ), Scalar :: all ( 0 ) );
            cvtColor ( dummy, dummy, CV_GRAY2RGB );
            line ( dummy, Point ( RectPoints [ 0 ] ), Point ( RectPoints [ 1 ] ), Scalar ( 0, 0, 255 ) );
            line ( dummy, Point ( RectPoints [ 1 ] ), Point ( RectPoints [ 2 ] ), Scalar ( 0, 0, 255 ) );
            line ( dummy, Point ( RectPoints [ 2 ] ), Point ( RectPoints [ 3 ] ), Scalar ( 0, 0, 255 ) );
            line ( dummy, Point ( RectPoints [ 3 ] ), Point ( RectPoints [ 0 ] ), Scalar ( 0, 0, 255 ) );

            line ( dummy, Point ( p1 ), Point ( p2 ), Scalar ( 0, 255, 0 ) );
            line ( dummy, Point ( p2 ), Point ( p4 ), Scalar ( 0, 255, 0 ) );
            line ( dummy, Point ( p3 ), Point ( p4 ), Scalar ( 0, 255, 0 ) );
            line ( dummy, Point ( p3 ), Point ( p1 ), Scalar ( 0, 255, 0 ) );
            SAVE ( dummy, "Figure 08 - Perspective Rect" );

            transform = getPerspectiveTransform ( quad_pts, squre_pts );
            warpPerspective ( output, output, transform, output.size ( ) );
            SetImage ( output );
    #ifdef DEBUG_MODE
            Point P1 = Point ( boundRect.x,                   boundRect.y );
            Point P2 = Point ( boundRect.x,                   boundRect.y + boundRect.height );
            Point P3 = Point ( boundRect.x + boundRect.width, boundRect.y + boundRect.height );
            Point P4 = Point ( boundRect.x + boundRect.width, boundRect.y );

            cvtColor ( output, output, CV_GRAY2RGB );
            line ( output, P1, P2, Scalar ( 0, 0, 255 ), 1, CV_AA, 0 );
            line ( output, P2, P3, Scalar ( 0, 0, 255 ), 1, CV_AA, 0 );
            line ( output, P3, P4, Scalar ( 0, 0, 255 ), 1, CV_AA, 0 );
            line ( output, P4, P1, Scalar ( 0, 0, 255 ), 1, CV_AA, 0 );

            line ( output, rect_points [ 0 ], rect_points [ 1 ], Scalar ( 255, 0, 0 ), 1, CV_AA, 0 );
            line ( output, rect_points [ 1 ], rect_points [ 2 ], Scalar ( 255, 0, 0 ), 1, CV_AA, 0 );
            line ( output, rect_points [ 2 ], rect_points [ 3 ], Scalar ( 255, 0, 0 ), 1, CV_AA, 0 );
            line ( output, rect_points [ 3 ], rect_points [ 0 ], Scalar ( 255, 0, 0 ), 1, CV_AA, 0 );

            namedWindow ( "Perspective", WINDOW_NORMAL );
            imshow ( "Perspective", output );
            resizeWindow ( "Perspective", output.cols, output.rows );
    #endif
            success = true;
        }
    #endif
    }

    return success;
}

bool Image :: Labeling ( Mat input, Mat & output, bool store_major )
{
    bool success = false;

    output  = input.clone ( );

    /* Sanity check */
    if ( !input.empty ( ) )
    {
        // Find total markers
        vector < vector < Point > > Label;
        findContours ( output, Label, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE );

        output = Mat :: zeros ( output.size ( ), output.type ( ) );

        if ( store_major )
        {
            SetImage ( output );
        }

        for ( size_t i = 0; i < Label.size ( ); i++ )
        {
            drawContours ( output, Label, static_cast < int > ( i ), Scalar :: all ( static_cast < int > ( i ) + 1 ), -1 );

            if ( store_major )
            {
                Mat major = Mat :: zeros ( output.size ( ), output.type ( ) );

                drawContours ( major, Label, static_cast < int > ( i ), Scalar :: all ( 255 ), -1 );

                if ( GetArea ( ) < ( ( float ) Morph.CountWhites ( major ) ) )
                {
                    SetImage ( major );
                }
            }
        }

        if ( store_major )
        {
            output = GetImage ( );
        }

        else
        {
            output *= ( 255 / Label.size ( ) );
        }

#ifdef DEBUG_MODE
        imshow ( "Labeling", output );
#endif

        success = true;
    }

    return success;
}

float Image :: GetArea ( void )
{
    float area = ( ( float ) Morph.CountWhites ( Area ) );

#ifdef DEBUG_MODE
    Mat aux;
    cvtColor ( Area, aux, CV_GRAY2RGB );
    sprintf  ( text, "%.3f", area );
    putText  ( aux, text, cvPoint ( 15, 20 ), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar ( 0, 0, 255 ), 1, CV_AA );
    imshow   ( "Area", aux );
#endif

    return area;
}

float Image :: GetPerimeter ( void )
{
    float perimeter = ( ( float ) Morph.CountWhites ( Perimeter ) );

#ifdef DEBUG_MODE
    Mat aux;
    cvtColor ( Perimeter, aux, CV_GRAY2RGB );
    sprintf  ( text, "%.3f", perimeter );
    putText  ( aux, text, cvPoint ( 15, 20 ), FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar ( 0, 0, 255 ), 1, CV_AA );
    imshow   ( "Perimeter", aux );
#endif

    return perimeter;
}

Point Image :: MassCenter ( vector < Point > points )
{
    Point mass_center ( 0, 0 );

    for( size_t i = 0; points.size ( ) > i; i++ )
    {
        mass_center += points [ i ];
    }

    mass_center.x /= points.size ( );
    mass_center.y /= points.size ( );

    return mass_center;
}

void Image :: ChangeFolder ( String folder )
{
    SaveImage.ChangeFolder ( folder );
}
