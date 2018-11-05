#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <cstring>
#include <iostream>

char src[255];
using namespace cv;
double threshold1 , threshold2;
int main(int argc , char ** argv)
{

    if (argc >= 2 )
        strcpy(src,*(argv+1));
    else strcpy(src,"test.jpg");

    cv::Mat mat = cv::imread(src);
    cv::namedWindow(src);
    cv::imshow(src,mat);
    
    std::cout << "file name " << src << std::endl;
    std::cout << "format " <<  mat.type() << std::endl;
    cv::Mat result;
    
    GaussianBlur(mat, result , Size(3,3),1000);
    
    cv::namedWindow("result");
    cv::imshow("result",result);
    
    cv::waitKey(0);
    return 0;
}