# CannyEdge

````c++
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

    threshold1 = 0;
    threshold2 = 100;

    if (argc >= 3)
        threshold1 = atof(*(argv+2));
    if (argc >= 4)
        threshold2 = atof(*(argv+3));

    
    cv::Mat mat = cv::imread(src);
    cv::namedWindow(src);
    cv::imshow(src,mat);
    
    std::cout << "file name " << src << std::endl;
    std::cout << "format " <<  mat.type() << std::endl;
    cv::Mat result;
    
    GaussianBlur(mat, mat , Size(3,3),1000);

    cv::Mat grey;
    cv::cvtColor(mat , grey,COLOR_BGR2GRAY);

    
    cv::namedWindow("Grey");
    cv::imshow("Grey",grey);

    std::cout <<"result type " << result.type() << std::endl;


    cv::namedWindow("Gaussian Blur");
    cv::imshow("Gaussian Blur",mat);

    

    Canny(grey, result,threshold1 ,threshold2);
    
    cv::namedWindow("result");
    cv::imshow("result",result);
    
    cv::waitKey(0);
    return 0;
}
````

Canny 함수의 인자 

InputArray : 입력되는 이지미

OutputArray : 출력되는 이미지

threshold1 : 

threshold2 : 