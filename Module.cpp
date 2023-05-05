#include <random>
#include"opencv.hpp"
#include"ImageInfo.hpp"

namespace image_lib
{
  /*
    功能：创建一个纯色图片
    约束：
      输入:分辨率(float)，颜色(float)，输出：纯色图（Mat）
    */
    cv::Mat CreateSolidColorImage(const int x,
                                  const int y,
                                  const float r,const float g,const float b)
    {
        return cv::Mat(x,y,CV_8UC3,cv::Scalar(b,g,r));
    }

    //生成噪声图
    cv::Mat Salt(const int x,const int y,const int seed)
    {
      cv::Mat image=CreateSolidColorImage(x,y,0,0,0);
      //生成随机种子
      std::default_random_engine generater;
	    std::uniform_int_distribution<int>randomRow(0, image.rows - 1);
	    std::uniform_int_distribution<int>randomCol(0, image.cols - 1);
    
	    int i, j;
	    for (int k = 0; k < seed; k++)
	    {
	    	i = randomCol(generater);
	    	j = randomRow(generater);
	    	if (image.channels() == 1)
	    	{
	    		image.at<uchar>(j, i) = 255;
	    	}
	    	else if (image.channels() == 3)
	    	{
	    		image.at<cv::Vec3b>(j, i)[0] = 255;
	    		image.at<cv::Vec3b>(j, i)[1] = 255;
	    		image.at<cv::Vec3b>(j, i)[2] = 255;
	    	}
	    }
      return image;
    }

    //指定斜率，按方向生成渐变，支持三个颜色，采用图形学中的顶点着色插值算法
    //整理一下思路，想画出渐变图关键在于求出每一点像素应该如何赋值，将图片内的点P用向量表示即可得到其中的分量信息
    cv::Mat GradientColor(const cv::Scalar& color1, const cv::Scalar& color2, const cv::Scalar& color3,int slope,int x=200,int y=200)
    {
      double alpha=0.0,beta=0.0;//分量的比例
      ImageInfo A,B,C,D;//图片的四个顶点，A(0,0),B(x,0),C(0,x),D(x,x)
      cv::Mat img(x,y,CV_8UC3,cv::Scalar(255,255,255));
      for (int i = 0; i < img.rows; i++)
        {
            for (int j = 0; j < (int)(y-(y*i/(double)x)); j++)//相似三角形，j=y-y*i/x
            {
                alpha=(i-0)/(double)x;
                beta=(j-0)/(double)y;
                int newB=(int)((1-alpha-beta)*color1[0]+(alpha+beta)*color2[0]);
                int newG=(int)((1-alpha-beta)*color1[1]+(alpha+beta)*color2[1]);
                int newR=(int)((1-alpha-beta)*color1[2]+(alpha+beta)*color2[2]);

                img.at<cv::Vec3b>(i,j)[0]=newB;
                img.at<cv::Vec3b>(i,j)[1]=newG;
                img.at<cv::Vec3b>(i,j)[2]=newR;
            }
            for (int j = y-1; j >= (int)((x-i)*y/(double)x); j--)//j=(x-i)*y/x
            {
              
                alpha=(x-i)/(double)x;
                beta=(y-j)/(double)y;
                int newB=(int)((1-alpha-beta)*color3[0]+(alpha+beta)*color2[0]);
                int newG=(int)((1-alpha-beta)*color3[1]+(alpha+beta)*color2[1]);
                int newR=(int)((1-alpha-beta)*color3[2]+(alpha+beta)*color2[2]);

                img.at<cv::Vec3b>(i,j)[0]=newB;
                img.at<cv::Vec3b>(i,j)[1]=newG;
                img.at<cv::Vec3b>(i,j)[2]=newR;
            }
        }

        return img;
    }
    //todo:直方图调整（优先度低）
    //todo:高通/低通滤波（优先度低）
    //todo:频谱图输出（优先度低）    
}