/*
 * Grid.hpp
 *
 *  Created on: 07/11/2017
 *      Author: alex
 */

#ifndef GRID_HPP_
#define GRID_HPP_

#include <opencv2/opencv.hpp>

#include "Image.hpp"

using namespace cv;

class Grid : public Image
{
    public:
        Grid  ( void );
        Grid  ( Mat image );
        ~Grid ( void );
};

#endif /* GRID_HPP_ */
