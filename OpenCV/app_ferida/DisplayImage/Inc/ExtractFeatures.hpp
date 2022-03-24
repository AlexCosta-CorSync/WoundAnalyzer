/*
 * ExtractFeatures.hpp
 *
 *  Created on: 06/11/2017
 *      Author: alex
 */

#ifndef EXTRACT_FEATURES_HPP_
#define EXTRACT_FEATURES_HPP_

#include <opencv2/opencv.hpp>

#include "Wound.hpp"
#include "Grid.hpp"
#include "SaveImages.hpp"

using namespace cv;

class ExtractFeatures
{
    public:
        ExtractFeatures  ( void );
        ~ExtractFeatures ( void );

        void EvaluateFeatures ( Mat input );
        void SetImageFolder   ( String folder );

    private:
        Morphology Morph;
        Wound      wound;
        Grid       grid;
        Mat        Transform;
        SaveImages SaveImage;

        Mat  IsolateWound ( Mat input );
        Mat  IsolateGrid  ( Mat input );
};

#endif /* EXTRACT_FEATURES_HPP_ */
