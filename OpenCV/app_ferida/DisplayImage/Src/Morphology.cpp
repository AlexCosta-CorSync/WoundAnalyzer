/*
 * Morphology.cpp
 *
 *  Created on: 17/10/2017
 *      Author: alex
 */

#include "Morphology.hpp"

#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>

//#define DEBUG_MODE

#ifdef DEBUG_MODE
#warning "DEBUG MODE ENABLED!!!"
#endif // #ifdef DEBUG_MODE

using namespace cv;
using namespace std;

Morphology :: Morphology ( void )
{
}

Morphology :: ~Morphology ( void )
{
}

int Morphology :: CountWhites ( Mat input )
{
    /* Sanity check */
    if ( !input.empty ( ) )
    {
        return ( countNonZero ( input ) );
    }

    return 0;
}

bool Morphology :: Grayscale ( Mat input, Mat & output )
{
    bool success = false;

    output = input.clone ( );

    /* Sanity check */
    if ( !input.empty ( ) )
    {
        if ( CV_8UC3 == input.type ( ) )
        {
            cvtColor ( input, output, COLOR_BGR2GRAY );
        }

        output.convertTo ( output, CV_8UC1 );

        success = true;
    }

    ShowImage ( output, __FUNCTION__ );

    return success;
}

bool Morphology :: Negative ( Mat input, Mat & output )
{
    bool success = false;

    output = input.clone ( );

    /* Sanity check */
    if ( !input.empty ( ) )
    {
        subtract ( Mat ( input.size ( ), input.type ( ), Scalar :: all ( 255 ) ), input, output );

        success = true;
    }

    ShowImage ( output, __FUNCTION__ );

    return success;
}

bool Morphology :: Binarize ( Mat input, Mat & output )
{
    bool success = false;

    output = input.clone ( );

    /* Sanity check */
    if ( !input.empty ( ) )
    {
        Grayscale ( input, output );

        threshold ( output, output, 0, 255, ( CV_THRESH_BINARY | CV_THRESH_OTSU ) );

        success = true;
    }

    ShowImage ( output, __FUNCTION__ );

    return success;
}

bool Morphology :: FloodFill ( Mat input, Mat & output )
{
    bool success = false;

    output = input.clone ( );

    /* Sanity check */
    if ( !input.empty ( ) )
    {
        Mat floodfill = output.clone ( );

        /* Floodfill from point (0, 0) */
        floodFill ( floodfill, cv :: Point ( 0, 0 ), Scalar :: all ( 255 ) );

        /* Invert floodfilled image */
        Negative ( floodfill, floodfill );

        /* Combine the two images to get the foreground. */
        output |= floodfill;

        success = true;
    }

    ShowImage ( output, __FUNCTION__ );

    return success;
}

bool Morphology :: Contour ( Mat input, Mat & output )
{
    bool success = false;

    output = input.clone ( );

    /* Sanity check */
    if ( !input.empty ( ) )
    {
        vector < vector < Point > > contours;

        //findContours ( input.clone ( ), contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point ( 0, 0 ) );
        findContours ( input.clone ( ), contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE, Point ( 0, 0 ) );

        output = Mat :: zeros ( input.size ( ), CV_8UC1 );

        //drawContours ( output, contours, -1, Scalar :: all ( 255 ), 1, 8, hierarchy, 0, Point ( ) );
        drawContours ( output, contours, -1, Scalar :: all ( 255 ), 1 );

        success = true;
    }

    ShowImage ( output, __FUNCTION__ );

    return success;
}

bool Morphology :: Averaging ( Mat input, Mat & output, int iterations, int kernel_size )
{
    bool success = false;

    output = input.clone ( );

    /* Sanity check */
    if ( SanityCheck ( input, iterations, kernel_size, MORPH_RECT ) )
    {
        input.convertTo ( input, CV_8UC3 );

        while ( iterations-- )
        {
            bilateralFilter ( input, output, kernel_size, ( kernel_size * 2 ), ( kernel_size / 2 ) );
            input = output.clone ( );
        };

        success = true;
    }

    ShowImage ( output, __FUNCTION__ );

    return success;
}

bool Morphology :: Erode ( Mat input, Mat & output, int iterations, int kernel_size, int kernel_type )
{
    bool success = false;

    output = input.clone ( );

    /* Sanity check */
    if ( SanityCheck ( input, iterations, kernel_size, kernel_type ) )
    {
        Mat kernel = Kernel.Get_StructuringElement ( kernel_type, kernel_size );

        erode ( output, output, kernel, Point ( -1,-1 ), iterations );

        success = true;
    }

    ShowImage ( output, __FUNCTION__ );

    return success;
}

bool Morphology :: Dilate ( Mat input, Mat & output, int iterations, int kernel_size, int kernel_type )
{
    bool success = false;

    output = input.clone ( );

    /* Sanity check */
    if ( SanityCheck ( input, iterations, kernel_size, kernel_type ) )
    {
        Mat kernel = Kernel.Get_StructuringElement ( kernel_type, kernel_size );

        dilate ( output, output, kernel, Point ( -1,-1 ), iterations );

        success = true;
    }

    ShowImage ( output, __FUNCTION__ );

    return success;
}

bool Morphology :: Open ( Mat input, Mat & output, int iterations, int kernel_size, int kernel_type )
{
    bool success = false;

    output = input.clone ( );

    /* Sanity check */
    if ( SanityCheck ( input, iterations, kernel_size, kernel_type ) )
    {
        Mat kernel = Kernel.Get_StructuringElement ( kernel_type, kernel_size );

        morphologyEx ( output, output, MORPH_OPEN, kernel, Point ( -1,-1 ), iterations );

        success = true;
    }

    ShowImage ( output, __FUNCTION__ );

    return success;
}

bool Morphology :: Close ( Mat input, Mat & output, int iterations, int kernel_size, int kernel_type )
{
    bool success = false;

    output = input.clone ( );

    /* Sanity check */
    if ( SanityCheck ( input, iterations, kernel_size, kernel_type ) )
    {
        Mat kernel = Kernel.Get_StructuringElement ( kernel_type, kernel_size );

        morphologyEx ( output, output, MORPH_CLOSE, kernel, Point ( -1,-1 ), iterations );

        success = true;
    }

    ShowImage ( output, __FUNCTION__ );

    return success;
}

bool Morphology :: SanityCheck ( Mat input, int iterations, int kernel_size, int kernel_type )
{
    /* Sanity check */
    if ( !input.empty ( ) )
    {
        if ( 0 < iterations )
        {
            if ( ( MORPH_RECT == kernel_type ) || ( MORPH_CROSS == kernel_type ) || ( MORPH_ELLIPSE == kernel_type ) )
            {
                if ( 0 <= kernel_size )
                {
                    return true;
                }
            }
        }
    }

    return false;
}

void Morphology :: ShowImage ( Mat image, const char * caller )
{
#ifdef DEBUG_MODE
    imshow ( caller, image );
#endif
}
