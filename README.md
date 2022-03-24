# WoundAnalyzer

Step 1 – Updating Ubuntu  
$ sudo apt-get update  
$ sudo apt-get upgrade  

Step 2 – Install dependencies  
$ sudo apt-get install build-essential cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev  
$ sudo apt-get install python3.5-dev python3-numpy libtbb2 libtbb-dev  
$ sudo apt-get install libjpeg-dev libpng-dev libtiff5-dev libjasper-dev libdc1394-22-dev libeigen3-dev libtheora-dev libvorbis-dev libxvidcore-dev libx264-dev sphinx-common libtbb-dev yasm libfaac-dev libopencore-amrnb-dev libopencore-amrwb-dev libopenexr-dev libgstreamer-plugins-base1.0-dev libavutil-dev libavfilter-dev libavresample-dev  
  
Step 3 –  Get OpenCV  
$ sudo -s  
$ cd /opt  
/opt$ git clone https://github.com/Itseez/opencv.git  
/opt$ git clone https://github.com/Itseez/opencv_contrib.git  
  
Step 4 – build and install OpenCV  
/opt$ cd opencv  
/opt/opencv$ mkdir release  
/opt/opencv$ cd release  
/opt/opencv/release$ cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_TBB=ON -D WITH_V4L=ON -D WITH_QT=ON -D WITH_OPENGL=OFF -D OPENCV_EXTRA_MODULES_PATH=/opt/opencv_contrib/modules /opt/opencv/  
/opt/opencv/release$ make -j4  
/opt/opencv/release$ make install  
/opt/opencv/release$ ldconfig  
/opt/opencv/release$ exit  
/opt/opencv/release$ cd ~  
  
Now to check if OpenCV is installed on a machine, run the following commands  
$ pkg-config --modversion opencv  
3.2.x  
