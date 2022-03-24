/*
 * Morphology.hpp
 *
 *  Created on: 17/10/2017
 *      Author: alex
 */

#ifndef MORPHOLOGY_HPP_
#define MORPHOLOGY_HPP_

#include <opencv2/opencv.hpp>

#include "StructuringElement.hpp"

typedef std :: pair < int, int > point;

using namespace cv;
using namespace std;

class Morphology
{
    public:
        Morphology  ( void );
        ~Morphology ( void );

        int  CountWhites ( Mat input );
        bool Grayscale   ( Mat input, Mat & output );
        bool Negative    ( Mat input, Mat & output );
        bool Binarize    ( Mat input, Mat & output );
        bool FloodFill   ( Mat input, Mat & output );
        bool Contour     ( Mat input, Mat & output );
        bool Averaging   ( Mat input, Mat & output, int iterations, int kernel_size = 1 );
        bool Erode       ( Mat input, Mat & output, int iterations, int kernel_size = 1, int kernel_type = MORPH_RECT );
        bool Dilate      ( Mat input, Mat & output, int iterations, int kernel_size = 1, int kernel_type = MORPH_RECT );
        bool Open        ( Mat input, Mat & output, int iterations, int kernel_size = 1, int kernel_type = MORPH_RECT );
        bool Close       ( Mat input, Mat & output, int iterations, int kernel_size = 1, int kernel_type = MORPH_RECT );

    private:
        StructuringElement Kernel;

        bool SanityCheck ( Mat input, int iterations, int kernel_size = 1, int kernel_type = MORPH_RECT );
        void ShowImage   ( Mat image, const char * caller );
};

#endif /* MORPHOLOGY_HPP_ */
