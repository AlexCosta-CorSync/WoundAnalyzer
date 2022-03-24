/*
 * StructuringElement.hpp
 *
 *  Created on: 17/10/2017
 *      Author: alex
 */

#ifndef STRUCTURING_ELEMENT_HPP_
#define STRUCTURING_ELEMENT_HPP_

#include <opencv2/opencv.hpp>

using namespace cv;

class StructuringElement
{
    public:
        StructuringElement  ( void );
        ~StructuringElement ( void );

        Mat Get_StructuringElement ( int type, int size );
};

#endif /* STRUCTURING_ELEMENT_HPP_ */
