/*
 * Wound.hpp
 *
 *  Created on: 06/11/2017
 *      Author: alex
 */

#ifndef WOUND_HPP_
#define WOUND_HPP_

#include <opencv2/opencv.hpp>

#include "Image.hpp"

using namespace cv;

class Wound : public Image
{
    public:
        Wound  ( void );
        Wound  ( Mat image );
        ~Wound ( void );
};

#endif /* WOUND_HPP_ */
