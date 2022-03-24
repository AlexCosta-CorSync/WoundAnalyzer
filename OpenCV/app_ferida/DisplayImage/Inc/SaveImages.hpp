/*
 * SaveImages.h
 *
 *  Created on: 24/02/2018
 *      Author: alex
 */

#ifndef SAVEIMAGES_H_
#define SAVEIMAGES_H_

#include <opencv2/opencv.hpp>

using namespace cv;

class SaveImages
{
    public:
        SaveImages  ( void );
        SaveImages  ( String folder );
        ~SaveImages ( void );

        void ChangeFolder ( String folder );
        void Save         ( Mat &image, String name );

    private:
        String Folder;
};

#endif /* SAVEIMAGES_H_ */
