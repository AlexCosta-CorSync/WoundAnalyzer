/*
 * Image.hpp
 *
 *  Created on: 07/11/2017
 *      Author: alex
 */

#ifndef IMAGE_HPP_
#define IMAGE_HPP_

#include <opencv2/opencv.hpp>
#include <opencv2/xphoto.hpp>

#include "Morphology.hpp"
#include "SaveImages.hpp"

using namespace cv;
using namespace cv :: xphoto;

class Image
{
    public:
        Image  ( void );
        ~Image ( void );

        bool  SetImage              ( Mat input );
        Mat   GetImage              ( void );

        bool  WhiteBalance          ( Mat input, Mat & output );
        bool  PerspectiveCorrection ( Mat input, Mat & output, Mat & transform );
        bool  Labeling              ( Mat input, Mat & output, bool store_major );

        float GetArea               ( void );
        float GetPerimeter          ( void );

        Point MassCenter            ( vector < Point > points );

        void  ChangeFolder          ( String folder );
        Mat        Area;
        Mat        Perimeter;
    private:
        Morphology Morph;
        SaveImages SaveImage;

        //Mat        Area;
        //Mat        Perimeter;

        Ptr < xphoto :: WhiteBalancer > WB;
};

#endif /* IMAGE_HPP_ */
