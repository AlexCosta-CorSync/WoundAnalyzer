/*
 * Acquire.hpp
 *
 *  Created on: 25/10/2017
 *      Author: alex
 */

#ifndef ACQUIRE_HPP_
#define ACQUIRE_HPP_

#include <opencv2/opencv.hpp>

#include "Image.hpp"

using namespace cv;

class Acquire
{
    public:
        Acquire  ( void );
        ~Acquire ( void );

        void        OpenFile     ( String image_path );
        void        OpenFile     ( char * image_path );
        bool        OpenWebcam   ( int deviceID );
        Mat         Capture      ( bool show_image = false );

        static void MouseHandler ( int event, int x, int y, int flags, void * userdata );
        static Mat  GetROI       ( bool show_image = false );

    private:
        VideoCapture Webcam;
        bool         FromWebcam;
        string       ImagePath;

        static Image ImageProcessing;
        static Point Origin;
        static Point Destiny;
        static bool  Drag;
        static Mat   Frame;
        static Mat   ROI;
        static int   Width;
        static int   Height;
};

#endif /* ACQUIRE_HPP_ */
