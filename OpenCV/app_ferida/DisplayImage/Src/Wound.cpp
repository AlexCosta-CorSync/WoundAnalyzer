/*
 * Wound.cpp
 *
 *  Created on: 06/11/2017
 *      Author: alex
 */

#include "Wound.hpp"

#include <opencv2/opencv.hpp>

using namespace cv;

Wound :: Wound ( void )
{
}

Wound :: Wound ( Mat image )
{
    SetImage ( image );
}

Wound :: ~Wound ( void )
{
}
