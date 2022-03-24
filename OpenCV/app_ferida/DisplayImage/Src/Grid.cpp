/*
 * Grid.cpp
 *
 *  Created on: 07/11/2017
 *      Author: alex
 */

#include "Grid.hpp"

#include <opencv2/opencv.hpp>

using namespace cv;

Grid :: Grid ( void )
{
}

Grid :: Grid ( Mat image )
{
    SetImage ( image );
}

Grid :: ~Grid ( void )
{
}
