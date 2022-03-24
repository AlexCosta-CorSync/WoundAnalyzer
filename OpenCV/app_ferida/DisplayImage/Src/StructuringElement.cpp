/*
 * StructuringElement.cpp
 *
 *  Created on: 17/10/2017
 *      Author: alex
 */

#include "StructuringElement.hpp"

#include <opencv2/opencv.hpp>

using namespace cv;

StructuringElement :: StructuringElement ( void )
{
}

StructuringElement :: ~StructuringElement ( void )
{
}

Mat StructuringElement :: Get_StructuringElement ( int type, int size )
{
    Mat structuring_element;

    structuring_element = getStructuringElement ( type, Size ( ( 2 * size ) + 1, ( 2 * size ) + 1 ) );

    return structuring_element;
}
