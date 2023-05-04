#include "Module.hpp"
namespace image_lib{
enum grayscaleChangeMode{Reverse,Logarithmic,Gamma};
    
    
    /*
    功能：执行灰度变换，支持反转变换，对数变换和伽马变换
    约束：
      输入：原图片(Mat)，格式（enum），输出：结果（Mat）
    */
    cv::Mat GrayscaleChange(cv::Mat originImage,grayscaleChangeMode mode=grayscaleChangeMode::Gamma)
    {
      if(originImage.empty())
      {
        return CreateSolidColorImage(300,300,255,255,255);
      }
      cv::Mat output,grayImage;//输出图以及灰度图
      cv::cvtColor(originImage,grayImage,cv::COLOR_BGR2GRAY);//生成灰度图
      output=grayImage.clone();
      switch(mode)
      {
        case grayscaleChangeMode::Reverse:
        {
          for(int i=0;i<grayImage.rows;i++)
          {
            for(int j=0;j<grayImage.cols;j++)
            {
                output.at<uchar>(i,j)=255-grayImage.at<uchar>(i,j);
            }
          }
          break;
        }
        case grayscaleChangeMode::Logarithmic:
        {
          for(int i=0;i<grayImage.rows;i++)
          {
            for(int j=0;j<grayImage.cols;j++)
            {
                output.at<uchar>(i,j)=6*log((double)(grayImage.at<uchar>(i, j))+1);
            }
          }
          normalize(output, output, 0, 255, cv::NORM_MINMAX); 
	        convertScaleAbs(output, output);
          break;
        }
        case grayscaleChangeMode::Gamma:
        {
          for (int i = 0; i < grayImage.rows; i++)
	          {
          		for (int j = 0; j < grayImage.cols; j++)
          		{
          			output.at<uchar>(i, j) =6*pow((double)grayImage.at<uchar>(i, j),0.5);  //幂律变换 s=6*r^0.5
          		}
          	}
          	normalize(output, output, 0, 255, cv::NORM_MINMAX);  //图像归一化，转到0~255范围内
          	convertScaleAbs(output, output);  //数据类型转换到CV_8U
          }
      }
      return output;
    };

}
