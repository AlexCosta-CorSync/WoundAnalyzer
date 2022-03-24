/*
 * ExtractFeatures.cpp
 *
 *  Created on: 06/11/2017
 *      Author: alex
 */

#include "ExtractFeatures.hpp"

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/imgproc/types_c.h>

#include "Wound.hpp"

using namespace cv;

#define SAVE( image, name )  SaveImage.Save ( image, name )

ExtractFeatures :: ExtractFeatures ( void )
{
    namedWindow ( "Features", WINDOW_NORMAL );
}

ExtractFeatures :: ~ExtractFeatures ( void )
{
}

void ExtractFeatures :: EvaluateFeatures ( Mat input )
{
    resizeWindow ( "Features", 200, 200 );

    /* Sanity check */
    if ( !input.empty ( ) )
    {
        char text [ 64 ];
        Mat isolated, features;

        Morph.Averaging ( input, input, 5 );
        SAVE ( input,    "Figure 01 - Averaging" );
        Morph.Binarize  ( input, isolated );
        SAVE ( isolated, "Figure 02 - Binarize" );

        IsolateWound ( isolated );
        IsolateGrid  ( isolated );

        //if ( !Transform.empty ( ) )
        {
            //warpPerspective ( input, input, Transform, input.size ( ) );
            //SAVE ( input, "Figure 10 - Original Perspective Correction" );
        }

        float area      = (       wound.GetArea ( )        / grid.GetArea ( ) );
        float perimeter = ( ( 4 * wound.GetPerimeter ( ) ) / grid.GetPerimeter ( ) );

        cvtColor ( wound.GetImage ( ), isolated, CV_GRAY2RGB );
        input += isolated;
        hconcat ( isolated, Mat ( isolated.rows, 3, input.type ( ), Scalar :: all ( 64 ) ), isolated );
        hconcat ( isolated, input, isolated );

        features = Mat ( 50, isolated.cols, isolated.type ( ), Scalar :: all ( 0 ) );
        sprintf ( text, "Area = %.3f cm * cm", area );
        putText ( features, text, cvPoint ( 15, 20 ), FONT_HERSHEY_COMPLEX_SMALL, 0.75, Scalar :: all ( 255 ), 1, CV_AA );
        sprintf ( text, "Perimeter = %.3f cm", perimeter );
        putText ( features, text, cvPoint ( 15, 40 ), FONT_HERSHEY_COMPLEX_SMALL, 0.75, Scalar :: all ( 255 ), 1, CV_AA );

        vconcat ( features, Mat ( 3, features.cols, features.type ( ), Scalar :: all ( 64 ) ), features );
        vconcat ( features, isolated, features );

        imshow ( "Features", features );
        SAVE ( features, "Figure 11 - Final" );
        resizeWindow ( "Features", features.cols, features.rows );
    }
}

void ExtractFeatures :: SetImageFolder ( String folder )
{
    SaveImage.ChangeFolder ( folder );
    wound.ChangeFolder ( folder );
}

Mat ExtractFeatures :: IsolateWound ( Mat input )
{
    Mat output = input.clone ( );

    Morph.Negative  ( output, output );
    SAVE ( output, "Figure 03 - Negative" );
    Morph.Erode     ( output, output, 2, 1, MORPH_CROSS );
    SAVE ( output, "Figure 04 - Erode" );

    wound.PerspectiveCorrection ( output, output, Transform );
    SAVE ( output, "Figure 09 - Perspective Correction" );

    return output.clone ( );
}

Mat ExtractFeatures :: IsolateGrid ( Mat input )
{
    Mat output = input.clone ( );

    //if ( !Transform.empty ( ) )
    {
        //warpPerspective ( output, output, Transform, output.size ( ) );

        Morph.Binarize ( output, output );
        Morph.Open ( output, output, 2 );
        grid.Labeling ( output, output, true );
    }

    return output.clone ( );
}
