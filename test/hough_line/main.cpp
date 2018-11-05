#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <cstring>
#include <iostream>


struct LineInfo
{
    int slope; // 차선 기울기 
    int position;  // 차선과 차량사이의 거리 음수는 왼쪽 차선에 가까움 양수는 오른쪽 차선에 가까움 
};


char src[255];
using namespace cv;
using namespace std;
double threshold1 , threshold2;
float calcSlop(float x1 , float y1 , float x2 , float y2);


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
    
    
    vector<Vec4i> lines;
    Mat color_dst;
    color_dst = mat.clone();
    cv::HoughLinesP(result, lines,1, CV_PI/180, 200, 30, 10 );


    std::cout << "count of line " << lines.size() <<std::endl;
    for( size_t i = 0; i < lines.size() ;i++ )
    {
        std::cout << "line  " << i <<"" << lines[i] << std::endl;
        
        line( color_dst, Point(lines[i][0], lines[i][1]),
            Point(lines[i][2], lines[i][3]), Scalar(0,0,255), 3, 8 );
    }
    int lineshort_x[10];
    for( int i = 0; i < lines.size() ;i++ )
    {
        lineshort_x[i] = i;
    }
    for( int i = 0; i < lines.size() ;i++ )
    {
        for(int j = i+1 ; j < lines.size();j++)
        {
            int xi = lines[lineshort_x[i]][0] + lines[lineshort_x[i]][3];
            int xj = lines[lineshort_x[j]][0] + lines[lineshort_x[j]][3];
            if( xi > xj )
            {
                int temp = lineshort_x[i];
                lineshort_x[i] =  lineshort_x[j];
                lineshort_x[j] = temp;
            }
        }
    }

    int j;
    float avgSlope = 0;
    for( int i = 0; i < lines.size(); i++ )
    {
        std::cout << lines[lineshort_x[i]] << std::endl;
        j = lineshort_x[i];
        float slope = calcSlop(lines[j][0], lines[j][1],lines[j][2],lines[j][3]);
        std::cout << "slope  " << j <<"  " << calcSlop(lines[j][0], lines[j][1],lines[j][2],lines[j][3])  << std::endl;
        avgSlope += slope;
    }


    namedWindow( "Detected Lines");
    imshow( "Detected Lines", color_dst );

    cv::waitKey(0);
    return 0;
}

float calcSlop(float x1 , float y1 , float x2 , float y2)
{
    if(x1 > x2)
    {
        return (y2 - y1) / (x2 - x1);
    }

    return (y1 - y2 ) / (x1 - x2);
}

struct LineInfo getLineInfo(cv::Mat frame)
{
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
    
    
    vector<Vec4i> lines;
    Mat color_dst;
    color_dst = mat.clone();
    cv::HoughLinesP(result, lines,1, CV_PI/180, 200, 30, 10 );


    std::cout << "count of line " << lines.size() <<std::endl;
    for( size_t i = 0; i < lines.size() ;i++ )
    {
        std::cout << "line  " << i <<"" << lines[i] << std::endl;
        
        line( color_dst, Point(lines[i][0], lines[i][1]),
            Point(lines[i][2], lines[i][3]), Scalar(0,0,255), 3, 8 );
    }
    int lineshort_x[10];
    for( int i = 0; i < lines.size() ;i++ )
    {
        lineshort_x[i] = i;
    }
    for( int i = 0; i < lines.size() ;i++ )
    {
        for(int j = i+1 ; j < lines.size();j++)
        {
            int xi = lines[lineshort_x[i]][0] + lines[lineshort_x[i]][3];
            int xj = lines[lineshort_x[j]][0] + lines[lineshort_x[j]][3];
            if( xi > xj )
            {
                int temp = lineshort_x[i];
                lineshort_x[i] =  lineshort_x[j];
                lineshort_x[j] = temp;
            }
        }
    }

    int j;
    float avgSlope = 0;
    for( int i = 0; i < lines.size(); i++ )
    {
        std::cout << lines[lineshort_x[i]] << std::endl;
        j = lineshort_x[i];
        float slope = calcSlop(lines[j][0], lines[j][1],lines[j][2],lines[j][3]);
        std::cout << "slope  " << j <<"  " << calcSlop(lines[j][0], lines[j][1],lines[j][2],lines[j][3])  << std::endl;
        avgSlope += slope;
    }


    namedWindow( "Detected Lines");
    imshow( "Detected Lines", color_dst );
}

void printLineInfo(struct LineInfo info)
{
    std::cout << "slope " <<info.slope  <<  " position " << info.position << std::endl;
}

